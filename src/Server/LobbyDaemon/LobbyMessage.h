// LobbyMessage.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class LobbyMessageAcceptor;
class MembershipMileage;
class PcCafeMileage;

class CliSessionGradeChangedMessage
{
public:
    virtual void Dispatch(MembershipMileage*);  // 0x2fb10
};

class CliSessionMileageInterimDepositMessage
{
public:
    virtual void Dispatch(PcCafeMileage*);  // 0x2fb60
};

class CliSessionStartPcCafeChargeMessage
{
public:
    virtual void Dispatch(PcCafeMileage*);  // 0x2fad0
};

class CliSessionStopPcCafeChargeMessage
{
public:
    virtual void Dispatch(PcCafeMileage*);  // 0x2fa90
    virtual ~CliSessionStopPcCafeChargeMessage();  // 0x32b60
};

class LobbyMessage
{
public:
    virtual ~LobbyMessage();  // 0x2f9d0
    virtual void Dispatch(LobbyMessageAcceptor*);  // 0x2f9e0
};
