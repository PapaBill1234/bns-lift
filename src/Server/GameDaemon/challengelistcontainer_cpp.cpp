// challengelistcontainer_cpp.cpp: challengelistcontainer.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "challengelistcontainer.h"
#include "pc.h"
#include "LiftStub.h"

// 0xe920
bool __cdecl ChallengeListEntry::Initialize(::Pc *const, ::Data::ChallengeListRecordPtr)
{
    LIFT_STUB(0xe920);
}

// 0xe9a0
bool __cdecl ChallengeListEntry::Initialize(::Pc *const, ::Data::ChallengeListRecordPtr, bool)
{
    LIFT_STUB(0xe9a0);
}

// 0xeab0
bool __cdecl ChallengeListEntry::SetCompletion(char)
{
    LIFT_STUB(0xeab0);
}

// 0xeb60
bool __cdecl ChallengeListEntry::SetTakenRewardCount(char)
{
    LIFT_STUB(0xeb60);
}

// 0xec30
short __cdecl ChallengeListEntry::FetchAll(char *, short) const
{
    LIFT_STUB(0xec30);
}

// 0xecf0
short __cdecl ChallengeListEntry::FetchDb(char *, short) const
{
    LIFT_STUB(0xecf0);
}

// 0xee80
char __cdecl ChallengeListEntry::GetCompletionCount(void) const
{
    LIFT_STUB(0xee80);
}

// 0xef90
__cdecl ChallengeListContainer::~ChallengeListContainer(void)
{
    LIFT_STUB(0xef90);
}

// 0xf020
int __cdecl ChallengeListContainer::SetDbList(short, char const *, int)
{
    LIFT_STUB(0xf020);
}

// 0xf6a0
bool __cdecl ChallengeListContainer::Acquire(void)
{
    LIFT_STUB(0xf6a0);
}

// 0xfaa0
void __cdecl ChallengeListContainer::SetCompletionChallenge(char, char, __int64, wchar_t const *)
{
    LIFT_STUB(0xfaa0);
}

// 0xfe50
bool __cdecl ChallengeListContainer::SetTakenRewardCount(char, char)
{
    LIFT_STUB(0xfe50);
}

// 0xff40
void __cdecl ChallengeListContainer::ResetChallengeLists(void)
{
    LIFT_STUB(0xff40);
}

// 0x10440
void __cdecl ChallengeListContainer::SendChallengeLists(void)
{
    LIFT_STUB(0x10440);
}

// 0x107b0
::ChallengeListEntry * __cdecl ChallengeListContainer::getEntry(char)
{
    LIFT_STUB(0x107b0);
}

// 0x10900
bool __cdecl ChallengeListContainer::addEntry(::ChallengeListEntry *)
{
    LIFT_STUB(0x10900);
}

// 0x10b50
void __cdecl ChallengeListContainer::notifyChange(::ChallengeListEntry *)
{
    LIFT_STUB(0x10b50);
}
