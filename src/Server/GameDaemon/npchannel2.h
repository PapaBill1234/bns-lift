// npchannel2.h: npchannel2.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class NPChannel
{
public:
    static bool __cdecl Setup(int, wchar_t const *, wchar_t *, unsigned int, unsigned __int64, long);  // 0x1b880
private:
    bool __cdecl handlePacket(::Packet const *);  // 0x1c2e0
protected:
    bool __cdecl onConnect(::Session const *, bool);  // 0x1c5e0
private:
    bool __cdecl sendInitialConnectMessage(::Session const *);  // 0x1c750
    bool __cdecl checkLibError(::StsMsgLib::EStsMsgError);  // 0x1c860
};

