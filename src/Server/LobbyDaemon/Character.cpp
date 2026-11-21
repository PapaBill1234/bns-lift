// Character.obj (LobbyDaemon PDB, 2019 + PDB). Logic from the 2019 + PDB pseudocode (Character.c).
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include "Character.h"
#include "CliSession.h"
#include "FragmentPacket.h"
#include "LiftStub.h"
#include "LobbyDB.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Packet.h"

namespace
{
wchar_t const kFile[] = L"Character.cpp";

// LIFT: the original calls Packet::Compose(PacketComposer*, int n, ...) (0xde140) in 0x31380.
// Packet.h has only ComposeV. This helper gives the variadic form.
unsigned short composeWith(Packet* packet, PacketComposer* pcr, int n, ...)
{
    va_list args;
    va_start(args, n);
    unsigned short const result = packet->ComposeV(pcr, n, args);
    va_end(args);
    return result;
}
}  // namespace

// 0x30e90
bool Character::DB::Setup(DB const& r)
{
    if (r.pcid != 0 && r.belongingWorld != 0 && r.showcase != nullptr && r.showcaseSize > 0 && r.showcaseSize <= 512)
    {
        memcpy(this, &r, sizeof(DB));
        showcase = static_cast<char*>(Memory::_Manager[2]->AllocZero(r.showcaseSize, kFile, 33));
        showcaseSize = r.showcaseSize;
        memcpy(showcase, r.showcase, r.showcaseSize);
        return true;
    }
    Log::Write(Log::LT_ERROR, kFile, 27,
               L"[pc], setup db field fail;invalid parameter, pcid:0x%I64X, wid:%d, "
               L"slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, showcase:%p, size:%d",
               r.pcid, static_cast<int>(r.belongingWorld), r.slotid.guid.id1, r.slotid.guid.id2, r.slotid.guid.id3,
               r.slotid.guid.id4[0], r.slotid.guid.id4[1], r.slotid.guid.id4[2], r.slotid.guid.id4[3],
               r.slotid.guid.id4[4], r.slotid.guid.id4[5], r.slotid.guid.id4[6], r.slotid.guid.id4[7], r.showcase,
               static_cast<int>(r.showcaseSize));
    return false;
}

// 0x31040
Character::ErrCode Character::IsPlayable() const
{
    if (_db.block)
        return ERR_BLOCKED;
    if (_db.state == IN_TRY_DELETE || _db.state == IN_TRY_RESTORE)
        return ERR_STUCK;
    if (_db.state != IN_NORMAL)
        return ERR_INVALID_STATE;
    if (_status.in_playing || _status.in_service)
        return ERR_INVALID_STATUS;
    return ERR_OK;
}

// 0x31090
Character::ClientState Character::GetClientState() const
{
    switch (_db.state)
    {
    case IN_NORMAL:
        return CLIENTSTATE_IN_USUAL;
    case IN_TRY_DELETE:
    case IN_TRY_RESTORE:
        return CLIENTSTATE_IN_STUCK;
    case IN_WAIT_DELETE:
        return CLIENTSTATE_IN_WAIT_DELETION;
    default:
        return CLIENTSTATE_UNKNOWN;
    }
}

// 0x310c0
bool Character::FetchCharacterInfo(FragmentPacket* fp) const
{
    if (fp == nullptr)
        return false;
    if (fp->FreeSize() < sizeof(unsigned long long) + sizeof(id128) + sizeof(short))
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(3, _db.pcid, _db.slotid, static_cast<int>(_db.belongingWorld)) == 0)
        return false;
    if (fp->FreeSize() < sizeof(_db.name) + sizeof(short))
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(1, _db.name) == 0)
        return false;
    if (fp->FreeSize() < _db.showcaseSize + sizeof(short))
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(1, _db.showcase, static_cast<int>(_db.showcaseSize)) == 0)
        return false;
    if (fp->FreeSize() < sizeof(long long))
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(1, _db.lastPlayEndTime) == 0)
        return false;

    ClientState const clientState = GetClientState();
    if (clientState == CLIENTSTATE_UNKNOWN)
        Log::Write(Log::LT_ERROR, kFile, 150, L"[pc], fetch info exception; unknown client-state, state:%d, pcid:0x%I64X",
                   static_cast<int>(clientState), _db.pcid);
    char value = 0;
    switch (clientState)
    {
    case CLIENTSTATE_IN_USUAL:
        value = 1;
        break;
    case CLIENTSTATE_IN_WAIT_DELETION:
        value = 2;
        break;
    case CLIENTSTATE_IN_STUCK:
        value = 3;
        break;
    default:
        break;
    }
    int remain = 0;
    if (clientState == CLIENTSTATE_IN_WAIT_DELETION)
    {
        remain = static_cast<int>(_db.deletionDelayTime - _time64(nullptr));
        if (remain < 0)
            remain = 0;
    }

    if (fp->FreeSize() < sizeof(char))
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(1, value) == 0)
        return false;
    if (fp->FreeSize() < sizeof(char))
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(1, _db.jumpingCharacterState) == 0)
        return false;
    if (fp->FreeSize() < sizeof(int))
        fp->packet.Allocate(&fp->composer);
    return fp->Compose(1, remain) != 0;
}

// 0x31380
bool Character::FetchCharacterInfo(Packet* p, PacketComposer* pcr) const
{
    if (p == nullptr || pcr == nullptr)
        return false;
    if (composeWith(p, pcr, 3, _db.pcid, _db.slotid, static_cast<int>(_db.belongingWorld)) == 0)
        return false;
    if (composeWith(p, pcr, 1, _db.name) == 0)
        return false;
    if (composeWith(p, pcr, 1, _db.showcase, static_cast<int>(_db.showcaseSize)) == 0 ||
        composeWith(p, pcr, 1, _db.lastPlayEndTime) == 0)
        return false;

    ClientState const clientState = GetClientState();
    if (clientState == CLIENTSTATE_UNKNOWN)
        Log::Write(Log::LT_ERROR, kFile, 206, L"[pc], fetch info exception; unknown client-state, state:%d, pcid:0x%I64X",
                   static_cast<int>(clientState), _db.pcid);
    char value = 0;
    switch (clientState)
    {
    case CLIENTSTATE_IN_USUAL:
        value = 1;
        break;
    case CLIENTSTATE_IN_WAIT_DELETION:
        value = 2;
        break;
    case CLIENTSTATE_IN_STUCK:
        value = 3;
        break;
    default:
        break;
    }
    int remain = 0;
    if (clientState == CLIENTSTATE_IN_WAIT_DELETION)
    {
        remain = static_cast<int>(_db.deletionDelayTime - _time64(nullptr));
        if (remain < 0)
            remain = 0;
    }
    return composeWith(p, pcr, 1, value) != 0 && composeWith(p, pcr, 1, _db.jumpingCharacterState) != 0 &&
           composeWith(p, pcr, 1, remain) != 0;
}

// 0x31550
Character::ErrCode Character::TryCreation(GameAccount const& acb, id128 const& slotid, short wid,
                                          wchar_t const* characterName, short characterNameLen)
{
    if (_db.state != IN_INVALID)
    {
        Log::Write(Log::LT_ERROR, kFile, 236, L"[pc], try create fail; invalid state, state:%d", _db.state);
        return ERR_INVALID_STATE;
    }
    if ((slotid.id[0] == 0 && slotid.id[1] == 0) || wid == 0 || characterName == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 241, L"[pc], try create fail; invalid parameter");
        return ERR_INVALID_PARAMETER;
    }

    int dbrtn = 0;
    unsigned long long pcid = 0;
    // LIFT: LTCG removed the char argument of LobbyDB::TryCharacterCreation (0xa39b0). The callee binds the
    // constant 1 (righta[0] = 1 at 0xa39b0), so the call passes 1 here. ❓ the original source expression.
    if (!LobbyDB::TryCharacterCreation(dbrtn, acb._id, slotid, wid, characterName, 2 * characterNameLen + 2, 1,
                                       &pcid))
    {
        Log::Write(Log::LT_ERROR, kFile, 255,
                   L"[pc], try create fail; db error, dbrtn:%d, "
                   L"game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
                   L"slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, wid:%d, character-name:%s",
                   dbrtn, acb._id.guid.id1, acb._id.guid.id2, acb._id.guid.id3, acb._id.guid.id4[0],
                   acb._id.guid.id4[1], acb._id.guid.id4[2], acb._id.guid.id4[3], acb._id.guid.id4[4],
                   acb._id.guid.id4[5], acb._id.guid.id4[6], acb._id.guid.id4[7], slotid.guid.id1, slotid.guid.id2,
                   slotid.guid.id3, slotid.guid.id4[0], slotid.guid.id4[1], slotid.guid.id4[2], slotid.guid.id4[3],
                   slotid.guid.id4[4], slotid.guid.id4[5], slotid.guid.id4[6], slotid.guid.id4[7],
                   static_cast<int>(wid), characterName);
        switch (dbrtn)
        {
        case 0:
            return ERR_SYSTEM;
        case 1:
            return ERR_DB_ERROR;
        case 2:
            return ERR_NAME_IN_USE;
        case 3:
            return ERR_LIMITED_NAME;
        default:
            return ERR_UNKNOWN;
        }
    }

    _db.pcid = pcid;
    _db.slotid = slotid;
    _db.belongingWorld = wid;
    wcscpy_s(_db.name, 33, characterName);
    Log::Write(Log::LT_DEBUG, kFile, 281,
               L"[pc], try create ok, pcid:0x%I64X, "
               L"game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
               L"slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, wid:%d, character-name:%s",
               pcid, acb._id.guid.id1, acb._id.guid.id2, acb._id.guid.id3, acb._id.guid.id4[0], acb._id.guid.id4[1],
               acb._id.guid.id4[2], acb._id.guid.id4[3], acb._id.guid.id4[4], acb._id.guid.id4[5],
               acb._id.guid.id4[6], acb._id.guid.id4[7], slotid.guid.id1, slotid.guid.id2, slotid.guid.id3,
               slotid.guid.id4[0], slotid.guid.id4[1], slotid.guid.id4[2], slotid.guid.id4[3], slotid.guid.id4[4],
               slotid.guid.id4[5], slotid.guid.id4[6], slotid.guid.id4[7], static_cast<int>(wid), characterName);
    _db.state = IN_TRY_CREATE;
    return ERR_OK;
}

// 0x319b0
Character::ErrCode Character::FinishCreation(short job, short level, char const jumpingCharacterState,
                                             bool const useJumpingCharacterCreationQuota, char const* showcase,
                                             short showcaseSize)
{
    if (job >= 0 && level > 0 && showcase != nullptr && static_cast<unsigned short>(showcaseSize - 1) <= 0x1FF)
    {
        if (_db.state != IN_TRY_CREATE)
        {
            Log::Write(Log::LT_ERROR, kFile, 295, L"[pc], finish create fail; invalid state, state:%d, pcid:0x%I64X",
                       _db.state, _db.pcid);
            return ERR_INVALID_STATE;
        }
        _db.job = job;
        _db.jumpingCharacterState = jumpingCharacterState;
        if (!SetLevel(level))
        {
            Log::Write(Log::LT_ERROR, kFile, 303, L"[pc], finish create fail; set level fail, pcid:0x%I64X", _db.pcid);
            return ERR_SYSTEM;
        }
        if (!SetShowcase(showcase, showcaseSize))
        {
            Log::Write(Log::LT_ERROR, kFile, 308, L"[pc], finish create fail; set showcase fail, pcid:0x%I64X",
                       _db.pcid);
            return ERR_SYSTEM;
        }
        int dbrtn = 0;
        if (LobbyDB::FinishCharacterCreation(dbrtn, _db.pcid, job, level, jumpingCharacterState,
                                             useJumpingCharacterCreationQuota, showcase, showcaseSize))
        {
            _db.state = IN_NORMAL;
            Log::Write(Log::LT_DEBUG, kFile, 320,
                       L"[pc], finish create ok, jumpingCharacterState:%d, useJumpingCharacterCreationQuota:%d, "
                       L"pcid:0x%I64X",
                       static_cast<int>(_db.jumpingCharacterState), static_cast<int>(useJumpingCharacterCreationQuota),
                       _db.pcid);
            return ERR_OK;
        }
        Log::Write(Log::LT_ERROR, kFile, 314, L"[pc], finish create fail; db fail, dbrtn:%d, pcid:0x%I64X", dbrtn,
                   _db.pcid);
        return ERR_DB_ERROR;
    }
    Log::Write(Log::LT_ERROR, kFile, 290,
               L"[pc], finish create fail; invalid parameter, pcid:0x%I64X, job:%d, level:%d, showcase:%p, size:%d",
               _db.pcid, static_cast<int>(job), static_cast<int>(level), showcase, static_cast<int>(showcaseSize));
    return ERR_INVALID_PARAMETER;
}

// 0x31c00
Character::ErrCode Character::CancelCreation()
{
    if (_db.state != IN_TRY_CREATE)
    {
        // BUG: the format has no separator between "%d" and "pcid" (orig 0x31c00).
        Log::Write(Log::LT_ERROR, kFile, 327, L"[pc], cancel creation fail; invalid state, state:%dpcid:0x%I64X",
                   _db.state, _db.pcid);
        return ERR_INVALID_STATE;
    }
    int dbrtn = 0;
    if (!LobbyDB::CancelCharacterCreation(dbrtn, _db.pcid))
    {
        Log::Write(Log::LT_ERROR, kFile, 333, L"[pc], cancel creation fail; db fail, dbrtn:%d, pcid:0x%I64X", dbrtn,
                   _db.pcid);
        return ERR_DB_ERROR;
    }
    Log::Write(Log::LT_DEBUG, kFile, 337, L"[pc], cancel creation ok, pcid:0x%I64X", _db.pcid);
    return ERR_OK;
}

// 0x31cf0
Character::ErrCode Character::TryDeletion()
{
    if (_db.block)
    {
        Log::Write(Log::LT_DEBUG, kFile, 344, L"[pc], try deletion fail; blocked, pcid:0x%I64X", _db.pcid);
        return ERR_BLOCKED;
    }
    if (_db.state == IN_TRY_DELETE || _db.state == IN_TRY_RESTORE)
    {
        Log::Write(Log::LT_ERROR, kFile, 349, L"[pc], try deletion fail; stuck, state:%d, pcid:0x%I64X", _db.state,
                   _db.pcid);
        return ERR_STUCK;
    }
    if (_db.state != IN_NORMAL)
    {
        Log::Write(Log::LT_ERROR, kFile, 354, L"[pc], try deletion fail; invalid state, state:%d, pcid:0x%I64X",
                   _db.state, _db.pcid);
        return ERR_INVALID_STATE;
    }
    int dbrtn = 0;
    if (!LobbyDB::TryCharacterDeletion(dbrtn, _db.pcid))
    {
        Log::Write(Log::LT_ERROR, kFile, 360, L"[pc], try deletion fail; db fail, dbrtn:%d, pcid:0x%I64X", dbrtn,
                   _db.pcid);
        return ERR_DB_ERROR;
    }
    _db.state = IN_TRY_DELETE;
    Log::Write(Log::LT_DEBUG, kFile, 366, L"[pc], try deletion ok, pcid:0x%I64X", _db.pcid);
    return ERR_OK;
}

// 0x31e60
Character::ErrCode Character::FinishDeletion(long remain)
{
    if (_db.state != IN_TRY_DELETE)
    {
        Log::Write(Log::LT_ERROR, kFile, 373, L"[pc], finish deletion fail; invalid state, state:%d, pcid:0x%I64X",
                   _db.state, _db.pcid);
        return ERR_INVALID_STATE;
    }
    long long until = 0;
    int dbrtn = 0;
    if (!LobbyDB::FinishCharacterDeletion(dbrtn, _db.pcid, remain, &until))
    {
        Log::Write(Log::LT_ERROR, kFile, 380, L"[pc], finish deletion fail; db fail, dbrtn:%d, pcid:0x%I64X", dbrtn,
                   _db.pcid);
        return ERR_DB_ERROR;
    }
    if (remain <= 0)
    {
        _db.state = IN_DELETED;
    }
    else
    {
        _db.state = IN_WAIT_DELETE;
        _db.deletionDelayTime = until;
    }
    Log::Write(Log::LT_DEBUG, kFile, 391, L"[pc], finish deletion ok, wait:%s, pcid:0x%I64X",
               remain > 0 ? L"yes" : L"no", _db.pcid);
    return ERR_OK;
}

// 0x31fb0
Character::ErrCode Character::CancelDeletion()
{
    if (_db.state != IN_TRY_DELETE)
    {
        Log::Write(Log::LT_ERROR, kFile, 398, L"[pc], cancel deletion fail; invalid state, state:%d, pcid:0x%I64X",
                   _db.state, _db.pcid);
        return ERR_INVALID_STATE;
    }
    int dbrtn = 0;
    if (!LobbyDB::CancelCharacterDeletion(dbrtn, _db.pcid))
    {
        Log::Write(Log::LT_ERROR, kFile, 404, L"[pc], cancel deletion fail; db fail, dbrtn:%d, pcid:0x%I64X", dbrtn,
                   _db.pcid);
        return ERR_DB_ERROR;
    }
    _db.state = IN_NORMAL;
    Log::Write(Log::LT_DEBUG, kFile, 410, L"[pc], cancel deletion ok, pcid:0x%I64X", _db.pcid);
    return ERR_OK;
}

// 0x320a0
Character::ErrCode Character::TryRestore()
{
    if (_db.state == IN_TRY_DELETE || _db.state == IN_TRY_RESTORE)
    {
        Log::Write(Log::LT_ERROR, kFile, 417, L"[pc], try restore fail; stuck, state:%d, pcid:0x%I64X", _db.state,
                   _db.pcid);
        return ERR_STUCK;
    }
    if (_db.state != IN_WAIT_DELETE)
    {
        Log::Write(Log::LT_ERROR, kFile, 422, L"[pc], try restore fail; invalid state, state:%d, pcid:0x%I64X",
                   _db.state, _db.pcid);
        return ERR_INVALID_STATE;
    }
    int dbrtn = 0;
    if (!LobbyDB::TryCharacterRestoration(dbrtn, _db.pcid))
    {
        Log::Write(Log::LT_ERROR, kFile, 428, L"[pc], try restore fail; db fail, dbrtn:%d, pcid:0x%I64X", dbrtn,
                   _db.pcid);
        return ERR_DB_ERROR;
    }
    _db.deletionDelayTime = 0;
    _db.state = IN_TRY_RESTORE;
    Log::Write(Log::LT_DEBUG, kFile, 435, L"[pc], try restore ok, pcid:0x%I64X", _db.pcid);
    return ERR_OK;
}

// 0x321e0
Character::ErrCode Character::FinishRestore()
{
    if (_db.state != IN_TRY_RESTORE)
    {
        Log::Write(Log::LT_ERROR, kFile, 442, L"[pc], finish restore fail; invalid state, state:%d, pcid:0x%I64X",
                   _db.state, _db.pcid);
        return ERR_INVALID_STATE;
    }
    int dbrtn = 0;
    if (!LobbyDB::FinishCharacterRestoration(dbrtn, _db.pcid))
    {
        Log::Write(Log::LT_ERROR, kFile, 448, L"[pc], finish restore fail; db fail, dbrtn:%d, pcid:0x%I64X", dbrtn,
                   _db.pcid);
        return ERR_DB_ERROR;
    }
    _db.state = IN_NORMAL;
    Log::Write(Log::LT_DEBUG, kFile, 454, L"[pc], finish restore ok, pcid:0x%I64X", _db.pcid);
    return ERR_OK;
}

// 0x322d0
Character::ErrCode Character::EndWaitDeletion()
{
    if (_db.state == IN_WAIT_DELETE)
    {
        _db.state = IN_DELETED;
        Log::Write(Log::LT_DEBUG, kFile, 467, L"[pc], end wait deletion ok, pcid:0x%I64X", _db.pcid);
        return ERR_OK;
    }
    Log::Write(Log::LT_ERROR, kFile, 461, L"[pc], end wait deletion fail; invalid state, state:%d, pcid:0x%I64X",
               _db.state, _db.pcid);
    return ERR_INVALID_STATE;
}

// 0x32350
// LIFT: the body does not read acb. LTCG drops it, so withCreationQuota arrives in dl (0x14003235f movzbl %dl,%r8d).
Character::ErrCode Character::UpgradeJumpingCharacterState(GameAccount const&, bool withCreationQuota)
{
    if (_db.state != IN_NORMAL)
    {
        Log::Write(Log::LT_ERROR, kFile, 474,
                   L"[pc], upgrade jumping character state fail; invalid state, state:%d, pcid:0x%I64X", _db.state,
                   _db.pcid);
        return ERR_INVALID_STATE;
    }
    if (_db.jumpingCharacterState != JUMPINGCHARACTERSTATE_TRIAL)
    {
        Log::Write(Log::LT_ERROR, kFile, 480,
                   L"[pc], upgrade jumping character state fail; invalid current jumpingCharacterState, "
                   L"jumpingCharacterState:%d, pcid:0x%I64X",
                   static_cast<int>(_db.jumpingCharacterState), _db.pcid);
        return ERR_INVALID_PARAMETER;
    }
    int dbrtn = 0;
    if (!LobbyDB::UpdateJumpingCharacterStateComplete(dbrtn, _db.pcid, withCreationQuota))
    {
        Log::Write(Log::LT_ERROR, kFile, 487,
                   L"[pc], upgrade jumping character state fail; db fail, dbrtn:%d, pcid:0x%I64X", dbrtn, _db.pcid);
        return ERR_DB_ERROR;
    }
    _db.jumpingCharacterState = JUMPINGCHARACTERSTATE_JUMPING;
    Log::Write(Log::LT_DEBUG, kFile, 493,
               L"[pc], upgrade jumping character state ok, jumpingCharacterState:%d, pcid:0x%I64X",
               static_cast<int>(_db.jumpingCharacterState), _db.pcid);
    return ERR_OK;
}

// 0x32490
bool Character::SetLevel(short level)
{
    if (level > 0)
    {
        _db.level = level;
        Log::Write(Log::LT_DEBUG, kFile, 506, L"[pc], set level ok, level:%d, pcid:0x%I64X", static_cast<int>(level),
                   _db.pcid);
        return true;
    }
    // BUG: "paramter" is a typo in the original log text (orig 0x32490).
    Log::Write(Log::LT_ERROR, kFile, 500, L"[pc], set level fail; invalid paramter, level:%d, pcid:0x%I64X",
               static_cast<int>(level), _db.pcid);
    return false;
}

// 0x32510
bool Character::SetShowcase(char const* showcase, short showcaseSize)
{
    if (showcase != nullptr && static_cast<unsigned short>(showcaseSize - 1) <= 0x1FF)
    {
        if (_db.showcaseSize < showcaseSize)
        {
            if (_db.showcase != nullptr)
                _db.showcase = static_cast<char*>(
                    Memory::_Manager[2]->ReallocZero(_db.showcase, showcaseSize, _db.showcaseSize, kFile, 519));
            else
                _db.showcase = static_cast<char*>(Memory::_Manager[2]->AllocZero(showcaseSize, kFile, 521));
        }
        _db.showcaseSize = showcaseSize;
        memcpy(_db.showcase, showcase, showcaseSize);
        Log::Write(Log::LT_DEBUG, kFile, 527, L"[pc], set showcase ok, showcase:%p, size:%d, pcid:0x%I64X", showcase,
                   static_cast<int>(showcaseSize), _db.pcid);
        return true;
    }
    Log::Write(Log::LT_ERROR, kFile, 513,
               L"[pc], set showcase fail; invalid parameter, showcase:%p, size:%d, pcid:0x%I64X", showcase,
               static_cast<int>(showcaseSize), _db.pcid);
    return false;
}

// 0x32630
bool Character::SetName(wchar_t const* name)
{
    if (name != nullptr)
    {
        wcscpy_s(_db.name, 33, name);
        Log::Write(Log::LT_DEBUG, kFile, 541, L"[pc], set name ok, name:%s, pcid:0x%I64X", name, _db.pcid);
        return true;
    }
    Log::Write(Log::LT_ERROR, kFile, 535, L"[pc], set name fail; invalid param, pcid:0x%I64X", _db.pcid);
    return false;
}

// 0x326c0
bool Character::StartGameWorldPlay(unsigned long ipv4)
{
    if (_status.in_playing)
    {
        Log::Write(Log::LT_ERROR, kFile, 548, L"[pc], start game-world play fail; already started, pcid:0x%I64X",
                   _db.pcid);
        return false;
    }
    int dbrtn = 0;
    if (!LobbyDB::UpdateLastPlayStart(dbrtn, _db.pcid, ipv4))
    {
        Log::Write(Log::LT_ERROR, kFile, 554, L"[pc], start game-world play fail; db error, dbrtn:%d, pcid:0x%I64X",
                   dbrtn, _db.pcid);
        return false;
    }
    _status.in_playing = true;
    Log::Write(Log::LT_DEBUG, kFile, 560, L"[pc], start game-world play ok, ip-address:%s, pcid:0x%I64X",
               LobbyDaemon::GetAddressStringWForLogs(ipv4), _db.pcid);
    return true;
}

// 0x32800
bool Character::EndGameWorldPlay()
{
    if (_status.in_playing)
    {
        int dbrtn = 0;
        if (!LobbyDB::UpdateLastPlayEnd(dbrtn, _db.pcid))
            Log::Write(Log::LT_ERROR, kFile, 573,
                       L"[pc], end game-world play exception; update db fail, dbrtn:%d, pcid:0x%I64X", dbrtn, _db.pcid);
        __time64_t const now = _time64(nullptr);
        if (now == -1)
            Log::Write(Log::LT_ERROR, kFile, 577,
                       L"[pc], end game-world play exception; get current time(UTC) fail, pcid:0x%I64X", _db.pcid);
        else
            _db.lastPlayEndTime = now;
        _status.in_playing = false;
        Log::Write(Log::LT_DEBUG, kFile, 583, L"[pc], end game-world play ok, pcid:0x%I64X", _db.pcid);
        return true;
    }
    Log::Write(Log::LT_ERROR, kFile, 567, L"[pc], end game-world play fail; not started, pcid:0x%I64X", _db.pcid);
    return false;
}

// 0x328f0
void Character::SetSlotId(id128 const& slotid)
{
    _db.slotid = slotid;
    Log::Write(Log::LT_DEBUG, kFile, 596,
               L"[pc], set slot id ok, pcid:0x%I64X, slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
               _db.pcid, slotid.guid.id1, slotid.guid.id2, slotid.guid.id3, slotid.guid.id4[0], slotid.guid.id4[1],
               slotid.guid.id4[2], slotid.guid.id4[3], slotid.guid.id4[4], slotid.guid.id4[5], slotid.guid.id4[6],
               slotid.guid.id4[7]);
}
