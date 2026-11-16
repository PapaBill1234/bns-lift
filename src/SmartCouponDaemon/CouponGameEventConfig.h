// CouponGameEventConfig.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h and IDA.
#pragma once
#include <stddef.h>
#include <map>
#include "Lock.h"
#include "StlMemory.h"

class GameEventConfig
{
public:
    struct GameEventInfo
    {
        int id;
        wchar_t name[260];
        char eventType;
        bool enable;
        unsigned char daemonType;
    };

    GameEventConfig();   // 0x2a40
    ~GameEventConfig();  // 0x2b10

    bool Load(wchar_t const* configPath);  // 0x3430
    void Dump();                           // 0x3580

    bool SetupGameEventListFromXml(wchar_t const* xml);  // 0x2c80
    bool addGameEventInfo(GameEventInfo* gameEventInfo);  // 0x3260
    GameEventInfo* FindGameEventInfo(int id);             // 0x3390

private:
    // ❓ Not in the PDB. Inlined in each fail path of the original.
    static void writeStartLog(class Console* console, wchar_t const* message);

public:
    CriticalSection _lock;
    std::map<int, GameEventInfo*, std::less<int>, StlAllocator<std::pair<int const, GameEventInfo*>, 2> > _gameEventList;
};
static_assert(sizeof(GameEventConfig::GameEventInfo) == 528, "sizeof GameEventConfig::GameEventInfo");
static_assert(sizeof(GameEventConfig) == 0x48, "sizeof GameEventConfig");
static_assert(offsetof(GameEventConfig, _gameEventList) == 0x28, "GameEventConfig::_gameEventList");
