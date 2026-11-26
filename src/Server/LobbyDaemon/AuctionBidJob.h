// AuctionBidJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
// LIFT: header layouts only (fix7). The function bodies are still LIFT_STUB.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class GamedChannel;
class ObjPool;
struct Game_AuctionBidReqParam;
struct LobbyJobDef;

// LIFT: PDB layout (sizeof 0x88, CliSessionJob base). Layout from tools/pdbcls.py LobbyDaemon AuctionBidJob.
class AuctionBidJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        AUCTION_BID = 1,
        FIN = 2,
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0x110d0
    static void* _vtbl();  // 0x11130
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x110e0
    virtual bool work(int, void*);  // 0x11210
    bool init(Game_AuctionBidReqParam*);  // 0x11290
    bool auctionBidReq();  // 0x11750
    bool auctionBidResponse(void*);  // 0x11aa0
    bool auctionBidExpire();  // 0x12130

private:
    friend struct AuctionBidJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    GamedChannel* _gamed;  // +0x58
    unsigned long long _pcId;  // +0x60
    id128 _auctionId;  // +0x68
    short _bidCurrencyGroupId;  // +0x78
    long long _bidPrice;  // +0x80

public:
    static ObjPool _pool;  // .data 0x2039c0
    static LobbyJobDef _def;
};
static_assert(sizeof(AuctionBidJob) == 0x88, "sizeof AuctionBidJob");
struct AuctionBidJobLayoutCheck
{
    static_assert(offsetof(AuctionBidJob, _gamed) == 0x58, "AuctionBidJob::_gamed");
    static_assert(offsetof(AuctionBidJob, _pcId) == 0x60, "AuctionBidJob::_pcId");
    static_assert(offsetof(AuctionBidJob, _auctionId) == 0x68, "AuctionBidJob::_auctionId");
    static_assert(offsetof(AuctionBidJob, _bidCurrencyGroupId) == 0x78, "AuctionBidJob::_bidCurrencyGroupId");
    static_assert(offsetof(AuctionBidJob, _bidPrice) == 0x80, "AuctionBidJob::_bidPrice");
};
