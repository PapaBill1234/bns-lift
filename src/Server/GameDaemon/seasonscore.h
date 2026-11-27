// seasonscore.h: seasonscore.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class SeasonContentsCombatRecordContainer
{
public:
    enum CombatResultType {};
    struct SeasonContentsCombatRecordValue {};
public:
    __cdecl ~SeasonContentsCombatRecordContainer(void);  // 0x1ba0a0
private:
    int const __cdecl convertSeasonContentsTypeToEntryIndex(char) const;  // 0x1ba150
    void __cdecl syncToClient(::SeasonContentsCombatRecordEntry *) const;  // 0x1ba1f0
public:
    bool __cdecl Initialize(::Pc *);  // 0x1ba440
    bool __cdecl GetNewRecordValue(char, ::SeasonContentsCombatRecordContainer::CombatResultType, int, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue &, bool &) const;  // 0x1ba580
    bool __cdecl GetRestoreDisconnectRecordValue(char, int, int, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue &, int &) const;  // 0x1ba830
    bool __cdecl SetRecordValue(char, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue &, bool, bool);  // 0x1baba0
    bool __cdecl GetNewRecordValueForBattleRoyal(char, int, int, int, bool, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue &, bool &) const;  // 0x1bae40
    ::SeasonContentsCombatRecordEntry const * __cdecl GetRecordEntry(char);  // 0x1bb0c0
    void __cdecl FetchList(::Packet *, ::RepeatPacketComposer *);  // 0x1bb150
};

class SeasonContentsCombatRecordEntry
{
public:
    __cdecl SeasonContentsCombatRecordEntry(void);  // 0x1b9f00
    __cdecl ~SeasonContentsCombatRecordEntry(void);  // 0x1b9f50
    void __cdecl Initialize(char, int, int, int, int, int, int, int, int, int);  // 0x1b9f70
};

class SeasonContentsGuildCombatRecordContainer
{
public:
    enum GuildCombatResultType {};
public:
    __cdecl ~SeasonContentsGuildCombatRecordContainer(void);  // 0x1bb4b0
private:
    void __cdecl syncToMember(::SeasonContentsGuildCombatRecordEntry *, int) const;  // 0x1bb540
public:
    bool __cdecl Initialize(::Guild *);  // 0x1bb7c0
    bool __cdecl GetNewRecord(char, ::SeasonContentsGuildCombatRecordContainer::GuildCombatResultType, int, ::SeasonContentsGuildCombatRecord &, bool &) const;  // 0x1bb900
    bool __cdecl SetRecord(::SeasonContentsGuildCombatRecord const &, bool, bool, int);  // 0x1bbba0
    ::SeasonContentsGuildCombatRecordEntry const * __cdecl GetRecordEntry(char);  // 0x1bbe50
    void __cdecl FetchList(::FragmentPacket &);  // 0x1bbed0
};

class SeasonContentsGuildCombatRecordEntry
{
public:
    bool __cdecl FetchPacket(::FragmentPacket &) const;  // 0x1bb3f0
};

class SeasonContentsTimeAttackRecordContainer
{
public:
    struct SeasonContentsTimeAttackRecordValue {};
public:
    __cdecl ~SeasonContentsTimeAttackRecordContainer(void);  // 0x1bc1e0
private:
    void __cdecl syncToClient(::SeasonContentsTimeAttackRecordEntry *) const;  // 0x1bc290
public:
    bool __cdecl Initialize(::Pc *);  // 0x1bc4e0
    bool __cdecl GetNewRecordValue(char, short, int, wchar_t const *, ::SeasonContentsTimeAttackRecordContainer::SeasonContentsTimeAttackRecordValue &, bool &, bool &) const;  // 0x1bc620
    bool __cdecl SetRecordValue(char, ::SeasonContentsTimeAttackRecordContainer::SeasonContentsTimeAttackRecordValue &, bool, bool);  // 0x1bc940
    ::SeasonContentsTimeAttackRecordEntry const * __cdecl GetRecordEntry(char);  // 0x1bcbc0
    void __cdecl FetchList(::Packet *, ::RepeatPacketComposer *);  // 0x1bcc70
};

class SeasonContentsTimeAttackRecordEntry
{
public:
    __cdecl SeasonContentsTimeAttackRecordEntry(void);  // 0x1bc090
    __cdecl ~SeasonContentsTimeAttackRecordEntry(void);  // 0x1bc0e0
    void __cdecl Initialize(char, int, short, int, short, int, wchar_t *);  // 0x1bc100
};

