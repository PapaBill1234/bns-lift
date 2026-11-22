// LobbyService.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: Classes with only stub bodies do not have full PDB layouts yet.
#pragma once
#include "StringUtil.h"

class Character;
class CliSession;
class FragmentPacket;

class LobbyService
{
public:
    struct DB
    {
        unsigned long long serviceId;
        char serviceType;
        unsigned long long itemInstanceId;
        char serviceState;
    };

    LobbyService() : _db() {}
    virtual ~LobbyService() {}
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6c330
    virtual bool IsServiceTarget(id128 const&);  // 0xefb20
    virtual bool IsServiceTarget(Character*) { return false; }  // 0xefb20 (folded)
    // LIFT: Inline the PDB accessor for the DB reads in CliSession::addLobbyService (0x373a0).
    DB const& GetDB() const { return _db; }

protected:
    bool setup(DB*);
    DB _db;
};
static_assert(sizeof(LobbyService::DB) == 0x20, "sizeof LobbyService::DB");
static_assert(sizeof(LobbyService) == 0x28, "sizeof LobbyService");

class AddSlotService : public LobbyService
{
public:
    struct DB
    {
        id128 slotid;
    };

    AddSlotService() : _dbAddSlotService() {}
    bool Setup(LobbyService::DB*, DB*);  // 0x6d180
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6d240
    virtual bool IsServiceTarget(id128 const&);  // 0x6d3e0
    bool Start(CliSession*, unsigned int);  // 0x6d420
    bool ConsumeItemTried(CliSession*);  // 0x6d5d0
    bool TaskDone(CliSession*, id128 const&);  // 0x6d7d0
    bool ConsumeItemFinished(CliSession*);  // 0x6dab0
    bool Finish(CliSession*);  // 0x6dcb0

private:
    DB _dbAddSlotService;
};
static_assert(sizeof(AddSlotService) == 0x38, "sizeof AddSlotService");

class ChangeCharacterRaceService
{
public:
    virtual bool IsServiceTarget(Character*);  // 0x6c760
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x70900
    bool Start(CliSession*, unsigned int, char, char, char*, int);  // 0x70b10
    bool ConsumeItemTried(CliSession*);  // 0x70d50
    bool TaskDone(CliSession*);  // 0x70f50
    bool ConsumeItemFinished(CliSession*);  // 0x71150
    bool Finish(CliSession*);  // 0x71350
};

class ChangeCharacterSexService
{
public:
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6fc10
    virtual bool IsServiceTarget(Character*);  // 0x6c760
    bool Start(CliSession*, unsigned int, char, char*, int);  // 0x6fe20
    bool ConsumeItemTried(CliSession*);  // 0x70040
    bool TaskDone(CliSession*);  // 0x70240
    bool ConsumeItemFinished(CliSession*);  // 0x70440
    bool Finish(CliSession*);  // 0x70640
};

class CharacterCosmesisService : public LobbyService
{
public:
    struct DB
    {
        unsigned long long pcid;
    };

    CharacterCosmesisService() : _characterCosmesisServiceDB() {}
    bool Setup(LobbyService::DB*, DB*);  // 0x6c4a0
    virtual bool Fetch(CliSession*, FragmentPacket*) const override;  // 0x6c550
    virtual bool IsServiceTarget(Character*) override;  // 0x6c760
    bool Start(CliSession*, unsigned int, char*, int);  // 0x6c780
    bool ConsumeItemTried(CliSession*);  // 0x6c980
    bool TaskDone(CliSession*);  // 0x6cb80
    bool ConsumeItemFinished(CliSession*);  // 0x6cd80
    bool Finish(CliSession*);  // 0x6cf80

private:
    DB _characterCosmesisServiceDB;
};
static_assert(sizeof(CharacterCosmesisService) == 0x30, "sizeof CharacterCosmesisService");

class ExtendJumpingCharacterCreationQuotaService
{
public:
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6f000
    bool Start(CliSession*, unsigned int);  // 0x6f1b0
    bool ConsumeItemTried(CliSession*);  // 0x6f360
    bool TaskDone(CliSession*);  // 0x6f560
    bool ConsumeItemFinished(CliSession*);  // 0x6f760
    bool Finish(CliSession*);  // 0x6f960
};

class RenameCharacterService : public LobbyService
{
public:
    struct DB
    {
        unsigned long long pcid;
    };

    RenameCharacterService() : _dbRenameCharacterService() {}
    bool Setup(LobbyService::DB*, DB*);  // 0x6deb0
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6df60
    virtual bool IsServiceTarget(Character*);  // 0x6e170
    bool Start(CliSession*, unsigned int, wchar_t const*, int);  // 0x6e190
    bool ConsumeItemTried(CliSession*);  // 0x6e440
    bool TaskDone(CliSession*);  // 0x6e640
    bool ConsumeItemFinished(CliSession*);  // 0x6e840
    bool Finish(CliSession*);  // 0x6ea40

private:
    DB _dbRenameCharacterService;
};
static_assert(sizeof(RenameCharacterService) == 0x30, "sizeof RenameCharacterService");

class RenameUserService : public LobbyService
{
public:
    RenameUserService() : _oldUserName(), _newUserName() {}
    virtual bool Fetch(CliSession*, FragmentPacket*) const override;  // 0x6ec40
    bool Start(CliSession*, wchar_t const*, wchar_t const*);  // 0x6ece0
    bool Finish(CliSession*, unsigned long long, unsigned int);  // 0x6edf0

private:
    wchar_t _oldUserName[65];
    wchar_t _newUserName[65];
};
static_assert(sizeof(RenameUserService) == 0x130, "sizeof RenameUserService");
