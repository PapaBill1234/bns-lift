// ChangeCharacterSexJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct LobbyJobDef;

class ChangeCharacterSexJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x22a60
    ChangeCharacterSexJob(CliSession*);  // 0x22ac0
    virtual ~ChangeCharacterSexJob();  // 0x22b60
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x22a70
    virtual bool work(int, void*);  // 0x22c10
    bool init(void*);  // 0x22db0
    bool checkAccountInventoryItem();  // 0x23a10
    bool checkAccountInventoryItemOk(void*);  // 0x23bc0
    bool checkAccountInventoryItemFail(void*);  // 0x24030
    bool checkAccountInventoryItemTimeout();  // 0x242a0
    bool registerServiceEntry();  // 0x243c0
    bool tryConsumeAccountInventoryItem();  // 0x24a10
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x24bd0
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x24eb0
    bool tryConsumeAccountInventoryItemTimeout();  // 0x25110
    bool changeCharacterSex();  // 0x25240
    bool changeCharacterSexOk(void*);  // 0x25490
    bool changeCharacterSexFail(void*);  // 0x25a20
    bool changeCharacterSexTimeout();  // 0x25c80
    bool finConsumeAccountInventoryItem();  // 0x25db0
    bool finConsumeAccountInventoryItemOk(void*);  // 0x25f70
    bool finConsumeAccountInventoryItemFail(void*);  // 0x26240
    bool finConsumeAccountInventoryItemTimeout();  // 0x264a0
    bool finServiceEntry();  // 0x265d0
};
