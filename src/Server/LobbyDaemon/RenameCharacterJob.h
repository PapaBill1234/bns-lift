// RenameCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct LobbyJobDef;

class RenameCharacterJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x66ae0
    RenameCharacterJob(CliSession*);  // 0x66b40
    virtual ~RenameCharacterJob();  // 0x66c50
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x66af0
    virtual bool work(int, void*);  // 0x66cd0
    bool init(void*);  // 0x66e70
    bool checkAccountInventoryItem();  // 0x68e80
    bool checkAccountInventoryItemOk(void*);  // 0x69100
    bool checkAccountInventoryItemFail(void*);  // 0x694c0
    bool checkAccountInventoryItemTimeout();  // 0x69730
    bool registerServiceEntry();  // 0x69850
    bool tryConsumeAccountInventoryItem();  // 0x69f70
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x6a120
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x6a3f0
    bool tryConsumeAccountInventoryItemTimeout();  // 0x6a650
    bool renameCharacter();  // 0x6a770
    bool renameCharacterOk(void*);  // 0x6a9a0
    bool renameCharacterFail(void*);  // 0x6ae30
    bool renameCharacterTimeout();  // 0x6b090
    bool finConsumeAccountInventoryItem();  // 0x6b1b0
    bool finConsumeAccountInventoryItemOk(void*);  // 0x6b360
    bool finConsumeAccountInventoryItemFail(void*);  // 0x6b630
    bool finConsumeAccountInventoryItemTimeout();  // 0x6b890
    bool finServiceEntry();  // 0x6b9b0
    void sendFriendMessageToNP();  // 0x6bc50
};
