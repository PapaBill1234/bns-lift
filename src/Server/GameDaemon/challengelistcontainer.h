// challengelistcontainer.h: challengelistcontainer.cpp, challengelistcontainer.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ChallengeListContainer
{
public:
    __cdecl ~ChallengeListContainer(void);  // 0xef90
    int __cdecl SetDbList(short, char const *, int);  // 0xf020
    bool __cdecl Acquire(void);  // 0xf6a0
    void __cdecl SetCompletionChallenge(char, char, __int64, wchar_t const *);  // 0xfaa0
    bool __cdecl SetTakenRewardCount(char, char);  // 0xfe50
    void __cdecl ResetChallengeLists(void);  // 0xff40
    void __cdecl SendChallengeLists(void);  // 0x10440
private:
    ::ChallengeListEntry * __cdecl getEntry(char);  // 0x107b0
    bool __cdecl addEntry(::ChallengeListEntry *);  // 0x10900
    void __cdecl notifyChange(::ChallengeListEntry *);  // 0x10b50
};

class ChallengeListEntry
{
public:
    __cdecl ChallengeListEntry(void);  // 0xe320
    bool __cdecl Initialize(::Pc *const, ::Data::ChallengeListRecordPtr);  // 0xe920
    bool __cdecl Initialize(::Pc *const, ::Data::ChallengeListRecordPtr, bool);  // 0xe9a0
    bool __cdecl SetCompletion(char);  // 0xeab0
    bool __cdecl SetTakenRewardCount(char);  // 0xeb60
    short __cdecl FetchAll(char *, short) const;  // 0xec30
    short __cdecl FetchDb(char *, short) const;  // 0xecf0
    char __cdecl GetCompletionCount(void) const;  // 0xee80
};

