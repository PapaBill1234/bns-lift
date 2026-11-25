// LobbyMessage.obj (LobbyDaemon 2019 + PDB).
#pragma once
#include "GradeService.h"

class CliSession;
class LobbyMessageAcceptor;
class MembershipMileage;
class PcCafeMileage;

class LobbyMessage
{
public:
    virtual ~LobbyMessage();  // 0x2f9d0
    // LIFT: MSVC reverses overloaded virtuals in the vtable. The PDB slots are
    // MembershipMileage* at +8, PcCafeMileage* at +16, LobbyMessageAcceptor* at +24.
    virtual void Dispatch(LobbyMessageAcceptor* acceptor);  // 0x2f9e0
    virtual void Dispatch(PcCafeMileage*) {}  // 0x32b50 (folded)
    virtual void Dispatch(MembershipMileage*) {}  // 0x32b50 (folded)
};
static_assert(sizeof(LobbyMessage) == 0x8, "sizeof LobbyMessage");

class CliSessionMessage : public LobbyMessage
{
public:
    explicit CliSessionMessage(CliSession* cs);
    virtual ~CliSessionMessage();

protected:
    CliSession* _cs;

private:
    // LIFT: these lifts do not use copies of ref-counted messages (0x2fa40).
    CliSessionMessage(CliSessionMessage const&);
    CliSessionMessage& operator=(CliSessionMessage const&);
};
static_assert(sizeof(CliSessionMessage) == 0x10, "sizeof CliSessionMessage");

class CliSessionGradeChangedMessage : public CliSessionMessage
{
public:
    // LIFT: the constructor is inline in the original (0x539d0).
    CliSessionGradeChangedMessage(CliSession* cs, int gameGradeKey, GradeService::GradeChangedReasonType reason, Grade* grade)
        : CliSessionMessage(cs), gameGradeKey(gameGradeKey), reason(reason), grade(grade) {}
    virtual void Dispatch(MembershipMileage*);  // 0x2fb10
    int gameGradeKey;
    GradeService::GradeChangedReasonType reason;
    Grade* grade;
};
static_assert(sizeof(CliSessionGradeChangedMessage) == 0x20, "sizeof CliSessionGradeChangedMessage");

class CliSessionMileageInterimDepositMessage : public CliSessionMessage
{
public:
    CliSessionMileageInterimDepositMessage(CliSession* cs, unsigned long long sessionId)
        : CliSessionMessage(cs), sessionId(sessionId) {}
    virtual void Dispatch(PcCafeMileage*);  // 0x2fb60
    unsigned long long sessionId;
};
static_assert(sizeof(CliSessionMileageInterimDepositMessage) == 0x18, "sizeof CliSessionMileageInterimDepositMessage");

class CliSessionStartPcCafeChargeMessage : public CliSessionMessage
{
public:
    explicit CliSessionStartPcCafeChargeMessage(CliSession* cs) : CliSessionMessage(cs) {}
    virtual void Dispatch(PcCafeMileage* acceptor);  // 0x2fad0
};
static_assert(sizeof(CliSessionStartPcCafeChargeMessage) == 0x10, "sizeof CliSessionStartPcCafeChargeMessage");

class CliSessionStopPcCafeChargeMessage : public CliSessionMessage
{
public:
    explicit CliSessionStopPcCafeChargeMessage(CliSession* cs) : CliSessionMessage(cs) {}
    virtual ~CliSessionStopPcCafeChargeMessage();  // 0x32b60
    virtual void Dispatch(PcCafeMileage* acceptor);  // 0x2fa90
};
static_assert(sizeof(CliSessionStopPcCafeChargeMessage) == 0x10, "sizeof CliSessionStopPcCafeChargeMessage");

// PDB class CliSessionEnterWorldMessage (size 0x10). GameServiceLocation::OnEnter (0x3b3d0) sends it.
// LIFT: /OPT:ICF folds both Dispatch bodies into 0x2fad0 (same code as CliSessionStartPcCafeChargeMessage).
class CliSessionEnterWorldMessage : public CliSessionMessage
{
public:
    explicit CliSessionEnterWorldMessage(CliSession* cs) : CliSessionMessage(cs) {}
    virtual void Dispatch(PcCafeMileage* acceptor);  // 0x2fad0 (folded)
    virtual void Dispatch(MembershipMileage* acceptor);  // 0x2fad0 (folded)
};
static_assert(sizeof(CliSessionEnterWorldMessage) == 0x10, "sizeof CliSessionEnterWorldMessage");

// PDB class CliSessionLeaveWorldMessage (size 0x10). GameServiceLocation::OnLeave (0x3b540) sends it.
// LIFT: /OPT:ICF folds both Dispatch bodies into 0x2fa90 (same code as CliSessionStopPcCafeChargeMessage).
class CliSessionLeaveWorldMessage : public CliSessionMessage
{
public:
    explicit CliSessionLeaveWorldMessage(CliSession* cs) : CliSessionMessage(cs) {}
    virtual void Dispatch(PcCafeMileage* acceptor);  // 0x2fa90 (folded)
    virtual void Dispatch(MembershipMileage* acceptor);  // 0x2fa90 (folded)
};
static_assert(sizeof(CliSessionLeaveWorldMessage) == 0x10, "sizeof CliSessionLeaveWorldMessage");
