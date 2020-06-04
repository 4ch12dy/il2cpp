#include <cassert>
#include "mono-api.h"
#include "il2cpp-api.h"

#ifdef WINDOWS
IL2CPP_EXPORT
void* mono_jit_info_get_code_start(void* jit)
{
    return NULL;
}

IL2CPP_EXPORT
int mono_jit_info_get_code_size(void* jit)
{
    return 0;
}

IL2CPP_EXPORT
MonoJitInfo* mono_jit_info_table_find(MonoDomain * domain, void* ip)
{
    return NULL;
}

#endif

// The mono_unity_liveness functions are not preserved in the resulting UserAssembly.dylib
// on macOS unless we reference the address of one of the methods here. This one
// reference is enough to pull in all of them.
extern "C"
{
struct LivenessState;
extern void mono_unity_liveness_stop_gc_world(LivenessState* state);
}
void* unused = (void*)&mono_unity_liveness_stop_gc_world;

extern "C"
{
IL2CPP_EXPORT
void mono_jit_parse_options(int argc, char * argv[])
{
}

IL2CPP_EXPORT
int mono_parse_default_optimizations(const char* p)
{
    return 0;
}

IL2CPP_EXPORT
char* mono_pmip(void *ip)
{
    return NULL;
}

IL2CPP_EXPORT
void mono_set_defaults(int verbose_level, int32_t opts)
{
}

IL2CPP_EXPORT
void mono_unity_jit_cleanup(MonoDomain * domain)
{
}

IL2CPP_EXPORT
void mono_set_signal_chaining(bool chain)
{
}
}
