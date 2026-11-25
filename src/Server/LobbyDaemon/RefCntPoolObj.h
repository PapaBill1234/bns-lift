// AuctionDeliverJob.obj (LobbyDaemon PDB, 2019 + PDB). RefCntPoolObj has its symbols in this object.
// LIFT: own header (fix7). LobbyJob.h needs RefCntPoolObj, and AuctionDeliverJob needs LobbyJob. One header for both made an include cycle.
#pragma once
#include "RefCntObject.h"

// PDB: RefCntPoolObj : RefCntObject (no own members). Same form as SmartCouponDaemon CouponJob.h.
class RefCntPoolObj : public RefCntObject
{
public:
    virtual ~RefCntPoolObj();  // 0x12230
};
static_assert(sizeof(RefCntPoolObj) == 0x18, "sizeof RefCntPoolObj");
