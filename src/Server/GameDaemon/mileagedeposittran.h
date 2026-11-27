// mileagedeposittran.h: mileagedeposittran.cpp, mileagedeposittran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class MileageDepositTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1107e0
    __cdecl MileageDepositTran(::User *);  // 0x16b9d0
private:
    virtual bool __cdecl work(int, void *);  // 0x16bb30
    bool __cdecl init(int, void *);  // 0x16bbe0
    bool __cdecl mileageDepositTranOk(void *);  // 0x16bf00
    bool __cdecl mileageDepositTranFail(void *);  // 0x16ca90
};

class UnsentMileageDepositManager
{
private:
    __cdecl ~UnsentMileageDepositManager(void);  // 0x16cf30
public:
    bool __cdecl Initialize(::FragmentPacketConcatenater *);  // 0x16cf70
    void __cdecl SendMileageDeposit(void);  // 0x16d290
};

