// AuctionDeliverJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class AuctionDeliverJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x12300
    AuctionDeliverJob();  // 0x12360
    virtual ~AuctionDeliverJob();  // 0x123f0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x12310
    virtual bool work(int, void*);  // 0x12460
    bool init(void*);  // 0x124f0
    bool registerPostOk(void*);  // 0x12f30
    bool registerPostFail(void*);  // 0x13230
    bool registerPostTimeout();  // 0x13520
};

class RefCntPoolObj
{
public:
    virtual ~RefCntPoolObj();  // 0x12230
};
