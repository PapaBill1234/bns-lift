// questjournal_h.cpp: questjournal.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "questjournal.h"
#include "Daemon.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?getDaemonUpTimeSec@OpenQuest@@AEAAJXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?findQuestIndex@QuestJournal@@AEBAHG@Z")  // LIFT: dead-strip keep (no live caller yet)

// Partial PDB layouts for findQuestIndex.
struct QuestRecordView  // DrEl (size 6)
{
    char type;              // +0
    short subtype;          // +2
    unsigned short size;    // +4
};

struct QuestDataView  // Quest
{
    QuestRecordView *_questRecord;  // +0
};

struct OpenQuestView
{
    QuestDataView *_questData;      // +0
};

enum
{
    QuestJournal_openQuests = 32,   // OpenQuest * _openQuests[67]
    QuestJournal_openQuestCount = 67
};

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
    OpenQuestView *const *openQuests = reinterpret_cast<OpenQuestView *const *>(reinterpret_cast<const char *>(this) + QuestJournal_openQuests);
    for (unsigned short i = 0; i < QuestJournal_openQuestCount; ++i)
    {
        OpenQuestView *quest = openQuests[i];
        if (quest != nullptr && quest->_questData->_questRecord[1].subtype == questId)
            return i;
    }
    return -1;
}
