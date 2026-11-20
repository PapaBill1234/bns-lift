// AddSlotJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct LobbyJobDef;

class AddSlotJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0xd1e0
    static void* _vtbl();  // 0xd240
    AddSlotJob(CliSession*);  // 0xd2c0
    virtual ~AddSlotJob();  // 0xd340
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0xd1f0
    virtual bool work(int, void*);  // 0xd3b0
    bool init(void*);  // 0xd570
    bool checkAccountInventoryItem();  // 0xdc90
    bool checkAccountInventoryItemOk(void*);  // 0xde30
    bool checkAccountInventoryItemFail(void*);  // 0xe2a0
    bool checkAccountInventoryItemTimeout();  // 0xe500
    bool checkSlotCapacity();  // 0xe610
    bool checkSlotCapacityAck(void*);  // 0xe8b0
    bool checkSlotCapacityExpire();  // 0xedb0
    bool registerServiceEntry();  // 0xeec0
    bool tryConsumeAccountInventoryItem();  // 0xf370
    bool tryConsumeAccountInventoryItemOk(void*);  // 0xf510
    bool tryConsumeAccountInventoryItemFail(void*);  // 0xf7d0
    bool tryConsumeAccountInventoryItemTimeout();  // 0xfa20
    bool createSlot();  // 0xfb30
    bool createSlotAck(void*);  // 0xfe00
    bool createSlotExpire();  // 0x105a0
    bool finConsumeAccountInventoryItem();  // 0x106b0
    bool finConsumeAccountInventoryItemOk(void*);  // 0x10850
    bool finConsumeAccountInventoryItemFail(void*);  // 0x10b10
    bool finConsumeAccountInventoryItemTimeout();  // 0x10d60
    bool finServiceEntry();  // 0x10e70
};
