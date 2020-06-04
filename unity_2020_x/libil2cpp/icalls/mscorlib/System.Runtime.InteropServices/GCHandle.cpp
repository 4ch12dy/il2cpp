#include "il2cpp-config.h"
#include "il2cpp-class-internals.h"
#include "icalls/mscorlib/System.Runtime.InteropServices/GCHandle.h"
#include "gc/GCHandle.h"
#include "vm/Exception.h"

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
namespace Runtime
{
namespace InteropServices
{
    bool GCHandle::CheckCurrentDomain(int32_t handle)
    {
        return true; // il2cpp doesn't support multiple domains
    }

    void GCHandle::FreeHandle(int32_t handle)
    {
        gc::GCHandle::Free(handle);
    }

// Returns -2 if gchandle is not pinned
    intptr_t GCHandle::GetAddrOfPinnedObject(int32_t handle)
    {
        gc::GCHandleType type = gc::GCHandle::GetHandleType(handle);

        if (type != gc::HANDLE_PINNED)
            return reinterpret_cast<intptr_t>(reinterpret_cast<uint8_t*>(-2)); // mscorlib on managed land expects us to return "-2" as IntPtr if this condition occurs

        Il2CppObject* obj = gc::GCHandle::GetTarget(handle);
        if (obj == NULL)
            return 0;

        ptrdiff_t offset;

        if (obj->klass->rank > 0)
        {
            // Pointer to first array element
            offset = kIl2CppSizeOfArray;
        }
        else if (obj->klass->byval_arg.type == IL2CPP_TYPE_STRING)
        {
            // Pointer to first character
            offset = offsetof(Il2CppString, chars);
        }
        else
        {
            // Pointer to struct in boxed object
            offset = sizeof(Il2CppObject);
        }

        return reinterpret_cast<intptr_t>((reinterpret_cast<uint8_t*>(obj) + offset));
    }

    Il2CppObject* GCHandle::GetTarget(int32_t handle)
    {
        return gc::GCHandle::GetTarget(handle);
    }

    static inline bool IsObjectPinnable(Il2CppObject* obj)
    {
        if (obj == NULL)
            return true;

        Il2CppClass* klass = obj->klass;
        if (klass->byval_arg.type == IL2CPP_TYPE_ARRAY || klass->byval_arg.type == IL2CPP_TYPE_SZARRAY)
        {
            Il2CppClass* elementClass = klass->element_class;
            return elementClass->is_blittable ||
                elementClass->byval_arg.type == IL2CPP_TYPE_CHAR || // while "char" and "bool" are not blittable, we can still pin their arrays
                elementClass->byval_arg.type == IL2CPP_TYPE_BOOLEAN;
        }

        if (klass->byval_arg.type == IL2CPP_TYPE_CHAR  || klass->byval_arg.type == IL2CPP_TYPE_BOOLEAN || klass->byval_arg.type == IL2CPP_TYPE_STRING)
            return true;

        return klass->is_blittable;
    }

    int32_t GCHandle::GetTargetHandle(Il2CppObject* obj, int32_t handle, int32_t type)
    {
        if (type == gc::HANDLE_PINNED && !IsObjectPinnable(obj))
        {
            Il2CppException* ex = vm::Exception::GetArgumentException(NULL, "Object contains non-primitive or non-blittable data.");
            vm::Exception::Raise(ex);
        }

        return gc::GCHandle::GetTargetHandle(obj, handle, type);
    }
} /* namespace InteropServices */
} /* namespace Runtime */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
