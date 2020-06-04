#pragma once
#include "os/WindowsRuntime.h"
#include "vm/Exception.h"
#include "utils/StringView.h"

struct Il2CppIActivationFactory;

namespace il2cpp
{
namespace vm
{
    class LIBIL2CPP_CODEGEN_API WindowsRuntime
    {
    public:
        static Il2CppIActivationFactory* GetActivationFactory(const utils::StringView<Il2CppNativeChar>& runtimeClassName);

        static inline void CreateHStringReference(const utils::StringView<Il2CppNativeChar>& str, Il2CppHStringHeader* header, Il2CppHString* hstring)
        {
            il2cpp_hresult_t hr = os::WindowsRuntime::CreateHStringReference(str, header, hstring);
            Exception::RaiseIfFailed(hr, false);
        }

        static inline Il2CppHString CreateHString(Il2CppString* str)
        {
            Il2CppHString result;
            il2cpp_hresult_t hr = os::WindowsRuntime::CreateHString(utils::StringView<Il2CppChar>(str->chars, str->length), &result);
            Exception::RaiseIfFailed(hr, false);
            return result;
        }

        static inline void DeleteHString(Il2CppHString hstring)
        {
            il2cpp_hresult_t hr = os::WindowsRuntime::DeleteHString(hstring);
            Exception::RaiseIfFailed(hr, false);
        }

        static inline Il2CppString* HStringToManagedString(Il2CppHString hstring)
        {
            return os::WindowsRuntime::HStringToManagedString(hstring);
        }
    };
}
}
