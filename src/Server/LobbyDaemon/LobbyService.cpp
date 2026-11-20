// LobbyService.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyService.h"
#include "LiftStub.h"

// 0x6c330
bool LobbyService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6c330);
}

// 0x6c550
bool CharacterCosmesisService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6c550);
}

// 0x6c760
bool ChangeCharacterRaceService::IsServiceTarget(Character*)
{
    LIFT_STUB(0x6c760);
}

// 0x6c780
bool CharacterCosmesisService::Start(CliSession*, unsigned int, char*, int)
{
    LIFT_STUB(0x6c780);
}

// 0x6c980
bool CharacterCosmesisService::ConsumeItemTried(CliSession*)
{
    LIFT_STUB(0x6c980);
}

// 0x6cb80
bool CharacterCosmesisService::TaskDone(CliSession*)
{
    LIFT_STUB(0x6cb80);
}

// 0x6cd80
bool CharacterCosmesisService::ConsumeItemFinished(CliSession*)
{
    LIFT_STUB(0x6cd80);
}

// 0x6cf80
bool CharacterCosmesisService::Finish(CliSession*)
{
    LIFT_STUB(0x6cf80);
}

// 0x6d240
bool AddSlotService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6d240);
}

// 0x6d3e0
bool AddSlotService::IsServiceTarget(id128 const&)
{
    LIFT_STUB(0x6d3e0);
}

// 0x6d420
bool AddSlotService::Start(CliSession*, unsigned int)
{
    LIFT_STUB(0x6d420);
}

// 0x6d5d0
bool AddSlotService::ConsumeItemTried(CliSession*)
{
    LIFT_STUB(0x6d5d0);
}

// 0x6d7d0
bool AddSlotService::TaskDone(CliSession*, id128 const&)
{
    LIFT_STUB(0x6d7d0);
}

// 0x6dab0
bool AddSlotService::ConsumeItemFinished(CliSession*)
{
    LIFT_STUB(0x6dab0);
}

// 0x6dcb0
bool AddSlotService::Finish(CliSession*)
{
    LIFT_STUB(0x6dcb0);
}

// 0x6df60
bool RenameCharacterService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6df60);
}

// 0x6e170
bool RenameCharacterService::IsServiceTarget(Character*)
{
    LIFT_STUB(0x6e170);
}

// 0x6e190
bool RenameCharacterService::Start(CliSession*, unsigned int, wchar_t const*, int)
{
    LIFT_STUB(0x6e190);
}

// 0x6e440
bool RenameCharacterService::ConsumeItemTried(CliSession*)
{
    LIFT_STUB(0x6e440);
}

// 0x6e640
bool RenameCharacterService::TaskDone(CliSession*)
{
    LIFT_STUB(0x6e640);
}

// 0x6e840
bool RenameCharacterService::ConsumeItemFinished(CliSession*)
{
    LIFT_STUB(0x6e840);
}

// 0x6ea40
bool RenameCharacterService::Finish(CliSession*)
{
    LIFT_STUB(0x6ea40);
}

// 0x6ec40
bool RenameUserService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6ec40);
}

// 0x6ece0
bool RenameUserService::Start(CliSession*, wchar_t const*, wchar_t const*)
{
    LIFT_STUB(0x6ece0);
}

// 0x6edf0
bool RenameUserService::Finish(CliSession*, unsigned long long, unsigned int)
{
    LIFT_STUB(0x6edf0);
}

// 0x6f000
bool ExtendJumpingCharacterCreationQuotaService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6f000);
}

// 0x6f1b0
bool ExtendJumpingCharacterCreationQuotaService::Start(CliSession*, unsigned int)
{
    LIFT_STUB(0x6f1b0);
}

// 0x6f360
bool ExtendJumpingCharacterCreationQuotaService::ConsumeItemTried(CliSession*)
{
    LIFT_STUB(0x6f360);
}

// 0x6f560
bool ExtendJumpingCharacterCreationQuotaService::TaskDone(CliSession*)
{
    LIFT_STUB(0x6f560);
}

// 0x6f760
bool ExtendJumpingCharacterCreationQuotaService::ConsumeItemFinished(CliSession*)
{
    LIFT_STUB(0x6f760);
}

// 0x6f960
bool ExtendJumpingCharacterCreationQuotaService::Finish(CliSession*)
{
    LIFT_STUB(0x6f960);
}

// 0x6fc10
bool ChangeCharacterSexService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6fc10);
}

// 0x6fe20
bool ChangeCharacterSexService::Start(CliSession*, unsigned int, char, char*, int)
{
    LIFT_STUB(0x6fe20);
}

// 0x70040
bool ChangeCharacterSexService::ConsumeItemTried(CliSession*)
{
    LIFT_STUB(0x70040);
}

// 0x70240
bool ChangeCharacterSexService::TaskDone(CliSession*)
{
    LIFT_STUB(0x70240);
}

// 0x70440
bool ChangeCharacterSexService::ConsumeItemFinished(CliSession*)
{
    LIFT_STUB(0x70440);
}

// 0x70640
bool ChangeCharacterSexService::Finish(CliSession*)
{
    LIFT_STUB(0x70640);
}

// 0x70900
bool ChangeCharacterRaceService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x70900);
}

// 0x70b10
bool ChangeCharacterRaceService::Start(CliSession*, unsigned int, char, char, char*, int)
{
    LIFT_STUB(0x70b10);
}

// 0x70d50
bool ChangeCharacterRaceService::ConsumeItemTried(CliSession*)
{
    LIFT_STUB(0x70d50);
}

// 0x70f50
bool ChangeCharacterRaceService::TaskDone(CliSession*)
{
    LIFT_STUB(0x70f50);
}

// 0x71150
bool ChangeCharacterRaceService::ConsumeItemFinished(CliSession*)
{
    LIFT_STUB(0x71150);
}

// 0x71350
bool ChangeCharacterRaceService::Finish(CliSession*)
{
    LIFT_STUB(0x71350);
}

// 0xefb20
bool LobbyService::IsServiceTarget(id128 const&)
{
    LIFT_STUB(0xefb20);
}
