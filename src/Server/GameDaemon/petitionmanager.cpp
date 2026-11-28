// petitionmanager.cpp: petitionmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "petitionmanager.h"
#include <wchar.h>
#include "Log.h"
#include "LiftStub.h"

#define PETITIONMANAGER_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\PetitionManager.cpp"

static_assert(sizeof(Petition) == 0x110, "sizeof Petition");

#pragma comment(linker, "/INCLUDE:??0Petition@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Accept@Petition@@QEAA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x18f8d0
__cdecl Petition::Petition(void)
    : _id(0), _state(1), _pcDbId(0), _reqPcDbId(0), _gmPcDbId(0), _forced(false)
{
    // ❓ _state 1 is the first Petition::State value. The PDB enumerator name is not looked up.
    _tag = 6666;  // ❓ The original stores this tag after the vtable store. The source name of the constant is not known.
    // LIFT: the original copies Petition::INVALID_NAME (an empty string literal) into the three names.
    wcsncpy(_pcName, L"", 33);
    wcsncpy(_reqPcName, L"", 33);
    wcsncpy(_gmPcName, L"", 33);
}

// 0x18f970
bool __cdecl Petition::Submit(__int64, wchar_t const *)
{
    LIFT_STUB(0x18f970);
}

// 0x18fa50
bool __cdecl Petition::Accept(int id)
{
    if (_state != 2)  // ❓ Petition::State value 2 (submitted). The PDB enumerator name is not looked up.
    {
        Log::Write(Log::LT_DEBUG, PETITIONMANAGER_FILE, 97, L"[petition], Accept() invald state, state:%d", _state);
        return false;
    }
    _id = id;
    return true;
}

// 0x18fa90
bool __cdecl Petition::CheckOut(__int64, wchar_t const *)
{
    LIFT_STUB(0x18fa90);
}

// 0x18fb30
__cdecl PetitionManager::PetitionManager(void)
{
    // ❓ Not done: needs three std::map members (StlAllocator<..., 2>) and a CriticalSection member in the class view.
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
