// zonecellattributemanager.h: zonecellattributemanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ZoneCellAttributeManager
{
private:
    __cdecl ZoneCellAttributeManager(void);  // 0x13c20
    __cdecl ~ZoneCellAttributeManager(void);  // 0x13d60
public:
    bool __cdecl Create(int, ::Data::ZoneCellAttributeRecordPtr);  // 0x13ed0
    bool __cdecl Check(int, short, short, short, ::Data::ZoneCellAttributeCellAttributeType) const;  // 0x14240
};

class ZoneCellAttributeTable
{
private:
    __cdecl ZoneCellAttributeTable(int, ::Data::ZoneCellAttributeRecordPtr);  // 0x130c0
    __cdecl ~ZoneCellAttributeTable(void);  // 0x13150
    bool __cdecl setAttr(short, short, ::Data::ZoneCellAttributeCellAttributeType);  // 0x131f0
    char __cdecl getAttr(short, short) const;  // 0x13390
    bool __cdecl initialize(void);  // 0x13510
    bool __cdecl check(short, short, short, ::Data::ZoneCellAttributeCellAttributeType) const;  // 0x13b90
};

