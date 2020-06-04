#pragma once

#include "il2cpp-config.h"
#include "il2cpp-class-internals.h"

namespace il2cpp
{
namespace utils
{
    class MarshalingUtils
    {
    public:
        static void MarshalStructToNative(void* managedStructure, void* marshaledStructure, const Il2CppInteropData* interopData);
        static void MarshalStructFromNative(void* marshaledStructure, void* managedStructure, const Il2CppInteropData* interopData);
        static bool MarshalFreeStruct(void* marshaledStructure, const Il2CppInteropData* interopData);
    };
} // namespace utils
} // namespace il2cpp
