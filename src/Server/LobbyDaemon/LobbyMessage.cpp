// LobbyMessage.obj (LobbyDaemon 2019 + PDB).
#include "LobbyMessage.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "Log.h"
#include "MembershipMileage.h"
#include "PcCafeMileage.h"
#include <time.h>

#pragma comment(linker, "/INCLUDE:??1LobbyMessage@@UEAA@XZ")  // LIFT: keep until the callers are lifted (0x2f9d0).
#pragma comment(linker, "/INCLUDE:?Dispatch@LobbyMessage@@UEAAXPEAVLobbyMessageAcceptor@@@Z")  // LIFT: keep until the callers are lifted (0x2f9e0).
#pragma comment(linker, "/INCLUDE:?Dispatch@CliSessionStopPcCafeChargeMessage@@UEAAXPEAVPcCafeMileage@@@Z")  // LIFT: keep until the callers are lifted (0x2fa90).
#pragma comment(linker, "/INCLUDE:?Dispatch@CliSessionGradeChangedMessage@@UEAAXPEAVMembershipMileage@@@Z")  // LIFT: keep until the caller is lifted (0x2fb10).
#pragma comment(linker, "/INCLUDE:?Dispatch@CliSessionStartPcCafeChargeMessage@@UEAAXPEAVPcCafeMileage@@@Z")  // LIFT: keep until the callers are lifted (0x2fad0).

// 0x2f9d0
LobbyMessage::~LobbyMessage()
{
}

// 0x2f9e0
void LobbyMessage::Dispatch(LobbyMessageAcceptor* acceptor)
{
    Log::Write(Log::LT_ERROR,
               L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\lobbydaemon\\LobbyMessage.h",
               70, L"== CRASH == [message], dispatching unregistered acceptor, address:%p", acceptor);
    AlertSender::Write(
        L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\lobbydaemon\\LobbyMessage.h",
        70, L"== CRASH == [message], dispatching unregistered acceptor, address:%p", acceptor);
}

// LIFT: inlined at the call site of 0x2fad0 in CliSession::onPcCafeChargeStart.
CliSessionMessage::CliSessionMessage(CliSession* cs) : _cs(cs)
{
    if (_cs != nullptr)
        _cs->addReferenceCount(L"LobbyMessage.cpp", 21);
}

// LIFT: the original deleting destructor at 0x2fa40 inlines this body.
CliSessionMessage::~CliSessionMessage()
{
    if (_cs != nullptr)
        _cs->removeReferenceCount(L"LobbyMessage.cpp", 27);
}

// 0x2fa90
void CliSessionStopPcCafeChargeMessage::Dispatch(PcCafeMileage* acceptor)
{
    if (acceptor != nullptr)
    {
        long long now = _time64(nullptr);
        acceptor->Stop(_cs, now, nullptr);
    }
}

// 0x2fad0
void CliSessionStartPcCafeChargeMessage::Dispatch(PcCafeMileage* acceptor)
{
    if (acceptor != nullptr)
    {
        long long now = _time64(nullptr);
        acceptor->Start(_cs, now);
    }
}

// 0x2fb10
void CliSessionGradeChangedMessage::Dispatch(MembershipMileage* acceptor)
{
    if (acceptor != nullptr)
    {
        long long now = _time64(nullptr);
        acceptor->GradeChanged(_cs, now, gameGradeKey, reason, grade);
    }
}

// 0x2fb60
// LIFT: Not done. It needs the PcCafeMileage layout (_slotId, Mileage base), which lift-lobbydaemon-5 owns and main does not have yet (0x2fb60).
void CliSessionMileageInterimDepositMessage::Dispatch(PcCafeMileage*)
{
    LIFT_STUB(0x2fb60);
}
