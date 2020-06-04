#pragma once

#include "ExtendedAtomicTypes.h"

namespace il2cpp
{
namespace utils
{
    class AtomicNode
    {
        friend class AtomicStack;
        friend class AtomicQueue;
        friend class MutexLockedStack;
        friend class MutexLockedQueue;

        atomic_word _next;

    public:
        void* data[3];

        AtomicNode *Next() const
        {
            return (AtomicNode*)_next;
        }

        AtomicNode *Link(AtomicNode *next);
    };
} // utils
} // il2cpp
