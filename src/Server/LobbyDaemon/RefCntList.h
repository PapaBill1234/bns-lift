// RefCntList.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class RefCntListNode;

class RefCntList
{
public:
    RefCntList();  // 0x64c80
    ~RefCntList();  // 0x64c90
    bool Pushback(RefCntListNode*);  // 0x64d00
    bool Remove(RefCntListNode*);  // 0x64da0
};
