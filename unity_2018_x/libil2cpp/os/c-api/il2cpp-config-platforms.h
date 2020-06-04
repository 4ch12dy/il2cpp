#pragma once

#include <assert.h>

#if defined(__aarch64__) && defined(__arm__)
#error We assume both __aarch64__ and __arm__ cannot be defined at tha same time.
#endif

#if defined(__aarch64__)
#define IL2CPP_TARGET_ARM64 1
#define IL2CPP_TARGET_ARMV7 0
#elif defined(__arm__)
#define IL2CPP_TARGET_ARM64 0
#define IL2CPP_TARGET_ARMV7 1
#else
#define IL2CPP_TARGET_ARM64 0
#define IL2CPP_TARGET_ARMV7 0
#endif

#define IL2CPP_BINARY_SECTION_NAME ".il2cpp"

#if defined(SN_TARGET_PSP2)
#define IL2CPP_TARGET_PSP2 1
#define _UNICODE 1
#define UNICODE 1
#include "il2cpp-config-psp2.h"
#elif defined(SN_TARGET_ORBIS)
#define IL2CPP_TARGET_PS4 1
#define _UNICODE 1
#define UNICODE 1
#elif defined(_MSC_VER)
#define IL2CPP_TARGET_WINDOWS 1
#define IL2CPP_PLATFORM_SUPPORTS_CUSTOM_SECTIONS 1
#define IL2CPP_PLATFORM_SUPPORTS_DEBUGGER_PRESENT 1
#define IL2CPP_METHOD_ATTR  __declspec(code_seg (".il2cpp"))
#if defined(_XBOX_ONE)
#define IL2CPP_TARGET_XBOXONE 1
#define IL2CPP_PLATFORM_SUPPORTS_DEBUGGER_PRESENT 1
#elif defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
#define IL2CPP_TARGET_WINRT 1
#define IL2CPP_PLATFORM_SUPPORTS_SYSTEM_CERTIFICATES 1
#else
#define IL2CPP_TARGET_WINDOWS_DESKTOP 1
#define IL2CPP_PLATFORM_SUPPORTS_SYSTEM_CERTIFICATES 1
#define IL2CPP_PLATFORM_SUPPORTS_CPU_INFO 1
#endif
#define _UNICODE 1
#define UNICODE 1
#define STRICT 1
#elif defined(__APPLE__)
#define IL2CPP_TARGET_DARWIN 1
#define IL2CPP_PLATFORM_SUPPORTS_CPU_INFO 1
#define IL2CPP_PLATFORM_SUPPORTS_TIMEZONEINFO 1

#include "TargetConditionals.h"
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR || TARGET_OS_TV || TARGET_TVOS_SIMULATOR
#define IL2CPP_TARGET_IOS 1
#define IL2CPP_PLATFORM_SUPPORTS_CPU_INFO 1
#else
#define IL2CPP_TARGET_OSX 1
#define IL2CPP_PLATFORM_SUPPORTS_SYSTEM_CERTIFICATES 1
#endif

#define IL2CPP_PLATFORM_SUPPORTS_CUSTOM_SECTIONS !(IL2CPP_TARGET_IOS && IL2CPP_TARGET_ARMV7)
#if IL2CPP_PLATFORM_SUPPORTS_CUSTOM_SECTIONS
// The following gives managed stack traces (even with bitcode App Store submission), but may cause linker
// errors on ARMv7 builds.
#define IL2CPP_METHOD_ATTR __attribute__((section ("__TEXT," IL2CPP_BINARY_SECTION_NAME ",regular,pure_instructions")))
#endif

#elif defined(__ANDROID__)
#define IL2CPP_TARGET_ANDROID 1
#define IL2CPP_PLATFORM_SUPPORTS_TIMEZONEINFO 1
#define IL2CPP_PLATFORM_SUPPORTS_CUSTOM_SECTIONS 1
#define IL2CPP_METHOD_ATTR __attribute__((section ("__TEXT," IL2CPP_BINARY_SECTION_NAME ",regular,pure_instructions")))
#elif defined(EMSCRIPTEN)
#define IL2CPP_TARGET_JAVASCRIPT 1
#define IL2CPP_PLATFORM_SUPPORTS_CPU_INFO 1
#elif defined(NOVA)
#define IL2CPP_TARGET_NOVA 1
#elif defined(__linux__)
#define IL2CPP_TARGET_LINUX 1
#define IL2CPP_PLATFORM_SUPPORTS_CPU_INFO 1
#define IL2CPP_PLATFORM_SUPPORTS_SYSTEM_CERTIFICATES 1
#elif defined(NN_PLATFORM_CTR)
#define IL2CPP_TARGET_N3DS 1
#elif defined(NN_BUILD_TARGET_PLATFORM_NX)
#define IL2CPP_TARGET_SWITCH 1
#include "il2cpp-config-switch.h"
#else
#error please define your target platform
#endif

#ifndef IL2CPP_TARGET_WINDOWS
#define IL2CPP_TARGET_WINDOWS 0
#endif

#ifndef IL2CPP_TARGET_WINDOWS_DESKTOP
#define IL2CPP_TARGET_WINDOWS_DESKTOP 0
#endif

#ifndef IL2CPP_TARGET_WINRT
#define IL2CPP_TARGET_WINRT 0
#endif

#ifndef IL2CPP_TARGET_XBOXONE
#define IL2CPP_TARGET_XBOXONE 0
#endif

#ifndef IL2CPP_TARGET_DARWIN
#define IL2CPP_TARGET_DARWIN 0
#endif

#ifndef IL2CPP_TARGET_IOS
#define IL2CPP_TARGET_IOS 0
#endif

#ifndef IL2CPP_TARGET_OSX
#define IL2CPP_TARGET_OSX 0
#endif

#ifndef IL2CPP_TARGET_ANDROID
#define IL2CPP_TARGET_ANDROID 0
#endif

#ifndef IL2CPP_TARGET_JAVASCRIPT
#define IL2CPP_TARGET_JAVASCRIPT 0
#endif

#ifndef IL2CPP_TARGET_LINUX
#define IL2CPP_TARGET_LINUX 0
#endif

#ifndef IL2CPP_TARGET_N3DS
#define IL2CPP_TARGET_N3DS 0
#endif

#ifndef IL2CPP_TARGET_PS4
#define IL2CPP_TARGET_PS4 0
#endif

#ifndef IL2CPP_TARGET_PSP2
#define IL2CPP_TARGET_PSP2 0
#endif

#ifndef IL2CPP_TARGET_SWITCH
#define IL2CPP_TARGET_SWITCH 0
#endif

#define IL2CPP_TARGET_POSIX (IL2CPP_TARGET_DARWIN || IL2CPP_TARGET_JAVASCRIPT || IL2CPP_TARGET_LINUX || IL2CPP_TARGET_ANDROID || IL2CPP_TARGET_PS4 || IL2CPP_TARGET_PSP2 || IL2CPP_TARGET_NOVA)

#define IL2CPP_SUPPORT_THREADS !IL2CPP_TARGET_JAVASCRIPT

#ifndef IL2CPP_PLATFORM_SUPPORTS_SYSTEM_CERTIFICATES
#define IL2CPP_PLATFORM_SUPPORTS_SYSTEM_CERTIFICATES 0
#endif

#ifndef IL2CPP_PLATFORM_SUPPORTS_TIMEZONEINFO
#define IL2CPP_PLATFORM_SUPPORTS_TIMEZONEINFO 0
#endif

#ifndef IL2CPP_PLATFORM_SUPPORTS_CUSTOM_SECTIONS
#define IL2CPP_PLATFORM_SUPPORTS_CUSTOM_SECTIONS 0
#endif

#if IL2CPP_TARGET_WINDOWS || IL2CPP_TARGET_XBOXONE || IL2CPP_TARGET_WINRT
#include <crtdbg.h>
#define IL2CPP_ASSERT(expr) \
    _ASSERTE(expr)
#else
#define IL2CPP_ASSERT(expr) \
    assert(expr)
#endif

#ifndef IL2CPP_PLATFORM_SUPPORTS_CPU_INFO
#define IL2CPP_PLATFORM_SUPPORTS_CPU_INFO 0
#endif

#ifndef IL2CPP_PLATFORM_SUPPORTS_DEBUGGER_PRESENT
#define IL2CPP_PLATFORM_SUPPORTS_DEBUGGER_PRESENT 0
#endif

#define IL2CPP_USE_STD_THREAD 0

#define IL2CPP_THREADS_STD IL2CPP_USE_STD_THREAD
#define IL2CPP_THREADS_PTHREAD (!IL2CPP_THREADS_STD && IL2CPP_TARGET_POSIX)
#define IL2CPP_THREADS_WIN32 (!IL2CPP_THREADS_STD && IL2CPP_TARGET_WINDOWS)
#define IL2CPP_THREADS_N3DS (!IL2CPP_THREADS_STD && IL2CPP_TARGET_N3DS)
#define IL2CPP_THREADS_PS4 (!IL2CPP_THREADS_STD && IL2CPP_TARGET_PS4)
#define IL2CPP_THREADS_PSP2 (!IL2CPP_THREADS_STD && IL2CPP_TARGET_PSP2)
#define IL2CPP_THREADS_SWITCH (!IL2CPP_THREADS_STD && IL2CPP_TARGET_SWITCH)

/* Trigger assert if 'ptr' is not aligned to 'alignment'. */
#define ASSERT_ALIGNMENT(ptr, alignment) \
    IL2CPP_ASSERT((((ptrdiff_t) ptr) & (alignment - 1)) == 0 && "Unaligned pointer!")

    #if defined(_MSC_VER)
    #if defined(_M_X64)
        #define IL2CPP_SIZEOF_VOID_P 8
    #elif defined(_M_IX86) || defined(_M_ARM)
        #define IL2CPP_SIZEOF_VOID_P 4
    #else
        #error invalid windows architecture
    #endif
#elif defined(__GNUC__) || defined(__SNC__)
    #if defined(__x86_64__)
        #define IL2CPP_SIZEOF_VOID_P 8
    #elif defined(__i386__)
        #define IL2CPP_SIZEOF_VOID_P 4
    #elif defined(EMSCRIPTEN)
        #define IL2CPP_SIZEOF_VOID_P 4
    #elif defined(__arm__)
        #define IL2CPP_SIZEOF_VOID_P 4
    #elif defined(__arm64__) || defined(__aarch64__)
        #define IL2CPP_SIZEOF_VOID_P 8
    #else
        #error invalid windows architecture
    #endif
#else
    #error please define your target architecture size
#endif
