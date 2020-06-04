#pragma once

#if IL2CPP_TARGET_WINDOWS

#include "os/Win32/WindowsHeaders.h"
#include "c-api/Atomic-c-api.h"

namespace il2cpp
{
namespace os
{
    inline void Atomic::FullMemoryBarrier()
    {
#if defined(_AMD64_)
        ::__faststorefence();
#elif defined(_M_IX86)
        ::MemoryBarrier();
#elif defined(_M_ARM)
        __dmb(_ARM_BARRIER_SY);
#else
#error Not implemented;
#endif
    }
}
}

#endif
