#pragma once

#include "il2cpp-config.h"

// This file is a compile-time abstraction for VM support needed by code in the os and utils namespaces that is used by both the
// libil2cpp and the libmono runtimes. Code in those namespaces should never depend up on the vm namespace directly.

#if defined(RUNTIME_MONO)
    #include "mono-api.h"
    #include <cassert>
    #define IL2CPP_VM_RAISE_EXCEPTION(exception) mono_raise_exception(exception)
    #define IL2CPP_VM_RAISE_COM_EXCEPTION(hresult, defaultToCOMException) assert(false && "COM exceptions are not implemented yet.")
    #define IL2CPP_VM_STRING_NEW_LEN(value, length) mono_string_new_len(mono_domain_get(), value, length);
    #define IL2CPP_VM_NOT_SUPPORTED(func, reason) mono_raise_exception(mono_get_exception_not_supported(NOTSUPPORTEDICALLMESSAGE ("IL2CPP", #func, #reason)))
typedef MonoString VmString;
#else // Assume the libil2cpp runtime
    #include "vm/Exception.h"
    #include "vm/String.h"
    #define IL2CPP_VM_RAISE_EXCEPTION(exception) il2cpp::vm::Exception::Raise(exception)
    #define IL2CPP_VM_RAISE_COM_EXCEPTION(hresult, defaultToCOMException) il2cpp::vm::Exception::Raise(hresult, defaultToCOMException)
    #define IL2CPP_VM_STRING_NEW_LEN(value, length) il2cpp::vm::String::NewLen(value, length)
    #define IL2CPP_VM_NOT_SUPPORTED(func, reason) NOT_SUPPORTED_IL2CPP(func, reason)
typedef Il2CppString VmString;
#endif
