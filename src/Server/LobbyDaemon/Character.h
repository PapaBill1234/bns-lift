// Character.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class FragmentPacket;
class Packet;
class PacketComposer;
union id128;

class Character
{
public:
    bool FetchCharacterInfo(FragmentPacket*) const;  // 0x310c0
    bool FetchCharacterInfo(Packet*, PacketComposer*) const;  // 0x31380
    bool SetLevel(short);  // 0x32490
    bool SetShowcase(char const*, short);  // 0x32510
    bool SetName(wchar_t const*);  // 0x32630
    bool StartGameWorldPlay(unsigned long);  // 0x326c0
    bool EndGameWorldPlay();  // 0x32800
    void SetSlotId(id128 const&);  // 0x328f0
};
