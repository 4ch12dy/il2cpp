#if NET_4_0

#include "il2cpp-config.h"
#include "SafeStringMarshal.h"
#include "utils/StringUtils.h"

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace Mono
{
    intptr_t SafeStringMarshal::StringToUtf8(Il2CppString* str)
    {
        std::string strobj = il2cpp::utils::StringUtils::Utf16ToUtf8(str->chars, str->length);
        size_t size = strobj.size();
        char *cstr = new char[size + 1];
        memcpy(cstr, strobj.c_str(), size);
        cstr[size] = 0;

        return reinterpret_cast<intptr_t>(cstr);
    }

    void SafeStringMarshal::GFree(intptr_t ptr)
    {
        char *cstr = (char*)ptr;
        delete cstr;
    }
} // namespace Mono
} // namespace mscorlib
} // namespace icalls
} // namespace il2cpp

#endif
