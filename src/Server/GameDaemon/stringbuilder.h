// stringbuilder.h: stringbuilder.cpp (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"

// PDB layout: size 0x18.
class StringBuilderW
{
public:
    __cdecl ~StringBuilderW(void);  // 0x69dd00
    bool __cdecl AppendFormat(wchar_t const *, ...);  // 0x69dd40

private:
    wchar_t* _str;      // +0x00
    int _len;           // +0x08
    int _capacity;      // +0x0C
    bool _delete;       // +0x10
};

