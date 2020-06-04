#include "il2cpp-config.h"
#include <memory>
#include "il2cpp-object-internals.h"
#include "il2cpp-class-internals.h"
#include "il2cpp-tabledefs.h"
#include "vm/Array.h"
#include "vm/Class.h"
#include "vm/Exception.h"
#include "vm/Field.h"
#include "vm/Runtime.h"
#include "vm/Type.h"
#include "icalls/mscorlib/System.Runtime.CompilerServices/RuntimeHelpers.h"

using namespace il2cpp::vm;

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
namespace CompilerServices
{
    int RuntimeHelpers::get_OffsetToStringData(void)
    {
        return offsetof(Il2CppString, chars);
    }

    void RuntimeHelpers::InitializeArray(Il2CppArray * array, intptr_t ptr)
    {
        FieldInfo* field_handle = (FieldInfo*)ptr;
        Il2CppClass *klass = array->klass;
        uint32_t size = Array::GetElementSize(klass);
        const Il2CppType *type = Type::GetUnderlyingType(klass->element_class->byval_arg);

        const char *field_data;

        if (Type::IsReference(type) || (type->type == IL2CPP_TYPE_VALUETYPE && (!Type::GetClass(type) || Type::GetClass(type)->has_references)))
        {
            Il2CppException *exc = Exception::GetArgumentException("array",
                    "Cannot initialize array containing references");
            Exception::Raise(exc);
        }

        if (!(field_handle->type->attrs & FIELD_ATTRIBUTE_HAS_FIELD_RVA))
        {
            Il2CppException *exc = Exception::GetArgumentException("field_handle", "Field doesn't have an RVA");
            Exception::Raise(exc);
        }

        size *= ARRAY_LENGTH_AS_INT32(array->max_length);
        field_data = Field::GetData(field_handle);

        NOT_IMPLEMENTED_ICALL_NO_ASSERT(RuntimeHelpers::InitializeArray, "Check type size");
        //int align;
        //if (size > mono_type_size (field_handle->type, &align)) {
        //  MonoException *exc = mono_get_exception_argument("field_handle",
        //      "Field not large enough to fill array");
        //  mono_raise_exception (exc);
        //}

        NOT_IMPLEMENTED_ICALL_NO_ASSERT(RuntimeHelpers::InitializeArray, "Ignoring Endianess");
        memcpy(il2cpp_array_addr(array, char, 0), field_data, size);
    }

    Il2CppObject* RuntimeHelpers::GetObjectValue(Il2CppObject* obj)
    {
        NOT_SUPPORTED_IL2CPP(RuntimeHelpers::GetObjectValue, "This icall is not supported by il2cpp.");

        return 0;
    }

    void RuntimeHelpers::RunClassConstructor(intptr_t typeIntPtr)
    {
        const Il2CppType* type = reinterpret_cast<const Il2CppType*>(typeIntPtr);
        IL2CPP_CHECK_ARG_NULL(type);

        Il2CppClass* klass = Class::FromIl2CppType(type);
        //MONO_CHECK_ARG(handle, klass);

        il2cpp::vm::Runtime::ClassInit(klass);
    }

    void RuntimeHelpers::RunModuleConstructor(intptr_t module)
    {
        NOT_SUPPORTED_IL2CPP(RuntimeHelpers::RunModuleConstructor, "This icall is not supported by il2cpp.");
    }

#if NET_4_0
    bool RuntimeHelpers::SufficientExecutionStack()
    {
        return true;
    }

#endif
} /* namespace CompilerServices */
} /* namespace Runtime */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
