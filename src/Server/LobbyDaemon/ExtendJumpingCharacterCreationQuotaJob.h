// ExtendJumpingCharacterCreationQuotaJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct LobbyJobDef;

class ExtendJumpingCharacterCreationQuotaJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x2a300
    static void* _vtbl();  // 0x2a3c0
    ExtendJumpingCharacterCreationQuotaJob(CliSession*);  // 0x2a440
    virtual ~ExtendJumpingCharacterCreationQuotaJob();  // 0x2a4c0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x2a310
    virtual bool work(int, void*);  // 0x2a540
    bool init(void*);  // 0x2a6a0
    bool checkAccountInventoryItem();  // 0x2b0a0
    bool checkAccountInventoryItemOk(void*);  // 0x2b220
    bool checkAccountInventoryItemFail(void*);  // 0x2b640
    bool checkAccountInventoryItemTimeout();  // 0x2b890
    bool registerServiceEntry();  // 0x2b990
    bool tryConsumeAccountInventoryItem();  // 0x2bdf0
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x2bf80
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x2c220
    bool tryConsumeAccountInventoryItemTimeout();  // 0x2c450
    bool extendJumpingCharacterCreationQuota();  // 0x2c550
    bool finConsumeAccountInventoryItem();  // 0x2c730
    bool finConsumeAccountInventoryItemOk(void*);  // 0x2c8c0
    bool finConsumeAccountInventoryItemFail(void*);  // 0x2cb60
    bool finConsumeAccountInventoryItemTimeout();  // 0x2cd90
    bool finServiceEntry();  // 0x2ce90
    void sendFailReason(short);  // 0x2d140
};

class UpgradeJumpingCharacterStateJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x2a360
    static void* _vtbl();  // 0x2d440
    UpgradeJumpingCharacterStateJob(CliSession*);  // 0x2d4c0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x2a370
    virtual bool work(int, void*);  // 0x2d550
    bool init(int, void*);  // 0x2d580
    bool upgradeJumpingCharacterState();  // 0x2d9c0
};
