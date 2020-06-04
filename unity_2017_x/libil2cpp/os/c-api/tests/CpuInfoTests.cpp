#if ENABLE_UNIT_TESTS
#if NET_4_0

#include "UnitTest++.h"

#include "../CpuInfo-c-api.h"
#include "../../CpuInfo.h"

#include "il2cpp-config.h"
#if !IL2CPP_USE_GENERIC_CPU_INFO

SUITE(CpuInfo)
{
    TEST(ApiCreateReturnsANonNullObject)
    {
        CHECK_NOT_NULL(UnityPalCpuInfoCreate());
    }

    TEST(ApiCpuInfoUsageMatchesClassCpuInfo)
    {
        CHECK_EQUAL(il2cpp::os::CpuInfo::Usage(NULL), UnityPalCpuInfoUsage(NULL));
    }
}

#endif // !IL2CPP_USE_GENERIC_CPU_INFO

#endif // NET_4_0
#endif // ENABLE_UNIT_TESTS
