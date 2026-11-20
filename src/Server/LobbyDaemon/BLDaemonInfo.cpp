// BLDaemonInfo.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "BLDaemonInfo.h"
#include "LiftStub.h"

// 0x403c0
BLDaemonInfoTable::BLDaemonInfoTable()
{
    LIFT_STUB(0x403c0);
}

// 0x40490
BLDaemonInfoTable::~BLDaemonInfoTable()
{
    LIFT_STUB(0x40490);
}

// 0x40510
bool BLDaemonInfoTable::load(wchar_t const*, BLDaemonInfo**&, int&)
{
    LIFT_STUB(0x40510);
}

// 0x40e30
bool BLDaemonInfoTable::add(BLDaemonInfo*)
{
    LIFT_STUB(0x40e30);
}

// 0x40f30
bool BLDaemonInfoTable::Load(wchar_t const*)
{
    LIFT_STUB(0x40f30);
}

// 0x41090
void BLDaemonInfoTable::Update(wchar_t const*)
{
    LIFT_STUB(0x41090);
}

// 0x41210
BLDaemonInfo const* BLDaemonInfoTable::Find(BLDaemonID const&) const
{
    LIFT_STUB(0x41210);
}

// 0x412d0
void BLDaemonInfoTable::Clear()
{
    LIFT_STUB(0x412d0);
}
