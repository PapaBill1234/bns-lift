// leaveworldtran_cpp.cpp: leaveworldtran.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "leaveworldtran.h"
#include "user.h"
#include "LiftStub.h"

// 0x13a500
__cdecl LeaveWorldTran::~LeaveWorldTran(void)
{
    LIFT_STUB(0x13a500);
}

// 0x13a640
bool __cdecl LeaveWorldTran::init(int, void *)
{
    LIFT_STUB(0x13a640);
}

// 0x13a8d0
bool __cdecl LeaveWorldTran::tryStopCharge(void)
{
    LIFT_STUB(0x13a8d0);
}

// 0x13aa00
bool __cdecl LeaveWorldTran::stopChargeOk(void *)
{
    LIFT_STUB(0x13aa00);
}

// 0x13aa70
bool __cdecl LeaveWorldTran::stopChargeFail(short)
{
    LIFT_STUB(0x13aa70);
}

// 0x13aae0
bool __cdecl LeaveWorldTran::tryLeaveZone(short)
{
    LIFT_STUB(0x13aae0);
}

// 0x13ad20
bool __cdecl LeaveWorldTran::leaveZoneOk(void *)
{
    LIFT_STUB(0x13ad20);
}

// 0x13ae40
bool __cdecl LeaveWorldTran::leaveZoneFailExpire(void)
{
    LIFT_STUB(0x13ae40);
}

// 0x13af70
bool __cdecl LeaveWorldTran::leaveZoneArenaOk(void *)
{
    LIFT_STUB(0x13af70);
}

// 0x13b1c0
bool __cdecl LeaveWorldTran::tryUpdateCharacterInfo(void)
{
    LIFT_STUB(0x13b1c0);
}

// 0x13b2b0
bool __cdecl LeaveWorldTran::updateCharacterInfoOk(void *)
{
    LIFT_STUB(0x13b2b0);
}

// 0x13b320
bool __cdecl LeaveWorldTran::updateCharacterInfoFail(short)
{
    LIFT_STUB(0x13b320);
}

// 0x13b390
bool __cdecl LeaveWorldTran::tryUpdateAccountInfo(void)
{
    LIFT_STUB(0x13b390);
}

// 0x13b570
bool __cdecl LeaveWorldTran::updateAccountInfoOk(void *)
{
    LIFT_STUB(0x13b570);
}

// 0x13b5e0
bool __cdecl LeaveWorldTran::updateAccountInfoFail(short)
{
    LIFT_STUB(0x13b5e0);
}

// 0x13b720
bool __cdecl LeaveWorldTran::tryTakeTimeBasedReward(void)
{
    LIFT_STUB(0x13b720);
}

// 0x13b770
bool __cdecl LeaveWorldTran::takeTimeBasedRewardResponse(void *)
{
    LIFT_STUB(0x13b770);
}

// 0x13b7e0
bool __cdecl LeaveWorldTran::tryUnloadCharacter(void)
{
    LIFT_STUB(0x13b7e0);
}

// 0x13b990
bool __cdecl LeaveWorldTran::unloadCharacterOk(void *)
{
    LIFT_STUB(0x13b990);
}

// 0x13ba00
bool __cdecl LeaveWorldTran::unloadCharacterFail(short)
{
    LIFT_STUB(0x13ba00);
}

// 0x13ba70
void __cdecl LeaveWorldTran::clearArenaSession(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x13ba70);
}

// 0x13bbe0
bool __cdecl ReturnToLobbyTran::init(int, void *)
{
    LIFT_STUB(0x13bbe0);
}

// 0x13bc10
bool __cdecl ReturnToLobbyTran::work(int, void *)
{
    LIFT_STUB(0x13bc10);
}

// 0x13bdc0
void __cdecl ReturnToLobbyTran::failProcess(void)
{
    LIFT_STUB(0x13bdc0);
}

// 0x13be20
bool __cdecl ReturnToLobbyTran::tryLeaveWorld(void)
{
    LIFT_STUB(0x13be20);
}

// 0x13bf80
bool __cdecl ReturnToLobbyTran::leaveWorldOk(void *)
{
    LIFT_STUB(0x13bf80);
}

// 0x13c030
bool __cdecl ReturnToLobbyTran::leaveWorldFail(short)
{
    LIFT_STUB(0x13c030);
}

// 0x13c0f0
bool __cdecl LogoutTran::init(int, void *)
{
    LIFT_STUB(0x13c0f0);
}

// 0x13c130
bool __cdecl LogoutTran::work(int, void *)
{
    LIFT_STUB(0x13c130);
}

// 0x13c2b0
bool __cdecl LogoutTran::logoutNotify(void)
{
    LIFT_STUB(0x13c2b0);
}

// 0x13c3c0
bool __cdecl KickTran::init(int, void *)
{
    LIFT_STUB(0x13c3c0);
}

// 0x13c400
bool __cdecl KickTran::work(int, void *)
{
    LIFT_STUB(0x13c400);
}

// 0x13c580
void __cdecl KickTran::failProcess(void)
{
    LIFT_STUB(0x13c580);
}

// 0x13c5d0
bool __cdecl KickTran::kickOk(void)
{
    LIFT_STUB(0x13c5d0);
}

// 0x13c7c0
bool __cdecl LogoutArenaTran::init(int, void *)
{
    LIFT_STUB(0x13c7c0);
}

// 0x13c920
bool __cdecl LogoutArenaTran::work(int, void *)
{
    LIFT_STUB(0x13c920);
}

// 0x13ca00
bool __cdecl LogoutArenaTran::tryLeaveZone(void)
{
    LIFT_STUB(0x13ca00);
}

// 0x13cb40
bool __cdecl LogoutArenaTran::leaveZoneOk(void)
{
    LIFT_STUB(0x13cb40);
}

// 0x13cd40
bool __cdecl LogoutArenaTran::leaveZoneFailExpire(void)
{
    LIFT_STUB(0x13cd40);
}

// 0x13cf00
bool __cdecl LogoutArenaTran::removeArenaLobbyMemberOk(void)
{
    LIFT_STUB(0x13cf00);
}

// 0x13cff0
void __cdecl LogoutArenaTran::failProcess(wchar_t const *)
{
    LIFT_STUB(0x13cff0);
}

// 0x13d100
__cdecl ReturnToArenaLobbyTran::ReturnToArenaLobbyTran(::User *)
{
    LIFT_STUB(0x13d100);
}

// 0x13d230
__cdecl ReturnToArenaLobbyTran::~ReturnToArenaLobbyTran(void)
{
    LIFT_STUB(0x13d230);
}

// 0x13d2b0
bool __cdecl ReturnToArenaLobbyTran::init(int, void *)
{
    LIFT_STUB(0x13d2b0);
}

// 0x13d440
bool __cdecl ReturnToArenaLobbyTran::work(int, void *)
{
    LIFT_STUB(0x13d440);
}

// 0x13d4e0
bool __cdecl ReturnToArenaLobbyTran::tryLeaveZone(void)
{
    LIFT_STUB(0x13d4e0);
}

// 0x13d6c0
bool __cdecl ReturnToArenaLobbyTran::leaveZoneOk(void)
{
    LIFT_STUB(0x13d6c0);
}

// 0x13d7f0
bool __cdecl ReturnToArenaLobbyTran::leaveZoneFailExpire(void)
{
    LIFT_STUB(0x13d7f0);
}

// 0x13d980
bool __cdecl ReturnToArenaLobbyTran::tryLeaveArena(void)
{
    LIFT_STUB(0x13d980);
}

// 0x13dcb0
bool __cdecl ReturnToArenaLobbyTran::leaveArenaOk(void)
{
    LIFT_STUB(0x13dcb0);
}

// 0x13dee0
bool __cdecl ReturnToArenaLobbyTran::leaveArenaFail(void *)
{
    LIFT_STUB(0x13dee0);
}

// 0x13df70
void __cdecl ReturnToArenaLobbyTran::failProcess(wchar_t const *)
{
    LIFT_STUB(0x13df70);
}
