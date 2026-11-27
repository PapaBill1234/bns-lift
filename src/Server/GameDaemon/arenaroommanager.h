// arenaroommanager.h: arenaroommanager.cpp, arenaroommanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ArenaDuelRoom
{
protected:
    virtual bool __cdecl build(char);  // 0x49c50
    virtual bool __cdecl getZoneCreationInfo(unsigned int, unsigned int *, ::vector16 *, int *);  // 0x49c80
public:
    virtual bool __cdecl GetPcSpawnInfo(unsigned int, unsigned __int64, unsigned int *, ::vector16 *, int *);  // 0x49d90
};

class ArenaDungeonRoom
{
public:
    __cdecl ArenaDungeonRoom(void);  // 0x49ed0
protected:
    virtual bool __cdecl build(char);  // 0x49f50
    virtual bool __cdecl getZoneCreationInfo(unsigned int, unsigned int *, ::vector16 *, int *);  // 0x49ff0
    virtual ::Data::PcContentsTypeType __cdecl GetPcContentsType(void);  // 0x4a090
public:
    virtual bool __cdecl GetPcSpawnInfo(unsigned int, unsigned __int64, unsigned int *, ::vector16 *, int *);  // 0x4a0e0
    virtual char __cdecl GetArenaAttraction(void);  // 0x66a1a0
};

// LIFT: views of the PDB record Data::InterDungeonListRecord (base DrEl, size 0x48) and of Data::InterDungeonListRecordPtr.
// Only the fields that the lifted bodies read are declared.
struct ArenaInterDungeonListRecordView
{
    char lift_pad_0[0x30];  // ❓ no PDB name: fields +0 to +0x2F are not declared yet
    unsigned __int64 public_raid;  // +48 (0x30)
};

class ArenaInterDungeonListRecordPtrView
{
public:
    ::ArenaInterDungeonListRecordView *_record;  // 0x0 (PDB: DrRecordPtr::_record, DrEl *)
};

// LIFT: view of the PDB base ArenaDungeonRoom of ArenaPublicRaidRoom (+8 to +0xD37F). It is a private base,
// so the declared members of ArenaPublicRaidRoom keep their PDB offsets.
struct ArenaPublicRaidRoomBaseView
{
    char lift_pad_8[0xD370];  // ❓ no PDB name: base ArenaDungeonRoom up to +0xD377 is not declared yet
    ::ArenaInterDungeonListRecordPtrView _interDungeonList;  // +54136 (0xD378) in ArenaPublicRaidRoom (PDB: ArenaDungeonRoom::_interDungeonList)
};

class ArenaPublicRaidRoom : private ::ArenaPublicRaidRoomBaseView  // LIFT: view of the PDB base ArenaDungeonRoom (+8 to +0xD37F)
{
public:
    virtual void __cdecl SetPublicRaidReservePcCount(int);  // 0x27b30
    virtual bool __cdecl IsSetPublicRaidReservePcCount(void);  // 0x27b40
    virtual int __cdecl GetPublicRaidReservePcCount(void);  // 0x27b50
    virtual unsigned __int64 __cdecl GetPublicRaidKey(void);  // 0x27b80
    virtual char __cdecl GetArenaPortalPublicRaidModeType(void) const;  // 0x27ba0
    __cdecl ArenaPublicRaidRoom(char);  // 0x4a350
protected:
    virtual bool __cdecl build(char);  // 0x4a3e0
    virtual bool __cdecl getZoneCreationInfo(unsigned int, unsigned int *, ::vector16 *, int *);  // 0x4a480
    virtual ::Data::PcContentsTypeType __cdecl GetPcContentsType(void);  // 0x4a500
public:
    virtual bool __cdecl GetPcSpawnInfo(unsigned int, unsigned __int64, unsigned int *, ::vector16 *, int *);  // 0x4a520
protected:
    // PDB layout (size 0xD388). The vfptr is at +0.
    char _arenaPortalPublicRaidModeType;  // +54144 (0xD380) (LIFT: PDB type is char const; const waits for the lifted ctor)
    long volatile _reservePcCount;  // +54148 (0xD384)
};

class ArenaRoom
{
public:
    virtual char __cdecl GetArenaPortalPublicRaidModeType(void) const;  // 0x27b20
    bool __cdecl Build(short, unsigned __int64, unsigned __int64, bool, ::FragmentPacketConcatenater *);  // 0x49a20
    __int64 __cdecl GetGuildRegistrationTime(unsigned __int64);  // 0x49b40
    int __cdecl GetMemberCount(void);  // 0x49bc0
};

class ArenaRoomManager
{
public:
    __cdecl ArenaRoomManager(void);  // 0x4a6e0
    virtual __cdecl ~ArenaRoomManager(void);  // 0x4a780
    unsigned __int64 __cdecl IssueOtp(void);  // 0x4a900
    unsigned __int64 __cdecl Add(::ArenaRoom *);  // 0x4a950
    ::ArenaRoom * __cdecl Acquire(unsigned __int64);  // 0x4aa30
    void __cdecl RemoveTimeout(__int64, __int64);  // 0x4aae0
};

class ArenaSessionTimer
{
public:
    enum STATE {};
public:
    __cdecl ArenaSessionTimer(__int64, __int64, wchar_t const *);  // 0x4ac20
};

class DisconnectedArenaSessionInfo
{
public:
    void __cdecl Init(::DisconnectedArenaSessionInfo const *);  // 0x4acd0
    bool __cdecl BuildPacket(::Packet &, ::PacketComposer &);  // 0x4ad60
    bool __cdecl Decompose(::Packet const *, ::PacketDecomposer &);  // 0x4ae50
    void __cdecl SendExpireUpdateArenaSession(char);  // 0x4af50
};

class DisconnectedArenaSessionManager
{
public:
    __cdecl DisconnectedArenaSessionManager(void);  // 0x4b030
    virtual __cdecl ~DisconnectedArenaSessionManager(void);  // 0x4b130
    bool __cdecl CreateTimer(unsigned __int64, __int64, wchar_t const *);  // 0x4b420
    void __cdecl RemoveTimeoutTimer(__int64, __int64, __int64);  // 0x4b540
    __int64 __cdecl GetTouchTime(unsigned __int64);  // 0x4b720
    bool __cdecl ClearTimer(unsigned __int64);  // 0x4b7c0
    bool __cdecl ChangeTimer(unsigned __int64, ::ArenaSessionTimer::STATE);  // 0x4b8b0
    bool __cdecl IsReturnSession(unsigned __int64);  // 0x4b9a0
    bool __cdecl ExistSession(unsigned __int64, __int64, __int64 &, char &, bool);  // 0x4ba50
    bool __cdecl CreateSession(::DisconnectedArenaSessionInfo const *);  // 0x4bc40
    void __cdecl RemoveTimeoutSession(__int64, __int64);  // 0x4bde0
    ::DisconnectedArenaSessionInfo * __cdecl PopSession(unsigned __int64);  // 0x4bfe0
    ::DisconnectedArenaSessionInfo * __cdecl AcquireSession(unsigned __int64);  // 0x4c0b0
};

