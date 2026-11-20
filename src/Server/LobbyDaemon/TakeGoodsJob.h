// TakeGoodsJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;

class TakeGoodsJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x79f00
    static void* _vtbl();  // 0x79f60
    TakeGoodsJob(CliSession*, LobbyGateChannel*, unsigned long long);  // 0x79fe0
    virtual ~TakeGoodsJob();  // 0x7a080
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x79f10
    virtual bool work(int, void*);  // 0x7a0f0
    bool init();  // 0x7a190
    bool takeGoodsReq();  // 0x7a540
    bool takeGoodsOk(void*);  // 0x7a6d0
    bool takeGoodsFail(void*);  // 0x7a8d0
    bool takeGoodsTimeout();  // 0x7ab30
};
