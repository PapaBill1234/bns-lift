// worldserializer.h: worldserializer.cpp, worldserializer.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class WorldSerializer
{
public:
    bool __cdecl PostWakeupEvent(long);  // 0x3ebf20
    virtual __cdecl ~WorldSerializer(void);  // 0x681f50
    bool __cdecl Initialize(::World *, long, long);  // 0x681fc0
    bool __cdecl Clear(void);  // 0x682060
};

