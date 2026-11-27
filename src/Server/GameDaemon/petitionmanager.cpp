// petitionmanager.cpp: petitionmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "petitionmanager.h"
#include "LiftStub.h"

// 0x18f8d0
__cdecl Petition::Petition(void)
{
    LIFT_STUB(0x18f8d0);
}

// 0x18f970
bool __cdecl Petition::Submit(__int64, wchar_t const *)
{
    LIFT_STUB(0x18f970);
}

// 0x18fa50
bool __cdecl Petition::Accept(int)
{
    LIFT_STUB(0x18fa50);
}

// 0x18fa90
bool __cdecl Petition::CheckOut(__int64, wchar_t const *)
{
    LIFT_STUB(0x18fa90);
}

// 0x18fb30
__cdecl PetitionManager::PetitionManager(void)
{
    LIFT_STUB(0x18fb30);
}

// 0x18fbc0
__cdecl PetitionManager::~PetitionManager(void)
{
    LIFT_STUB(0x18fbc0);
}

// 0x18ff10
bool __cdecl PetitionManager::MakeConnectedCharInfoAckPacket(::Packet *, unsigned char, ::Packet const *, unsigned short, unsigned int)
{
    LIFT_STUB(0x18ff10);
}

// 0x190080
bool __cdecl PetitionManager::AddTran(int *, __int64, wchar_t const *)
{
    LIFT_STUB(0x190080);
}

// 0x190180
void __cdecl PetitionManager::RemoveTran(int)
{
    LIFT_STUB(0x190180);
}

// 0x190240
::Petition * __cdecl PetitionManager::AcquireByTid(int)
{
    LIFT_STUB(0x190240);
}

// 0x1902f0
void __cdecl PetitionManager::ClearTranList(void)
{
    LIFT_STUB(0x1902f0);
}

// 0x190420
bool __cdecl PetitionManager::AddPetition(int, ::Petition *)
{
    LIFT_STUB(0x190420);
}

// 0x190500
void __cdecl PetitionManager::RemovePetition(int)
{
    LIFT_STUB(0x190500);
}

// 0x1905c0
::Petition * __cdecl PetitionManager::AcquireById(int)
{
    LIFT_STUB(0x1905c0);
}

// 0x190670
bool __cdecl PetitionManager::AddPc(__int64, int)
{
    LIFT_STUB(0x190670);
}

// 0x190740
void __cdecl PetitionManager::RemovePc(__int64)
{
    LIFT_STUB(0x190740);
}

// 0x1907e0
bool __cdecl PetitionManager::GetPetitionId(__int64, int *)
{
    LIFT_STUB(0x1907e0);
}

// 0x190890
bool __cdecl PetitionManager::addTran(int *, ::Petition *)
{
    LIFT_STUB(0x190890);
}
