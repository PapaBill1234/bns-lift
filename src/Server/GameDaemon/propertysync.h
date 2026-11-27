// propertysync.h: propertysync.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class SyncBuffer
{
public:
    struct Def {};
protected:
    __cdecl ~SyncBuffer(void);  // 0x687ce0
    bool __cdecl Initialize(::SyncBuffer::Def const *);  // 0x687df0
    bool __cdecl Initialize(::SyncBuffer const *);  // 0x687fc0
public:
    bool __cdecl Clear(void) const;  // 0x6880c0
    short __cdecl Copy(char *, unsigned __int64, short *, bool) const;  // 0x688130
protected:
    bool __cdecl Set(::Field::Def const *, int, void const *, int, bool, bool *, int, int);  // 0x6881b0
private:
    char * __cdecl set(::Field::Def const *, int, char *, void const *, int, bool, short &);  // 0x688560
    char * __cdecl setInt(char *, void const *, unsigned char);  // 0x688890
    char * __cdecl setString(char *, wchar_t const *, short, int, bool, short &);  // 0x6888d0
    void __cdecl realign(int, char *, short);  // 0x688990
};

