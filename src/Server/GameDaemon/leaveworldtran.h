// leaveworldtran.h: leaveworldtran.cpp, leaveworldtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class KickTran
{
private:
    virtual bool __cdecl init(int, void *);  // 0x13c3c0
    virtual bool __cdecl work(int, void *);  // 0x13c400
    virtual void __cdecl failProcess(void);  // 0x13c580
    bool __cdecl kickOk(void);  // 0x13c5d0
};

class LeaveWorldTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x35fe0
    static ::GameTranDef _def;  // LIFT: PDB data LeaveWorldTran::_def
    virtual __cdecl ~LeaveWorldTran(void);  // 0x13a500
protected:
    virtual bool __cdecl init(int, void *);  // 0x13a640
    bool __cdecl tryStopCharge(void);  // 0x13a8d0
    bool __cdecl stopChargeOk(void *);  // 0x13aa00
    bool __cdecl stopChargeFail(short);  // 0x13aa70
    bool __cdecl tryLeaveZone(short);  // 0x13aae0
    bool __cdecl leaveZoneOk(void *);  // 0x13ad20
    bool __cdecl leaveZoneFailExpire(void);  // 0x13ae40
    bool __cdecl leaveZoneArenaOk(void *);  // 0x13af70
    bool __cdecl tryUpdateCharacterInfo(void);  // 0x13b1c0
    bool __cdecl updateCharacterInfoOk(void *);  // 0x13b2b0
    bool __cdecl updateCharacterInfoFail(short);  // 0x13b320
    bool __cdecl tryUpdateAccountInfo(void);  // 0x13b390
    bool __cdecl updateAccountInfoOk(void *);  // 0x13b570
    bool __cdecl updateAccountInfoFail(short);  // 0x13b5e0
    bool __cdecl tryTakeTimeBasedReward(void);  // 0x13b720
    bool __cdecl takeTimeBasedRewardResponse(void *);  // 0x13b770
    bool __cdecl tryUnloadCharacter(void);  // 0x13b7e0
    bool __cdecl unloadCharacterOk(void *);  // 0x13b990
    bool __cdecl unloadCharacterFail(short);  // 0x13ba00
    void __cdecl clearArenaSession(unsigned __int64, wchar_t const *);  // 0x13ba70
};

class LogoutArenaTran
{
public:
    __cdecl LogoutArenaTran(::User *);  // 0x36080
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x360f0
    static ::GameTranDef _def;  // LIFT: PDB data LogoutArenaTran::_def
private:
    virtual bool __cdecl init(int, void *);  // 0x13c7c0
    virtual bool __cdecl work(int, void *);  // 0x13c920
    bool __cdecl tryLeaveZone(void);  // 0x13ca00
    bool __cdecl leaveZoneOk(void);  // 0x13cb40
    bool __cdecl leaveZoneFailExpire(void);  // 0x13cd40
    bool __cdecl removeArenaLobbyMemberOk(void);  // 0x13cf00
    void __cdecl failProcess(wchar_t const *);  // 0x13cff0
};

class LogoutTran
{
public:
    __cdecl LogoutTran(::User *);  // 0x35ff0
private:
    virtual bool __cdecl init(int, void *);  // 0x13c0f0
    virtual bool __cdecl work(int, void *);  // 0x13c130
    bool __cdecl logoutNotify(void);  // 0x13c2b0
};

class ReturnToArenaLobbyTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1397e0
    static ::GameTranDef _def;  // LIFT: PDB data ReturnToArenaLobbyTran::_def
    __cdecl ReturnToArenaLobbyTran(::User *);  // 0x13d100
    virtual __cdecl ~ReturnToArenaLobbyTran(void);  // 0x13d230
private:
    virtual bool __cdecl init(int, void *);  // 0x13d2b0
    virtual bool __cdecl work(int, void *);  // 0x13d440
    bool __cdecl tryLeaveZone(void);  // 0x13d4e0
    bool __cdecl leaveZoneOk(void);  // 0x13d6c0
    bool __cdecl leaveZoneFailExpire(void);  // 0x13d7f0
    bool __cdecl tryLeaveArena(void);  // 0x13d980
    bool __cdecl leaveArenaOk(void);  // 0x13dcb0
    bool __cdecl leaveArenaFail(void *);  // 0x13dee0
    void __cdecl failProcess(wchar_t const *);  // 0x13df70
};

class ReturnToLobbyTran
{
private:
    virtual bool __cdecl init(int, void *);  // 0x13bbe0
    virtual bool __cdecl work(int, void *);  // 0x13bc10
    virtual void __cdecl failProcess(void);  // 0x13bdc0
    bool __cdecl tryLeaveWorld(void);  // 0x13be20
    bool __cdecl leaveWorldOk(void *);  // 0x13bf80
    bool __cdecl leaveWorldFail(short);  // 0x13c030
};

