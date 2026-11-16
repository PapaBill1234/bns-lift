/* The Wine msvcr100 import lib has no export for the global operator delete(void*) (??3@YAXPEAX@Z)
   and operator new(size_t) (??2@YAPEAX_K@Z). This gives them.
   operator delete calls free, as the msvcr100 operator delete does.
   operator new calls malloc. The msvcr100 operator new also calls the new handler and throws
   std::bad_alloc when malloc fails. This version returns null. */
#include <stdlib.h>

#pragma comment(linker, "/alternatename:??3@YAXPEAX@Z=lift_operator_delete")
#pragma comment(linker, "/alternatename:??2@YAPEAX_K@Z=lift_operator_new")

void __cdecl lift_operator_delete(void* ptr)
{
    free(ptr);
}

void* __cdecl lift_operator_new(size_t size)
{
    return malloc(size);
}
