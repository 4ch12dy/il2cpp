#pragma once

#include <stdint.h>
#include "il2cpp-config.h"

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
    class LIBIL2CPP_CODEGEN_API DateTime
    {
    public:
        static int64_t GetNow(void);
        static int64_t GetTimeMonotonic();
#if NET_4_0
        static int64_t GetSystemTimeAsFileTime();
#endif
    };
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
