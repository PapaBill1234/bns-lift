// ListLobbyServiceItemJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;

class ListLobbyServiceItemJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x55b20
    static void* _vtbl();  // 0x55b80
    ListLobbyServiceItemJob(CliSession*, LobbyGateChannel*, char, unsigned long long);  // 0x55c00
    virtual ~ListLobbyServiceItemJob();  // 0x55cb0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x55b30
    virtual bool work(int, void*);  // 0x55d20
    bool init();  // 0x55dc0
    bool listLobbyServiceItemReq();  // 0x560f0
    bool listLobbyServiceItemOk(void*);  // 0x56280
    bool listLobbyServiceItemFail(void*);  // 0x56490
    bool listLobbyServiceItemTimeout();  // 0x56670
};
