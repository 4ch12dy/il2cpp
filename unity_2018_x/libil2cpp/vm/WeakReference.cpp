#include "il2cpp-config.h"
#include "gc/GCHandle.h"
#include "utils/Memory.h"
#include "vm/Atomic.h"
#include "vm/CCW.h"
#include "vm/ScopedThreadAttacher.h"
#include "WeakReference.h"

using namespace il2cpp::vm;

il2cpp_hresult_t WeakReference::Create(Il2CppObject* managedObject, Il2CppIWeakReference** result)
{
    void* memory = utils::Memory::Malloc(sizeof(WeakReference));
    if (memory == NULL)
        return IL2CPP_E_OUTOFMEMORY;

    *result = new(memory)WeakReference(managedObject);
    return IL2CPP_S_OK;
}

WeakReference::WeakReference(Il2CppObject* managedObject) :
    m_GCHandle(gc::GCHandle::NewWeakref(managedObject, false)),
    m_RefCount(1)
{
}

il2cpp_hresult_t STDCALL WeakReference::QueryInterface(const Il2CppGuid& iid, void** object)
{
    if (memcmp(&iid, &Il2CppIUnknown::IID, sizeof(Il2CppGuid)) == 0 ||
        memcmp(&iid, &Il2CppIWeakReference::IID, sizeof(Il2CppGuid)) == 0)
    {
        AddRef();
        *object = static_cast<Il2CppIWeakReference*>(this);
        return IL2CPP_S_OK;
    }

    return IL2CPP_E_NOINTERFACE;
}

uint32_t STDCALL WeakReference::AddRef()
{
    return Atomic::Increment(&m_RefCount);
}

uint32_t STDCALL WeakReference::Release()
{
    const uint32_t refCount = Atomic::Decrement(&m_RefCount);
    if (refCount == 0)
    {
        this->~WeakReference();
        utils::Memory::Free(this);
    }

    return refCount;
}

il2cpp_hresult_t STDCALL WeakReference::Resolve(const Il2CppGuid& iid, Il2CppIInspectable** object)
{
    ScopedThreadAttacher managedThreadAttached;

    Il2CppObject* managedObject = gc::GCHandle::GetTarget(m_GCHandle);
    if (managedObject == NULL)
    {
        *object = NULL;
        return IL2CPP_S_OK;
    }

    try
    {
        *object = static_cast<Il2CppIInspectable*>(CCW::GetOrCreate(managedObject, iid));
    }
    catch (Il2CppExceptionWrapper& ex)
    {
        return ex.ex->hresult;
    }

    return IL2CPP_S_OK;
}
