// raiddungeon.h: raiddungeon.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <stddef.h>
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

    // LIFT: PDB layout of RaidDungeon (size 0x1B0). Only the fields that the lifted bodies read are declared.
    char lift_pad_8[0x10];  // ❓ base DynamicRefCntObj (+0x8 to +0x17, after the vfptr) is not declared yet
    unsigned __int64 _id;  // +24 (0x18)
    unsigned __int64 _dbId;  // +32 (0x20)
    char _currentStep;  // +40 (0x28)
    bool _waitConfirm;  // +41 (0x29)
    long volatile _boundPcCount;  // +44 (0x2C)
    __int64 _expireTime;  // +48 (0x30)
    char lift_pad_38[0x8];  // ❓ _data (Data::RaidDungeonRecordPtr, +0x38) is not declared yet
    bool _removed;  // +64 (0x40)
    unsigned __int64 _occupyingObjectId;  // +72 (0x48)
    char lift_pad_50[0x138];  // ❓ _occupyingPcInfo to _currentBossNpcInCombat (+0x50 to +0x187) are not declared yet
    ::CriticalSection _raidDungeonCS;  // +392 (0x188)
};
static_assert(offsetof(RaidDungeon, _occupyingObjectId) == 0x48, "RaidDungeon::_occupyingObjectId");
static_assert(offsetof(RaidDungeon, _raidDungeonCS) == 0x188, "RaidDungeon::_raidDungeonCS");
static_assert(sizeof(RaidDungeon) == 0x1B0, "RaidDungeon size");

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

    // LIFT: PDB nested type RaidDungeonManager::BoundDungeonList.
    typedef std::map<unsigned __int64, ::RaidDungeon *, std::less<unsigned __int64>, StlAllocator<std::pair<unsigned __int64, ::RaidDungeon *>, 2> > BoundDungeonList;
private:
    int _raidDungeonCount;  // +8 (0x8)
    int _raidDungeonCapacity;  // +12 (0xC)
    ::RaidDungeon **_raidDungeonList;  // +16 (0x10)
    BoundDungeonList _boundRaidDungeonlist;  // +24 (0x18)
    __int64 _expirationTime;  // +56 (0x38)
    ::CriticalSection _lock;  // +64 (0x40)
    __int64 _lastIssuedId;  // +104 (0x68)
};
static_assert(offsetof(RaidDungeonManager, _expirationTime) == 0x38, "RaidDungeonManager::_expirationTime");
static_assert(sizeof(RaidDungeonManager) == 0x70, "RaidDungeonManager size");

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

    // LIFT: PDB nested types RaidDungeonPropertyContainer::BindList and UnbindList.
    typedef std::map<__int64, ::RaidDungeonBindPropertyEntry *, std::less<__int64>, StlAllocator<std::pair<__int64, ::RaidDungeonBindPropertyEntry *>, 2> > BindList;
    typedef std::map<int, ::RaidDungeonUnbindPropertyEntry *, std::less<int>, StlAllocator<std::pair<int, ::RaidDungeonUnbindPropertyEntry *>, 2> > UnbindList;
private:
    BindList _bindList;  // +0 (0x0)
    UnbindList _unbindList;  // +32 (0x20)
    ::Pc *_owner;  // +64 (0x40)
};
static_assert(offsetof(RaidDungeonPropertyContainer, _owner) == 0x40, "RaidDungeonPropertyContainer::_owner");
static_assert(sizeof(RaidDungeonPropertyContainer) == 0x48, "RaidDungeonPropertyContainer size");

class RaidDungeonUnbindPropertyEntry
{
public:
    __cdecl RaidDungeonUnbindPropertyEntry(void);  // 0x1ab130
    void __cdecl Initialize(int, ::Pc *);  // 0x1ab180
    short __cdecl FetchDb(char *, short) const;  // 0x1ab1d0
    short __cdecl FetchBroadcast(char *, short);  // 0x1ab250
};

