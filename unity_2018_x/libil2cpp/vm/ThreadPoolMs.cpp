#if NET_4_0

#include "il2cpp-api.h"
#include "il2cpp-config.h"
#include "utils/dynamic_array.h"
#include "vm/ThreadPoolMs.h"
#include "vm/Domain.h"
#include "vm/Array.h"
#include "vm/Object.h"
#include "vm/Runtime.h"
#include "os/Atomic.h"
#include "gc/WriteBarrier.h"
#include "mono/ThreadPool/threadpool-ms.h"

namespace il2cpp
{
namespace vm
{
    Il2CppAsyncResult* ThreadPoolMs::DelegateBeginInvoke(Il2CppDelegate* delegate, void** params, Il2CppDelegate* asyncCallback, Il2CppObject* state)
    {
        int numParams = delegate->method->parameters_count;
        il2cpp::utils::dynamic_array<void*> newParams(numParams + 2);
        for (int i = 0; i < numParams; ++i)
            newParams[i] = params[i];

        newParams[numParams] = asyncCallback;
        newParams[numParams + 1] = state;

        return threadpool_ms_begin_invoke(il2cpp::vm::Domain::GetCurrent(), (Il2CppObject*)delegate, const_cast<MethodInfo*>(delegate->method), newParams.data());
    }

    Il2CppObject* ThreadPoolMs::DelegateEndInvoke(Il2CppAsyncResult* asyncResult, void **out_args)
    {
        Il2CppArray *arrayOutArgs;
        Il2CppObject *exc, *retVal;

        retVal = threadpool_ms_end_invoke(asyncResult, &arrayOutArgs, &exc);

        if (exc)
            il2cpp_raise_exception((Il2CppException*)exc);

        if (out_args)
        {
            const MethodInfo *method = asyncResult->async_delegate->method;
            void** outArgsPtr = (void**)il2cpp_array_addr(arrayOutArgs, Il2CppObject*, 0);

            for (il2cpp_array_size_t i = 0; i < arrayOutArgs->max_length; ++i)
            {
                const Il2CppType* paramType = method->parameters[i].parameter_type;

                if (!paramType->byref)
                    continue;

                Il2CppClass *paramClass = il2cpp_class_from_type(paramType);

                if (paramClass->valuetype)
                {
                    IL2CPP_ASSERT(paramClass->native_size > 0 && "EndInvoke: Invalid native_size found when trying to copy a value type in the out_args.");

                    // NOTE(gab): in case of value types, we need to copy the data over.
                    memcpy(out_args[i], il2cpp::vm::Object::Unbox((Il2CppObject*)outArgsPtr[i]), paramClass->native_size);
                }
                else
                {
                    *((void**)out_args[i]) = outArgsPtr[i];
                }
            }
        }

        return retVal;
    }

    Il2CppObject* ThreadPoolMs::MessageInvoke(Il2CppObject *target, Il2CppMethodMessage *msg, Il2CppObject **exc, Il2CppArray **out_args)
    {
        static Il2CppClass *object_array_klass = NULL;
        MethodInfo *method;
        Il2CppObject *ret;
        Il2CppArray *arr;
        int i, j, outarg_count = 0;

        method = (MethodInfo*)msg->method->method;

        for (i = 0; i < method->parameters_count; i++)
        {
            if (method->parameters[i].parameter_type->byref)
                outarg_count++;
        }

        if (!object_array_klass)
        {
            Il2CppClass *klass;

            klass = il2cpp_array_class_get(il2cpp_defaults.object_class, 1);
            IL2CPP_ASSERT(klass);

            os::Atomic::FullMemoryBarrier();
            object_array_klass = klass;
        }

        arr = il2cpp_array_new(object_array_klass, outarg_count);

        il2cpp::gc::WriteBarrier::GenericStore(out_args, (Il2CppObject*)arr);
        *exc = NULL;

        ret = vm::Runtime::InvokeArray(method, method->klass->valuetype ? il2cpp_object_unbox(target) : target, method->parameters_count > 0 ? msg->args : NULL, (Il2CppException**)exc);

        for (i = 0, j = 0; i < method->parameters_count; i++)
        {
            if (method->parameters[i].parameter_type->byref)
            {
                Il2CppObject* arg;
                arg = (Il2CppObject*)il2cpp_array_get(msg->args, void*, i);
                il2cpp_array_setref(*out_args, j, arg);
                j++;
            }
        }

        return ret;
    }

    void ThreadPoolMs::Suspend()
    {
        threadpool_ms_suspend();
    }

    void ThreadPoolMs::Resume()
    {
        threadpool_ms_resume();
    }
} /* namespace vm */
} /* namespace il2cpp */

#endif
