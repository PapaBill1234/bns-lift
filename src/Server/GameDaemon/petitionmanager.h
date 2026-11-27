// petitionmanager.h: petitionmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class Petition
{
public:
    __cdecl Petition(void);  // 0x18f8d0
    bool __cdecl Submit(__int64, wchar_t const *);  // 0x18f970
    bool __cdecl Accept(int);  // 0x18fa50
    bool __cdecl CheckOut(__int64, wchar_t const *);  // 0x18fa90
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

