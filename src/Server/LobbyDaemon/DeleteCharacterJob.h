// DeleteCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct DeleteCharacterOkParam;
struct LobbyJobDef;

class DeleteCharacterJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x45040
    static void* _vtbl();  // 0x450a0
    DeleteCharacterJob(CliSession*);  // 0x45120
    virtual ~DeleteCharacterJob();  // 0x451a0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x45050
    virtual bool work(int, void*);  // 0x45240
    bool init(int, void*);  // 0x453a0
    bool checkSecondPasswordStatus();  // 0x46440
    bool checkSecondPasswordStatusResponse(void*);  // 0x46760
    bool checkSecondPasswordStatusExpire();  // 0x46d20
    bool checkSecondPasswordVerified();  // 0x46ed0
    bool checkSecondPasswordVerifiedResponse(void*);  // 0x47200
    bool checkSecondPasswordVerifiedExpire();  // 0x47560
    bool getCharacterGoodsReq();  // 0x47710
    bool getCharacterGoodsCountOk(void*);  // 0x47ac0
    bool getCharacterGoodsCountFail(void*);  // 0x47d80
    bool getCharacterGoodsCountExpire();  // 0x47fa0
    bool deleteReq();  // 0x482b0
    bool deleteOk(DeleteCharacterOkParam*);  // 0x48890
    bool deleteFail(void*);  // 0x48a10
    bool deleteExpire();  // 0x49090
    bool directDelete();  // 0x493a0
    bool scheduleDelete();  // 0x49770
};
