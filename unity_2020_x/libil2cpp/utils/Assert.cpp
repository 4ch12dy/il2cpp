#include "Assert.h"

#if IL2CPP_DEBUG

#if IL2CPP_TARGET_WINDOWS || IL2CPP_TARGET_XBOXONE || IL2CPP_TARGET_WINRT
#include <crtdbg.h>
#else
#include <cstdio>
#include <cstdlib>
#endif

void il2cpp_assert(const char* assertion, const char* file, unsigned int line)
{
#if IL2CPP_TARGET_WINDOWS || IL2CPP_TARGET_XBOXONE || IL2CPP_TARGET_WINRT

    if (_CrtDbgReport(_CRT_ASSERT, file, line, "", "%s", assertion) != 1)
    {
        _CrtDbgBreak();
    }
#else
    printf("Assertion failed: %s, file %s, line %u", assertion, file, line);
    abort();
#endif
}

#endif
