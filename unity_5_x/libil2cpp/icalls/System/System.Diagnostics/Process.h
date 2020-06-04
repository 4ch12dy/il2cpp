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
namespace System
{
namespace System
{
namespace Diagnostics
{
    struct ProcInfo;

    class LIBIL2CPP_CODEGEN_API Process
    {
    public:
        static Il2CppArray* GetProcesses_internal();
        static int32_t GetPid_internal();
        static bool CreateProcess_internal(void* /* System.Diagnostics.ProcessStartInfo */ startInfo, Il2CppIntPtr _stdin, Il2CppIntPtr _stdout, Il2CppIntPtr _stderr, ProcInfo* proc_info);
        static int64_t ExitTime_internal(Il2CppIntPtr handle);
        static Il2CppArray* GetModules_internal(void* /* System.Diagnostics.Process */ self, Il2CppIntPtr handle);
        static int32_t GetPriorityClass(Il2CppIntPtr handle, int32_t* error);
        static int64_t GetProcessData(int32_t pid, int32_t data_type, int32_t* error);
        static Il2CppIntPtr GetProcess_internal(int32_t pid);
        static bool GetWorkingSet_internal(Il2CppIntPtr handle, int32_t* min, int32_t* max);
        static bool Kill_internal(Il2CppIntPtr handle, int32_t signo);
        static Il2CppString* ProcessName_internal(Il2CppIntPtr handle);
        static void Process_free_internal(void* /* System.Diagnostics.Process */ self, Il2CppIntPtr handle);
        static bool SetPriorityClass(Il2CppIntPtr handle, int32_t priority, int32_t* error);
        static bool SetWorkingSet_internal(Il2CppIntPtr handle, int32_t min, int32_t max, bool use_min);
        static bool ShellExecuteEx_internal(void* /* System.Diagnostics.ProcessStartInfo */ startInfo, ProcInfo* proc_info);
        static int64_t StartTime_internal(Il2CppIntPtr handle);
        static int64_t Times(Il2CppIntPtr handle, int32_t type);
        static bool WaitForExit_internal(void* /* System.Diagnostics.Process */ self, Il2CppIntPtr handle, int32_t ms);
        static bool WaitForInputIdle_internal(void* /* System.Diagnostics.Process */ self, Il2CppIntPtr handle, int32_t ms);
        static int32_t ExitCode_internal(Il2CppIntPtr handle);
    };
} /* namespace Diagnostics */
} /* namespace System */
} /* namespace System */
} /* namespace icalls */
} /* namespace il2cpp */
