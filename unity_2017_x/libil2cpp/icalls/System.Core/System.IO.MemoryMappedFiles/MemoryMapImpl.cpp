#if NET_4_0
#include "il2cpp-config.h"
#include "MemoryMapImpl.h"

namespace il2cpp
{
namespace icalls
{
namespace System
{
namespace Core
{
namespace System
{
namespace IO
{
namespace MemoryMappedFiles
{
    bool MemoryMapImpl::Unmap(intptr_t mmap_handle)
    {
        NOT_IMPLEMENTED_ICALL(MemoryMapImpl::Unmap);
        IL2CPP_UNREACHABLE;
        return false;
    }

    int32_t MemoryMapImpl::MapInternal(intptr_t handle, int64_t offset, int64_t* size, int32_t access, intptr_t* mmap_handle, intptr_t* base_address)
    {
        NOT_IMPLEMENTED_ICALL(MemoryMapImpl::MapInternal);
        IL2CPP_UNREACHABLE;
        return 0;
    }

    intptr_t MemoryMapImpl::OpenFileInternal(Il2CppString* path, int32_t mode, Il2CppString* mapName, int64_t* capacity, int32_t access, int32_t options, int32_t* error)
    {
        NOT_IMPLEMENTED_ICALL(MemoryMapImpl::OpenFileInternal);
        IL2CPP_UNREACHABLE;
        return intptr_t();
    }

    intptr_t MemoryMapImpl::OpenHandleInternal(intptr_t handle, Il2CppString* mapName, int64_t* capacity, int32_t access, int32_t options, int32_t* error)
    {
        NOT_IMPLEMENTED_ICALL(MemoryMapImpl::OpenHandleInternal);
        IL2CPP_UNREACHABLE;
        return intptr_t();
    }

    void MemoryMapImpl::CloseMapping(intptr_t handle)
    {
        NOT_IMPLEMENTED_ICALL(MemoryMapImpl::CloseMapping);
        IL2CPP_UNREACHABLE;
    }

    void MemoryMapImpl::ConfigureHandleInheritability(intptr_t handle, int32_t inheritability)
    {
        NOT_IMPLEMENTED_ICALL(MemoryMapImpl::ConfigureHandleInheritability);
        IL2CPP_UNREACHABLE;
    }

    void MemoryMapImpl::Flush(intptr_t file_handle)
    {
        NOT_IMPLEMENTED_ICALL(MemoryMapImpl::Flush);
        IL2CPP_UNREACHABLE;
    }
} // namespace MemoryMappedFiles
} // namespace IO
} // namespace System
} // namespace Core
} // namespace System
} // namespace icalls
} // namespace il2cpp
#endif
