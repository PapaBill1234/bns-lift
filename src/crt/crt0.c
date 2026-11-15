/* crt0: process entry point for lift exes (msvcr100 from Wine).
 * mainCRTStartup: set app type, get argc/argv, run C and C++ static init,
 * then exit(main(argc, argv, envp)). exit runs the atexit handlers
 * (static destructors that clang-cl registers with atexit). */
#include <corecrt_startup.h>
#include <stdlib.h>

_ACRTIMP void __cdecl _initterm(_PVFV *first, _PVFV *last);
_ACRTIMP int  __cdecl _initterm_e(_PIFV *first, _PIFV *last);

int __cdecl main(int argc, char **argv, char **envp);

/* The compiler references _fltused when the code uses floating point. */
int _fltused = 0x9875;

/* Section markers. The linker sorts .CRT$X?? by name: XIA < XIU < XIZ, XCA < XCU < XCZ.
 * The compiler puts C++ static initializers in .CRT$XCU. */
#pragma section(".CRT$XIA", long, read)
#pragma section(".CRT$XIZ", long, read)
#pragma section(".CRT$XCA", long, read)
#pragma section(".CRT$XCZ", long, read)

__declspec(allocate(".CRT$XIA")) _PIFV __xi_a[] = { 0 };
__declspec(allocate(".CRT$XIZ")) _PIFV __xi_z[] = { 0 };
__declspec(allocate(".CRT$XCA")) _PVFV __xc_a[] = { 0 };
__declspec(allocate(".CRT$XCZ")) _PVFV __xc_z[] = { 0 };

/* msvcr100.dll does not export atexit (the MSVC CRT puts it in the static lib).
 * Register the handler with _onexit, which msvcr100 exports. exit runs it. */
int __cdecl atexit(void (__cdecl *func)(void))
{
    return _onexit((_onexit_t)func) ? 0 : -1;
}

int __cdecl mainCRTStartup(void)
{
    int argc = 0;
    char **argv = 0;
    char **envp = 0;
    int newmode = 0;

    _set_app_type(_crt_console_app);
    __getmainargs(&argc, &argv, &envp, 0, &newmode);

    /* C init. The NULL entries are skipped. */
    if (_initterm_e(__xi_a, __xi_z) != 0)
        exit(255);
    /* C++ static init. */
    _initterm(__xc_a, __xc_z);

    exit(main(argc, argv, envp));
    return 0;
}
