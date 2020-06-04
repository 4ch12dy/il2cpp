#pragma once

#include <stdint.h>
#include "il2cpp-config.h"
#include "object-internals.h"

struct Il2CppObject;
struct Il2CppDelegate;
struct Il2CppReflectionType;
struct Il2CppReflectionMethod;
struct Il2CppReflectionField;
struct Il2CppArray;
struct Il2CppException;
struct Il2CppReflectionModule;
struct Il2CppAssembly;
struct Il2CppAssemblyName;
struct Il2CppAppDomain;

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
namespace Reflection
{
    class LIBIL2CPP_CODEGEN_API ParameterInfo
    {
    public:
        static Il2CppArray* GetTypeModifiers(void* /* System.Reflection.ParameterInfo */ self, bool optional);
        static int32_t GetMetadataToken(Il2CppReflectionParameter* self);
    };
} /* namespace Reflection */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
