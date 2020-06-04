#pragma once

struct String_t;
struct Type_t;
struct Exception_t;
struct StringBuilder_t;
struct MulticastDelegate_t;
struct MethodBase_t;
struct Assembly_t;

#if RUNTIME_MONO
extern "C"
{
#include <mono/metadata/class.h>
#include <mono/metadata/image.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/object.h>
#include <mono/metadata/object-internals.h>
}

typedef MonoClass RuntimeClass;
typedef MonoMethod RuntimeMethod;
typedef MonoClassField RuntimeField;
typedef MonoType RuntimeType;
typedef MonoObject RuntimeObject;
typedef MonoImage RuntimeImage;
typedef MonoException RuntimeException;
typedef MonoArray RuntimeArray;
typedef MonoAssembly RuntimeAssembly;
typedef MonoString RuntimeString;
typedef MonoStringBuilder RuntimeStringBuilder;
typedef MonoDelegate RuntimeDelegate;
#include "il2cpp-codegen-mono.h"


#else
struct TypeInfo;
struct MethodInfo;
struct FieldInfo;
struct Il2CppType;
typedef Il2CppClass RuntimeClass;
typedef MethodInfo RuntimeMethod;
typedef FieldInfo RuntimeField;
typedef Il2CppType RuntimeType;
typedef Il2CppObject RuntimeObject;
typedef Il2CppImage RuntimeImage;
typedef Il2CppException RuntimeException;
typedef Il2CppArray RuntimeArray;
typedef Il2CppAssembly RuntimeAssembly;
typedef Il2CppString RuntimeString;
struct Il2CppStringBuilder;
typedef Il2CppStringBuilder RuntimeStringBuilder;
typedef Il2CppDelegate RuntimeDelegate;
#include "il2cpp-codegen-il2cpp.h"
#endif
