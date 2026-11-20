// WaitQueue.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class WaitQueue
{
public:
    WaitQueue();  // 0xdc540
    ~WaitQueue();  // 0xdc590
    bool Add(unsigned long long, short&, int&);  // 0xdc5e0
    bool Remove(short const&, unsigned long long);  // 0xdc720
    bool QueryTurn(short const&, int&) const;  // 0xdc870
};

class WaitQueueList
{
public:
    ~WaitQueueList();  // 0xdc920
    bool Init(int);  // 0xdc940
    unsigned long long Pop();  // 0xdca20
};
