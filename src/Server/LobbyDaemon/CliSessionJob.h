// CliSessionJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;

class CliSessionJob
{
public:
    CliSessionJob(CliSession*);  // 0x3bef0
    virtual ~CliSessionJob();  // 0x3bfa0
protected:
    virtual bool dispatch_work(int, void*);  // 0x3c010
};
