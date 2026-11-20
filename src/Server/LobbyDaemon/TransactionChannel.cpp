// TransactionChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "TransactionChannel.h"
#include "LiftStub.h"

// 0x7b0d0
unsigned long long LobbyJobTransaction::GetTid() const
{
    LIFT_STUB(0x7b0d0);
}

// 0x7b100
TransactionChannel::~TransactionChannel()
{
    LIFT_STUB(0x7b100);
}

// 0x7b170
bool TransactionChannel::InitializeTransactionChannel(long)
{
    LIFT_STUB(0x7b170);
}

// 0x7b7a0
void LobbyJobTransaction::Expire()
{
    LIFT_STUB(0x7b7a0);
}
