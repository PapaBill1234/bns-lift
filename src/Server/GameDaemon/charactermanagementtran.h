// charactermanagementtran.h: charactermanagementtran.cpp, charactermanagementtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ChangeCharacterAppearanceTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x725a0
private:
    virtual bool __cdecl work(int, void *);  // 0x73bf0
    bool __cdecl init(int, void *);  // 0x73c60
    bool __cdecl tryChangeCharacterAppearance(void);  // 0x73d40
    bool __cdecl changeCharacterAppearanceOk(void *);  // 0x73e30
    bool __cdecl changeCharacterAppearanceFail(short);  // 0x74120
};

class ChangeCharacterRaceTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x725c0
private:
    virtual bool __cdecl work(int, void *);  // 0x74e10
    bool __cdecl init(int, void *);  // 0x74e80
    bool __cdecl tryChangeCharacterRace(void);  // 0x74f70
    bool __cdecl changeCharacterRaceOk(void *);  // 0x75080
    bool __cdecl changeCharacterRaceFail(short);  // 0x753b0
    void __cdecl updateShowcaseItemRecord(void);  // 0x75490
};

class ChangeCharacterSexTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x725b0
private:
    virtual bool __cdecl work(int, void *);  // 0x74200
    bool __cdecl init(int, void *);  // 0x74270
    bool __cdecl tryChangeCharacterSex(void);  // 0x74350
    bool __cdecl changeCharacterSexOk(void *);  // 0x74440
    bool __cdecl changeCharacterSexFail(short);  // 0x74740
    void __cdecl updateShowcaseItemRecord(void);  // 0x74820
};

class CreateCharacterTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x72590
    __cdecl CreateCharacterTran(void);  // 0x726c0
private:
    virtual bool __cdecl work(int, void *);  // 0x72790
    bool __cdecl init(int, void *);  // 0x72800
    bool __cdecl tryCreateCharacter(void);  // 0x73210
    bool __cdecl createCharacterOk(void *);  // 0x734f0
    bool __cdecl createCharacterFail(short);  // 0x73a00
};

class DeleteCharacterTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x725e0
    __cdecl DeleteCharacterTran(void);  // 0x760b0
private:
    virtual bool __cdecl work(int, void *);  // 0x76160
    bool __cdecl init(int, void *);  // 0x761d0
    bool __cdecl tryDeleteCharacter(void);  // 0x762d0
    bool __cdecl deleteCharacterOk(void *);  // 0x763c0
    bool __cdecl deleteCharacterFail(void *);  // 0x767e0
};

class RenameCharacterTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x725d0
private:
    virtual bool __cdecl work(int, void *);  // 0x75b30
    bool __cdecl init(int, void *);  // 0x75ba0
    bool __cdecl tryRenameCharacter(void);  // 0x75cb0
    bool __cdecl renameCharacterOk(void *);  // 0x75dd0
    bool __cdecl renameCharacterFail(short);  // 0x75fe0
};

class RestoreCharacterTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x725f0
private:
    virtual bool __cdecl work(int, void *);  // 0x76930
    bool __cdecl init(int, void *);  // 0x769b0
    bool __cdecl tryRestoreCharacter(void);  // 0x76a40
    bool __cdecl restoreCharacterOk(void *);  // 0x76b40
    bool __cdecl restoreCharacterFail(short);  // 0x76bd0
};

