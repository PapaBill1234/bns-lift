// TryEnterGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;
union id128;

class TryEnterGameWorldJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x7b840
    static void* _vtbl();  // 0x7b8a0
    TryEnterGameWorldJob(CliSession*);  // 0x7b920
    virtual ~TryEnterGameWorldJob();  // 0x7b9a0
    bool Initialize(LobbyGateChannel*, id128 const&);  // 0x7ba40
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x7b850
    virtual bool work(int, void*);  // 0x7bb70
    bool init();  // 0x7bcf0
    bool restorePcReq();  // 0x7c660
    bool restorePcOk();  // 0x7c820
    bool restorePcFail(short*);  // 0x7cba0
    bool restorePcExpired();  // 0x7cfe0
    bool checkSecondPasswordStatus();  // 0x7d0e0
    bool checkSecondPasswordStatusResponse(void*);  // 0x7d400
    bool checkSecondPasswordStatusExpire();  // 0x7d900
    bool checkSecondPasswordVerified();  // 0x7daa0
    bool checkSecondPasswordVerifiedResponse(void*);  // 0x7ddc0
    bool checkSecondPasswordVerifiedExpire();  // 0x7e0f0
    bool requestGetSlot();  // 0x7e290
    bool responseGetSlot(void*);  // 0x7e570
    bool expireGetSlot();  // 0x7eb60
    bool requestChargeGetInfo();  // 0x7ecf0
    bool responseChargeGetInfo(void*);  // 0x7efd0
    bool expireChargeGetInfo();  // 0x7fa60
    bool tryEnterGameWorld();  // 0x7fbf0
    bool issueGameWorldToken();  // 0x7ffe0
};
