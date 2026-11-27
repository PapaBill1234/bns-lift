// closettran.h: closettran.cpp, closettran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class PutItemIntoClosetTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x80070
    static ::GameTranDef _def;  // LIFT: PDB data PutItemIntoClosetTran::_def
private:
    virtual bool __cdecl work(int, void *);  // 0x800c0
    bool __cdecl init(int, void *);  // 0x80120
    bool __cdecl putItemIntoClosetOk(void);  // 0x802d0
    bool __cdecl putItemIntoClosetFail(void *);  // 0x80750
};

class TakeItemFromClosetTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x80080
    static ::GameTranDef _def;  // LIFT: PDB data TakeItemFromClosetTran::_def
private:
    virtual bool __cdecl work(int, void *);  // 0x80aa0
    bool __cdecl init(int, void *);  // 0x80b00
    bool __cdecl takeCostumeFromClosetOk(void);  // 0x80ca0
    bool __cdecl takeCostumeFromClosetFail(void *);  // 0x81150
};

