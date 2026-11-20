// Character.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "Character.h"
#include "LiftStub.h"

// 0x310c0
bool Character::FetchCharacterInfo(FragmentPacket*) const
{
    LIFT_STUB(0x310c0);
}

// 0x31380
bool Character::FetchCharacterInfo(Packet*, PacketComposer*) const
{
    LIFT_STUB(0x31380);
}

// 0x32490
bool Character::SetLevel(short)
{
    LIFT_STUB(0x32490);
}

// 0x32510
bool Character::SetShowcase(char const*, short)
{
    LIFT_STUB(0x32510);
}

// 0x32630
bool Character::SetName(wchar_t const*)
{
    LIFT_STUB(0x32630);
}

// 0x326c0
bool Character::StartGameWorldPlay(unsigned long)
{
    LIFT_STUB(0x326c0);
}

// 0x32800
bool Character::EndGameWorldPlay()
{
    LIFT_STUB(0x32800);
}

// 0x328f0
void Character::SetSlotId(id128 const&)
{
    LIFT_STUB(0x328f0);
}
