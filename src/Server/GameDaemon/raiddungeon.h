// raiddungeon.h: raiddungeon.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RaidDungeon
{
public:
    __cdecl RaidDungeon(void);  // 0x1a6f00
    virtual __cdecl ~RaidDungeon(void);  // 0x1a6ff0
    bool __cdecl Initialize(unsigned __int64, short);  // 0x1a70b0
    short __cdecl GetMaxUnbindCount(void);  // 0x1a71c0
    bool __cdecl Initialize(unsigned __int64, unsigned __int64, short, char, short, __int64);  // 0x1a7260
    bool __cdecl LoginCharacter(unsigned __int64, __int64, wchar_t const *, char, char, char);  // 0x1a7370
    bool __cdecl LogoutCharacter(unsigned __int64);  // 0x1a76d0
    void __cdecl SendOnlinePlayerInfo(::Pc *);  // 0x1a78e0
    ::GameFailReason __cdecl SetOccupyingObjectId(unsigned __int64, ::Team *);  // 0x1a7b60
    void __cdecl SendInfomationToOccupyingObject(::Team *);  // 0x1a7f60
    void __cdecl SendInfomation(::Pc *);  // 0x1a8200
    unsigned __int64 __cdecl GetOccupyingObjectId(void);  // 0x1a8360
    void __cdecl BossCombatStart(::Pc *, ::BossNpc *);  // 0x1a83a0
    void __cdecl BossCombatEnd(::BossNpc *);  // 0x1a8660
    void __cdecl LeaveMemberAfterCombatStart(::Pc *);  // 0x1a87f0
    bool __cdecl OnBossNpcKilled(::Data::BossNpcRecordPtr);  // 0x1a90e0
    bool __cdecl IsBound(void);  // 0x1a94a0
private:
    void __cdecl broadcastStep(void);  // 0x1a94f0
    void __cdecl insertToDB(void);  // 0x1a9780
    void __cdecl updateToDB(void);  // 0x1a9890
public:
    void __cdecl PostConfirmTask(__int64);  // 0x1a9a00
private:
    bool __cdecl confirm(unsigned __int64);  // 0x1a9b90
};

class RaidDungeonBindPropertyEntry
{
public:
    __cdecl RaidDungeonBindPropertyEntry(void);  // 0x1ab0e0
};

class RaidDungeonManager
{
public:
    __cdecl RaidDungeonManager(void);  // 0x1aa220
    virtual __cdecl ~RaidDungeonManager(void);  // 0x1aa2d0
private:
    __int64 __cdecl makeId(void);  // 0x1aa340
public:
    bool __cdecl Initialize(int, int, int);  // 0x1aa3e0
    bool __cdecl SetRaidDungeonExpirationTime(int, int);  // 0x1aa5b0
    __int64 __cdecl GetRaidDungeonExpirationTime(void);  // 0x1aa6f0
    bool __cdecl SetRaidDungeonFromDBData(::FragmentPacketConcatenater *);  // 0x1aa740
    ::Pointer2< ::RaidDungeon> __cdecl Confirm(unsigned __int64, __int64);  // 0x1aaa30
    ::Pointer2< ::RaidDungeon> __cdecl CreateRaidDungeon(int);  // 0x1aabb0
    ::Pointer2< ::RaidDungeon> __cdecl DestroyRaidDungeon(unsigned __int64);  // 0x1aadf0
    ::Pointer2< ::RaidDungeon> __cdecl GetRaidDungeonPtrById(unsigned __int64);  // 0x1aaf70
    ::Pointer2< ::RaidDungeon> __cdecl GetRaidDungeonPtrByDbId(unsigned __int64);  // 0x1aaff0
};

class RaidDungeonPropertyContainer
{
public:
    __cdecl RaidDungeonPropertyContainer(void);  // 0x1ab2e0
    __cdecl ~RaidDungeonPropertyContainer(void);  // 0x1ab3b0
    int __cdecl SetBindDbData(short, char const *, int);  // 0x1ab5a0
    bool __cdecl ConfirmAcquireBindData(__int64);  // 0x1ab7f0
    bool __cdecl BindRaidDungeonByDbId(__int64);  // 0x1ab8c0
    int __cdecl SetUnbindDbData(short, char const *, int);  // 0x1aba20
    bool __cdecl ConfirmAcquireUnbindData(int);  // 0x1abca0
    short __cdecl FetchUnbindList(short *, char *, short);  // 0x1abd50
    bool __cdecl UnbindRaidDungeon(int, __int64, bool);  // 0x1abe30
    bool __cdecl CheckExpiredRaidDungeon(bool);  // 0x1ac3c0
    bool __cdecl DisposeAll(void);  // 0x1ac690
};

class RaidDungeonUnbindPropertyEntry
{
public:
    __cdecl RaidDungeonUnbindPropertyEntry(void);  // 0x1ab130
    void __cdecl Initialize(int, ::Pc *);  // 0x1ab180
    short __cdecl FetchDb(char *, short) const;  // 0x1ab1d0
    short __cdecl FetchBroadcast(char *, short);  // 0x1ab250
};

