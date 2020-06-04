#include "mono-structs.h"
#include "os/c-api/il2cpp-config-platforms.h"
#include "os/c-api/Allocator.h"

GPtrArray* void_ptr_array_to_gptr_array(const VoidPtrArray& array)
{
    GPtrArray *pRetVal;

    pRetVal = (GPtrArray*)Allocator::Allocate(sizeof(GPtrArray));

    pRetVal->len = (unsigned int)array.size();
    if (pRetVal->len > 0)
    {
        size_t numBytes = sizeof(void*) * pRetVal->len;
        pRetVal->pdata = Allocator::Allocate(numBytes);
        memcpy(pRetVal->pdata, array.data(), numBytes);
    }
    else
    {
        pRetVal->pdata = NULL;
    }

    return pRetVal;
}

GPtrArray* empty_gptr_array()
{
    GPtrArray *pRetVal = (GPtrArray*)Allocator::Allocate(sizeof(GPtrArray));
    pRetVal->len = 0;
    pRetVal->pdata = NULL;
    return pRetVal;
}

void free_gptr_array(GPtrArray *pArray)
{
    if (!pArray)
        return;

    if (pArray->pdata)
    {
        IL2CPP_FREE(pArray->pdata);
        pArray->pdata = NULL;
    }

    IL2CPP_FREE(pArray);
}
