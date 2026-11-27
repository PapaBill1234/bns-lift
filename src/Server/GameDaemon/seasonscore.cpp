// seasonscore.cpp: seasonscore.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "seasonscore.h"
#include "guild.h"
#include "pc.h"
#include "LiftStub.h"

// 0x1b9f00
__cdecl SeasonContentsCombatRecordEntry::SeasonContentsCombatRecordEntry(void)
{
    LIFT_STUB(0x1b9f00);
}

// 0x1b9f50
__cdecl SeasonContentsCombatRecordEntry::~SeasonContentsCombatRecordEntry(void)
{
    LIFT_STUB(0x1b9f50);
}

// 0x1b9f70
void __cdecl SeasonContentsCombatRecordEntry::Initialize(char, int, int, int, int, int, int, int, int, int)
{
    LIFT_STUB(0x1b9f70);
}

// 0x1ba0a0
__cdecl SeasonContentsCombatRecordContainer::~SeasonContentsCombatRecordContainer(void)
{
    LIFT_STUB(0x1ba0a0);
}

// 0x1ba150
int const __cdecl SeasonContentsCombatRecordContainer::convertSeasonContentsTypeToEntryIndex(char) const
{
    LIFT_STUB(0x1ba150);
}

// 0x1ba1f0
void __cdecl SeasonContentsCombatRecordContainer::syncToClient(::SeasonContentsCombatRecordEntry *) const
{
    LIFT_STUB(0x1ba1f0);
}

// 0x1ba440
bool __cdecl SeasonContentsCombatRecordContainer::Initialize(::Pc *)
{
    LIFT_STUB(0x1ba440);
}

// 0x1ba580
bool __cdecl SeasonContentsCombatRecordContainer::GetNewRecordValue(char, ::SeasonContentsCombatRecordContainer::CombatResultType, int, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue &, bool &) const
{
    LIFT_STUB(0x1ba580);
}

// 0x1ba830
bool __cdecl SeasonContentsCombatRecordContainer::GetRestoreDisconnectRecordValue(char, int, int, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue &, int &) const
{
    LIFT_STUB(0x1ba830);
}

// 0x1baba0
bool __cdecl SeasonContentsCombatRecordContainer::SetRecordValue(char, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue &, bool, bool)
{
    LIFT_STUB(0x1baba0);
}

// 0x1bae40
bool __cdecl SeasonContentsCombatRecordContainer::GetNewRecordValueForBattleRoyal(char, int, int, int, bool, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue &, bool &) const
{
    LIFT_STUB(0x1bae40);
}

// 0x1bb0c0
::SeasonContentsCombatRecordEntry const * __cdecl SeasonContentsCombatRecordContainer::GetRecordEntry(char)
{
    LIFT_STUB(0x1bb0c0);
}

// 0x1bb150
void __cdecl SeasonContentsCombatRecordContainer::FetchList(::Packet *, ::RepeatPacketComposer *)
{
    LIFT_STUB(0x1bb150);
}

// 0x1bb3f0
bool __cdecl SeasonContentsGuildCombatRecordEntry::FetchPacket(::FragmentPacket &) const
{
    LIFT_STUB(0x1bb3f0);
}

// 0x1bb4b0
__cdecl SeasonContentsGuildCombatRecordContainer::~SeasonContentsGuildCombatRecordContainer(void)
{
    LIFT_STUB(0x1bb4b0);
}

// 0x1bb540
void __cdecl SeasonContentsGuildCombatRecordContainer::syncToMember(::SeasonContentsGuildCombatRecordEntry *, int) const
{
    LIFT_STUB(0x1bb540);
}

// 0x1bb7c0
bool __cdecl SeasonContentsGuildCombatRecordContainer::Initialize(::Guild *)
{
    LIFT_STUB(0x1bb7c0);
}

// 0x1bb900
bool __cdecl SeasonContentsGuildCombatRecordContainer::GetNewRecord(char, ::SeasonContentsGuildCombatRecordContainer::GuildCombatResultType, int, ::SeasonContentsGuildCombatRecord &, bool &) const
{
    LIFT_STUB(0x1bb900);
}

// 0x1bbba0
bool __cdecl SeasonContentsGuildCombatRecordContainer::SetRecord(::SeasonContentsGuildCombatRecord const &, bool, bool, int)
{
    LIFT_STUB(0x1bbba0);
}

// 0x1bbe50
::SeasonContentsGuildCombatRecordEntry const * __cdecl SeasonContentsGuildCombatRecordContainer::GetRecordEntry(char)
{
    LIFT_STUB(0x1bbe50);
}

// 0x1bbed0
void __cdecl SeasonContentsGuildCombatRecordContainer::FetchList(::FragmentPacket &)
{
    LIFT_STUB(0x1bbed0);
}

// 0x1bc090
__cdecl SeasonContentsTimeAttackRecordEntry::SeasonContentsTimeAttackRecordEntry(void)
{
    LIFT_STUB(0x1bc090);
}

// 0x1bc0e0
__cdecl SeasonContentsTimeAttackRecordEntry::~SeasonContentsTimeAttackRecordEntry(void)
{
    LIFT_STUB(0x1bc0e0);
}

// 0x1bc100
void __cdecl SeasonContentsTimeAttackRecordEntry::Initialize(char, int, short, int, short, int, wchar_t *)
{
    LIFT_STUB(0x1bc100);
}

// 0x1bc1e0
__cdecl SeasonContentsTimeAttackRecordContainer::~SeasonContentsTimeAttackRecordContainer(void)
{
    LIFT_STUB(0x1bc1e0);
}

// 0x1bc290
void __cdecl SeasonContentsTimeAttackRecordContainer::syncToClient(::SeasonContentsTimeAttackRecordEntry *) const
{
    LIFT_STUB(0x1bc290);
}

// 0x1bc4e0
bool __cdecl SeasonContentsTimeAttackRecordContainer::Initialize(::Pc *)
{
    LIFT_STUB(0x1bc4e0);
}

// 0x1bc620
bool __cdecl SeasonContentsTimeAttackRecordContainer::GetNewRecordValue(char, short, int, wchar_t const *, ::SeasonContentsTimeAttackRecordContainer::SeasonContentsTimeAttackRecordValue &, bool &, bool &) const
{
    LIFT_STUB(0x1bc620);
}

// 0x1bc940
bool __cdecl SeasonContentsTimeAttackRecordContainer::SetRecordValue(char, ::SeasonContentsTimeAttackRecordContainer::SeasonContentsTimeAttackRecordValue &, bool, bool)
{
    LIFT_STUB(0x1bc940);
}

// 0x1bcbc0
::SeasonContentsTimeAttackRecordEntry const * __cdecl SeasonContentsTimeAttackRecordContainer::GetRecordEntry(char)
{
    LIFT_STUB(0x1bcbc0);
}

// 0x1bcc70
void __cdecl SeasonContentsTimeAttackRecordContainer::FetchList(::Packet *, ::RepeatPacketComposer *)
{
    LIFT_STUB(0x1bcc70);
}
