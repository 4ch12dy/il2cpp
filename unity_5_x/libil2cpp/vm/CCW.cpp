#include "il2cpp-config.h"
#include "object-internals.h"
#include "class-internals.h"
#include "vm/Object.h"
#include "vm/CCW.h"
#include "vm/Class.h"
#include "vm/CachedCCWBase.h"
#include "vm/Exception.h"
#include "vm/MetadataCache.h"
#include "vm/RCW.h"

namespace il2cpp
{
namespace vm
{
    struct ManagedObject : CachedCCWBase<ManagedObject>
    {
        inline ManagedObject(Il2CppObject* obj) :
            CachedCCWBase<ManagedObject>(obj)
        {
        }

        virtual il2cpp_hresult_t STDCALL QueryInterface(const Il2CppGuid& iid, void** object) IL2CPP_OVERRIDE
        {
            if (::memcmp(&iid, &Il2CppIUnknown::IID, sizeof(Il2CppGuid)) == 0
                || ::memcmp(&iid, &Il2CppIInspectable::IID, sizeof(Il2CppGuid)) == 0
                || ::memcmp(&iid, &Il2CppIAgileObject::IID, sizeof(Il2CppGuid)) == 0)
            {
                *object = GetIdentity();
                AddRefImpl();
                return IL2CPP_S_OK;
            }

            if (::memcmp(&iid, &Il2CppIManagedObjectHolder::IID, sizeof(Il2CppGuid)) == 0)
            {
                *object = static_cast<Il2CppIManagedObjectHolder*>(this);
                AddRefImpl();
                return IL2CPP_S_OK;
            }

            if (::memcmp(&iid, &Il2CppIMarshal::IID, sizeof(Il2CppGuid)) == 0)
            {
                *object = static_cast<Il2CppIMarshal*>(this);
                AddRefImpl();
                return IL2CPP_S_OK;
            }

            *object = NULL;
            return IL2CPP_E_NOINTERFACE;
        }

        virtual il2cpp_hresult_t STDCALL GetIids(uint32_t* iidCount, Il2CppGuid** iids) IL2CPP_OVERRIDE
        {
            *iidCount = 0;
            *iids = NULL;
            return IL2CPP_S_OK;
        }
    };

    Il2CppIUnknown* CCW::CreateCCW(Il2CppObject* obj)
    {
        // check for ccw create function, which is implemented by objects that implement COM or Windows Runtime interfaces
        const Il2CppInteropData* interopData = obj->klass->interopData;
        if (interopData != NULL)
        {
            const CreateCCWFunc createCcw = interopData->createCCWFunction;

            if (createCcw != NULL)
                return createCcw(obj);
        }

        // otherwise create generic ccw object that "only" implements IUnknown, IMarshal, IInspectable, IAgileObject and IManagedObjectHolder interfaces
        void* memory = utils::Memory::Malloc(sizeof(ManagedObject));
        if (memory == NULL)
            Exception::RaiseOutOfMemoryException();
        return static_cast<Il2CppIManagedObjectHolder*>(new(memory)ManagedObject(obj));
    }
} /* namespace vm */
} /* namespace il2cpp */
