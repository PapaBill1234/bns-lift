// collectingmanager_cpp.cpp: collectingmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "collectingmanager.h"
#include "LiftStub.h"

// 0x814b0
__cdecl CollectingEntry::~CollectingEntry(void)
{
    LIFT_STUB(0x814b0);
}

// 0x81540
short __cdecl CollectingEntry::FetchAll(char *, short) const
{
    LIFT_STUB(0x81540);
}

// 0x81600
short __cdecl CollectingEntry::FetchDb(char *, short) const
{
    LIFT_STUB(0x81600);
}

// 0x81780
bool __cdecl CollectingEntry::FetchXmlData(wchar_t *, short) const
{
    LIFT_STUB(0x81780);
}

// 0x819b0
bool __cdecl CollectingEntry::SetSyncContext(::SyncContext &)
{
    LIFT_STUB(0x819b0);
}

// 0x81ab0
bool __cdecl CollectingEntry::GetCollectingPropertyTransaction(::PropertyTransactionSyncData &)
{
    LIFT_STUB(0x81ab0);
}

// 0x81c50
__cdecl CollectingContainer::~CollectingContainer(void)
{
    LIFT_STUB(0x81c50);
}

// 0x81d20
int __cdecl CollectingContainer::SetDbList(short, char const *, int)
{
    LIFT_STUB(0x81d20);
}

// 0x82200
void __cdecl CollectingContainer::SendCollectingList(void)
{
    LIFT_STUB(0x82200);
}

// 0x82470
void __cdecl CollectingContainer::notifyAcquire(::CollectingEntry const *)
{
    LIFT_STUB(0x82470);
}

// 0x82630
::CollectingEntry * __cdecl CollectingContainer::getCollectingByIndex(short, int, int)
{
    LIFT_STUB(0x82630);
}

// 0x82840
bool __cdecl CollectingContainer::addCollecting(::CollectingEntry *, int &)
{
    LIFT_STUB(0x82840);
}

// 0x82aa0
bool __cdecl CollectingContainer::checkItemEquipFilter(::Data::ItemRecordPtr, int)
{
    LIFT_STUB(0x82aa0);
}

// 0x82cb0
bool __cdecl CollectingContainer::checkClosetCollectingItem(::Data::CollectingRecordClosetPtr, short, ::CollectingContainer::CollectingOrder *const, ::CollectingEntry::CollectingGameLogInfo &)
{
    LIFT_STUB(0x82cb0);
}

// 0x837a0
::GameFailReason __cdecl CollectingContainer::TryToCompleteClosetCollecting(int, short, ::CollectingContainer::CollectingOrder *const)
{
    LIFT_STUB(0x837a0);
}

// 0x84030
::GameFailReason __cdecl CollectingContainer::CompleteClosetCollectingOk(::CompleteClosetCollectingOkParam &)
{
    LIFT_STUB(0x84030);
}

// 0x84a10
void __cdecl CollectingContainer::CompleteClosetCollectingFail(::CompleteClosetCollectingFailParam &)
{
    LIFT_STUB(0x84a10);
}

// 0x84ee0
int __cdecl CollectingContainer::GetClosetCollectingGrade(void)
{
    LIFT_STUB(0x84ee0);
}

// 0x84fb0
bool __cdecl CollectingContainer::CheckEquipCharacteristics(::Data::CollectingRecordPtr const &)
{
    LIFT_STUB(0x84fb0);
}
