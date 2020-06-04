#pragma once
#include "il2cpp-class-internals.h"

struct Il2CppSequencePoint;
struct Il2CppSequencePointExecutionContext;
struct Il2CppThreadUnwindState;

typedef void(*DebugInfoInitialization)();
typedef void(*ThreadCallback)(void*, uintptr_t);

#ifdef __cplusplus

#include <stdint.h>
#include "os/Thread.h"
#include "os/ThreadLocalValue.h"

namespace il2cpp
{
namespace utils
{
    class Debugger
    {
    public:
        static void RegisterSequencePointCheck(volatile uint32_t* check);
        static void RegisterMetadata(const Il2CppDebuggerMetadataRegistration *data);
        static void SetAgentOptions(const char* options);
        static void Init();
        static void Start();
        static void StartDebuggerThread();
        static void PushExecutionContext(Il2CppSequencePointExecutionContext* executionContext);
        static void PopExecutionContext();
        typedef void(*OnBreakPointHitCallback) (Il2CppSequencePoint* sequencePoint);
        typedef void (*OnPausePointHitCallback) ();
        static void RegisterCallbacks(OnBreakPointHitCallback breakCallback, OnPausePointHitCallback pauseCallback);
        static Il2CppThreadUnwindState* GetThreadStatePointer();
        static void SaveThreadContext(Il2CppThreadUnwindState* context, int frameCountAdjust);
        static void FreeThreadContext(Il2CppThreadUnwindState* context);
        static void OnBreakPointHit(Il2CppSequencePoint *sequencePoint);
        static void OnPausePointHit();
        static bool IsGlobalBreakpointActive();
        static bool GetIsDebuggerAttached();
        static void SetIsDebuggerAttached(bool attached);
        static bool IsDebuggerThread(os::Thread* thread);
        static void AllocateThreadLocalData();
        static void FreeThreadLocalData();
        static Il2CppSequencePoint* GetSequencePoint(size_t id);
        static Il2CppSequencePoint* GetSequencePoints(void* *iter);
        static Il2CppSequencePoint* GetSequencePoints(const MethodInfo* method, void**iter);
        static void HandleException(Il2CppException *exc, Il2CppSequencePoint *sequencePoint);
        static const char** GetTypeSourceFiles(const Il2CppClass *klass, int& count);
        static void UserBreak();
        static bool IsLoggingEnabled();
        static void Log(int level, Il2CppString *category, Il2CppString *message);
        static bool IsSequencePointActive(Il2CppSequencePoint *seqPoint);
        static bool IsPausePointActive();
        static const MethodInfo* GetSequencePointMethod(Il2CppSequencePoint *seqPoint);

        static void CheckSequencePoint(Il2CppSequencePointExecutionContext* executionContext, size_t seqPointId);
        static void CheckPausePoint();

        static void GetMethodExecutionContextInfo(const MethodInfo* method, uint32_t* executionContextInfoCount, const Il2CppMethodExecutionContextInfo **executionContextInfo, const Il2CppMethodHeaderInfo **headerInfo, const Il2CppMethodScope **scopes);

    private:
        static os::ThreadLocalValue s_IsGlobalBreakpointActive;
        static void InitializeMethodToSequencePointMap();
        static void InitializeTypeSourceFileMap();
    };
}
}
#endif //__cplusplus

typedef struct Il2CppSequencePointExecutionContext
{
    const MethodInfo* method;
    void** thisArg;
    void** params;
    void** locals;
    size_t currentSequencePoint;


#ifdef __cplusplus
    Il2CppSequencePointExecutionContext(const MethodInfo* method, void** thisArg, void** params, void** locals);
    ~Il2CppSequencePointExecutionContext();
#endif //__cplusplus
} Il2CppSequencePointExecutionContext;

typedef struct Il2CppThreadUnwindState
{
    Il2CppSequencePointExecutionContext** executionContexts;
    uint32_t frameCount;
    uint32_t frameCapacity;
} Il2CppThreadUnwindState;
