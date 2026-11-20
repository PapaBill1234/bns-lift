// CreateCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct LobbyJobDef;

class CreateCharacterJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x41840
    CreateCharacterJob(CliSession*);  // 0x418a0
    virtual ~CreateCharacterJob();  // 0x41940
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x41850
    virtual bool work(int, void*);  // 0x41a30
    bool init(int, void*);  // 0x41b10
    bool reqGetSlot();  // 0x43260
    bool responseGetSlot(void*);  // 0x433f0
    bool expireGetSlot();  // 0x43a80
    bool tryCreateCharacter();  // 0x43b90
    bool createCharacterOk(void*);  // 0x44270
    bool createCharacterFail(short);  // 0x44900
    bool createCharacterExpire();  // 0x44d40
};
