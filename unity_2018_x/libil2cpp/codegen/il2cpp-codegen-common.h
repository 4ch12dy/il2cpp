#pragma once

#include "il2cpp-config.h"

#include <cassert>
#include <cstdlib>
#include <limits>
#include <string>
#include <math.h>
#include <vector>

#include "il2cpp-object-internals.h"
#include "il2cpp-class-internals.h"
#include "il2cpp-tabledefs.h"

#include "gc/GarbageCollector.h"
#include "vm/PlatformInvoke.h"
#include "vm/StackTrace.h"
#include "vm/PlatformInvoke.h"
#include "vm/StackTrace.h"
#include "vm-utils/Debugger.h"
#include "utils/StringUtils.h"
#include "utils/StringView.h"
#include "utils/Exception.h"
#include "utils/Output.h"
#include "utils/Runtime.h"

REAL_NORETURN IL2CPP_NO_INLINE void il2cpp_codegen_no_return();

#if IL2CPP_COMPILER_MSVC
#define DEFAULT_CALL STDCALL
#else
#define DEFAULT_CALL
#endif

#if defined(__ARMCC_VERSION)
inline double bankers_round(double x)
{
    return __builtin_round(x);
}

inline float bankers_roundf(float x)
{
    return __builtin_roundf(x);
}

#else
inline double bankers_round(double x)
{
    double integerPart;
    if (x >= 0.0)
    {
        if (modf(x, &integerPart) == 0.5)
            return (int64_t)integerPart % 2 == 0 ? integerPart : integerPart + 1.0;
        return floor(x + 0.5);
    }
    else
    {
        if (modf(x, &integerPart) == -0.5)
            return (int64_t)integerPart % 2 == 0 ? integerPart : integerPart - 1.0;
        return ceil(x - 0.5);
    }
}

inline float bankers_roundf(float x)
{
    double integerPart;
    if (x >= 0.0f)
    {
        if (modf(x, &integerPart) == 0.5)
            return (int64_t)integerPart % 2 == 0 ? (float)integerPart : (float)integerPart + 1.0f;
        return floorf(x + 0.5f);
    }
    else
    {
        if (modf(x, &integerPart) == -0.5)
            return (int64_t)integerPart % 2 == 0 ? (float)integerPart : (float)integerPart - 1.0f;
        return ceilf(x - 0.5f);
    }
}

#endif

// returns true if overflow occurs
inline bool il2cpp_codegen_check_mul_overflow_i64(int64_t a, int64_t b, int64_t imin, int64_t imax)
{
    // TODO: use a better algorithm without division
    uint64_t ua = (uint64_t)llabs(a);
    uint64_t ub = (uint64_t)llabs(b);

    uint64_t c;
    if ((a > 0 && b > 0) || (a <= 0 && b <= 0))
        c = (uint64_t)llabs(imax);
    else
        c = (uint64_t)llabs(imin);

    return ua != 0 && ub > c / ua;
}

inline bool il2cpp_codegen_check_mul_oveflow_u64(uint64_t a, uint64_t b)
{
    return b != 0 && (a * b) / b != a;
}

inline int32_t il2cpp_codegen_abs(uint32_t value)
{
    return abs(static_cast<int32_t>(value));
}

inline int32_t il2cpp_codegen_abs(int32_t value)
{
    return abs(value);
}

inline int64_t il2cpp_codegen_abs(uint64_t value)
{
    return llabs(static_cast<int64_t>(value));
}

inline int64_t il2cpp_codegen_abs(int64_t value)
{
    return llabs(value);
}

// Exception support macros
#define IL2CPP_RESET_LEAVE(Offset) \
    if(__leave_target == 0) \
        __leave_target = Offset;

#define IL2CPP_LEAVE(Offset, Target) \
    __leave_target = Offset; \
    goto Target;

#define IL2CPP_END_FINALLY(Id) \
    goto __CLEANUP_ ## Id;

#define IL2CPP_CLEANUP(Id) \
    __CLEANUP_ ## Id:

#define IL2CPP_RETHROW_IF_UNHANDLED(ExcType) \
    if(__last_unhandled_exception) { \
        ExcType _tmp_exception_local = __last_unhandled_exception; \
        __last_unhandled_exception = 0; \
        il2cpp_codegen_raise_exception(_tmp_exception_local); \
        }

#define IL2CPP_JUMP_TBL(Offset, Target) \
    if(__leave_target == Offset) { \
        __leave_target = 0; \
        goto Target; \
        }

#define IL2CPP_END_CLEANUP(Offset, Target) \
    if(__leave_target == Offset) \
        goto Target;


#if IL2CPP_MONO_DEBUGGER
#define IL2CPP_RAISE_MANAGED_EXCEPTION(message, seqPoint, lastManagedFrame) \
    do {\
        il2cpp_codegen_raise_exception((Exception_t*)message, seqPoint, (MethodInfo*)lastManagedFrame);\
        il2cpp_codegen_no_return();\
    } while (0)
#else
#define IL2CPP_RAISE_MANAGED_EXCEPTION(message, seqPoint, lastManagedFrame) \
    do {\
        il2cpp_codegen_raise_exception((Exception_t*)message, NULL, (MethodInfo*)lastManagedFrame);\
        il2cpp_codegen_no_return();\
    } while (0)
#endif


template<typename T>
inline void Il2CppCodeGenWriteBarrier(T** targetAddress, T* object)
{
    il2cpp::gc::GarbageCollector::SetWriteBarrier((void**)targetAddress);
}

void il2cpp_codegen_memory_barrier();

template<typename T>
inline T VolatileRead(T* location)
{
    T result = *location;
    il2cpp_codegen_memory_barrier();
    return result;
}

template<typename T>
inline void VolatileWrite(T** location, T* value)
{
    il2cpp_codegen_memory_barrier();
    *location = value;
    Il2CppCodeGenWriteBarrier(location, value);
}

template<typename T>
inline void VolatileWrite(T* location, T value)
{
    il2cpp_codegen_memory_barrier();
    *location = value;
}

inline void il2cpp_codegen_write_to_stdout(const char* str)
{
    il2cpp::utils::Output::WriteToStdout(str);
}

inline void il2cpp_codegen_write_to_stderr(const char* str)
{
    il2cpp::utils::Output::WriteToStderr(str);
}

inline REAL_NORETURN void il2cpp_codegen_abort()
{
    il2cpp::utils::Runtime::Abort();
    il2cpp_codegen_no_return();
}

inline bool il2cpp_codegen_check_add_overflow(int64_t left, int64_t right)
{
    return (right >= 0 && left > kIl2CppInt64Max - right) ||
        (left < 0 && right < kIl2CppInt64Min - left);
}

inline bool il2cpp_codegen_check_sub_overflow(int64_t left, int64_t right)
{
    return (right >= 0 && left < kIl2CppInt64Min + right) ||
        (right < 0 && left > kIl2CppInt64Max + right);
}

template<bool, class T, class U>
struct pick_first;

template<class T, class U>
struct pick_first<true, T, U>
{
    typedef T type;
};

template<class T, class U>
struct pick_first<false, T, U>
{
    typedef U type;
};

template<class T, class U>
struct pick_bigger
{
    typedef typename pick_first<(sizeof(T) >= sizeof(U)), T, U>::type type;
};

template<typename T, typename U>
inline typename pick_bigger<T, U>::type il2cpp_codegen_multiply(T left, U right)
{
    return left * right;
}

template<typename T, typename U>
inline typename pick_bigger<T, U>::type il2cpp_codegen_add(T left, U right)
{
    return left + right;
}

template<typename T, typename U>
inline typename pick_bigger<T, U>::type il2cpp_codegen_subtract(T left, U right)
{
    return left - right;
}

inline void il2cpp_codegen_memcpy(void* dest, const void* src, size_t count)
{
    memcpy(dest, src, count);
}

inline void il2cpp_codegen_memset(void* ptr, int value, size_t num)
{
    memset(ptr, value, num);
}

#if IL2CPP_MONO_DEBUGGER
extern volatile uint32_t g_Il2CppDebuggerCheckPointEnabled;
#endif

inline void il2cpp_codegen_register_debugger_data(const Il2CppDebuggerMetadataRegistration *data)
{
#if IL2CPP_MONO_DEBUGGER
    il2cpp::utils::Debugger::RegisterSequencePointCheck(&g_Il2CppDebuggerCheckPointEnabled);
    il2cpp::utils::Debugger::RegisterMetadata(data);
#endif
}

inline void il2cpp_codegen_check_sequence_point(Il2CppSequencePointExecutionContext* executionContext, size_t seqPointId)
{
#if IL2CPP_MONO_DEBUGGER
    if (g_Il2CppDebuggerCheckPointEnabled)
        il2cpp::utils::Debugger::CheckSequencePoint(executionContext, seqPointId);
#endif
}

inline void il2cpp_codegen_check_pause_point()
{
#if IL2CPP_MONO_DEBUGGER
    if (g_Il2CppDebuggerCheckPointEnabled)
        il2cpp::utils::Debugger::CheckPausePoint();
#endif
}

inline Il2CppSequencePoint* il2cpp_codegen_get_sequence_point(size_t id)
{
#if IL2CPP_MONO_DEBUGGER
    return il2cpp::utils::Debugger::GetSequencePoint(id);
#else
    return NULL;
#endif
}

class MethodExitSequencePointChecker
{
private:
    size_t m_pSeqPoint;
    Il2CppSequencePointExecutionContext* m_seqPointStorage;

public:
    MethodExitSequencePointChecker(Il2CppSequencePointExecutionContext* seqPointStorage, size_t seqPointId) :
        m_seqPointStorage(seqPointStorage), m_pSeqPoint(seqPointId)
    {
    }

    ~MethodExitSequencePointChecker()
    {
#if IL2CPP_MONO_DEBUGGER
        il2cpp_codegen_check_sequence_point(m_seqPointStorage, m_pSeqPoint);
#endif
    }
};

#ifdef _MSC_VER
#define IL2CPP_DISABLE_OPTIMIZATIONS __pragma(optimize("", off))
#define IL2CPP_ENABLE_OPTIMIZATIONS __pragma(optimize("", on))
#else
#define IL2CPP_DISABLE_OPTIMIZATIONS __attribute__ ((optnone))
#define IL2CPP_ENABLE_OPTIMIZATIONS
#endif

// NativeArray macros
#define IL2CPP_NATIVEARRAY_GET_ITEM(TElementType, TTField, TIndex) \
    *(reinterpret_cast<TElementType*>(TTField) + TIndex)

#define IL2CPP_NATIVEARRAY_SET_ITEM(TElementType, TTField, TIndex, TValue) \
   *(reinterpret_cast<TElementType*>(TTField) + TIndex) = TValue;

#define IL2CPP_NATIVEARRAY_GET_LENGTH(TLengthField) \
   (TLengthField)

// Array Unsafe
#define IL2CPP_ARRAY_UNSAFE_LOAD(TArray, TIndex) \
    (TArray)->GetAtUnchecked(static_cast<il2cpp_array_size_t>(TIndex))

inline bool il2cpp_codegen_object_reference_equals(const RuntimeObject *obj1, const RuntimeObject *obj2)
{
    return obj1 == obj2;
}
