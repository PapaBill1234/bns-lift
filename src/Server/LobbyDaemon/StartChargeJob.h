// StartChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class GamedChannel;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base). The constructor is not in the PDB. It is inlined in the packet handler (0x8b5b0).
class StartChargeJob : public CliSessionJob
{
public:
    StartChargeJob(CliSession* owner) : CliSessionJob(owner), _gamed(nullptr), _gametid(0), _pcid(0) {}
    virtual ~StartChargeJob() {}
    virtual LobbyJobDef const* GetDefinition() const;  // 0x75570
    static void* _vtbl();  // 0x755d0
    bool Initialize(GamedChannel*, unsigned long long, unsigned long long);  // 0x756a0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x75580
    virtual bool work(int, void*);  // 0x757b0
    bool init();  // 0x75830
    bool requestStartCharge();  // 0x75a60
    bool responseStartCharge(void*);  // 0x75c10
    bool expireStartCharge();  // 0x76150

public:
    GamedChannel* _gamed;
    unsigned long long _gametid;
    unsigned long long _pcid;

    static ObjPool _pool;  // LIFT: no definition yet (like LeaveGameWorldJob::_pool).
};
static_assert(sizeof(StartChargeJob) == 0x70, "sizeof StartChargeJob");
static_assert(offsetof(StartChargeJob, _gamed) == 0x58, "StartChargeJob::_gamed");
static_assert(offsetof(StartChargeJob, _gametid) == 0x60, "StartChargeJob::_gametid");
static_assert(offsetof(StartChargeJob, _pcid) == 0x68, "StartChargeJob::_pcid");
