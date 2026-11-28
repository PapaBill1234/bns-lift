// aliasimpl_h.cpp: aliasimpl.h (GameDaemon PDB, 2019 + PDB).
#include "aliasimpl.h"
#include <wctype.h>

#pragma comment(linker, "/INCLUDE:?compare@ci_wchar_traits@@SAHPEB_W0_K@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x6f3310
int __cdecl ci_wchar_traits::compare(wchar_t const * _1, wchar_t const * _2, unsigned __int64 cnt)
{
    while (cnt != 0)
    {
        if (towupper(*_1) != towupper(*_2))
            return towupper(*_1) < towupper(*_2) ? -1 : 1;
        ++_1;
        ++_2;
        --cnt;
    }
    return 0;
}
