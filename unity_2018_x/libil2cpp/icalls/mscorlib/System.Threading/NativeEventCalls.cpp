#include "il2cpp-config.h"
#include "icalls/mscorlib/System.Threading/NativeEventCalls.h"
#include "os/Event.h"
#include "vm/Exception.h"

using namespace il2cpp::os;

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
namespace Threading
{
    bool NativeEventCalls::ResetEvent_internal(intptr_t handlePtr)
    {
        EventHandle* handle = (EventHandle*)handlePtr;
        ErrorCode result = handle->Get().Reset();

        return kErrorCodeSuccess == result;
    }

    bool NativeEventCalls::SetEvent_internal(intptr_t handlePtr)
    {
        EventHandle* handle = (EventHandle*)handlePtr;
        ErrorCode result = handle->Get().Set();

        return kErrorCodeSuccess == result;
    }

#if !NET_4_0

    intptr_t NativeEventCalls::CreateEvent_internal(bool manualReset, bool signaled, Il2CppString* name, bool* created)
    {
        *created = true;
        il2cpp::os::Event* event = NULL;

        if (name == NULL)
            event = new Event(manualReset, signaled);
        else
            NOT_SUPPORTED_IL2CPP(NativeEventCalls::CreateEvent_internal, "Named events are not supported.");

        return reinterpret_cast<intptr_t>(new EventHandle(event));
    }

    intptr_t NativeEventCalls::OpenEvent_internal(Il2CppString* name, EventWaitHandleRights rights, MonoIOError* error)
    {
        IL2CPP_NOT_IMPLEMENTED_ICALL(NativeEventCalls::OpenEvent_internal);
        return intptr_t();
    }

#else

    intptr_t NativeEventCalls::CreateEvent_internal(bool manual, bool initial, Il2CppString* name, int32_t *errorCode)
    {
        *errorCode = 0;
        il2cpp::os::Event* event = NULL;

        if (name == NULL)
            event = new Event(manual, initial);
        else
            NOT_SUPPORTED_IL2CPP(NativeEventCalls::CreateEvent_internal, "Named events are not supported.");

        return reinterpret_cast<intptr_t>(new EventHandle(event));
    }

    intptr_t NativeEventCalls::OpenEvent_internal(Il2CppString* name, EventWaitHandleRights rights, int32_t* errorCode)
    {
        IL2CPP_NOT_IMPLEMENTED_ICALL(NativeEventCalls::OpenEvent_internal);
        return intptr_t();
    }

#endif

    void NativeEventCalls::CloseEvent_internal(intptr_t handlePtr)
    {
        Handle* handle = (Handle*)handlePtr;
        // should we close or just delete
        //handle->Close ();
        delete handle;
    }
} /* namespace Threading */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
