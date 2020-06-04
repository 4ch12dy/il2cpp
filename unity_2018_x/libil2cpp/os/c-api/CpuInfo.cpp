#if NET_4_0
#include "os/CpuInfo.h"
#include "os/c-api/CpuInfo-c-api.h"

extern "C"
{
void* UnityPalCpuInfoCreate()
{
    return il2cpp::os::CpuInfo::Create();
}

int32_t UnityPalCpuInfoUsage(void* previous)
{
    return il2cpp::os::CpuInfo::Usage(previous);
}
}
#endif // NET_4_0
