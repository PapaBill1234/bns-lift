// ChangeCharacterAppearanceJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct LobbyJobDef;

class ChangeCharacterAppearanceJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x1ab60
    ChangeCharacterAppearanceJob(CliSession*);  // 0x1abc0
    virtual ~ChangeCharacterAppearanceJob();  // 0x1ac50
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x1ab70
    virtual bool work(int, void*);  // 0x1ad00
    bool init(void*);  // 0x1aea0
    bool checkAccountInventoryItem();  // 0x1bae0
    bool checkAccountInventoryItemOk(void*);  // 0x1bc90
    bool checkAccountInventoryItemFail(void*);  // 0x1c100
    bool checkAccountInventoryItemTimeout();  // 0x1c370
    bool registerServiceEntry();  // 0x1c490
    bool tryConsumeAccountInventoryItem();  // 0x1cad0
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x1cc90
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x1cf70
    bool tryConsumeAccountInventoryItemTimeout();  // 0x1d1d0
    bool changeCharacterAppearance();  // 0x1d300
    bool changeCharacterAppearanceOk(void*);  // 0x1d540
    bool changeCharacterAppearanceFail(void*);  // 0x1dad0
    bool changeCharacterAppearanceTimeout();  // 0x1dd30
    bool finConsumeAccountInventoryItem();  // 0x1de60
    bool finConsumeAccountInventoryItemOk(void*);  // 0x1e020
    bool finConsumeAccountInventoryItemFail(void*);  // 0x1e2f0
    bool finConsumeAccountInventoryItemTimeout();  // 0x1e550
    bool finServiceEntry();  // 0x1e680
    bool releasePcServiceStatus();  // 0x229a0
};
