// ChangeUserNameJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct LobbyJobDef;

class ChangeUserNameJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x26990
    static void* _vtbl();  // 0x269f0
    ChangeUserNameJob(CliSession*);  // 0x26a70
    virtual ~ChangeUserNameJob();  // 0x26ae0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x269a0
    virtual bool work(int, void*);  // 0x26b50
    bool init(void*);  // 0x26c80
    bool checkAccountInventoryItem();  // 0x275f0
    bool checkAccountInventoryItemOk(void*);  // 0x27790
    bool checkAccountInventoryItemFail(void*);  // 0x27bc0
    bool checkAccountInventoryItemTimeout();  // 0x27e50
    bool changeUserName();  // 0x27f70
    bool changeUserNameResponse(void*);  // 0x28580
    bool changeUserNameExpire();  // 0x28a80
    bool consumeLobbyServiceItem();  // 0x28bd0
    bool consumeLobbyServiceItemOk(void*);  // 0x28dc0
    bool consumeLobbyServiceItemFail(void*);  // 0x28ed0
    bool consumeLobbyServiceItemTimeout();  // 0x291f0
    bool finLobbyService();  // 0x29350
    void releaseService();  // 0x29630
};
