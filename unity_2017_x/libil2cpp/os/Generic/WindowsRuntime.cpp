#include "il2cpp-config.h"
#include "il2cpp-vm-support.h"
#include "os/WindowsRuntime.h"
#include "vm/Exception.h"

#if IL2CPP_USE_GENERIC_WINDOWSRUNTIME

namespace il2cpp
{
namespace os
{
    il2cpp_hresult_t WindowsRuntime::GetActivationFactory(Il2CppHString className, Il2CppIActivationFactory** activationFactory)
    {
        NO_UNUSED_WARNING(className);
        NO_UNUSED_WARNING(activationFactory);
        IL2CPP_ASSERT(className != NULL);
        IL2CPP_ASSERT(activationFactory != NULL);
        return IL2CPP_REGDB_E_CLASSNOTREG;
    }

    il2cpp_hresult_t WindowsRuntime::CreateHStringReference(const utils::StringView<Il2CppNativeChar>& str, Il2CppHStringHeader* header, Il2CppHString* hstring)
    {
        NO_UNUSED_WARNING(str);
        NO_UNUSED_WARNING(header);
        NO_UNUSED_WARNING(hstring);
        IL2CPP_ASSERT(header != NULL);
        IL2CPP_ASSERT(hstring != NULL);
        return IL2CPP_COR_E_PLATFORMNOTSUPPORTED;
    }

    il2cpp_hresult_t WindowsRuntime::CreateHString(const utils::StringView<Il2CppChar>& str, Il2CppHString* hstring)
    {
        NO_UNUSED_WARNING(str);
        NO_UNUSED_WARNING(hstring);
        return IL2CPP_COR_E_PLATFORMNOTSUPPORTED;
    }

    il2cpp_hresult_t WindowsRuntime::DeleteHString(Il2CppHString hstring)
    {
        NO_UNUSED_WARNING(hstring);
        return IL2CPP_COR_E_PLATFORMNOTSUPPORTED;
    }

    const Il2CppChar* WindowsRuntime::GetHStringBuffer(Il2CppHString hstring, uint32_t* length)
    {
        NO_UNUSED_WARNING(hstring);
        NO_UNUSED_WARNING(length);
        IL2CPP_VM_RAISE_COM_EXCEPTION(IL2CPP_COR_E_PLATFORMNOTSUPPORTED, false);
        return NULL;
    }

    Il2CppString* WindowsRuntime::HStringToManagedString(Il2CppHString hstring)
    {
        NO_UNUSED_WARNING(hstring);
        IL2CPP_VM_RAISE_COM_EXCEPTION(IL2CPP_COR_E_PLATFORMNOTSUPPORTED, false);
        return NULL;
    }

    Il2CppIRestrictedErrorInfo* WindowsRuntime::GetRestrictedErrorInfo()
    {
        return NULL;
    }

    void WindowsRuntime::OriginateLanguageException(Il2CppException* ex, Il2CppString* exceptionString)
    {
        NO_UNUSED_WARNING(ex);
        NO_UNUSED_WARNING(exceptionString);
    }

    void WindowsRuntime::EnableErrorReporting()
    {
    }
}
}

#endif
