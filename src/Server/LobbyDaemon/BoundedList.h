// BoundedList.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class BoundedList
{
public:
    bool Init(int);  // 0x18540
    short Pushback(void*);  // 0x18650
    void* Popfront();  // 0x186f0
    bool Remove(short);  // 0x18790
};
