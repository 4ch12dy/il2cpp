#include "il2cpp-config.h"
#include "os/Mutex.h"
#include "vm/Class.h"
#include "vm/GenericClass.h"
#include "vm/Image.h"
#include "vm/Type.h"
#include "metadata/GenericMetadata.h"
#include "metadata/GenericMethod.h"
#include "metadata/Il2CppGenericClassHash.h"
#include "metadata/Il2CppGenericClassCompare.h"
#include "metadata/Il2CppGenericInstCompare.h"
#include "metadata/Il2CppGenericInstHash.h"
#include "metadata/Il2CppTypeCompare.h"
#include "metadata/Il2CppTypeHash.h"
#include "utils/Memory.h"
#include "utils/Il2CppHashMap.h"
#include "utils/Il2CppHashSet.h"
#include "utils/StringUtils.h"
#include "vm/MetadataAlloc.h"
#include "vm/MetadataCache.h"
#include "il2cpp-class-internals.h"
#include "il2cpp-tabledefs.h"
#include <vector>

using namespace il2cpp::vm;
using il2cpp::metadata::GenericMethod;
using il2cpp::os::FastAutoLock;
using il2cpp::os::FastMutex;
using il2cpp::utils::StringUtils;

using std::vector;
using std::pair;

namespace il2cpp
{
namespace metadata
{
    ParameterInfo* GenericMetadata::InflateParameters(const ParameterInfo* parameters, uint8_t parameterCount, const Il2CppGenericContext* context, bool inflateMethodVars)
    {
        ParameterInfo* inflatedParameters = (ParameterInfo*)MetadataCalloc(parameterCount, sizeof(ParameterInfo));

        for (uint8_t j = 0; j < parameterCount; j++)
        {
            const ParameterInfo* param = parameters + j;
            ParameterInfo* param2 = inflatedParameters + j;

            param2->name = param->name;
            param2->position = param->position;
            param2->parameter_type = InflateIfNeeded(param->parameter_type, context, inflateMethodVars);
            param2->token = param->token;
        }

        return inflatedParameters;
    }

    const Il2CppType* GenericMetadata::InflateIfNeeded(const Il2CppType* type, const Il2CppGenericContext* context, bool inflateMethodVars)
    {
        switch (type->type)
        {
            case IL2CPP_TYPE_VAR:
            {
                Il2CppType* inflatedType = (Il2CppType*)MetadataMalloc(sizeof(Il2CppType));
                const Il2CppGenericParameter* gp = Type::GetGenericParameter(type);
                IL2CPP_ASSERT(context->class_inst);
                IL2CPP_ASSERT(gp->num < context->class_inst->type_argc);

                memcpy(inflatedType, context->class_inst->type_argv[gp->num], sizeof(Il2CppType));
                inflatedType->byref = type->byref;
                inflatedType->attrs = type->attrs;

                ++il2cpp_runtime_stats.inflated_type_count;

                return inflatedType;
            }
            case IL2CPP_TYPE_MVAR:
            {
                if (context->method_inst)
                {
                    Il2CppType* inflatedType = (Il2CppType*)MetadataMalloc(sizeof(Il2CppType));
                    const Il2CppGenericParameter* gp = Type::GetGenericParameter(type);
                    IL2CPP_ASSERT(gp->num < context->method_inst->type_argc);

                    memcpy(inflatedType, context->method_inst->type_argv[gp->num], sizeof(Il2CppType));
                    inflatedType->byref = type->byref;
                    inflatedType->attrs = type->attrs;

                    ++il2cpp_runtime_stats.inflated_type_count;

                    return inflatedType;
                }
                return type;
            }
            case IL2CPP_TYPE_ARRAY:
            {
                Il2CppType* inflatedType = (Il2CppType*)MetadataMalloc(sizeof(Il2CppType));
                memcpy(inflatedType, type, sizeof(Il2CppType));

                Il2CppArrayType* arrayType = (Il2CppArrayType*)MetadataMalloc(sizeof(Il2CppArrayType));
                memcpy(arrayType, type->data.array, sizeof(Il2CppArrayType));
                arrayType->etype = InflateIfNeeded(type->data.array->etype, context, inflateMethodVars);

                inflatedType->data.array = arrayType;

                ++il2cpp_runtime_stats.inflated_type_count;

                return inflatedType;
            }
            case IL2CPP_TYPE_SZARRAY:
            {
                Il2CppType* arrayType = (Il2CppType*)MetadataMalloc(sizeof(Il2CppType));
                memcpy(arrayType, type, sizeof(Il2CppType));
                arrayType->data.type = InflateIfNeeded(type->data.type, context, inflateMethodVars);

                ++il2cpp_runtime_stats.inflated_type_count;

                return arrayType;
            }
            case IL2CPP_TYPE_GENERICINST:
            {
                Il2CppType* genericType = (Il2CppType*)MetadataMalloc(sizeof(Il2CppType));
                memcpy(genericType, type, sizeof(Il2CppType));

                const Il2CppGenericInst* inst = type->data.generic_class->context.class_inst;

                Il2CppTypeVector types;
                for (uint32_t i = 0; i < inst->type_argc; i++)
                    types.push_back(InflateIfNeeded(inst->type_argv[i], context, inflateMethodVars));

                const Il2CppGenericInst* inflatedInst = MetadataCache::GetGenericInst(types);
                genericType->data.generic_class = GenericMetadata::GetGenericClass(GenericClass::GetTypeDefinition(type->data.generic_class), inflatedInst);

                ++il2cpp_runtime_stats.inflated_type_count;

                return genericType;
            }
            default:
                return type;
        }
    }

    static os::FastMutex s_GenericClassMutex;
    typedef Il2CppHashSet<Il2CppGenericClass*, Il2CppGenericClassHash, Il2CppGenericClassCompare> Il2CppGenericClassSet;
    static Il2CppGenericClassSet s_GenericClassSet;


    Il2CppGenericClass* GenericMetadata::GetGenericClass(Il2CppClass* containerClass, const Il2CppGenericInst* inst)
    {
        return GetGenericClass(MetadataCache::GetIndexForTypeDefinition(containerClass), inst);
    }

    Il2CppGenericClass* GenericMetadata::GetGenericClass(TypeDefinitionIndex elementClassIndex, const Il2CppGenericInst* inst)
    {
        // temporary inst to lookup a permanent one that may already exist
        Il2CppGenericClass genericClass = { 0 };
        genericClass.typeDefinitionIndex = elementClassIndex;
        genericClass.context.class_inst = inst;

        FastAutoLock lock(&s_GenericClassMutex);
        Il2CppGenericClassSet::const_iterator iter = s_GenericClassSet.find(&genericClass);
        if (iter != s_GenericClassSet.end())
            return *iter;

        Il2CppGenericClass* newClass = MetadataAllocGenericClass();
        newClass->typeDefinitionIndex = elementClassIndex;
        newClass->context.class_inst = inst;

        s_GenericClassSet.insert(newClass);

        ++il2cpp_runtime_stats.generic_class_count;

        return newClass;
    }

    const MethodInfo* GenericMetadata::Inflate(const MethodInfo* methodDefinition, Il2CppClass* declaringClass, const Il2CppGenericContext* context)
    {
        const Il2CppGenericMethod* gmethod = MetadataCache::GetGenericMethod(methodDefinition, context->class_inst, context->method_inst);
        return GenericMethod::GetMethod(gmethod);
    }

    static void RecursiveGenericDepthFor(const Il2CppGenericInst* inst, int& depth)
    {
        if (inst == NULL)
            return;

        int maximumDepth = depth;
        for (size_t i = 0; i < inst->type_argc; i++)
        {
            if (inst->type_argv[i]->type == IL2CPP_TYPE_GENERICINST)
            {
                maximumDepth++;

                int classInstDepth = 0;
                RecursiveGenericDepthFor(inst->type_argv[i]->data.generic_class->context.class_inst, classInstDepth);

                int methodInstDepth = 0;
                RecursiveGenericDepthFor(inst->type_argv[i]->data.generic_class->context.method_inst, methodInstDepth);

                maximumDepth += std::max(classInstDepth, methodInstDepth);
            }
        }

        depth = maximumDepth;
    }

    static int RecursiveGenericDepthFor(const Il2CppGenericInst* inst)
    {
        int depth = 0;
        RecursiveGenericDepthFor(inst, depth);
        return depth;
    }

    const Il2CppGenericMethod* GenericMetadata::Inflate(const Il2CppGenericMethod* genericMethod, const Il2CppGenericContext* context)
    {
        const Il2CppGenericInst* classInst = genericMethod->context.class_inst;
        const Il2CppGenericInst* methodInst = genericMethod->context.method_inst;
        if (classInst)
        {
            Il2CppTypeVector classTypes;
            for (size_t i = 0; i < classInst->type_argc; i++)
                classTypes.push_back(GenericMetadata::InflateIfNeeded(classInst->type_argv[i], context, true));
            classInst = MetadataCache::GetGenericInst(classTypes);
        }

        if (methodInst)
        {
            Il2CppTypeVector methodTypes;
            for (size_t i = 0; i < methodInst->type_argc; i++)
                methodTypes.push_back(GenericMetadata::InflateIfNeeded(methodInst->type_argv[i], context, true));
            methodInst = MetadataCache::GetGenericInst(methodTypes);
        }

        // We have cases where we could infinitely recurse, inflating generics at runtime. This will lead to a stack overflow.
        // As we do for code generation, let's cut this off at an arbitrary level. If something tries to execute code at this
        // level, a crash will happen. We'll assume that this code won't actually be executed though.
        if (RecursiveGenericDepthFor(classInst) > MaximumRuntimeGenericDepth || RecursiveGenericDepthFor(methodInst) > MaximumRuntimeGenericDepth)
            return NULL;

        return MetadataCache::GetGenericMethod(genericMethod->methodDefinition, classInst, methodInst);
    }

    Il2CppRGCTXData* GenericMetadata::InflateRGCTX(RGCTXIndex rgctxStartIndex, int16_t rgctxCount, const Il2CppGenericContext* context)
    {
        if (rgctxStartIndex == kRGCTXIndexInvalid)
            return NULL;

        Il2CppRGCTXData* dataValues = (Il2CppRGCTXData*)MetadataCalloc(rgctxCount, sizeof(Il2CppRGCTXData));
        for (RGCTXIndex rgctxIndex = 0; rgctxIndex < rgctxCount; rgctxIndex++)
        {
            const Il2CppRGCTXDefinition* definitionData = MetadataCache::GetRGCTXDefinitionFromIndex(rgctxStartIndex + rgctxIndex);
            switch (definitionData->type)
            {
                case IL2CPP_RGCTX_DATA_TYPE:
                    dataValues[rgctxIndex].type = GenericMetadata::InflateIfNeeded(MetadataCache::GetIl2CppTypeFromIndex(definitionData->data.typeIndex), context, true);
                    break;
                case IL2CPP_RGCTX_DATA_CLASS:
                    dataValues[rgctxIndex].klass = Class::FromIl2CppType(GenericMetadata::InflateIfNeeded(MetadataCache::GetIl2CppTypeFromIndex(definitionData->data.typeIndex), context, true));
                    break;
                case IL2CPP_RGCTX_DATA_METHOD:
                    dataValues[rgctxIndex].method = GenericMethod::GetMethod(Inflate(MetadataCache::GetGenericMethodFromIndex(definitionData->data.methodIndex), context));
                    break;
                default:
                    IL2CPP_ASSERT(0);
            }
        }

        return dataValues;
    }

// temporary while we generate generics
    void GenericMetadata::RegisterGenericClass(Il2CppGenericClass *gclass)
    {
        // don't lock, this should only be called from startup and temporarily
        s_GenericClassSet.insert(gclass);
    }

    void GenericMetadata::WalkAllGenericClasses(GenericClassWalkCallback callback, void* context)
    {
        FastAutoLock lock(&s_GenericClassMutex);

        for (Il2CppGenericClassSet::iterator it = s_GenericClassSet.begin(); it != s_GenericClassSet.end(); it++)
        {
            if ((*it).key->cached_class != NULL)
                callback((*it).key->cached_class, context);
        }
    }
} /* namespace vm */
} /* namespace il2cpp */
