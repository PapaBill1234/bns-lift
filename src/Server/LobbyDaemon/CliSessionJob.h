// CliSessionJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <stddef.h>
#include "LobbyJob.h"

class CliSession;

// LIFT: PDB layout (sizeof 0x58, LobbyJob base).
class CliSessionJob : public LobbyJob
{
public:
    CliSessionJob(CliSession*);  // 0x3bef0
    virtual ~CliSessionJob();  // 0x3bfa0
protected:
    virtual bool dispatch_work(int, void*);  // 0x3c010

public:
    CliSession* _owner;
};
static_assert(sizeof(CliSessionJob) == 0x58, "sizeof CliSessionJob");
static_assert(offsetof(CliSessionJob, _owner) == 0x50, "CliSessionJob::_owner");
