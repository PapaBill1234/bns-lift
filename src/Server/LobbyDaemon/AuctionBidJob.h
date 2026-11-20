// AuctionBidJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct Game_AuctionBidReqParam;
struct LobbyJobDef;

class AuctionBidJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x110d0
    static void* _vtbl();  // 0x11130
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x110e0
    virtual bool work(int, void*);  // 0x11210
    bool init(Game_AuctionBidReqParam*);  // 0x11290
    bool auctionBidReq();  // 0x11750
    bool auctionBidResponse(void*);  // 0x11aa0
    bool auctionBidExpire();  // 0x12130
};
