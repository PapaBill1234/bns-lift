/* Bridge from the narrow main (crt0.c calls it) to wmain. The servers use wmain.
 * The wide arguments come from __wgetmainargs (msvcr100). */
#include <wchar.h>

typedef struct
{
    int newmode;
} lift_startupinfo;

__declspec(dllimport) int __cdecl __wgetmainargs(int* argc, wchar_t*** argv, wchar_t*** envp, int doWildCard,
                                                 lift_startupinfo* startInfo);

int __cdecl wmain(int argc, wchar_t** argv);

int __cdecl main(int argc, char** argv, char** envp)
{
    int wargc = 0;
    wchar_t** wargv = 0;
    wchar_t** wenvp = 0;
    lift_startupinfo startInfo;
    (void)argc;
    (void)argv;
    (void)envp;
    startInfo.newmode = 0;
    __wgetmainargs(&wargc, &wargv, &wenvp, 0, &startInfo);
    return wmain(wargc, wargv);
}
