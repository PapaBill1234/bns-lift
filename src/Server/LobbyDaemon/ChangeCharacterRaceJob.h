// ChangeCharacterRaceJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct LobbyJobDef;

class ChangeCharacterRaceJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x1ea40
    ChangeCharacterRaceJob(CliSession*);  // 0x1eaa0
    virtual ~ChangeCharacterRaceJob();  // 0x1eb40
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x1ea50
    virtual bool work(int, void*);  // 0x1ebf0
    bool init(void*);  // 0x1ed90
    bool checkAccountInventoryItem();  // 0x1fa00
    bool checkAccountInventoryItemOk(void*);  // 0x1fbb0
    bool checkAccountInventoryItemFail(void*);  // 0x20020
    bool checkAccountInventoryItemTimeout();  // 0x20290
    bool registerServiceEntry();  // 0x203b0
    bool tryConsumeAccountInventoryItem();  // 0x20a10
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x20bd0
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x20eb0
    bool tryConsumeAccountInventoryItemTimeout();  // 0x21110
    bool changeCharacterRace();  // 0x21240
    bool changeCharacterRaceOk(void*);  // 0x214a0
    bool changeCharacterRaceFail(void*);  // 0x21a30
    bool changeCharacterRaceTimeout();  // 0x21c90
    bool finConsumeAccountInventoryItem();  // 0x21dc0
    bool finConsumeAccountInventoryItemOk(void*);  // 0x21f80
    bool finConsumeAccountInventoryItemFail(void*);  // 0x22250
    bool finConsumeAccountInventoryItemTimeout();  // 0x224b0
    bool finServiceEntry();  // 0x225e0
};
