#include "il2cpp-config.h"
#include "metadata/GenericMetadata.h"
#include "os/Mutex.h"
#include "utils/Memory.h"
#include "vm/Class.h"
#include "vm/GenericClass.h"
#include "vm/Exception.h"
#include "vm/MetadataAlloc.h"
#include "vm/MetadataCache.h"
#include "vm/MetadataLock.h"
#include "il2cpp-class-internals.h"
#include "il2cpp-runtime-metadata.h"

using il2cpp::metadata::GenericMetadata;
using il2cpp::os::FastAutoLock;

namespace il2cpp
{
namespace vm
{
    void GenericClass::SetupMethods(Il2CppClass* genericInstanceType)
    {
        Il2CppClass* genericTypeDefinition = GenericClass::GetTypeDefinition(genericInstanceType->generic_class);
        uint16_t methodCount = genericTypeDefinition->method_count;
        IL2CPP_ASSERT(genericTypeDefinition->method_count == genericInstanceType->method_count);

        if (methodCount == 0)
        {
            genericInstanceType->methods = NULL;
            return;
        }

        const MethodInfo** methods = (const MethodInfo**)MetadataCalloc(methodCount, sizeof(MethodInfo*));

        for (uint16_t methodIndex = 0; methodIndex < methodCount; ++methodIndex)
        {
            const MethodInfo* methodDefinition = genericTypeDefinition->methods[methodIndex];
            methods[methodIndex] = GenericMetadata::Inflate(methodDefinition, genericInstanceType, GenericClass::GetContext(genericInstanceType->generic_class));
        }

        genericInstanceType->methods = methods;

        il2cpp_runtime_stats.method_count += methodCount;
    }

    static void InflatePropertyDefinition(const PropertyInfo* propertyDefinition, PropertyInfo* newProperty, Il2CppClass* declaringClass, Il2CppGenericContext* context)
    {
        newProperty->attrs = propertyDefinition->attrs;
        newProperty->parent = declaringClass;
        newProperty->name = propertyDefinition->name;
        newProperty->token = propertyDefinition->token;

        if (propertyDefinition->get)
            newProperty->get = GenericMetadata::Inflate(propertyDefinition->get, declaringClass, context);
        if (propertyDefinition->set)
            newProperty->set = GenericMetadata::Inflate(propertyDefinition->set, declaringClass, context);
    }

    void GenericClass::SetupProperties(Il2CppClass* genericInstanceType)
    {
        Il2CppClass* genericTypeDefinition = GenericClass::GetTypeDefinition(genericInstanceType->generic_class);
        uint16_t propertyCount = genericTypeDefinition->property_count;
        IL2CPP_ASSERT(genericTypeDefinition->property_count == genericInstanceType->property_count);

        if (propertyCount == 0)
        {
            genericInstanceType->properties = NULL;
            return;
        }

        PropertyInfo* properties = (PropertyInfo*)MetadataCalloc(propertyCount, sizeof(PropertyInfo));
        PropertyInfo* property = properties;

        for (uint16_t propertyIndex = 0; propertyIndex < propertyCount; ++propertyIndex)
        {
            InflatePropertyDefinition(genericTypeDefinition->properties + propertyIndex, property, genericInstanceType, GenericClass::GetContext(genericInstanceType->generic_class));
            property++;
        }

        genericInstanceType->properties = properties;
    }

    static void InflateEventDefinition(const EventInfo* eventDefinition, EventInfo* newEvent, Il2CppClass* declaringClass, Il2CppGenericContext* context)
    {
        newEvent->eventType = GenericMetadata::InflateIfNeeded(eventDefinition->eventType, context, false);
        newEvent->name = eventDefinition->name;
        newEvent->parent = declaringClass;
        newEvent->token = eventDefinition->token;

        if (eventDefinition->add)
            newEvent->add = GenericMetadata::Inflate(eventDefinition->add, declaringClass, context);
        if (eventDefinition->raise)
            newEvent->raise = GenericMetadata::Inflate(eventDefinition->raise, declaringClass, context);
        if (eventDefinition->remove)
            newEvent->remove = GenericMetadata::Inflate(eventDefinition->remove, declaringClass, context);
    }

    void GenericClass::SetupEvents(Il2CppClass* genericInstanceType)
    {
        Il2CppClass* genericTypeDefinition = GenericClass::GetTypeDefinition(genericInstanceType->generic_class);
        uint16_t eventCount = genericTypeDefinition->event_count;
        IL2CPP_ASSERT(genericTypeDefinition->event_count == genericInstanceType->event_count);

        if (eventCount == 0)
        {
            genericInstanceType->events = NULL;
            return;
        }

        EventInfo* events = (EventInfo*)MetadataCalloc(eventCount, sizeof(EventInfo));
        EventInfo* event = events;

        for (uint16_t eventIndex = 0; eventIndex < eventCount; ++eventIndex)
        {
            InflateEventDefinition(genericTypeDefinition->events + eventIndex, event, genericInstanceType, GenericClass::GetContext(genericInstanceType->generic_class));
            event++;
        }

        genericInstanceType->events = events;
    }

    static FieldInfo* InflateFieldDefinition(const FieldInfo* fieldDefinition, FieldInfo* newField, Il2CppClass* declaringClass, Il2CppGenericContext* context)
    {
        newField->type = GenericMetadata::InflateIfNeeded(fieldDefinition->type, context, false);
        newField->name = fieldDefinition->name;
        newField->parent = declaringClass;
        newField->offset = fieldDefinition->offset;
        newField->token = fieldDefinition->token;

        return newField;
    }

    void GenericClass::SetupFields(Il2CppClass* genericInstanceType)
    {
        Il2CppClass* genericTypeDefinition = GenericClass::GetTypeDefinition(genericInstanceType->generic_class);
        uint16_t fieldCount = genericTypeDefinition->field_count;
        IL2CPP_ASSERT(genericTypeDefinition->field_count == genericInstanceType->field_count);

        if (fieldCount == 0)
        {
            genericInstanceType->fields = NULL;
            return;
        }

        FieldInfo* fields = (FieldInfo*)MetadataCalloc(fieldCount, sizeof(FieldInfo));
        FieldInfo* field = fields;

        for (uint16_t fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
        {
            InflateFieldDefinition(genericTypeDefinition->fields + fieldIndex, field, genericInstanceType, GenericClass::GetContext(genericInstanceType->generic_class));
            field++;
        }

        genericInstanceType->fields = fields;
    }

    Il2CppClass* GenericClass::GetClass(Il2CppGenericClass *gclass)
    {
        FastAutoLock lock(&g_MetadataLock);
        Il2CppClass* definition = GetTypeDefinition(gclass);
        if (definition == NULL)
            vm::Exception::Raise(vm::Exception::GetMaxmimumNestedGenericsException());

        if (!gclass->cached_class)
        {
            Il2CppClass* klass = gclass->cached_class = (Il2CppClass*)MetadataCalloc(1, sizeof(Il2CppClass) + (sizeof(VirtualInvokeData) * definition->vtable_count));
            klass->klass = klass;

            klass->name = definition->name;
            klass->namespaze = definition->namespaze;

            klass->image = definition->image;
            klass->flags = definition->flags;
            //klass->type_token = definition->type_token;
            klass->generic_class = gclass;

            Il2CppClass* genericTypeDefinition = GenericClass::GetTypeDefinition(klass->generic_class);
            Il2CppGenericContext* context = &klass->generic_class->context;

            if (genericTypeDefinition->parent)
                klass->parent = Class::FromIl2CppType(GenericMetadata::InflateIfNeeded(&genericTypeDefinition->parent->byval_arg, context, false));

            if (genericTypeDefinition->declaringType)
                klass->declaringType = Class::FromIl2CppType(GenericMetadata::InflateIfNeeded(&genericTypeDefinition->declaringType->byval_arg, context, false));

            klass->this_arg.type = klass->byval_arg.type = IL2CPP_TYPE_GENERICINST;
            klass->this_arg.data.generic_class = klass->byval_arg.data.generic_class = gclass;
            klass->this_arg.byref = true;

            klass->event_count = definition->event_count;
            klass->field_count = definition->field_count;
            klass->interfaces_count = definition->interfaces_count;
            klass->method_count = definition->method_count;
            klass->property_count = definition->property_count;

            klass->enumtype = definition->enumtype;
            klass->valuetype = definition->valuetype;
            klass->element_class = klass->castClass = klass;

            klass->has_cctor = definition->has_cctor;
            klass->has_finalize = definition->has_finalize;
            klass->native_size = klass->thread_static_fields_offset = -1;
            klass->token = definition->token;
            klass->interopData = MetadataCache::GetInteropDataForType(&klass->byval_arg);

            if (Class::IsNullable(klass))
                klass->element_class = klass->castClass  = Class::GetNullableArgument(klass);

            if (klass->enumtype)
                klass->element_class = klass->castClass =  definition->element_class;

            klass->is_import_or_windows_runtime = definition->is_import_or_windows_runtime;
        }

        return gclass->cached_class;
    }

    Il2CppGenericContext* GenericClass::GetContext(Il2CppGenericClass *gclass)
    {
        return &gclass->context;
    }

    Il2CppClass* GenericClass::GetTypeDefinition(Il2CppGenericClass *gclass)
    {
        return MetadataCache::GetTypeInfoFromTypeDefinitionIndex(gclass->typeDefinitionIndex);
    }

    bool GenericClass::IsEnum(Il2CppGenericClass *gclass)
    {
        return IsValueType(gclass) && GetTypeDefinition(gclass)->enumtype;
    }

    bool GenericClass::IsValueType(Il2CppGenericClass *gclass)
    {
        return GetTypeDefinition(gclass)->valuetype;
    }
} /* namespace vm */
} /* namespace il2cpp */
