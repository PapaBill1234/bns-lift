// WaitQueue.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "WaitQueue.h"
#include "LiftStub.h"

// 0xdc540
WaitQueue::WaitQueue()
{
    LIFT_STUB(0xdc540);
}

// 0xdc590
WaitQueue::~WaitQueue()
{
    LIFT_STUB(0xdc590);
}

// 0xdc5e0
bool WaitQueue::Add(unsigned long long, short&, int&)
{
    LIFT_STUB(0xdc5e0);
}

// 0xdc720
bool WaitQueue::Remove(short const&, unsigned long long)
{
    LIFT_STUB(0xdc720);
}

// 0xdc870
bool WaitQueue::QueryTurn(short const&, int&) const
{
    LIFT_STUB(0xdc870);
}

// 0xdc920
WaitQueueList::~WaitQueueList()
{
    LIFT_STUB(0xdc920);
}

// 0xdc940
bool WaitQueueList::Init(int)
{
    LIFT_STUB(0xdc940);
}

// 0xdca20
unsigned long long WaitQueueList::Pop()
{
    LIFT_STUB(0xdca20);
}
