// BindCharacterSlotJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon BindCharacterSlotJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class CliSession;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x78, CliSessionJob base).
class BindCharacterSlotJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        GET_SLOT = 1,
        BIND_CHARACTER_SLOT = 2,
        FIN = 3
    };

    static void* _vtbl();  // 0x16ef0
    // The PDB constructor has no own body in the binary. It is inline in _vtbl (0x16ef0).
    BindCharacterSlotJob(CliSession* owner) : CliSessionJob(owner), _lgate(nullptr), _pcId(0)
    {
        _slotId.id[0] = 0;
        _slotId.id[1] = 0;
    }
    virtual ~BindCharacterSlotJob();  // scalar deleting destructor 0x16f70
    virtual LobbyJobDef const* GetDefinition() const;  // 0x16e90
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x16ea0
    virtual bool work(int, void*);  // 0x16fc0
    bool init(void*);  // 0x17050
    bool reqGetSlot();  // 0x17840
    bool responseGetSlot(void*);  // 0x179e0
    bool expireGetSlot();  // 0x17ff0
    bool bindCharacterSlot();  // 0x18100

    LobbyGateChannel* _lgate;  // +0x58
    id128 _slotId;  // +0x60
    unsigned long long _pcId;  // +0x70

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct BindCharacterSlotJobLayoutCheck;
};

struct BindCharacterSlotJobLayoutCheck
{
    static_assert(sizeof(BindCharacterSlotJob) == 0x78, "sizeof BindCharacterSlotJob");
    static_assert(offsetof(BindCharacterSlotJob, _lgate) == 0x58, "BindCharacterSlotJob::_lgate");
    static_assert(offsetof(BindCharacterSlotJob, _slotId) == 0x60, "BindCharacterSlotJob::_slotId");
    static_assert(offsetof(BindCharacterSlotJob, _pcId) == 0x70, "BindCharacterSlotJob::_pcId");
};
