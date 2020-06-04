#pragma once

#include "il2cpp-codegen-common.h"
#include "icallincludes.h"
#include "utils/Il2CppHStringReference.h"
#include "utils/RegisterRuntimeInitializeAndCleanup.h"

#include "metadata/GenericMethod.h"
#include "vm/Array.h"
#include "vm/Assembly.h"
#include "vm/Atomic.h"
#include "vm/CCW.h"
#include "vm/Class.h"
#include "vm/COM.h"
#include "vm/Domain.h"
#include "vm/Exception.h"
#include "vm/InternalCalls.h"
#include "vm/LastError.h"
#include "vm/MarshalAlloc.h"
#include "vm/MetadataCache.h"
#include "vm/Method.h"
#include "vm/Object.h"
#include "vm/Profiler.h"
#include "vm/RCW.h"
#include "vm/Reflection.h"
#include "vm/Runtime.h"
#include "vm/ScopedThreadAttacher.h"
#include "vm/String.h"
#include "vm/Thread.h"
#include "vm/ThreadPool.h"
#include "vm/Type.h"
#include "vm/WindowsRuntime.h"
#include "vm/ThreadPoolMs.h"

struct ProfilerMethodSentry
{
    ProfilerMethodSentry(const RuntimeMethod* method)
#if IL2CPP_ENABLE_PROFILER
        : m_method(method)
#endif
    {
#if IL2CPP_ENABLE_PROFILER
        il2cpp::vm::Profiler::MethodEnter(m_method);
#endif
    }

    ~ProfilerMethodSentry()
    {
#if IL2CPP_ENABLE_PROFILER
        il2cpp::vm::Profiler::MethodExit(m_method);
#endif
    }

private:
    const RuntimeMethod* m_method;
};

struct StackTraceSentry
{
    StackTraceSentry(const RuntimeMethod* method) : m_method(method)
    {
        Il2CppStackFrameInfo frame_info;

        frame_info.method = method;

        il2cpp::vm::StackTrace::PushFrame(frame_info);
    }

    ~StackTraceSentry()
    {
        il2cpp::vm::StackTrace::PopFrame();
    }

private:
    const RuntimeMethod* m_method;
};

#define IL2CPP_FAKE_BOX_SENTRY (MonitorData*)UINTPTR_MAX

template<typename T>
struct Il2CppFakeBox : RuntimeObject
{
    T m_Value;

    Il2CppFakeBox(RuntimeClass* boxedType, T* value)
    {
        klass = boxedType;
        monitor = IL2CPP_FAKE_BOX_SENTRY;
        m_Value = *value;
    }
};

inline bool il2cpp_codegen_is_fake_boxed_object(RuntimeObject* object)
{
    return object->monitor == IL2CPP_FAKE_BOX_SENTRY;
}

// TODO: This file should contain all the functions and type declarations needed for the generated code.
// Hopefully, we stop including everything in the generated code and know exactly what dependencies we have.
// Note that all parameter and return types should match the generated types not the runtime types.

inline void il2cpp_codegen_register(const Il2CppCodeRegistration* const codeRegistration, const Il2CppMetadataRegistration* const metadataRegistration, const Il2CppCodeGenOptions* const codeGenOptions)
{
    il2cpp::vm::MetadataCache::Register(codeRegistration, metadataRegistration, codeGenOptions);
}

// type registration

inline void* il2cpp_codegen_get_thread_static_data(RuntimeClass* klass)
{
    return il2cpp::vm::Thread::GetThreadStaticData(klass->thread_static_fields_offset);
}

inline String_t* il2cpp_codegen_string_new_wrapper(const char* str)
{
    return (String_t*)il2cpp::vm::String::NewWrapper(str);
}

inline String_t* il2cpp_codegen_string_new_utf16(const il2cpp::utils::StringView<Il2CppChar>& str)
{
    return (String_t*)il2cpp::vm::String::NewUtf16(str.Str(), static_cast<int32_t>(str.Length()));
}

inline Type_t* il2cpp_codegen_type_get_object(const RuntimeType* type)
{
    return (Type_t*)il2cpp::vm::Reflection::GetTypeObject(type);
}

inline NORETURN void il2cpp_codegen_raise_exception(Exception_t *ex, Il2CppSequencePoint *seqPoint = NULL, MethodInfo* lastManagedFrame = NULL)
{
    il2cpp::vm::Exception::Raise((RuntimeException*)ex, seqPoint, lastManagedFrame);
}

inline void il2cpp_codegen_raise_execution_engine_exception_if_method_is_not_found(const RuntimeMethod* method)
{
    il2cpp::vm::Runtime::RaiseExecutionEngineExceptionIfMethodIsNotFound(method);
}

inline void il2cpp_codegen_raise_execution_engine_exception(const RuntimeMethod* method)
{
    il2cpp::vm::Runtime::AlwaysRaiseExecutionEngineException(method);
}

inline void il2cpp_codegen_raise_out_of_memory_exception()
{
    il2cpp::vm::Exception::RaiseOutOfMemoryException();
}

inline Exception_t* il2cpp_codegen_get_argument_exception(const char* param, const char* msg)
{
    return (Exception_t*)il2cpp::vm::Exception::GetArgumentException(param, msg);
}

inline Exception_t* il2cpp_codegen_get_argument_null_exception(const char* param)
{
    return (Exception_t*)il2cpp::vm::Exception::GetArgumentNullException(param);
}

inline Exception_t* il2cpp_codegen_get_overflow_exception()
{
    return (Exception_t*)il2cpp::vm::Exception::GetOverflowException("Arithmetic operation resulted in an overflow.");
}

inline Exception_t* il2cpp_codegen_get_not_supported_exception(const char* msg)
{
    return (Exception_t*)il2cpp::vm::Exception::GetNotSupportedException(msg);
}

inline Exception_t* il2cpp_codegen_get_array_type_mismatch_exception()
{
    return (Exception_t*)il2cpp::vm::Exception::GetArrayTypeMismatchException();
}

inline Exception_t* il2cpp_codegen_get_invalid_cast_exception(const char* msg)
{
    return (Exception_t*)il2cpp::vm::Exception::GetInvalidCastException(msg);
}

inline Exception_t* il2cpp_codegen_get_invalid_operation_exception(const char* msg)
{
    return (Exception_t*)il2cpp::vm::Exception::GetInvalidOperationException(msg);
}

inline Exception_t* il2cpp_codegen_get_marshal_directive_exception(const char* msg)
{
    return (Exception_t*)il2cpp::vm::Exception::GetMarshalDirectiveException(msg);
}

inline Exception_t* il2cpp_codegen_get_missing_method_exception(const char* msg)
{
    return (Exception_t*)il2cpp::vm::Exception::GetMissingMethodException(msg);
}

inline Exception_t* il2cpp_codegen_get_maximum_nested_generics_exception()
{
    return (Exception_t*)il2cpp::vm::Exception::GetMaxmimumNestedGenericsException();
}

inline RuntimeClass* il2cpp_codegen_object_class(RuntimeObject* obj)
{
    return obj->klass;
}

// OpCode.IsInst

inline RuntimeObject* IsInst(RuntimeObject *obj, RuntimeClass* targetType)
{
    return il2cpp::vm::Object::IsInst(obj, targetType);
}

inline RuntimeObject* IsInstSealed(RuntimeObject *obj, RuntimeClass* targetType)
{
#if IL2CPP_DEBUG
    IL2CPP_ASSERT((targetType->flags & TYPE_ATTRIBUTE_SEALED) != 0);
    IL2CPP_ASSERT((targetType->flags & TYPE_ATTRIBUTE_INTERFACE) == 0);
#endif
    if (!obj)
        return NULL;

    // optimized version to compare sealed classes
    return (obj->klass == targetType ? obj : NULL);
}

inline RuntimeObject* IsInstClass(RuntimeObject *obj, RuntimeClass* targetType)
{
#if IL2CPP_DEBUG
    IL2CPP_ASSERT((targetType->flags & TYPE_ATTRIBUTE_INTERFACE) == 0);
#endif
    if (!obj)
        return NULL;

    // optimized version to compare classes
    return il2cpp::vm::Class::HasParentUnsafe(obj->klass, targetType) ? obj : NULL;
}

// OpCode.Castclass

NORETURN inline void RaiseInvalidCastException(RuntimeObject* obj, RuntimeClass* targetType)
{
    std::string exceptionMessage = il2cpp::utils::Exception::FormatInvalidCastException(obj->klass->element_class, targetType);
    RuntimeException* exception = il2cpp::vm::Exception::GetInvalidCastException(exceptionMessage.c_str());
    il2cpp::vm::Exception::Raise(exception);
}

inline RuntimeObject* Castclass(RuntimeObject *obj, RuntimeClass* targetType)
{
    if (!obj)
        return NULL;

    RuntimeObject* result = il2cpp::vm::Object::IsInst(obj, targetType);
    if (result)
        return result;

    RaiseInvalidCastException(obj, targetType);
    return NULL;
}

inline RuntimeObject* CastclassSealed(RuntimeObject *obj, RuntimeClass* targetType)
{
    if (!obj)
        return NULL;

    RuntimeObject* result = IsInstSealed(obj, targetType);
    if (result)
        return result;

    RaiseInvalidCastException(obj, targetType);
    return NULL;
}

inline RuntimeObject* CastclassClass(RuntimeObject *obj, RuntimeClass* targetType)
{
    if (!obj)
        return NULL;

    RuntimeObject* result = IsInstClass(obj, targetType);
    if (result)
        return result;

    RaiseInvalidCastException(obj, targetType);
    return NULL;
}

inline void NullCheck(void* this_ptr, Il2CppSequencePoint *seqPoint = NULL)
{
    if (this_ptr != NULL)
        return;

    il2cpp::vm::Exception::RaiseNullReferenceException(seqPoint);
}

// OpCode.Box

inline RuntimeObject* Box(RuntimeClass* type, void* data)
{
    return il2cpp::vm::Object::Box(type, data);
}

// OpCode.UnBox

inline void* UnBox(RuntimeObject* obj)
{
    NullCheck(obj);
    return il2cpp::vm::Object::Unbox(obj);
}

inline void* UnBox(RuntimeObject* obj, RuntimeClass* expectedBoxedClass)
{
    NullCheck(obj);

    if (obj->klass->element_class == expectedBoxedClass->element_class)
        return il2cpp::vm::Object::Unbox(obj);

    RaiseInvalidCastException(obj, expectedBoxedClass);
    return NULL;
}

inline void UnBoxNullable(RuntimeObject* obj, RuntimeClass* expectedBoxedClass, void* storage)
{
    // We only need to do type checks if obj is not null
    // Unboxing null nullable is perfectly valid and returns an instance that has no value
    if (obj != NULL)
    {
        if (obj->klass->element_class != expectedBoxedClass->element_class)
            RaiseInvalidCastException(obj, expectedBoxedClass);
    }

    il2cpp::vm::Object::UnboxNullable(obj, expectedBoxedClass, storage);
}

inline uint32_t il2cpp_codegen_sizeof(RuntimeClass* klass)
{
    if (!klass->valuetype)
    {
        return sizeof(void*);
    }

    return il2cpp::vm::Class::GetInstanceSize(klass) - sizeof(RuntimeObject);
}

inline bool il2cpp_codegen_method_is_virtual(RuntimeMethod* method)
{
    return method->slot != kInvalidIl2CppMethodSlot;
}

inline bool il2cpp_codegen_object_is_of_sealed_type(RuntimeObject* obj)
{
    return obj != NULL && (obj->klass->flags & TYPE_ATTRIBUTE_SEALED) != 0;
}

inline bool il2cpp_codegen_method_is_generic_instance(RuntimeMethod* method)
{
    return il2cpp::vm::Method::IsGenericInstance(method);
}

inline bool il2cpp_codegen_method_is_interface_method(RuntimeMethod* method)
{
    return il2cpp::vm::Class::IsInterface(il2cpp::vm::Method::GetClass(method));
}

inline uint16_t il2cpp_codegen_method_get_slot(RuntimeMethod* method)
{
    return method->slot;
}

inline RuntimeClass* il2cpp_codegen_method_get_declaring_type(RuntimeMethod* method)
{
    return il2cpp::vm::Method::GetClass(method);
}

FORCE_INLINE const VirtualInvokeData& il2cpp_codegen_get_virtual_invoke_data(Il2CppMethodSlot slot, const RuntimeObject* obj)
{
    Assert(slot != kInvalidIl2CppMethodSlot && "il2cpp_codegen_get_virtual_invoke_data got called on a non-virtual method");
    return obj->klass->vtable[slot];
}

FORCE_INLINE const VirtualInvokeData& il2cpp_codegen_get_interface_invoke_data(Il2CppMethodSlot slot, const RuntimeObject* obj, const RuntimeClass* declaringInterface)
{
    Assert(slot != kInvalidIl2CppMethodSlot && "il2cpp_codegen_get_interface_invoke_data got called on a non-virtual method");
    return il2cpp::vm::Class::GetInterfaceInvokeDataFromVTable(obj, declaringInterface, slot);
}

FORCE_INLINE const RuntimeMethod* il2cpp_codegen_get_generic_virtual_method(const RuntimeMethod* method, const RuntimeObject* obj)
{
    uint16_t slot = method->slot;
    const RuntimeMethod* methodDefinition = obj->klass->vtable[slot].method;
    return il2cpp::vm::Runtime::GetGenericVirtualMethod(methodDefinition, method);
}

FORCE_INLINE void il2cpp_codegen_get_generic_virtual_invoke_data(const RuntimeMethod* method, const RuntimeObject* obj, VirtualInvokeData* invokeData)
{
    const RuntimeMethod* targetRuntimeMethod = il2cpp_codegen_get_generic_virtual_method(method, obj);
#if IL2CPP_DEBUG
    IL2CPP_ASSERT(targetRuntimeMethod);
#endif

    invokeData->methodPtr = targetRuntimeMethod->methodPointer;
    invokeData->method = targetRuntimeMethod;
}

FORCE_INLINE const RuntimeMethod* il2cpp_codegen_get_generic_interface_method(const RuntimeMethod* method, const RuntimeObject* obj)
{
    const RuntimeMethod* methodDefinition = il2cpp::vm::Class::GetInterfaceInvokeDataFromVTable(obj, method->klass, method->slot).method;
    return il2cpp::vm::Runtime::GetGenericVirtualMethod(methodDefinition, method);
}

FORCE_INLINE void il2cpp_codegen_get_generic_interface_invoke_data(const RuntimeMethod* method, const RuntimeObject* obj, VirtualInvokeData* invokeData)
{
    const RuntimeMethod* targetRuntimeMethod = il2cpp_codegen_get_generic_interface_method(method, obj);

#if IL2CPP_DEBUG
    IL2CPP_ASSERT(targetRuntimeMethod);
#endif

    invokeData->methodPtr = targetRuntimeMethod->methodPointer;
    invokeData->method = targetRuntimeMethod;
}

inline RuntimeClass* InitializedTypeInfo(RuntimeClass* klass)
{
    il2cpp::vm::Class::InitFromCodegen(klass);
    return klass;
}

inline RuntimeClass* il2cpp_codegen_class_from_type(const RuntimeType *type)
{
    return InitializedTypeInfo(il2cpp::vm::Class::FromIl2CppType(type));
}

inline void* InterlockedExchangeImplRef(void** location, void* value)
{
    return il2cpp::icalls::mscorlib::System::Threading::Interlocked::ExchangePointer(location, value);
}

template<typename T>
inline T InterlockedCompareExchangeImpl(T* location, T value, T comparand)
{
    return (T)il2cpp::icalls::mscorlib::System::Threading::Interlocked::CompareExchange_T((void**)location, value, comparand);
}

template<typename T>
inline T InterlockedExchangeImpl(T* location, T value)
{
    return (T)InterlockedExchangeImplRef((void**)location, value);
}

inline void il2cpp_codegen_memory_barrier()
{
    il2cpp::vm::Thread::FullMemoryBarrier();
}

inline void ArrayGetGenericValueImpl(RuntimeArray* thisPtr, int32_t pos, void* value)
{
    memcpy(value, ((uint8_t*)thisPtr) + sizeof(RuntimeArray) + pos * thisPtr->klass->element_size, thisPtr->klass->element_size);
}

inline void ArraySetGenericValueImpl(RuntimeArray * thisPtr, int32_t pos, void* value)
{
    memcpy(((uint8_t*)thisPtr) + sizeof(RuntimeArray) + pos * thisPtr->klass->element_size, value, thisPtr->klass->element_size);
}

inline RuntimeArray* SZArrayNew(RuntimeClass* arrayType, uint32_t length)
{
    return il2cpp::vm::Array::NewSpecific(arrayType, length);
}

inline RuntimeArray* GenArrayNew(RuntimeClass* arrayType, il2cpp_array_size_t* dimensions)
{
    return il2cpp::vm::Array::NewFull(arrayType, dimensions, NULL);
}

// Performance optimization as detailed here: http://blogs.msdn.com/b/clrcodegeneration/archive/2009/08/13/array-bounds-check-elimination-in-the-clr.aspx
// Since array size is a signed int32_t, a single unsigned check can be performed to determine if index is less than array size.
// Negative indices will map to a unsigned number greater than or equal to 2^31 which is larger than allowed for a valid array.
#define IL2CPP_ARRAY_BOUNDS_CHECK(index, length) \
    do { \
        if (((uint32_t)(index)) >= ((uint32_t)length)) il2cpp::vm::Exception::Raise (il2cpp::vm::Exception::GetIndexOutOfRangeException()); \
    } while (0)

inline bool il2cpp_codegen_class_is_assignable_from(RuntimeClass *klass, RuntimeClass *oklass)
{
    return il2cpp::vm::Class::IsAssignableFrom(klass, oklass);
}

inline RuntimeObject* il2cpp_codegen_object_new(RuntimeClass *klass)
{
    return il2cpp::vm::Object::New(klass);
}

inline Il2CppMethodPointer il2cpp_codegen_resolve_icall(const char* name)
{
    Il2CppMethodPointer method = il2cpp::vm::InternalCalls::Resolve(name);
    if (!method)
    {
        il2cpp::vm::Exception::Raise(il2cpp::vm::Exception::GetMissingMethodException(name));
    }
    return method;
}

template<typename FunctionPointerType, size_t dynamicLibraryLength, size_t entryPointLength>
inline FunctionPointerType il2cpp_codegen_resolve_pinvoke(const Il2CppNativeChar(&nativeDynamicLibrary)[dynamicLibraryLength], const char(&entryPoint)[entryPointLength],
    Il2CppCallConvention callingConvention, Il2CppCharSet charSet, int parameterSize, bool isNoMangle)
{
    const PInvokeArguments pinvokeArgs =
    {
        il2cpp::utils::StringView<Il2CppNativeChar>(nativeDynamicLibrary),
        il2cpp::utils::StringView<char>(entryPoint),
        callingConvention,
        charSet,
        parameterSize,
        isNoMangle
    };

    return reinterpret_cast<FunctionPointerType>(il2cpp::vm::PlatformInvoke::Resolve(pinvokeArgs));
}

template<typename T>
inline T* il2cpp_codegen_marshal_allocate_array(size_t length)
{
    return static_cast<T*>(il2cpp::vm::MarshalAlloc::Allocate((il2cpp_array_size_t)(sizeof(T) * length)));
}

template<typename T>
inline T* il2cpp_codegen_marshal_allocate()
{
    return static_cast<T*>(il2cpp::vm::MarshalAlloc::Allocate(sizeof(T)));
}

inline char* il2cpp_codegen_marshal_string(String_t* string)
{
    return il2cpp::vm::PlatformInvoke::MarshalCSharpStringToCppString((RuntimeString*)string);
}

inline void il2cpp_codegen_marshal_string_fixed(String_t* string, char* buffer, int numberOfCharacters)
{
    return il2cpp::vm::PlatformInvoke::MarshalCSharpStringToCppStringFixed((RuntimeString*)string, buffer, numberOfCharacters);
}

inline Il2CppChar* il2cpp_codegen_marshal_wstring(String_t* string)
{
    return il2cpp::vm::PlatformInvoke::MarshalCSharpStringToCppWString((RuntimeString*)string);
}

inline void il2cpp_codegen_marshal_wstring_fixed(String_t* string, Il2CppChar* buffer, int numberOfCharacters)
{
    return il2cpp::vm::PlatformInvoke::MarshalCSharpStringToCppWStringFixed((RuntimeString*)string, buffer, numberOfCharacters);
}

inline Il2CppChar* il2cpp_codegen_marshal_bstring(String_t* string)
{
    return il2cpp::vm::PlatformInvoke::MarshalCSharpStringToCppBString((RuntimeString*)string);
}

inline String_t* il2cpp_codegen_marshal_string_result(const char* value)
{
    return (String_t*)il2cpp::vm::PlatformInvoke::MarshalCppStringToCSharpStringResult(value);
}

inline String_t* il2cpp_codegen_marshal_wstring_result(const Il2CppChar* value)
{
    return (String_t*)il2cpp::vm::PlatformInvoke::MarshalCppWStringToCSharpStringResult(value);
}

inline String_t* il2cpp_codegen_marshal_bstring_result(const Il2CppChar* value)
{
    return (String_t*)il2cpp::vm::PlatformInvoke::MarshalCppBStringToCSharpStringResult(value);
}

inline void il2cpp_codegen_marshal_free_bstring(Il2CppChar* value)
{
    il2cpp::vm::PlatformInvoke::MarshalFreeBString(value);
}

inline char* il2cpp_codegen_marshal_string_builder(StringBuilder_t* stringBuilder)
{
    return il2cpp::vm::PlatformInvoke::MarshalStringBuilder((RuntimeStringBuilder*)stringBuilder);
}

inline Il2CppChar* il2cpp_codegen_marshal_wstring_builder(StringBuilder_t* stringBuilder)
{
    return il2cpp::vm::PlatformInvoke::MarshalWStringBuilder((RuntimeStringBuilder*)stringBuilder);
}

inline void il2cpp_codegen_marshal_string_builder_result(StringBuilder_t* stringBuilder, char* buffer)
{
    il2cpp::vm::PlatformInvoke::MarshalStringBuilderResult((RuntimeStringBuilder*)stringBuilder, buffer);
}

inline void il2cpp_codegen_marshal_wstring_builder_result(StringBuilder_t* stringBuilder, Il2CppChar* buffer)
{
    il2cpp::vm::PlatformInvoke::MarshalWStringBuilderResult((RuntimeStringBuilder*)stringBuilder, buffer);
}

inline Il2CppHString il2cpp_codegen_create_hstring(String_t* str)
{
    return il2cpp::vm::WindowsRuntime::CreateHString(reinterpret_cast<RuntimeString*>(str));
}

inline String_t* il2cpp_codegen_marshal_hstring_result(Il2CppHString hstring)
{
    return reinterpret_cast<String_t*>(il2cpp::vm::WindowsRuntime::HStringToManagedString(hstring));
}

inline void il2cpp_codegen_marshal_free_hstring(Il2CppHString hstring)
{
    il2cpp::vm::WindowsRuntime::DeleteHString(hstring);
}

inline void il2cpp_codegen_marshal_type_to_native(Type_t* type, Il2CppWindowsRuntimeTypeName& nativeType)
{
    return il2cpp::vm::WindowsRuntime::MarshalTypeToNative(type != NULL ? reinterpret_cast<Il2CppReflectionType*>(type)->type : NULL, nativeType);
}

inline Type_t* il2cpp_codegen_marshal_type_from_native(Il2CppWindowsRuntimeTypeName& nativeType)
{
    const Il2CppType* type = il2cpp::vm::WindowsRuntime::MarshalTypeFromNative(nativeType);
    if (type == NULL)
        return NULL;

    return il2cpp_codegen_type_get_object(type);
}

inline void il2cpp_codegen_delete_native_type(Il2CppWindowsRuntimeTypeName& nativeType)
{
    return il2cpp::vm::WindowsRuntime::DeleteNativeType(nativeType);
}

inline void il2cpp_codegen_marshal_free(void* ptr)
{
    il2cpp::vm::PlatformInvoke::MarshalFree(ptr);
}

inline Il2CppMethodPointer il2cpp_codegen_marshal_delegate(MulticastDelegate_t* d)
{
    return (Il2CppMethodPointer)il2cpp::vm::PlatformInvoke::MarshalDelegate((RuntimeDelegate*)d);
}

template<typename T>
inline T* il2cpp_codegen_marshal_function_ptr_to_delegate(Il2CppMethodPointer functionPtr, RuntimeClass* delegateType)
{
    return (T*)il2cpp::vm::PlatformInvoke::MarshalFunctionPointerToDelegate(reinterpret_cast<void*>(functionPtr), delegateType);
}

inline void il2cpp_codegen_marshal_store_last_error()
{
    il2cpp::vm::LastError::StoreLastError();
}

#if _DEBUG
struct ScopedMarshallingAllocationFrame
{
    ScopedMarshallingAllocationFrame()
    {
        il2cpp::vm::MarshalAlloc::PushAllocationFrame();
    }

    ~ScopedMarshallingAllocationFrame()
    {
        il2cpp::vm::MarshalAlloc::PopAllocationFrame();
    }
};

struct ScopedMarshallingAllocationCheck
{
    ~ScopedMarshallingAllocationCheck()
    {
        if (il2cpp::vm::MarshalAlloc::HasUnfreedAllocations())
            il2cpp::vm::Exception::Raise(il2cpp::vm::Exception::GetInvalidOperationException("Error in marshaling allocation. Some memory has been leaked."));
    }

private:
    ScopedMarshallingAllocationFrame m_AllocationFrame;
};

struct ScopedMarshalingAllocationClearer
{
    ~ScopedMarshalingAllocationClearer()
    {
        il2cpp::vm::MarshalAlloc::ClearAllTrackedAllocations();
    }

private:
    ScopedMarshallingAllocationFrame m_AllocationFrame;
};

#endif

inline void DivideByZeroCheck(int64_t denominator)
{
    if (denominator != 0)
        return;

    il2cpp::vm::Exception::RaiseDivideByZeroException();
}

inline void il2cpp_codegen_initobj(void* value, size_t size)
{
    memset(value, 0, size);
}

inline bool MethodIsStatic(const RuntimeMethod* method)
{
    return !il2cpp::vm::Method::IsInstance(method);
}

inline bool MethodHasParameters(const RuntimeMethod* method)
{
    return il2cpp::vm::Method::GetParamCount(method) != 0;
}

#define IL2CPP_RUNTIME_CLASS_INIT(klass) do { if((klass)->has_cctor && !(klass)->cctor_finished) il2cpp::vm::Runtime::ClassInit ((klass)); } while (0)

// generic sharing
#define IL2CPP_RGCTX_DATA(rgctxVar, index) (InitializedTypeInfo(rgctxVar[index].klass))
#define IL2CPP_RGCTX_SIZEOF(rgctxVar, index) (il2cpp_codegen_sizeof(IL2CPP_RGCTX_DATA(rgctxVar, index)))
#define IL2CPP_RGCTX_TYPE(rgctxVar, index) (rgctxVar[index].type)
#define IL2CPP_RGCTX_METHOD_INFO(rgctxVar, index) (rgctxVar[index].method)
#define IL2CPP_RGCTX_FIELD_INFO(klass, index) ((klass)->fields+index)

inline void ArrayElementTypeCheck(RuntimeArray* array, void* value)
{
    if (value != NULL && il2cpp::vm::Object::IsInst((RuntimeObject*)value, array->klass->element_class) == NULL)
        il2cpp_codegen_raise_exception(il2cpp_codegen_get_array_type_mismatch_exception());
}

inline const RuntimeMethod* GetVirtualMethodInfo(RuntimeObject* pThis, Il2CppMethodSlot slot)
{
    if (!pThis)
        il2cpp::vm::Exception::RaiseNullReferenceException();

    return pThis->klass->vtable[slot].method;
}

inline const RuntimeMethod* GetInterfaceMethodInfo(RuntimeObject* pThis, Il2CppMethodSlot slot, RuntimeClass* declaringInterface)
{
    if (!pThis)
        il2cpp::vm::Exception::RaiseNullReferenceException();

    return il2cpp::vm::Class::GetInterfaceInvokeDataFromVTable(pThis, declaringInterface, slot).method;
}

inline void il2cpp_codegen_initialize_method(uint32_t index)
{
    il2cpp::vm::MetadataCache::InitializeMethodMetadata(index);
}

inline bool il2cpp_codegen_type_implements_virtual_method(RuntimeClass* type, const RuntimeMethod* method)
{
    IL2CPP_ASSERT(il2cpp::vm::Class::IsValuetype(type));
    return method->klass == type;
}

inline MethodBase_t* il2cpp_codegen_get_method_object(const RuntimeMethod* method)
{
    if (method->is_inflated)
        method = il2cpp::vm::MetadataCache::GetGenericMethodDefinition(method);
    return (MethodBase_t*)il2cpp::vm::Reflection::GetMethodObject(method, method->klass);
}

inline Type_t* il2cpp_codegen_get_type(Il2CppMethodPointer getTypeFunction, String_t* typeName, const char* assemblyName)
{
    typedef Type_t* (*getTypeFuncType)(String_t*, const RuntimeMethod*);
    RuntimeString* assemblyQualifiedTypeName = il2cpp::vm::Type::AppendAssemblyNameIfNecessary((RuntimeString*)typeName, assemblyName);

    // Try to find the type using a hint about about calling assembly. If it is not found, fall back to calling GetType without the hint.
    Type_t* type = ((getTypeFuncType)getTypeFunction)((String_t*)assemblyQualifiedTypeName, NULL);
    if (type == NULL)
        return ((getTypeFuncType)getTypeFunction)(typeName, NULL);
    return type;
}

inline Type_t* il2cpp_codegen_get_type(Il2CppMethodPointer getTypeFunction, String_t* typeName, bool throwOnError, const char* assemblyName)
{
    typedef Type_t* (*getTypeFuncType)(String_t*, bool, const RuntimeMethod*);
    RuntimeString* assemblyQualifiedTypeName = il2cpp::vm::Type::AppendAssemblyNameIfNecessary((RuntimeString*)typeName, assemblyName);

    // Try to find the type using a hint about about calling assembly. If it is not found, fall back to calling GetType without the hint.
    Type_t* type = ((getTypeFuncType)getTypeFunction)((String_t*)assemblyQualifiedTypeName, throwOnError, NULL);
    if (type == NULL)
        return ((getTypeFuncType)getTypeFunction)(typeName, throwOnError, NULL);
    return type;
}

inline Type_t* il2cpp_codegen_get_type(Il2CppMethodPointer getTypeFunction, String_t* typeName, bool throwOnError, bool ignoreCase, const char* assemblyName)
{
    typedef Type_t* (*getTypeFuncType)(String_t*, bool, bool, const RuntimeMethod*);
    RuntimeString* assemblyQualifiedTypeName = il2cpp::vm::Type::AppendAssemblyNameIfNecessary((RuntimeString*)typeName, assemblyName);
    // Try to find the type using a hint about about calling assembly. If it is not found, fall back to calling GetType without the hint.

    Type_t* type = ((getTypeFuncType)getTypeFunction)((String_t*)assemblyQualifiedTypeName, throwOnError, ignoreCase, NULL);
    if (type == NULL)
        return ((getTypeFuncType)getTypeFunction)(typeName, throwOnError, ignoreCase, NULL);
    return type;
}

inline Assembly_t* il2cpp_codegen_get_executing_assembly(const RuntimeMethod* method)
{
    return (Assembly_t*)il2cpp::vm::Reflection::GetAssemblyObject(method->klass->image->assembly);
}

// Atomic

inline void* il2cpp_codegen_atomic_compare_exchange_pointer(void* volatile* dest, void* exchange, void* comparand)
{
    return il2cpp::vm::Atomic::CompareExchangePointer(dest, exchange, comparand);
}

template<typename T>
inline T* il2cpp_codegen_atomic_compare_exchange_pointer(T* volatile* dest, T* newValue, T* oldValue)
{
    return il2cpp::vm::Atomic::CompareExchangePointer(dest, newValue, oldValue);
}

// COM

inline void il2cpp_codegen_com_marshal_variant(RuntimeObject* obj, Il2CppVariant* variant)
{
    il2cpp::vm::COM::MarshalVariant(obj, variant);
}

inline RuntimeObject* il2cpp_codegen_com_marshal_variant_result(const Il2CppVariant* variant)
{
    return il2cpp::vm::COM::MarshalVariantResult(variant);
}

inline void il2cpp_codegen_com_destroy_variant(Il2CppVariant* variant)
{
    il2cpp::vm::COM::DestroyVariant(variant);
}

inline Il2CppSafeArray* il2cpp_codegen_com_marshal_safe_array(Il2CppChar type, RuntimeArray* managedArray)
{
    return il2cpp::vm::COM::MarshalSafeArray(type, managedArray);
}

inline RuntimeArray* il2cpp_codegen_com_marshal_safe_array_result(Il2CppChar variantType, RuntimeClass* type, Il2CppSafeArray* safeArray)
{
    return il2cpp::vm::COM::MarshalSafeArrayResult(variantType, type, safeArray);
}

inline Il2CppSafeArray* il2cpp_codegen_com_marshal_safe_array_bstring(RuntimeArray* managedArray)
{
    return il2cpp::vm::COM::MarshalSafeArrayBString(managedArray);
}

inline RuntimeArray* il2cpp_codegen_com_marshal_safe_array_bstring_result(RuntimeClass* type, Il2CppSafeArray* safeArray)
{
    return il2cpp::vm::COM::MarshalSafeArrayBStringResult(type, safeArray);
}

inline void il2cpp_codegen_com_destroy_safe_array(Il2CppSafeArray* safeArray)
{
    il2cpp::vm::COM::DestroySafeArray(safeArray);
}

inline void il2cpp_codegen_com_create_instance(const Il2CppGuid& clsid, Il2CppIUnknown** identity)
{
    il2cpp::vm::COM::CreateInstance(clsid, identity);
}

inline void il2cpp_codegen_com_register_rcw(Il2CppComObject* rcw)
{
    il2cpp::vm::RCW::Register(rcw);
}

template<typename T>
inline T* il2cpp_codegen_com_get_or_create_rcw_from_iunknown(Il2CppIUnknown* unknown, RuntimeClass* fallbackClass)
{
    return static_cast<T*>(il2cpp::vm::RCW::GetOrCreateFromIUnknown(unknown, fallbackClass));
}

template<typename T>
inline T* il2cpp_codegen_com_get_or_create_rcw_from_iinspectable(Il2CppIInspectable* unknown, RuntimeClass* fallbackClass)
{
    return static_cast<T*>(il2cpp::vm::RCW::GetOrCreateFromIInspectable(unknown, fallbackClass));
}

template<typename T>
inline T* il2cpp_codegen_com_get_or_create_rcw_for_sealed_class(Il2CppIUnknown* unknown, RuntimeClass* objectClass)
{
    return static_cast<T*>(il2cpp::vm::RCW::GetOrCreateForSealedClass(unknown, objectClass));
}

inline void il2cpp_codegen_il2cpp_com_object_cleanup(Il2CppComObject* rcw)
{
    il2cpp::vm::RCW::Cleanup(rcw);
}

template<typename InterfaceType>
inline InterfaceType* il2cpp_codegen_com_get_or_create_ccw(RuntimeObject* obj)
{
    return static_cast<InterfaceType*>(il2cpp::vm::CCW::GetOrCreate(obj, InterfaceType::IID));
}

inline intptr_t il2cpp_codegen_com_get_iunknown_for_object(RuntimeObject* obj)
{
    return reinterpret_cast<intptr_t>(il2cpp::vm::CCW::GetOrCreate(obj, Il2CppIUnknown::IID));
}

inline void il2cpp_codegen_com_raise_exception_if_failed(il2cpp_hresult_t hr, bool defaultToCOMException)
{
    il2cpp::vm::Exception::RaiseIfFailed(hr, defaultToCOMException);
}

inline RuntimeException* il2cpp_codegen_com_get_exception(il2cpp_hresult_t hr, bool defaultToCOMException)
{
    return il2cpp::vm::Exception::Get(hr, defaultToCOMException);
}

inline il2cpp_hresult_t il2cpp_codegen_com_handle_invalid_iproperty_conversion(const char* fromType, const char* toType)
{
    return il2cpp::vm::CCW::HandleInvalidIPropertyConversion(fromType, toType);
}

inline il2cpp_hresult_t il2cpp_codegen_com_handle_invalid_iproperty_conversion(RuntimeObject* value, const char* fromType, const char* toType)
{
    return il2cpp::vm::CCW::HandleInvalidIPropertyConversion(value, fromType, toType);
}

inline il2cpp_hresult_t il2cpp_codegen_com_handle_invalid_ipropertyarray_conversion(const char* fromArrayType, const char* fromElementType, const char* toElementType, il2cpp_array_size_t index)
{
    return il2cpp::vm::CCW::HandleInvalidIPropertyArrayConversion(fromArrayType, fromElementType, toElementType, index);
}

inline il2cpp_hresult_t il2cpp_codegen_com_handle_invalid_ipropertyarray_conversion(RuntimeObject* value, const char* fromArrayType, const char* fromElementType, const char* toElementType, il2cpp_array_size_t index)
{
    return il2cpp::vm::CCW::HandleInvalidIPropertyArrayConversion(value, fromArrayType, fromElementType, toElementType, index);
}

inline void il2cpp_codegen_store_exception_info(RuntimeException* ex, String_t* exceptionString)
{
    il2cpp::vm::Exception::StoreExceptionInfo(ex, reinterpret_cast<RuntimeString*>(exceptionString));
}

inline Il2CppIActivationFactory* il2cpp_codegen_windows_runtime_get_activation_factory(const il2cpp::utils::StringView<Il2CppNativeChar>& runtimeClassName)
{
    return il2cpp::vm::WindowsRuntime::GetActivationFactory(runtimeClassName);
}

// delegate

inline Il2CppAsyncResult* il2cpp_codegen_delegate_begin_invoke(RuntimeDelegate* delegate, void** params, RuntimeDelegate* asyncCallback, RuntimeObject* state)
{
#if NET_4_0
    return il2cpp::vm::ThreadPoolMs::DelegateBeginInvoke(delegate, params, asyncCallback, state);
#else
    return il2cpp::vm::ThreadPool::Queue(delegate, params, asyncCallback, state);
#endif
}

inline RuntimeObject* il2cpp_codegen_delegate_end_invoke(Il2CppAsyncResult* asyncResult, void **out_args)
{
#if NET_4_0
    return il2cpp::vm::ThreadPoolMs::DelegateEndInvoke(asyncResult, out_args);
#else
    return il2cpp::vm::ThreadPool::Wait(asyncResult, out_args);
#endif
}

inline bool il2cpp_codegen_delegate_has_invoker(Il2CppDelegate* delegate)
{
    return delegate->invoke_impl != NULL;
}

inline const Il2CppGenericInst* il2cpp_codegen_get_generic_class_inst(RuntimeClass* genericClass)
{
    IL2CPP_ASSERT(genericClass->generic_class);
    return genericClass->generic_class->context.class_inst;
}

inline RuntimeClass* il2cpp_codegen_inflate_generic_class(RuntimeClass* genericClassDefinition, const Il2CppGenericInst* genericInst)
{
    return il2cpp::vm::Class::GetInflatedGenericInstanceClass(genericClassDefinition, genericInst);
}

inline void* il2cpp_codegen_static_fields_for(RuntimeClass* klass)
{
    return klass->static_fields;
}

inline Il2CppMethodPointer il2cpp_codegen_get_method_pointer(const RuntimeMethod* method)
{
    return method->methodPointer;
}

inline const RuntimeType* il2cpp_codegen_method_return_type(const RuntimeMethod* method)
{
    return method->return_type;
}

inline int il2cpp_codegen_method_parameter_count(const RuntimeMethod* method)
{
    return method->parameters_count;
}

inline bool il2cpp_codegen_is_import_or_windows_runtime(const RuntimeObject *object)
{
    return object->klass->is_import_or_windows_runtime;
}

inline std::string il2cpp_codegen_format_exception(const RuntimeException* ex)
{
    return il2cpp::utils::Exception::FormatException(ex);
}

inline intptr_t il2cpp_codegen_get_com_interface_for_object(Il2CppObject* object, Type_t* type)
{
    return il2cpp::icalls::mscorlib::System::Runtime::InteropServices::Marshal::GetCCW(object, reinterpret_cast<Il2CppReflectionType*>(type));
}

inline NORETURN void il2cpp_codegen_raise_profile_exception(const RuntimeMethod* method)
{
    std::string methodName = il2cpp::vm::Method::GetFullName(method);
    il2cpp_codegen_raise_exception(il2cpp_codegen_get_not_supported_exception(methodName.c_str()));
}
