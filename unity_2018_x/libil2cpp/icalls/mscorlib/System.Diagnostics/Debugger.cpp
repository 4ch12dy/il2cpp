#include "il2cpp-config.h"

#include "icalls/mscorlib/System.Diagnostics/Debugger.h"
#include "vm-utils/Debugger.h"

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
namespace Diagnostics
{
// Until we have il2cpp debugger, return whether a native debugger is attached
    bool Debugger::IsAttached_internal()
    {
        return utils::Debugger::GetIsDebuggerAttached();
    }

#if NET_4_0
    bool Debugger::IsLogging()
    {
#if IL2CPP_MONO_DEBUGGER
        return utils::Debugger::IsLoggingEnabled();
#else
        return false;
#endif
    }

    void Debugger::Log(int32_t level, Il2CppString* category, Il2CppString* message)
    {
#if IL2CPP_MONO_DEBUGGER
        utils::Debugger::Log(level, category, message);
#endif
    }

#endif
} /* namespace Diagnostics */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
