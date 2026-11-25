// SetupNpScheduleInfoJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon SetupNpScheduleInfoJob.
#pragma once
#include <stddef.h>
#include <deque>
#include "LobbyJob.h"
#include "StlMemory.h"

class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0xb8, LobbyJob base).
class SetupNpScheduleInfoJob : public LobbyJob
{
public:
    enum State
    {
        INIT_SETUP_NP_SCHEDULE_INFO = 0,
        TRY_PROMOTIONSTAMP_LIST_CURRENT_PROMOTIONS = 1,
        TRY_PROMOTIONSTAMP_GET_PROMOTION_POLICY = 2,
        FIN_SETUP_NP_SCHEDULE_INFO_JOB = 3,
        FIN = 4,
    };

    static void* _vtbl();  // PDB declaration. LIFT: not lifted.
    SetupNpScheduleInfoJob();  // 0x72d90
    virtual ~SetupNpScheduleInfoJob();  // 0x72e40
    virtual LobbyJobDef const* GetDefinition() const;  // 0x72cf0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x72d00
    virtual bool work(int, void*);  // 0x72eb0
    // LIFT: PDB declarations without a body in the binary: init, listCurrentPromotionsExpire and
    // getPromotionPolicyExpire. work (0x72eb0) has the expire logs inline.
    bool tryListCurrentPromotions(void*);  // 0x72ff0
    bool listCurrentPromotionsAck(void*);  // 0x73160
    bool tryGetPromotionPolicy(void*);  // 0x733e0
    bool getPromotionPolicyAck(void*);  // 0x73630

private:
    friend struct SetupNpScheduleInfoJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    int _tryGetPromotionPolicy;  // +0x50
    std::deque<int, StlAllocator<int, 2> > _promotionIds[2];  // +0x58

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(SetupNpScheduleInfoJob) == 0xb8, "sizeof SetupNpScheduleInfoJob");
struct SetupNpScheduleInfoJobLayoutCheck
{
    static_assert(offsetof(SetupNpScheduleInfoJob, _tryGetPromotionPolicy) == 0x50, "SetupNpScheduleInfoJob::_tryGetPromotionPolicy");
    static_assert(offsetof(SetupNpScheduleInfoJob, _promotionIds) == 0x58, "SetupNpScheduleInfoJob::_promotionIds");
};
