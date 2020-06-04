#pragma once

#include <stdint.h>
#include "object-internals.h"
#include "il2cpp-config.h"

struct Il2CppArray;
struct Il2CppObject;

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
namespace Threading
{
    class LIBIL2CPP_CODEGEN_API WaitHandle
    {
    public:
        static bool SignalAndWait_Internal(Il2CppIntPtr toSignal, Il2CppIntPtr toWaitOn, int32_t ms, bool exitContext);
        static bool WaitAll_internal(Il2CppArray* handles, int32_t ms, bool exitContext);
        static int32_t WaitAny_internal(Il2CppArray* handles, int32_t ms, bool exitContext);
        static bool WaitOne_internal(Il2CppObject* unused, Il2CppIntPtr handlePtr, int32_t ms, bool exitContext);
#if NET_4_0
        static int32_t SignalAndWait_Internal40(Il2CppIntPtr toSignal, Il2CppIntPtr toWaitOn, int32_t ms);
        static int32_t WaitAll_internal40(Il2CppArray* handles, int32_t ms);
        static int32_t WaitAny_internal40(Il2CppArray* handles, int32_t ms);
        static int32_t WaitOne_internal40(Il2CppIntPtr handle, int32_t ms);
#endif

    private:
        static const int m_waitIntervalMs = 10;
    };
} /* namespace Threading */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
