#include "os/c-api/il2cpp-config-platforms.h"

#if !IL2CPP_TINY_WITHOUT_DEBUGGER

#include "os/Process.h"
#include "os/c-api/Process-c-api.h"
#include "Allocator.h"

#include <string>

extern "C"
{
    int UnityPalGetCurrentProcessId()
    {
        return il2cpp::os::Process::GetCurrentProcessId();
    }

    UnityPalProcessHandle* UnityPalGetProcess(int processId)
    {
        return il2cpp::os::Process::GetProcess(processId);
    }

    void UnityPalFreeProcess(UnityPalProcessHandle* handle)
    {
        return il2cpp::os::Process::FreeProcess(handle);
    }

    const char* UnityPalGetProcessName(UnityPalProcessHandle* handle)
    {
        return Allocator::CopyToAllocatedStringBuffer(il2cpp::os::Process::GetProcessName(handle));
    }
}

#endif
