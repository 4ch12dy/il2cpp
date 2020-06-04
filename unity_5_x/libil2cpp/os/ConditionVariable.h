#pragma once
#if NET_4_0
#include "utils/NonCopyable.h"

namespace il2cpp
{
namespace os
{
    class FastMutex;
    class ConditionVariableImpl;

    class ConditionVariable : public il2cpp::utils::NonCopyable
    {
    public:
        ConditionVariable();
        ~ConditionVariable();

        int Wait(FastMutex* lock);
        int TimedWait(FastMutex* lock, uint32_t timeout_ms);
        void Broadcast();
        void Signal();

    private:
        ConditionVariableImpl* m_ConditionVariable;
    };
}
}
#endif
