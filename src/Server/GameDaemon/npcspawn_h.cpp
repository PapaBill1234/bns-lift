// npcspawn_h.cpp: npcspawn.h (GameDaemon PDB, 2019 + PDB). Wave E: NpcSpawnInfo leaf getters lifted.
#include "npcspawn.h"
#include "LiftStub.h"

// LIFT: npcspawn.h declares NpcSpawnInfo without members. This view holds the PDB layout (size 0x20).
// The record pointers point to DrEl records (DrEl is 6 bytes, so record[n].size is at byte n*6+4).
struct NpcSpawnInfoView
{
    const char *_spawnData;        // +0x00 Data::ZoneNpcSpawnRecordPtr::_record
    const char *_npcRandomSpawnData; // +0x08 Data::ZoneNpcRandomSpawnRecordPtr::_record
    const wchar_t *_npcAlias;      // +0x10
    int _spawnIndex;               // +0x18
    int _npcRepeatIdx;             // +0x1C
};

#pragma comment(linker, "/INCLUDE:?GetAlias@NpcSpawnInfo@@QEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
// 0x1edf00
wchar_t const * __cdecl NpcSpawnInfo::GetAlias(void)
{
    const NpcSpawnInfoView *self = reinterpret_cast<const NpcSpawnInfoView *>(this);
    const char *record = self->_spawnData;
    if (record != nullptr)
        return *reinterpret_cast<const wchar_t *const *>(record + 0x10);
    record = self->_npcRandomSpawnData;
    if (record != nullptr)
        return *reinterpret_cast<const wchar_t *const *>(record + 0x10);
    const wchar_t *result = self->_npcAlias;
    if (result == nullptr)
        return L""; // LIFT: 0x1edf00 returns the shared empty wide string (zone._privateProp[292]).
    return result;
}

#pragma comment(linker, "/INCLUDE:?GetActDetect@NpcSpawnInfo@@QEAAHH@Z")  // LIFT: dead-strip keep (no live caller yet)
// 0x34f070
int __cdecl NpcSpawnInfo::GetActDetect(int index)
{
    const NpcSpawnInfoView *self = reinterpret_cast<const NpcSpawnInfoView *>(this);
    const char *record = self->_spawnData;
    if (record != nullptr)
    {
        // Server check: index must be 0 or 1 (unsigned compare).
        if (static_cast<unsigned int>(index) <= 1)
            return static_cast<int>(*(record + 0xA0 + index));
    }
    else
    {
        const char *random = self->_npcRandomSpawnData;
        if (random != nullptr)
            return static_cast<int>(*(random + 0x88 + self->_npcRepeatIdx));
    }
    return 1;
}

#pragma comment(linker, "/INCLUDE:?GetActSocial@NpcSpawnInfo@@QEAA_KH@Z")  // LIFT: dead-strip keep (no live caller yet)
// 0x34f0b0
unsigned __int64 __cdecl NpcSpawnInfo::GetActSocial(int index)
{
    const NpcSpawnInfoView *self = reinterpret_cast<const NpcSpawnInfoView *>(this);
    const char *record = self->_spawnData;
    if (record != nullptr)
    {
        // Server check: index must be 0, 1 or 2 (unsigned compare).
        if (static_cast<unsigned int>(index) <= 2)
            return *reinterpret_cast<const unsigned __int64 *>(record + 0x88 + static_cast<__int64>(index) * 8);
    }
    else
    {
        const char *random = self->_npcRandomSpawnData;
        if (random != nullptr)
            return static_cast<unsigned __int64>(static_cast<__int64>(*(random + 0x88 + self->_npcRepeatIdx)));
    }
    return 0;
}

// 0x34f0f0
::Data::ZoneAreaRecord::Key __cdecl NpcSpawn::PickAreaIdForNpcRandomSpawn(int)
{
    LIFT_STUB(0x34f0f0);
}
