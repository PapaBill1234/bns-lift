/* The Wine msvcr100 import lib has no export for the global operator delete(void*) (??3@YAXPEAX@Z).
   This gives it. It calls free, as the msvcr100 operator delete does. */
#include <stdlib.h>

#pragma comment(linker, "/alternatename:??3@YAXPEAX@Z=lift_operator_delete")

void __cdecl lift_operator_delete(void* ptr)
{
    free(ptr);
}
