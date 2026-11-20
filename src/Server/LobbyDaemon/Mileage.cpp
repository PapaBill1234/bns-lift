// Mileage.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "Mileage.h"
#include "LiftStub.h"

// 0x5d370
LobbyMessageAcceptor::~LobbyMessageAcceptor()
{
    LIFT_STUB(0x5d370);
}

// 0x5d390
bool MileageInfo::check() const
{
    LIFT_STUB(0x5d390);
}

// 0x5d410
MileageConfig::MileageConfig()
{
    LIFT_STUB(0x5d410);
}

// 0x5d460
MileageConfig::~MileageConfig()
{
    LIFT_STUB(0x5d460);
}

// 0x5d760
bool MileageConfig::Check() const
{
    LIFT_STUB(0x5d760);
}

// 0x5d8a0
Mileage::~Mileage()
{
    LIFT_STUB(0x5d8a0);
}

// 0x5d940
bool Mileage::Initialize(MileageConfig const&, long long)
{
    LIFT_STUB(0x5d940);
}

// 0x5dbf0
bool Mileage::FetchFeverTimeList(FragmentPacket*) const
{
    LIFT_STUB(0x5dbf0);
}

// 0x5e1a0
bool Mileage::deposit(id128 const&, long long, long long, long long, MileageLimit*, bool)
{
    LIFT_STUB(0x5e1a0);
}

// 0x5f480
MileageManager::~MileageManager()
{
    LIFT_STUB(0x5f480);
}

// 0x5f5a0
bool MileageManager::Initialize(long long)
{
    LIFT_STUB(0x5f5a0);
}

// 0x5fc30
MileageSlot* MileageManager::CreateSlot(id128 const&, unsigned long long)
{
    LIFT_STUB(0x5fc30);
}

// 0x60660
void MileageManager::Accept(LobbyMessage*)
{
    LIFT_STUB(0x60660);
}

// 0x606b0
MileageSession::MileageSession(Mileage*, long long)
{
    LIFT_STUB(0x606b0);
}

// 0x60770
MileageSession::~MileageSession()
{
    LIFT_STUB(0x60770);
}

// 0x60800
void MileageSession::ReserveInterimDeposit(unsigned long long)
{
    LIFT_STUB(0x60800);
}

// 0x608d0
MileageSlot::MileageSlot(int)
{
    LIFT_STUB(0x608d0);
}

// 0x60950
MileageSlot::~MileageSlot()
{
    LIFT_STUB(0x60950);
}

// 0x60a80
MileageInterimDepositTimer::MileageInterimDepositTimer(long long)
{
    LIFT_STUB(0x60a80);
}

// 0x60b20
MileageInterimDepositTimer::~MileageInterimDepositTimer()
{
    LIFT_STUB(0x60b20);
}

// 0x60d00
bool MileageInterimDepositTimer::Tick(long long)
{
    LIFT_STUB(0x60d00);
}

// 0x61060
bool MileageBatchRetryDeposit::Tick(long long)
{
    LIFT_STUB(0x61060);
}
