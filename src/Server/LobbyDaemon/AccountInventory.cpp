// AccountInventory.obj (LobbyDaemon PDB, 2019 + PDB). Source: ~/.cache/bns-lift/hr/LobbyDaemon/index.tsv, module AccountInventory.
// LIFT: no card owns this module yet. It holds GoodsItem::Fetch (0x5e60) and Goods::Fetch (0x6010).
// LIFT: This stub exists only so that LobbyGateChannel::SendListGoodsOk (0xbe770) links. A stub is not a lift.
// The card that lifts this module replaces the body and keeps the file.
#include "FragmentPacket.h"
#include "LiftStub.h"
#include "LobbyGoodsTypes.h"

// 0x6010
bool Goods::Fetch(FragmentPacket*)
{
    LIFT_STUB(0x6010);
}
