// tableimpl.h: tableimpl.cpp, tableimpl.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DrDataTableImpl
{
public:
    virtual __cdecl ~DrDataTableImpl(void);  // 0x6f7430
    virtual void __cdecl UseLegacyElHeader(bool);  // 0x6fd290
    virtual ::DrEl * __cdecl ReferenceCopiedEl(::DrEl *);  // 0x6feec0
    virtual ::DrEl *const __cdecl Find(wchar_t const *, ::DrAliasMap const &) const;  // 0x6feed0
    __cdecl DrDataTableImpl(void);  // 0x6fefa0
};

