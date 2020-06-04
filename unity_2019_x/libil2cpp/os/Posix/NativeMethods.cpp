#include "il2cpp-config.h"

#if IL2CPP_TARGET_POSIX && !IL2CPP_TINY_WITHOUT_DEBUGGER

#include "os/NativeMethods.h"
#include "os/Process.h"

namespace il2cpp
{
namespace os
{
    bool NativeMethods::CloseProcess(ProcessHandle* handle)
    {
        IL2CPP_NOT_IMPLEMENTED_ICALL(NativeMethods::CloseProcess);
        IL2CPP_UNREACHABLE;
        return false;
    }

    bool NativeMethods::GetExitCodeProcess(ProcessHandle* handle, int32_t* exitCode)
    {
        IL2CPP_NOT_IMPLEMENTED_ICALL(NativeMethods::GetExitCodeProcess);
        IL2CPP_UNREACHABLE;
        return false;
    }

    int32_t NativeMethods::GetCurrentProcessId()
    {
        return Process::GetCurrentProcessId();
    }

    ProcessHandle* NativeMethods::GetCurrentProcess()
    {
        return Process::GetProcess(Process::GetCurrentProcessId());
    }
}
}
#endif
