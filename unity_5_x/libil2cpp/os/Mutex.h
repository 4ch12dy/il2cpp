#pragma once

#include "os/ErrorCodes.h"
#include "os/Handle.h"
#include "os/WaitStatus.h"
#include "utils/NonCopyable.h"

namespace il2cpp
{
namespace os
{
    class MutexImpl;
    class FastMutexImpl;

    class Mutex : public il2cpp::utils::NonCopyable
    {
    public:
        Mutex(bool initiallyOwned = false);
        ~Mutex();

        void Lock(bool interruptible = false);
        bool TryLock(uint32_t milliseconds = 0, bool interruptible = false);
        void Unlock();

    private:
        MutexImpl* m_Mutex;
    };

    struct AutoLock : public il2cpp::utils::NonCopyable
    {
        AutoLock(Mutex* mutex) : m_Mutex(mutex) { m_Mutex->Lock(); }
        ~AutoLock() { m_Mutex->Unlock(); }
    private:
        Mutex* m_Mutex;
    };

    class MutexHandle : public Handle
    {
    public:
        MutexHandle(Mutex* mutex) : m_Mutex(mutex) {}
        virtual ~MutexHandle() { delete m_Mutex; }
        virtual bool Wait() { m_Mutex->Lock(true); return true; }
        virtual bool Wait(uint32_t ms) { return m_Mutex->TryLock(ms, true); }
        virtual void Signal() { m_Mutex->Unlock(); }
        Mutex* Get() { return m_Mutex; }

    private:
        Mutex* m_Mutex;
    };


/// Lightweight mutex that has no support for interruption or timed waits. Meant for
/// internal use only.
    class FastMutex
    {
    public:
        FastMutex();
        ~FastMutex();

        void Lock();
        void Unlock();

        FastMutexImpl* GetImpl();

    private:
        FastMutexImpl* m_Impl;
    };

    struct FastAutoLock : public il2cpp::utils::NonCopyable
    {
        FastAutoLock(FastMutex* mutex)
            : m_Mutex(mutex)
        {
            m_Mutex->Lock();
        }

        ~FastAutoLock()
        {
            m_Mutex->Unlock();
        }

    private:
        FastMutex* m_Mutex;
    };


    struct FastAutoUnlock : public il2cpp::utils::NonCopyable
    {
        FastAutoUnlock(FastMutex* mutex)
            : m_Mutex(mutex)
        {
            m_Mutex->Unlock();
        }

        ~FastAutoUnlock()
        {
            m_Mutex->Lock();
        }

    private:
        FastMutex* m_Mutex;
    };
}
}
