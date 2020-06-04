#pragma once

#include <stdint.h>
#include "il2cpp-config.h"
#include "object-internals.h"

struct mscorlib_Mono_Interop_ComInteropProxy;

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace Mono
{
namespace Interop
{
    class LIBIL2CPP_CODEGEN_API ComInteropProxy
    {
    public:
        static void AddProxy(Il2CppIntPtr pItf, mscorlib_Mono_Interop_ComInteropProxy * proxy);
        static mscorlib_Mono_Interop_ComInteropProxy* FindProxy(Il2CppIntPtr pItf);
    };
} /* namespace Interop */
} /* namespace Mono */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
