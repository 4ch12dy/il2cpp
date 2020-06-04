#pragma once

#include "File-c-api.h"

#if defined(__cplusplus)
extern "C"
{
#endif

void* UnityPalMemoryMappedFileMap(UnityPalFileHandle* file);
void UnityPalMemoryMappedFileUnmap(void* address);

void* UnityPalMemoryMappedFileMapWithParams(UnityPalFileHandle* file, size_t length, size_t offset);
void* UnityPalMemoryMappedFileMapWithFileDescriptor(int fd, size_t length, size_t offset);
void UnityPalMemoryMappedFileUnmapWithParams(void* address, size_t length);

#if defined(__cplusplus)
}
#endif
