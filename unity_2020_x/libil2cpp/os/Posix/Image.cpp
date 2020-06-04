#include "il2cpp-config.h"

#if (IL2CPP_TARGET_JAVASCRIPT || IL2CPP_TARGET_LINUX || IL2CPP_TARGET_LUMIN && !IL2CPP_TINY_WITHOUT_DEBUGGER) || IL2CPP_TARGET_ANDROID

#if IL2CPP_TARGET_JAVASCRIPT
#include <emscripten/emscripten.h>
#else
#include <dlfcn.h>
#endif

#if IL2CPP_ENABLE_NATIVE_INSTRUCTION_POINTER_EMISSION && (IL2CPP_TARGET_ANDROID || IL2CPP_TARGET_LINUX)
#include <elf.h>

#if __x86_64__ || __aarch64__
#  define ElfW(type) Elf64_##type
#else
#  define ElfW(type) Elf32_##type
#endif

#endif

#include <cstdio>

extern char __start_il2cpp;
extern char __stop_il2cpp;

namespace il2cpp
{
namespace os
{
namespace Image
{
    static char* s_ManagedSectionStart = NULL;
    static char* s_ManagedSectionEnd = NULL;

    void* GetImageBase()
    {
#if IL2CPP_TARGET_JAVASCRIPT
        emscripten_log(EM_LOG_NO_PATHS | EM_LOG_CONSOLE | EM_LOG_ERROR | EM_LOG_JS_STACK, "Warning: libil2cpp/os/Posix/Image.cpp: GetImageBase() called, but dynamic libraries are not available.");
        return NULL;
#else
        Dl_info info;
        void* const anySymbol = reinterpret_cast<void*>(&GetImageBase);
        if (dladdr(anySymbol, &info))
            return info.dli_fbase;
        else
            return NULL;
#endif
    }

    static IL2CPP_METHOD_ATTR void NoGeneratedCodeWorkaround()
    {
    }

    void InitializeManagedSection()
    {
        NoGeneratedCodeWorkaround();
        s_ManagedSectionStart = &__start_il2cpp;
        s_ManagedSectionEnd = &__stop_il2cpp;
    }

    void Initialize()
    {
#if IL2CPP_PLATFORM_SUPPORTS_CUSTOM_SECTIONS
        InitializeManagedSection();
#endif
    }

#if IL2CPP_ENABLE_NATIVE_INSTRUCTION_POINTER_EMISSION
#if IL2CPP_TARGET_ANDROID || IL2CPP_TARGET_LINUX
    void GetELFImageBuildID(char* build_id)
    {
        size_t imageBase = (size_t)GetImageBase();
        ElfW(Ehdr) * ehdr = (ElfW(Ehdr) *)imageBase;
        ElfW(Phdr) * phdr = (ElfW(Phdr) *)(imageBase + ehdr->e_phoff);

        for (int i = 0; i < ehdr->e_phnum; i++)
        {
            if (phdr[i].p_type == PT_NOTE)
            {
                size_t nhdr_ptr = phdr[i].p_offset + imageBase;
                int j = 0;
                while (nhdr_ptr < imageBase + phdr[i].p_offset + phdr[i].p_memsz)
                {
                    ElfW(Nhdr) * nhdr = (ElfW(Nhdr) *)nhdr_ptr;
                    if (nhdr->n_type == NT_GNU_BUILD_ID)
                    {
                        char* image_build_id = (char *)((size_t)nhdr + sizeof(ElfW(Nhdr)) + nhdr->n_namesz);
                        for (int j = 0; j < nhdr->n_descsz; j++)
                        {
                            snprintf(&build_id[j * 2], 3, "%02x", image_build_id[j]);
                        }
                        return;
                    }
                    nhdr_ptr += sizeof(ElfW(Nhdr)) + nhdr->n_descsz + nhdr->n_namesz;
                }
                break;
            }
        }
    }

#endif

    void GetImageUUID(char* uuid)
    {
#if IL2CPP_TARGET_ANDROID || IL2CPP_TARGET_LINUX
        GetELFImageBuildID(uuid);
#else
#error Implement GetImageUUID for this platform
#endif
    }

#endif

#if IL2CPP_PLATFORM_SUPPORTS_CUSTOM_SECTIONS
    bool IsInManagedSection(void* ip)
    {
        IL2CPP_ASSERT(s_ManagedSectionStart != NULL && s_ManagedSectionEnd != NULL);
        return s_ManagedSectionStart <= ip && ip <= s_ManagedSectionEnd;
    }

#endif
}
}
}

#endif
