// GradeService.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GradeService.h"
#include "LiftStub.h"

// 0x53370
bool Grade::FetchGame(FragmentPacket*) const
{
    LIFT_STUB(0x53370);
}

// 0x53450
GradeService::GradeService()
{
    LIFT_STUB(0x53450);
}

// 0x534d0
GradeService::GradeService(int)
{
    LIFT_STUB(0x534d0);
}

// 0x53550
GradeService::~GradeService()
{
    LIFT_STUB(0x53550);
}

// 0x535c0
void GradeService::clearGradeList()
{
    LIFT_STUB(0x535c0);
}

// 0x542e0
bool GradeService::IsActivated(int, long long) const
{
    LIFT_STUB(0x542e0);
}

// 0x54390
Grade const* GradeService::GetGrade(int) const
{
    LIFT_STUB(0x54390);
}

// 0x54400
bool GradeService::FetchGradeLevel(FragmentPacket*) const
{
    LIFT_STUB(0x54400);
}

// 0x544d0
bool GradeService::FetchGameGradeList(FragmentPacket*) const
{
    LIFT_STUB(0x544d0);
}
