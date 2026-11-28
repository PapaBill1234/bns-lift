// warfieldmanager.h: warfieldmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

// LIFT: view of the PDB record Data::WarFieldRecord (base DrEl, size 0x3B8).
// Only the fields that the lifted bodies read are declared.
struct WarFieldRecordView
{
    char lift_pad_0[0x8];  // ❓ base DrEl (+0 to +7) is not declared here
    unsigned __int64 key;  // +8 (0x8) PDB type Data::WarFieldRecord::Key
};

class WarFieldGroup
{
public:
    // LIFT: PDB Data::WarFieldRecordPtr _data (+0). Only the record pointer is declared.
    ::WarFieldRecordView *_data;  // +0 (0x0) (PDB: DrRecordPtr::_record, DrEl *)
private:
    __cdecl WarFieldGroup(void);  // 0x226b00
    __cdecl ~WarFieldGroup(void);  // 0x226c00
    bool __cdecl init(unsigned __int64);  // 0x226cf0
    unsigned __int64 __cdecl getDataKey(void);  // 0x226d70
    void __cdecl changeStep(char);  // 0x226de0
    int __cdecl executeSerializedJob(::Task *);  // 0x226f10
    int __cdecl executeSerializedJob(::Data::WarFieldWarFieldZoneTypeType, ::Task *);  // 0x227030
    void __cdecl timerExpired(long);  // 0x227250
    bool __cdecl addZone(::Data::WarFieldWarFieldZoneTypeType, ::Zone *);  // 0x227560
};

class WarFieldManager
{
private:
    __cdecl WarFieldManager(void);  // 0x227870
    __cdecl ~WarFieldManager(void);  // 0x227930
public:
    void __cdecl TimerExpired(long);  // 0x227ab0
    bool __cdecl AddZone(::Data::WarFieldWarFieldZoneTypeType, ::Zone *, unsigned __int64);  // 0x227b70
    char __cdecl GetStep(unsigned __int64);  // 0x227f00
};

