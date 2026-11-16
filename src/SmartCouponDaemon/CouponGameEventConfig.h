// CouponGameEventConfig.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Lock.h"

class GameEventConfig
{
public:
    GameEventConfig();   // ❓ address
    ~GameEventConfig();  // ❓ address

    bool Load(wchar_t const* configPath);  // ❓ address
    void Dump();                           // ❓ address

    CriticalSection _lock;
    alignas(8) unsigned char _gameEventList[0x20];  // ❓ PDB type 0x28BF: std::map<int,GameEventConfig::GameEventInfo *,std::less<int>,StlAllocator<std::pair<int,GameEventConfig::GameEventInfo *>,2> >
};
static_assert(sizeof(GameEventConfig) == 0x48, "sizeof GameEventConfig");
static_assert(offsetof(GameEventConfig, _gameEventList) == 0x28, "GameEventConfig::_gameEventList");
