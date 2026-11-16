/* TLS support for __declspec(thread). The MSVC CRT gives this (tlssup.obj). The link uses /nodefaultlib
   and the Wine msvcr100 import lib, so the exe gives it here. */
#include <windows.h>

ULONG _tls_index = 0;

#pragma section(".tls", read, write)
#pragma section(".tls$ZZZ", read, write)
#pragma section(".CRT$XLA", read)
#pragma section(".CRT$XLZ", read)

#pragma data_seg(".tls")
char _tls_start = 0;
#pragma data_seg(".tls$ZZZ")
char _tls_end = 0;
#pragma data_seg()

__declspec(allocate(".CRT$XLA")) PIMAGE_TLS_CALLBACK __xl_a = 0;
__declspec(allocate(".CRT$XLZ")) PIMAGE_TLS_CALLBACK __xl_z = 0;

const IMAGE_TLS_DIRECTORY64 _tls_used = {
    (ULONGLONG)&_tls_start,
    (ULONGLONG)&_tls_end,
    (ULONGLONG)&_tls_index,
    (ULONGLONG)(&__xl_a + 1),
    0,
    0,
};
