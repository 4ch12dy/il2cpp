#pragma once

#include <stdint.h>
#include "il2cpp-config.h"
#include "blob.h"
#include "class-internals.h"
#include "metadata/Il2CppTypeVector.h"
#include "utils/dynamic_array.h"
#include "class-internals.h"
#include "object-internals.h"
#include "Exception.h"
#include "Type.h"

#if NET_4_0
#include "vm/MetadataCache.h"
#include "tabledefs.h"
#endif


struct Il2CppClass;
struct EventInfo;
struct FieldInfo;
struct PropertyInfo;
struct MethodInfo;

struct Il2CppImage;
struct Il2CppReflectionType;
struct Il2CppType;
struct Il2CppDebugTypeInfo;
struct Il2CppGenericContainer;
struct Il2CppGenericContext;
struct Il2CppGenericParameter;

namespace il2cpp
{
namespace vm
{
    class TypeNameParseInfo;

    class LIBIL2CPP_CODEGEN_API Class
    {
    public:
        static Il2CppClass* FromIl2CppType(const Il2CppType* type);
        static Il2CppClass* FromName(const Il2CppImage* image, const char* namespaze, const char *name);
        static Il2CppClass* FromSystemType(Il2CppReflectionType *type);
        static Il2CppClass* FromGenericParameter(const Il2CppGenericParameter *param);
        static Il2CppClass* GetElementClass(Il2CppClass *klass);
        static const Il2CppType* GetEnumBaseType(Il2CppClass *klass);
        static const EventInfo* GetEvents(Il2CppClass *klass, void* *iter);
        static FieldInfo* GetFields(Il2CppClass *klass, void* *iter);
        static FieldInfo* GetFieldFromName(Il2CppClass *klass, const char* name);
        static const MethodInfo* GetFinalizer(Il2CppClass *klass);
        static int32_t GetInstanceSize(const Il2CppClass *klass);
        static Il2CppClass* GetInterfaces(Il2CppClass *klass, void* *iter);
        static const MethodInfo* GetMethods(Il2CppClass *klass, void* *iter);
        static const MethodInfo* GetMethodFromName(Il2CppClass *klass, const char* name, int argsCount);
        static const MethodInfo* GetMethodFromNameFlags(Il2CppClass *klass, const char* name, int argsCount, int32_t flags);
        static const char* GetName(Il2CppClass *klass);
        static const char* GetNamespace(Il2CppClass *klass);
        static Il2CppClass* GetNestedTypes(Il2CppClass *klass, void* *iter);
        static size_t GetNumMethods(const Il2CppClass* klass);
        static size_t GetNumProperties(const Il2CppClass* klass);
        static size_t GetNumFields(const Il2CppClass* klass);
        static Il2CppClass* GetParent(Il2CppClass *klass);
        static const PropertyInfo* GetProperties(Il2CppClass *klass, void* *iter);
        static const PropertyInfo* GetPropertyFromName(Il2CppClass *klass, const char* name);
        static int32_t GetValueSize(Il2CppClass *klass, uint32_t *align);
        static bool HasParent(Il2CppClass *klass, Il2CppClass *parent);
        // we assume that the Il2CppClass's have already been initialized in this case, like in code generation
        static bool HasParentUnsafe(const Il2CppClass* klass, const Il2CppClass* parent) { return klass->typeHierarchyDepth >= parent->typeHierarchyDepth && klass->typeHierarchy[parent->typeHierarchyDepth - 1] == parent; }
        static bool IsAssignableFrom(Il2CppClass *klass, Il2CppClass *oklass);
        static bool IsGeneric(const Il2CppClass *klass);
        static bool IsInflated(const Il2CppClass *klass);
        static bool IsSubclassOf(Il2CppClass *klass, Il2CppClass *klassc, bool check_interfaces);
        static bool IsValuetype(const Il2CppClass *klass);
        static bool HasDefaultConstructor(Il2CppClass* klass);
        static int GetFlags(const Il2CppClass *klass);
        static bool IsAbstract(const Il2CppClass *klass);
        static bool IsInterface(const Il2CppClass *klass);
        static bool IsNullable(const Il2CppClass *klass);
        static Il2CppClass* GetNullableArgument(const Il2CppClass* klass);
        static int GetArrayElementSize(const Il2CppClass *klass);
        static const Il2CppType* GetType(Il2CppClass *klass);
        static const Il2CppType* GetType(Il2CppClass *klass, const TypeNameParseInfo &info);
        static bool HasAttribute(Il2CppClass *klass, Il2CppClass *attr_class);
        static bool IsEnum(const Il2CppClass *klass);
        static const Il2CppImage* GetImage(Il2CppClass* klass);
        static const Il2CppDebugTypeInfo *GetDebugInfo(const Il2CppClass *klass);
        static const char *GetAssemblyName(const Il2CppClass *klass);

    public:
        //internal
        static FORCE_INLINE const VirtualInvokeData& GetInterfaceInvokeDataFromVTable(const Il2CppObject* obj, const Il2CppClass* itf, Il2CppMethodSlot slot)
        {
            const Il2CppClass* klass = obj->klass;
            IL2CPP_ASSERT(klass->initialized);
            IL2CPP_ASSERT(slot < itf->method_count);

            for (uint16_t i = 0; i < klass->interface_offsets_count; i++)
            {
                if (klass->interfaceOffsets[i].interfaceType == itf)
                {
                    int32_t offset = klass->interfaceOffsets[i].offset;
                    IL2CPP_ASSERT(offset != -1);
                    IL2CPP_ASSERT(offset + slot < klass->vtable_count);
                    return klass->vtable[offset + slot];
                }
            }

            return GetInterfaceInvokeDataFromVTableSlowPath(obj, itf, slot);
        }

        static bool Init(Il2CppClass *klass);

        static Il2CppClass* GetArrayClass(Il2CppClass *element_class, uint32_t rank);
        static Il2CppClass* GetBoundedArrayClass(Il2CppClass *element_class, uint32_t rank, bool bounded);
        static Il2CppClass* GetInflatedGenericInstanceClass(Il2CppClass* klass, const metadata::Il2CppTypeVector& types);
        static Il2CppClass* GetInflatedGenericInstanceClass(Il2CppClass* klass, const Il2CppGenericInst* genericInst);
        static Il2CppClass* InflateGenericClass(Il2CppClass* klass, Il2CppGenericContext *context);
        static const Il2CppType* InflateGenericType(const Il2CppType* type, Il2CppGenericContext *context);

        static Il2CppClass* GetArrayClassCached(Il2CppClass *element_class, uint32_t rank)
        {
            return GetArrayClass(element_class, rank);
        }

        static const Il2CppGenericContainer* GetGenericContainer(Il2CppClass *klass);
        static const MethodInfo* GetCCtor(Il2CppClass *klass);
        static const char* GetFieldDefaultValue(const FieldInfo *field, const Il2CppType** type);
        static int GetFieldMarshaledSize(const FieldInfo *field);
        static Il2CppClass* GetPtrClass(const Il2CppType* type);
        static Il2CppClass* GetPtrClass(Il2CppClass* elementClass);
        static bool HasReferences(Il2CppClass *klass);
        static void SetupEvents(Il2CppClass *klass);
        static void SetupFields(Il2CppClass *klass);
        static void SetupMethods(Il2CppClass *klass);
        static void SetupNestedTypes(Il2CppClass *klass);
        static void SetupProperties(Il2CppClass *klass);
        static void SetupTypeHierarchy(Il2CppClass *klass);
        static void SetupInterfaces(Il2CppClass *klass);

        static const dynamic_array<Il2CppClass*>& GetStaticFieldData();

        static size_t GetBitmapSize(const Il2CppClass* klass);
        static void GetBitmap(Il2CppClass* klass, size_t* bitmap, size_t& maxSetBit);

        static const Il2CppType* il2cpp_type_from_type_info(const TypeNameParseInfo& info, bool throwOnError, bool ignoreCase);

        static Il2CppClass* GetDeclaringType(Il2CppClass* klass);
    private:
#if NET_4_0
        static FORCE_INLINE bool IsGenericClassAssignableFrom(const Il2CppClass* klass, const Il2CppClass* oklass, const Il2CppGenericContainer* genericContainer)
        {
            const Il2CppGenericClass* genericClass = klass->generic_class;
            const Il2CppGenericClass* oGenericClass = oklass->generic_class;

            if (oGenericClass == NULL || oGenericClass->typeDefinitionIndex != genericClass->typeDefinitionIndex)
                return false;

            const int32_t genericParameterCount = genericContainer->type_argc;

            const Il2CppGenericInst* genericInst = genericClass->context.class_inst;
            IL2CPP_ASSERT(genericInst->type_argc == genericParameterCount);

            const Il2CppGenericInst* oGenericInst = oGenericClass->context.class_inst;
            IL2CPP_ASSERT(oGenericInst->type_argc == genericParameterCount);

            for (int32_t i = 0; i < genericParameterCount; ++i)
            {
                const Il2CppGenericParameter* genericParameter = MetadataCache::GetGenericParameterFromIndex(genericContainer->genericParameterStart + i);
                const int32_t parameterVariance = genericParameter->flags & GENERIC_PARAMETER_ATTRIBUTE_VARIANCE_MASK;
                Il2CppClass* genericParameterType = Class::FromIl2CppType(genericInst->type_argv[i]);
                Il2CppClass* oGenericParameterType = Class::FromIl2CppType(oGenericInst->type_argv[i]);

                if (parameterVariance == GENERIC_PARAMETER_ATTRIBUTE_NON_VARIANT || Class::IsValuetype(genericParameterType) || Class::IsValuetype(oGenericParameterType))
                {
                    if (genericParameterType != oGenericParameterType)
                        return false;
                }
                else if (parameterVariance == GENERIC_PARAMETER_ATTRIBUTE_COVARIANT)
                {
                    if (!Class::IsAssignableFrom(genericParameterType, oGenericParameterType))
                        return false;
                }
                else
                {
                    IL2CPP_ASSERT(parameterVariance == GENERIC_PARAMETER_ATTRIBUTE_CONTRAVARIANT);
                    if (!Class::IsAssignableFrom(oGenericParameterType, genericParameterType))
                        return false;
                }
            }

            return true;
        }

#endif

        // we don't want this method to get inlined because that makes GetInterfaceInvokeDataFromVTable method itself very large and performance suffers
        static IL2CPP_NO_INLINE const VirtualInvokeData& GetInterfaceInvokeDataFromVTableSlowPath(const Il2CppObject* obj, const Il2CppClass* itf, Il2CppMethodSlot slot);
    };
} /* namespace vm */
} /* namespace il2cpp */
