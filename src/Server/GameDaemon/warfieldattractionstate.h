// warfieldattractionstate.h: warfieldattractionstate.cpp, warfieldattractionstate.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class WarFieldAttractionState
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x1ee750
    virtual bool __cdecl Init(::Zone *, bool);  // 0x225ba0
private:
    ::Data::WarFieldWarFieldZoneTypeType __cdecl calcWarFieldZoneType(unsigned int);  // 0x226240
public:
    void __cdecl ChangeStep(char, char);  // 0x226360
    virtual void __cdecl FetchInZoneAttractionState(::FragmentPacket &);  // 0x226850
private:
    void __cdecl leaveAttractionZone(::Pc *);  // 0x226910
};

