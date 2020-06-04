#include "il2cpp-config.h"
#include <vector>
#include <algorithm>
#include "icalls/mscorlib/System.Threading/WaitHandle.h"
#include "os/Mutex.h"
#include "os/Thread.h"
#include "vm/Thread.h"
#include "vm/Exception.h"
#include "vm/Array.h"
#include "vm/WaitHandle.h"

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
    std::vector<os::Handle*> ExtractOsWaitHandles(Il2CppArray* handles)
    {
        uint32_t numberOfHandles = vm::Array::GetLength(handles);

        std::vector<os::Handle*> osWaitHandles(numberOfHandles);

        for (uint32_t i = 0; i < numberOfHandles; ++i)
        {
            Il2CppObject* handle = il2cpp_array_get(handles, Il2CppObject*, i);
            Il2CppWaitHandle* waitHandle = (Il2CppWaitHandle*)handle;
            osWaitHandles[i] = vm::WaitHandle::GetPlatformHandle(waitHandle);
        }

        return osWaitHandles;
    }

    int32_t WaitHandle::WaitAny_internal(Il2CppArray* handles, int32_t ms, bool exitContext)
    {
        std::vector<os::Handle*> osWaitHandles = ExtractOsWaitHandles(handles);

        vm::ThreadStateSetter state(vm::kThreadStateWaitSleepJoin);

        return os::Handle::WaitAny(osWaitHandles, ms);
    }

    bool WaitHandle::WaitOne_internal(Il2CppObject* unused, intptr_t handlePtr, int32_t ms, bool exitContext)
    {
        il2cpp::os::Handle* handle = (il2cpp::os::Handle*)handlePtr;

        vm::ThreadStateSetter state(vm::kThreadStateWaitSleepJoin);

        // Check for pending interrupt before we go waiting.
        il2cpp::vm::Thread::CheckCurrentThreadForInterruptAndThrowIfNecessary();

        if (ms == -1)
            return handle->Wait();

        return handle->Wait((uint32_t)ms);
    }

    bool WaitHandle::WaitAll_internal(Il2CppArray* handles, int32_t ms, bool exitContext)
    {
        std::vector<os::Handle*> osWaitHandles = ExtractOsWaitHandles(handles);

        vm::ThreadStateSetter state(vm::kThreadStateWaitSleepJoin);

        return os::Handle::WaitAll(osWaitHandles, ms);
    }

    bool WaitHandle::SignalAndWait_Internal(intptr_t toSignal, intptr_t toWaitOn, int32_t ms, bool exitContext)
    {
        os::Handle* toSignalOsHandle = (os::Handle*)toSignal;
        toSignalOsHandle->Signal();

        return WaitOne_internal(NULL, toWaitOn, ms, exitContext);
    }

#if NET_4_0
    int32_t WaitHandle::SignalAndWait_Internal40(intptr_t toSignal, intptr_t toWaitOn, int32_t ms)
    {
        return SignalAndWait_Internal(toSignal, toWaitOn, ms, false) ? 0 : 1;
    }

    int32_t WaitHandle::WaitAll_internal40(Il2CppArray* handles, int32_t ms)
    {
        return WaitAll_internal(handles, ms, false) ? 0 : 258;
    }

    int32_t WaitHandle::WaitAny_internal40(Il2CppArray* handles, int32_t ms)
    {
        return WaitAny_internal(handles, ms, false);
    }

    int32_t WaitHandle::WaitOne_internal40(intptr_t handle, int32_t ms)
    {
        return WaitOne_internal(NULL, handle, ms, false) ? 0 : 258;
    }

#endif
} /* namespace Threading */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
