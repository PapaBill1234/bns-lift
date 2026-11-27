// zonebroadcast.h: zonebroadcast.cpp, zonebroadcast.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ZoneBroadcastCube
{
protected:
    __cdecl ZoneBroadcastCube(::GeoCube const *);  // 0x25a6c0
    __cdecl ~ZoneBroadcastCube(void);  // 0x25aa40
};

class ZoneCampfireNode
{
protected:
    bool __cdecl AddToCube(::ZoneBroadcastCube *);  // 0x25a2a0
};

class ZoneCreatureList
{
public:
    ::Pointer2< ::Creature> __cdecl GetPtr(unsigned __int64, ::ZoneCreatureNode **);  // 0x27230
    __cdecl ZoneCreatureList(::Zone const *);  // 0x25ac50
    __cdecl ~ZoneCreatureList(void);  // 0x25ade0
    ::ZoneCreatureNode * __cdecl Add(::Creature *);  // 0x25af40
    ::ZoneCreatureNode * __cdecl AddPc(::Pc *);  // 0x25b060
    ::ZoneCreatureNode * __cdecl AddNpc(::Npc *);  // 0x25b300
    ::ZoneCreatureNode * __cdecl AddDuelBot(::DuelBot *);  // 0x25b6b0
    ::ZoneCreatureNode * __cdecl AddSummoned(::Summoned *);  // 0x25b8d0
    ::ZoneCreatureNode * __cdecl AddDuelBotSummoned(::DuelBotSummoned *);  // 0x25bb50
    bool __cdecl Remove(unsigned __int64);  // 0x25bd70
    bool __cdecl RemovePc(unsigned __int64);  // 0x25be80
    bool __cdecl RemoveNpc(unsigned __int64);  // 0x25bf40
    bool __cdecl RemoveDuelBot(unsigned __int64);  // 0x25c090
    bool __cdecl RemoveSummoned(unsigned __int64);  // 0x25c1a0
    bool __cdecl RemoveDuelBotSummoned(unsigned __int64);  // 0x25c270
    void __cdecl RemoveAll(void);  // 0x25c380
protected:
    void __cdecl fetchPcLocInfo(::FragmentPacket &);  // 0x25c6a0
    ::ZoneCreatureNode * __cdecl find(unsigned __int64) const;  // 0x25c800
};

class ZoneCreatureNode
{
protected:
    bool __cdecl AddToCube(::ZoneBroadcastCube *);  // 0x25a050
    bool __cdecl RemoveFromCube(void);  // 0x25a100
};

class ZoneCubeMigratorList
{
public:
    bool __cdecl AddToCube(::ZoneCreatureNode *);  // 0x25c9f0
};

class ZoneFieldItemNode
{
protected:
    bool __cdecl AddToCube(::ZoneBroadcastCube *);  // 0x25a1e0
    bool __cdecl RemoveFromCube(void);  // 0x25a230
};

class ZoneObjectIdList
{
public:
    __cdecl ~ZoneObjectIdList(void);  // 0x25a2f0
    void __cdecl Add(unsigned __int64, char, __int64, unsigned char);  // 0x25a3b0
    void __cdecl Clear(void);  // 0x25a430
private:
    void __cdecl grow(void);  // 0x25a480
};

