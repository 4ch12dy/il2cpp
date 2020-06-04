#include "os/MemoryMappedFile.h"
#include "os/c-api/MemoryMappedFile-c-api.h"

extern "C"
{
void* UnityPalMemoryMappedFileMap(UnityPalFileHandle* file)
{
    return il2cpp::os::MemoryMappedFile::Map(file);
}

void UnityPalMemoryMappedFileUnmap(void* address)
{
    il2cpp::os::MemoryMappedFile::Unmap(address);
}

void* UnityPalMemoryMappedFileMapWithParams(UnityPalFileHandle* file, size_t length, size_t offset)
{
    return il2cpp::os::MemoryMappedFile::Map(file, length, offset);
}

void UnityPalMemoryMappedFileUnmapWithParams(void* address, size_t length)
{
    il2cpp::os::MemoryMappedFile::Unmap(address, length);
}

void* UnityPalMemoryMappedFileMapWithFileDescriptor(int fd, size_t length, size_t offset)
{
#if IL2CPP_TARGET_POSIX
    return il2cpp::os::MemoryMappedFile::Map(fd, length, offset);
#else
    IL2CPP_ASSERT(false && "mmap with file descriptor not supported");
    return NULL;
#endif
}
}
