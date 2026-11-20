// ListGoodsJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;

class ListGoodsJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x54ee0
    static void* _vtbl();  // 0x54f40
    ListGoodsJob(CliSession*, LobbyGateChannel*);  // 0x54fc0
    virtual ~ListGoodsJob();  // 0x55050
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x54ef0
    virtual bool work(int, void*);  // 0x550c0
    bool init(void*);  // 0x55160
    bool listGoodsReq();  // 0x55490
    bool listGoodsOk(void*);  // 0x55620
    bool listGoodsFail(void*);  // 0x55820
    bool listGoodsTimeout();  // 0x55a20
};
