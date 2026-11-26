// PcCafeMileage.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon PcCafeMileage.
// LIFT: header layout only (fix7). The function bodies are still LIFT_STUB.
#pragma once
#include "Mileage.h"

class CliSession;
class LobbyMessage;

// LIFT: PDB layout (sizeof 0x1368, Mileage base, no own members). The virtual dtor has no own symbol in the lift
// scope. It is not declared.
class PcCafeMileage : public Mileage
{
public:
    // LIFT: inline in MileageManager::Initialize (0x5f5a0).
    explicit PcCafeMileage(int slotId) : Mileage(slotId) {}
    virtual void Accept(LobbyMessage*);  // 0x633b0
    virtual bool Start(CliSession*, long long);  // 0x63400
    virtual bool Stop(CliSession*, long long, long long*);  // 0x636b0
};
static_assert(sizeof(PcCafeMileage) == 0x1368, "sizeof PcCafeMileage");
