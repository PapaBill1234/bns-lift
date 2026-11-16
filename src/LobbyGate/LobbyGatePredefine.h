// LobbyGatePredefine.obj (LobbyGate PDB). Declarations only. The bodies come from a later card.
#pragma once

class FragmentPacket;

// ❓ The members of Goods are not lifted yet. This stand-in keeps only the size from the PDB.
struct Goods
{
    bool Fetch(FragmentPacket* fragmentPacket);  // 0x15960

    char _data[0x390];  // ❓ layout not lifted
};
static_assert(sizeof(Goods) == 0x390, "sizeof Goods");
