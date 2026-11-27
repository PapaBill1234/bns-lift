// teaminvitationcardbox.h: teaminvitationcardbox.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class TeamInvitationCardBox
{
public:
    virtual __cdecl ~TeamInvitationCardBox(void);  // 0x210860
    bool __cdecl Initialize(::Pc *, int);  // 0x2108f0
    bool __cdecl Find(::TeamInvitationType, unsigned __int64, unsigned __int64, ::TeamInvitationCard *);  // 0x210a40
    bool __cdecl Add(::TeamInvitationCard const *);  // 0x210ad0
    bool __cdecl Remove(::TeamInvitationType, unsigned __int64, unsigned __int64);  // 0x210d10
    void __cdecl Clear(void);  // 0x210de0
    void __cdecl RemoveExpired(void);  // 0x210f10
private:
    int __cdecl find(::TeamInvitationType, unsigned __int64, unsigned __int64);  // 0x2110a0
};

