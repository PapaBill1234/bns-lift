// DepositMileageJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class DepositMileageJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x49b40
    virtual ~DepositMileageJob();  // 0x49c90
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x49b50
    virtual bool work(int, void*);  // 0x49d20
    bool init(void*);  // 0x49da0
    bool depositReq();  // 0x4a3e0
    bool depositAck(void*);  // 0x4aa40
    bool depositExpire();  // 0x4aee0
};
