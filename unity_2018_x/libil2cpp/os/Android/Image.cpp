#include "il2cpp-config.h"

#if IL2CPP_TARGET_ANDROID

#include <stdio.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <link.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <vector>
#include <string>

namespace il2cpp
{
namespace os
{
namespace Image
{
    static void* s_ManagedSectionStart = NULL;
    static void* s_ManagedSectionEnd = NULL;

    void* GetImageBase()
    {
        Dl_info info;
        void* const anySymbol = reinterpret_cast<void*>(&GetImageBase);
        if (dladdr(anySymbol, &info))
            return info.dli_fbase;
        else
            return NULL;
    }

#if IL2CPP_SIZEOF_VOID_P == 8
    typedef Elf64_Addr elf_address_t;
    typedef uint64_t elf_section_size_t;
    typedef Elf64_Ehdr elf_header_t;
    typedef Elf64_Shdr elf_section_header_t;
#else
    typedef Elf32_Addr elf_address_t;
    typedef uint32_t elf_section_size_t;
    typedef Elf32_Ehdr elf_header_t;
    typedef Elf32_Shdr elf_section_header_t;
#endif

    struct ManagedSectionData
    {
        elf_address_t addressOffsetFromBase;
        elf_section_size_t sectionSize;
    };

    struct MemoryMappedExecutable
    {
        MemoryMappedExecutable(const char* path)
        {
            int fd = open(path, O_RDONLY);
            IL2CPP_ASSERT(fd != -1);

            struct stat sb;
            int result = fstat(fd, &sb);
            IL2CPP_ASSERT(result == 0);
            NO_UNUSED_WARNING(result);
            size = sb.st_size;

            data = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
            IL2CPP_ASSERT(data != (void*)-1);
        }

        ~MemoryMappedExecutable()
        {
            int result = munmap(data, size);
            IL2CPP_ASSERT(result == 0);
            NO_UNUSED_WARNING(result);
        }

        void* data;
        size_t size;
    };

    const int stopSearch = 1;
    const int continueSearch = 0;

    static int FindManagedCodeSectionInElfBinary(const char* path, ManagedSectionData* sectionData)
    {
        // Some files may not be possible to read, filter the candidates by extension first
        if (strstr(path, ".dex") != NULL)
            return continueSearch;

        // Load the binary as a read-only memory mapped file
        MemoryMappedExecutable executable(path);

        // Make sure this is really an ELF binary
        if (executable.size < 4 || memcmp(executable.data, "\177ELF", 4))
            return continueSearch;

        // Process the ELF binary headers
        // There is a section in the binary which lists the names of all of the other sections.
        // Find that section name table, then iterate each section, looking for a name
        // that matches the name IL2CPP gives to the generated code. Once we find that section,
        // get its address offset and size, then stop looking.
        elf_header_t* elfHeader = (elf_header_t*)executable.data;
        elf_section_header_t* sectionHeaders = (elf_section_header_t*)((uint8_t*)executable.data + elfHeader->e_shoff);

        uint16_t indexOfSectionNameTable = elfHeader->e_shstrndx;
        elf_section_header_t* sectionNameTableSectionHeader = &sectionHeaders[indexOfSectionNameTable];

        const char* sectionNames = (char*)executable.data + sectionNameTableSectionHeader->sh_offset;

        int numberOfSectionheaders = elfHeader->e_shnum;
        for (int i = 0; i < numberOfSectionheaders; ++i)
        {
            uint32_t sectionNameIndex = sectionHeaders[i].sh_name;
            const char* sectionName = sectionNames + sectionNameIndex;
            if (strstr(sectionName, IL2CPP_BINARY_SECTION_NAME) != NULL)
            {
                sectionData->addressOffsetFromBase = sectionHeaders[i].sh_addr;
                sectionData->sectionSize = sectionHeaders[i].sh_size;
                return stopSearch;
            }
        }

        return continueSearch;
    }

    static bool IsLibraryWhichMightHaveManagedCode(const char* name)
    {
        return strstr(name, "libil2cpp") != NULL || strstr(name, "test") != NULL;
    }

#if __ANDROID_API__ >= 21
    static int FindManagedCodeSection(struct dl_phdr_info *info, size_t unused, void *data)
    {
        if (info->dlpi_name != NULL && IsLibraryWhichMightHaveManagedCode(info->dlpi_name))
            return FindManagedCodeSectionInElfBinary(info->dlpi_name, (ManagedSectionData*)data);

        return continueSearch;
    }

#endif

    static char* trim(char* input)
    {
        char *end;

        while (isspace((unsigned char)*input))
            input++;

        if (*input == 0)
            return input;

        end = input + strlen(input) - 1;
        while (end > input && isspace((unsigned char)*end))
            end--;

        end[1] = '\0';

        return input;
    }

    static void FindManagedCodeSectionInAllLoadedLibraries(ManagedSectionData* sectionData)
    {
        const char* mapsFilePath = "/proc/self/maps";
        FILE* mapsFile = fopen(mapsFilePath, "r");
        IL2CPP_ASSERT(mapsFile != NULL);

        std::vector<std::string> libraryNames;
        char line[255];
        while (fgets(line, 255, mapsFile))
        {
            if (IsLibraryWhichMightHaveManagedCode(line))
            {
                char* libraryPath = strstr(line, "    ");
                if (libraryPath != NULL)
                {
                    char* trimmedLibraryPath = trim(libraryPath);
                    if (trimmedLibraryPath[0] == '/')
                        libraryNames.push_back(trimmedLibraryPath);
                }
            }
        }

        fclose(mapsFile);

        // The current executable is last in the maps file. It is most likely to have the managed code
        // section, so iterate the maps file in reverse, since we break out when we find it.
        for (std::vector<std::string>::reverse_iterator i = libraryNames.rbegin(); i != libraryNames.rend(); ++i)
        {
            int result = FindManagedCodeSectionInElfBinary(i->c_str(), sectionData);
            if (result == stopSearch)
                break;
        }
    }

    static void InitializeManagedSection()
    {
        // Process all loaded modules, looking for the IL2CPP managed code section
        ManagedSectionData sectionData = {};

#if __ANDROID_API__ >= 21
        dl_iterate_phdr(FindManagedCodeSection, &sectionData);
#else
        FindManagedCodeSectionInAllLoadedLibraries(&sectionData);
#endif

        if (sectionData.sectionSize != 0)
        {
            s_ManagedSectionStart = (char*)GetImageBase() + sectionData.addressOffsetFromBase;
            s_ManagedSectionEnd = (void*)((char*)s_ManagedSectionStart + sectionData.sectionSize);
        }
    }

    void Initialize()
    {
        InitializeManagedSection();
    }

    bool IsInManagedSection(void* ip)
    {
        IL2CPP_ASSERT(s_ManagedSectionStart != NULL && s_ManagedSectionEnd != NULL);
        return s_ManagedSectionStart <= ip && ip <= s_ManagedSectionEnd;
    }
}
}
}

#endif
