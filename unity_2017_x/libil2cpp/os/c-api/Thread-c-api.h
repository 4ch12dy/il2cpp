#pragma once

#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif

void UnityPalThreadInitialize();
void UnityPalSleep(uint32_t milliseconds);

#if defined(__cplusplus)
}
#endif
