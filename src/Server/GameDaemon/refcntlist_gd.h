// refcntlist_gd.h: refcntlist.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RefCntList
{
public:
    __cdecl ~RefCntList(void);  // 0x1b7460
    bool __cdecl Pushback(::RefCntListNode *);  // 0x1b74d0
    bool __cdecl Remove(::RefCntListNode *);  // 0x1b7570
};

