#include "Thread-c-api.h"
#include "os/Thread.h"

void UnityPalThreadInitialize()
{
    il2cpp::os::Thread::Init();
}

void UnityPalSleep(uint32_t milliseconds)
{
    il2cpp::os::Thread::Sleep(milliseconds, false);
}
