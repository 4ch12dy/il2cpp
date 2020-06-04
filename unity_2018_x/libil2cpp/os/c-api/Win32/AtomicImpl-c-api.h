#pragma once

#include <stdint.h>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#define WIN32_LEAN_AND_MEAN 1
#define INC_OLE2 1
#include <Windows.h>

#if defined(__cplusplus)
extern "C" {
#endif

static inline int32_t UnityPalCompareExchange(volatile int32_t* dest, int32_t exchange, int32_t comparand)
{
    return InterlockedCompareExchange((long volatile*)dest, exchange, comparand);
}

static inline int64_t UnityPalCompareExchange64(volatile int64_t* dest, int64_t exchange, int64_t comparand)
{
    return InterlockedCompareExchange64((long long volatile*)dest, exchange, comparand);
}

static inline void* UnityPalCompareExchangePointer(void* volatile* dest, void* exchange, void* comparand)
{
    return InterlockedCompareExchangePointer(dest, exchange, comparand);
}

static inline int32_t UnityPalAdd(volatile int32_t* location1, int32_t value)
{
    return (InterlockedExchangeAdd((long volatile*)location1, value) + value);
}

static inline int64_t UnityPalAdd64(volatile int64_t* location1, int64_t value)
{
    return (InterlockedExchangeAdd64((long long volatile*)location1, value) + value);
}

static inline int32_t UnityPalIncrement(volatile int32_t* value)
{
    return InterlockedIncrement((long volatile*)value);
}

static inline int64_t UnityPalIncrement64(volatile int64_t* value)
{
    return InterlockedIncrement64(value);
}

static inline int32_t UnityPalDecrement(volatile int32_t* value)
{
    return InterlockedDecrement((long volatile*)value);
}

static inline int64_t UnityPalDecrement64(volatile int64_t* value)
{
    return InterlockedDecrement64((long long volatile*)value);
}

static inline int64_t UnityPalExchange64(volatile int64_t* dest, int64_t exchange)
{
    return InterlockedExchange64(dest, exchange);
}

static inline int32_t UnityPalExchange(volatile int32_t* dest, int32_t exchange)
{
    return InterlockedExchange((long volatile*)dest, exchange);
}

static  inline void* UnityPalExchangePointer(void* volatile* dest, void* exchange)
{
    return InterlockedExchangePointer(dest, exchange);
}

static inline int64_t UnityPalRead64(volatile int64_t* addr)
{
    return InterlockedCompareExchange64((long long volatile*)addr, 0, 0);
}

#if defined(__cplusplus)
}
#endif
