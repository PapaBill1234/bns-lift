// petitionmanager.h: petitionmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class Petition : public ::DynamicRefCntObj
{
public:
    __cdecl Petition(void);  // 0x18f8d0
    bool __cdecl Submit(__int64, wchar_t const *);  // 0x18f970
    bool __cdecl Accept(int);  // 0x18fa50
    bool __cdecl CheckOut(__int64, wchar_t const *);  // 0x18fa90
private:
    // PDB layout of Petition (size 0x110).
    int _id;  // +0x18
    int _state;  // +0x1C
    __int64 _pcDbId;  // +0x20
    wchar_t _pcName[33];  // +0x28
    __int64 _reqPcDbId;  // +0x70
    wchar_t _reqPcName[33];  // +0x78
    __int64 _gmPcDbId;  // +0xC0
    wchar_t _gmPcName[33];  // +0xC8
    bool _forced;  // +0x10A
};

class PetitionManager
{
public:
    __cdecl PetitionManager(void);  // 0x18fb30
    __cdecl ~PetitionManager(void);  // 0x18fbc0
    bool __cdecl MakeConnectedCharInfoAckPacket(::Packet *, unsigned char, ::Packet const *, unsigned short, unsigned int);  // 0x18ff10
    bool __cdecl AddTran(int *, __int64, wchar_t const *);  // 0x190080
    void __cdecl RemoveTran(int);  // 0x190180
    ::Petition * __cdecl AcquireByTid(int);  // 0x190240
    void __cdecl ClearTranList(void);  // 0x1902f0
    bool __cdecl AddPetition(int, ::Petition *);  // 0x190420
    void __cdecl RemovePetition(int);  // 0x190500
    ::Petition * __cdecl AcquireById(int);  // 0x1905c0
    bool __cdecl AddPc(__int64, int);  // 0x190670
    void __cdecl RemovePc(__int64);  // 0x190740
    bool __cdecl GetPetitionId(__int64, int *);  // 0x1907e0
private:
    bool __cdecl addTran(int *, ::Petition *);  // 0x190890
};

