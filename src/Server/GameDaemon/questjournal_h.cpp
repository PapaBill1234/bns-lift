// questjournal_h.cpp: questjournal.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "questjournal.h"
#include "Daemon.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?getDaemonUpTimeSec@OpenQuest@@AEAAJXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x454cb0
__cdecl OpenQuest::OpenQuest(void)
{
    LIFT_STUB(0x454cb0);
}

// 0x454d30
long __cdecl OpenQuest::getDaemonUpTimeSec(void)
{
    return static_cast<long>((static_cast<__int64>(GetTickCount64() - Daemon::Instance->StartSystemTick64)) / 1000);
}

// 0x454d70
int __cdecl QuestJournal::findQuestIndex(unsigned short questId) const
{
    LIFT_STUB(0x454d70);
}
