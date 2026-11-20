// GetLobbyServiceItemJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;

class GetLobbyServiceItemJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x52060
    static void* _vtbl();  // 0x520c0
    GetLobbyServiceItemJob(CliSession*, LobbyGateChannel*, unsigned long long);  // 0x52140
    virtual ~GetLobbyServiceItemJob();  // 0x521e0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x52070
    virtual bool work(int, void*);  // 0x52250
    bool init();  // 0x522f0
    bool getLobbyServiceItemReq();  // 0x52620
    bool getLobbyServiceItemOk(void*);  // 0x527b0
    bool getLobbyServiceItemFail(void*);  // 0x529d0
    bool getLobbyServiceItemTimeout();  // 0x52be0
};
