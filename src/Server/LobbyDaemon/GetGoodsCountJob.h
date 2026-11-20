// GetGoodsCountJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;

class GetGoodsCountJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x51460
    static void* _vtbl();  // 0x514c0
    GetGoodsCountJob(CliSession*, LobbyGateChannel*);  // 0x51540
    virtual ~GetGoodsCountJob();  // 0x515d0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x51470
    virtual bool work(int, void*);  // 0x51640
    bool init();  // 0x516e0
    bool getGoodsCountReq();  // 0x51a00
    bool getGoodsCountOk(void*);  // 0x51b80
    bool getGoodsCountFail(void*);  // 0x51d60
    bool getGoodsCountTimeout();  // 0x51f60
};
