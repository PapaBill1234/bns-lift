// SetupNpScheduleInfoJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class SetupNpScheduleInfoJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x72cf0
    SetupNpScheduleInfoJob();  // 0x72d90
    virtual ~SetupNpScheduleInfoJob();  // 0x72e40
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x72d00
    virtual bool work(int, void*);  // 0x72eb0
    bool tryListCurrentPromotions(void*);  // 0x72ff0
    bool listCurrentPromotionsAck(void*);  // 0x73160
    bool tryGetPromotionPolicy(void*);  // 0x733e0
    bool getPromotionPolicyAck(void*);  // 0x73630
};
