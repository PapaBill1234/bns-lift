// CliSessionJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "CliSessionJob.h"
#include "LiftStub.h"

// 0x3bef0
CliSessionJob::CliSessionJob(CliSession*)
{
    LIFT_STUB(0x3bef0);
}

// 0x3bfa0
CliSessionJob::~CliSessionJob()
{
    LIFT_STUB(0x3bfa0);
}

// 0x3c010
bool CliSessionJob::dispatch_work(int, void*)
{
    LIFT_STUB(0x3c010);
}
