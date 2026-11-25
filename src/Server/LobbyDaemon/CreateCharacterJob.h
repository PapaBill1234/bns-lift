// CreateCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon CreateCharacterJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class CliSession;
class GamedChannel;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0xb0, CliSessionJob base). The PDB also has static _vtbl(). The binary has no body for it. It
// is not declared here.
class CreateCharacterJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        GET_SLOT = 1,
        CREATE_CHARACTER = 2,
        FIN = 3
    };

    CreateCharacterJob(CliSession* owner);  // 0x418a0
    virtual ~CreateCharacterJob();  // 0x41940
    virtual LobbyJobDef const* GetDefinition() const;  // 0x41840
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

    LobbyGateChannel* _lgate;  // +0x58
    GamedChannel* _gamed;  // +0x60
    unsigned long long _pcid;  // +0x68
    id128 _slotid;  // +0x70
    short _wid;  // +0x80
    wchar_t* _characterName;  // +0x88
    short _characterNameLen;  // +0x90
    char* _characterMakeData;  // +0x98
    short _characterMakeDataSize;  // +0xa0
    bool _jumpingCharacter;  // +0xa2
    LobbyJobTransaction* _tran;  // +0xa8

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct CreateCharacterJobLayoutCheck;
};

struct CreateCharacterJobLayoutCheck
{
    static_assert(sizeof(CreateCharacterJob) == 0xB0, "sizeof CreateCharacterJob");
    static_assert(offsetof(CreateCharacterJob, _lgate) == 0x58, "CreateCharacterJob::_lgate");
    static_assert(offsetof(CreateCharacterJob, _gamed) == 0x60, "CreateCharacterJob::_gamed");
    static_assert(offsetof(CreateCharacterJob, _pcid) == 0x68, "CreateCharacterJob::_pcid");
    static_assert(offsetof(CreateCharacterJob, _slotid) == 0x70, "CreateCharacterJob::_slotid");
    static_assert(offsetof(CreateCharacterJob, _wid) == 0x80, "CreateCharacterJob::_wid");
    static_assert(offsetof(CreateCharacterJob, _characterName) == 0x88, "CreateCharacterJob::_characterName");
    static_assert(offsetof(CreateCharacterJob, _characterNameLen) == 0x90, "CreateCharacterJob::_characterNameLen");
    static_assert(offsetof(CreateCharacterJob, _characterMakeData) == 0x98, "CreateCharacterJob::_characterMakeData");
    static_assert(offsetof(CreateCharacterJob, _characterMakeDataSize) == 0xA0, "CreateCharacterJob::_characterMakeDataSize");
    static_assert(offsetof(CreateCharacterJob, _jumpingCharacter) == 0xA2, "CreateCharacterJob::_jumpingCharacter");
    static_assert(offsetof(CreateCharacterJob, _tran) == 0xA8, "CreateCharacterJob::_tran");
};
