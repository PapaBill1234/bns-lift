// CliSessionTable.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "CliSessionTable.h"
#include "LiftStub.h"

// 0x3d0a0
CliSessionTable::~CliSessionTable()
{
    LIFT_STUB(0x3d0a0);
}

// 0x3d940
bool CliSessionTable::Initialize(int, int, short, short, short, short)
{
    LIFT_STUB(0x3d940);
}

// 0x3de80
bool CliSessionTable::Insert(CliSession*)
{
    LIFT_STUB(0x3de80);
}

// 0x3df60
bool CliSessionTable::Insert_index_gate(short, GateNode*)
{
    LIFT_STUB(0x3df60);
}

// 0x3dff0
void CliSessionTable::Delete(unsigned long long)
{
    LIFT_STUB(0x3dff0);
}

// 0x3e100
void CliSessionTable::Delete_index_gate(short, GateNode*)
{
    LIFT_STUB(0x3e100);
}

// 0x3e180
CliSession* CliSessionTable::Select(unsigned long long)
{
    LIFT_STUB(0x3e180);
}

// 0x3e270
bool CliSessionTable::Insert_index_gatekey(short, unsigned long long, CliSession*)
{
    LIFT_STUB(0x3e270);
}

// 0x3e350
void CliSessionTable::Delete_index_gatekey(short, unsigned long long)
{
    LIFT_STUB(0x3e350);
}

// 0x3e450
CliSession* CliSessionTable::Select_index_gatekey(short, unsigned long long)
{
    LIFT_STUB(0x3e450);
}

// 0x3e670
bool CliSessionTable::Insert_index_account(id128 const&, CliSession*)
{
    LIFT_STUB(0x3e670);
}

// 0x3e750
void CliSessionTable::Delete_index_account(id128 const&)
{
    LIFT_STUB(0x3e750);
}

// 0x3e870
CliSession* CliSessionTable::Select_index_account(id128 const&)
{
    LIFT_STUB(0x3e870);
}

// 0x3e980
bool CliSessionTable::Insert_index_pcid(short, unsigned long long, CliSession*)
{
    LIFT_STUB(0x3e980);
}

// 0x3ea50
void CliSessionTable::Delete_index_pcid(short, unsigned long long)
{
    LIFT_STUB(0x3ea50);
}

// 0x3eb40
CliSession* CliSessionTable::Select_index_pcid(short, unsigned long long)
{
    LIFT_STUB(0x3eb40);
}
