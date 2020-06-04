#pragma once

#include "vm/Domain.h"
#include "vm/Thread.h"

namespace il2cpp
{
namespace vm
{
    class ScopedThreadAttacher
    {
    public:
        ScopedThreadAttacher();
        ~ScopedThreadAttacher();

    private:
        Il2CppThread* m_AttachedThread;
    };
}
}
