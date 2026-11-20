// TakeAccountTimeBasedPlayRewardJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;
struct TakeAccountTimeBasedPlayRewardReqParam;
struct UserPromotionReward;

class TakeAccountTimeBasedPlayRewardJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x788a0
    static void* _vtbl();  // 0x78900
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x788b0
    virtual bool work(int, void*);  // 0x789d0
    bool init(TakeAccountTimeBasedPlayRewardReqParam*);  // 0x78a50
    bool takeAccountTimeBasedPlayRewardReq();  // 0x78ec0
    bool takeAccountTimeBasedPlayRewardResponse(void*);  // 0x79220
    bool takeAccountTimeBasedPlayRewardExpire();  // 0x79a00
    void sendOk(UserPromotionReward&, short);  // 0x79b30
    void sendFail(short, int);  // 0x79eb0
};
