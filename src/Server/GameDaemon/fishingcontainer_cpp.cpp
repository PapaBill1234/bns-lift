// fishingcontainer_cpp.cpp: fishingcontainer.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "fishingcontainer.h"
#include "pc.h"
#include "LiftStub.h"

// 0xbae40
bool __cdecl FishingEntry::Initialize(::Pc *const, ::Data::FishRecordPtr)
{
    LIFT_STUB(0xbae40);
}

// 0xbaec0
bool __cdecl FishingEntry::Initialize(::Pc *const, ::Data::FishRecordPtr, int)
{
    LIFT_STUB(0xbaec0);
}

// 0xbaf70
short __cdecl FishingEntry::FetchAll(char *, short) const
{
    LIFT_STUB(0xbaf70);
}

// 0xbb030
short __cdecl FishingEntry::FetchDb(char *, short) const
{
    LIFT_STUB(0xbb030);
}

// 0xbb1c0
bool __cdecl FishingEntry::IncreaseFishCount(int)
{
    LIFT_STUB(0xbb1c0);
}

// 0xbb480
__cdecl FishingContainer::~FishingContainer(void)
{
    LIFT_STUB(0xbb480);
}

// 0xbb610
int __cdecl FishingContainer::SetDbList(short, char const *, int)
{
    LIFT_STUB(0xbb610);
}

// 0xbbac0
void __cdecl FishingContainer::SendFishingList(void)
{
    LIFT_STUB(0xbbac0);
}

// 0xbbd80
void __cdecl FishingContainer::notifyAcquire(::FishingEntry const *)
{
    LIFT_STUB(0xbbd80);
}

// 0xbbf40
void __cdecl FishingContainer::notifyChange(::FishingEntry const *)
{
    LIFT_STUB(0xbbf40);
}

// 0xbc100
::FishingEntry * __cdecl FishingContainer::getEntry(short)
{
    LIFT_STUB(0xbc100);
}

// 0xbc240
bool __cdecl FishingContainer::addEntry(::FishingEntry *)
{
    LIFT_STUB(0xbc240);
}

// 0xbc4b0
bool __cdecl FishingContainer::acquire(::Data::FishRecordPtr, int)
{
    LIFT_STUB(0xbc4b0);
}

// 0xbc7a0
bool __cdecl FishingContainer::update(::FishingEntry *, int, ::FishInfoStatus &)
{
    LIFT_STUB(0xbc7a0);
}

// 0xbc860
void __cdecl FishingContainer::writeGameLog(short, int, int)
{
    LIFT_STUB(0xbc860);
}

// 0xbc9e0
bool __cdecl FishingContainer::UpdateFishingInfo(::Data::FishRecordPtr, int, ::FishInfoStatus &)
{
    LIFT_STUB(0xbc9e0);
}

// 0xbcae0
bool __cdecl FishingContainer::ConfirmAcquire(short)
{
    LIFT_STUB(0xbcae0);
}
