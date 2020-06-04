#pragma once

#include "il2cpp-config.h"
#include "il2cpp-object-internals.h"
#include "mono-api.h"
#include "utils/StringView.h"

struct PInvokeArguments
{
    const il2cpp::utils::StringView<Il2CppNativeChar> moduleName;
    const il2cpp::utils::StringView<char> entryPoint;
    Il2CppCallConvention callingConvention;
    Il2CppCharSet charSet;
    int parameterSize;
    bool isNoMangle;    // Says whether P/Invoke should append to function name 'A'/'W' according to charSet.
};

namespace mono
{
namespace vm
{
    class PlatformInvoke
    {
    public:
        static char* MarshalCSharpStringToCppString(MonoString* managedString);
        static void MarshalCSharpStringToCppStringFixed(MonoString* managedString, char* buffer, int numberOfCharacters);
        static mono_unichar2* MarshalCSharpStringToCppWString(MonoString* managedString);
        static void MarshalCSharpStringToCppWStringFixed(MonoString* managedString, mono_unichar2* buffer, int numberOfCharacters);

        static MonoString* MarshalCppStringToCSharpStringResult(const char* value);
        static MonoString* MarshalCppWStringToCSharpStringResult(const mono_unichar2* value);

        static char* MarshalStringBuilder(MonoStringBuilder* stringBuilder);
        static mono_unichar2* MarshalWStringBuilder(MonoStringBuilder* stringBuilder);

        static void MarshalStringBuilderResult(MonoStringBuilder* stringBuilder, char* buffer);
        static void MarshalWStringBuilderResult(MonoStringBuilder* stringBuilder, mono_unichar2* buffer);

        static intptr_t MarshalDelegate(MonoDelegate* d);
        static Il2CppDelegate* MarshalFunctionPointerToDelegate(void* functionPtr, MonoClass* delegateType);

        template<typename T>
        static T* MarshalAllocateStringBuffer(size_t numberOfCharacters)
        {
            MonoError unused;
            return (T*)mono_marshal_alloc((unsigned long)numberOfCharacters * sizeof(T), &unused);
        }
    };
} // namespace vm
} // namespace mono
