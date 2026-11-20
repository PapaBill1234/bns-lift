// LobbyService.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Character;
class CliSession;
class FragmentPacket;
union id128;

class AddSlotService
{
public:
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6d240
    virtual bool IsServiceTarget(id128 const&);  // 0x6d3e0
    bool Start(CliSession*, unsigned int);  // 0x6d420
    bool ConsumeItemTried(CliSession*);  // 0x6d5d0
    bool TaskDone(CliSession*, id128 const&);  // 0x6d7d0
    bool ConsumeItemFinished(CliSession*);  // 0x6dab0
    bool Finish(CliSession*);  // 0x6dcb0
};

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
    bool Start(CliSession*, unsigned int, char, char*, int);  // 0x6fe20
    bool ConsumeItemTried(CliSession*);  // 0x70040
    bool TaskDone(CliSession*);  // 0x70240
    bool ConsumeItemFinished(CliSession*);  // 0x70440
    bool Finish(CliSession*);  // 0x70640
};

class CharacterCosmesisService
{
public:
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6c550
    bool Start(CliSession*, unsigned int, char*, int);  // 0x6c780
    bool ConsumeItemTried(CliSession*);  // 0x6c980
    bool TaskDone(CliSession*);  // 0x6cb80
    bool ConsumeItemFinished(CliSession*);  // 0x6cd80
    bool Finish(CliSession*);  // 0x6cf80
};

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

class LobbyService
{
public:
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6c330
    virtual bool IsServiceTarget(id128 const&);  // 0xefb20
};

class RenameCharacterService
{
public:
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6df60
    virtual bool IsServiceTarget(Character*);  // 0x6e170
    bool Start(CliSession*, unsigned int, wchar_t const*, int);  // 0x6e190
    bool ConsumeItemTried(CliSession*);  // 0x6e440
    bool TaskDone(CliSession*);  // 0x6e640
    bool ConsumeItemFinished(CliSession*);  // 0x6e840
    bool Finish(CliSession*);  // 0x6ea40
};

class RenameUserService
{
public:
    virtual bool Fetch(CliSession*, FragmentPacket*) const;  // 0x6ec40
    bool Start(CliSession*, wchar_t const*, wchar_t const*);  // 0x6ece0
    bool Finish(CliSession*, unsigned long long, unsigned int);  // 0x6edf0
};
