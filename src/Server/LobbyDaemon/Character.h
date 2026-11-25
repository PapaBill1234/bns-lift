// Character.obj (LobbyDaemon PDB, 2019 + PDB). Layout from include/pdb/LobbyDaemon/types.h.
// LIFT: the PDB has no header names. This module header holds the PDB layout of Character.
#pragma once
#include <stddef.h>
#include "StringUtil.h"

class FragmentPacket;
class GameAccount;
class Packet;
class PacketComposer;

class Character
{
public:
    struct DB;
    struct SlotAttribute;
    struct Status;

    enum ClientState : int
    {
        CLIENTSTATE_UNKNOWN = 0x0,
        CLIENTSTATE_IN_USUAL = 0x1,
        CLIENTSTATE_IN_WAIT_DELETION = 0x2,
        CLIENTSTATE_IN_STUCK = 0x3,
    };

    enum ErrCode : int
    {
        ERR_OK = 0x0,
        ERR_UNKNOWN = 0x1,
        ERR_SYSTEM = 0x2,
        ERR_INVALID_PARAMETER = 0x3,
        ERR_INVALID_STATE = 0x4,
        ERR_INVALID_STATUS = 0x5,
        ERR_DB_ERROR = 0x6,
        ERR_NAME_IN_USE = 0x7,
        ERR_LIMITED_NAME = 0x8,
        ERR_BLOCKED = 0x9,
        ERR_STUCK = 0xA,
    };

    enum JumpingCharacterState : int
    {
        JUMPINGCHARACTERSTATE_NONE = 0x0,
        JUMPINGCHARACTERSTATE_TRIAL = 0x1,
        JUMPINGCHARACTERSTATE_JUMPING = 0x2,
    };

    enum State : int
    {
        IN_INVALID = 0x0,
        IN_TRY_CREATE = 0x1,
        IN_NORMAL = 0x2,
        IN_TRY_DELETE = 0x3,
        IN_WAIT_DELETE = 0x4,
        IN_TRY_RESTORE = 0x5,
        IN_DELETED = 0x6,
    };

    struct DB
    {
        bool Setup(DB const& r);  // 0x30e90

        unsigned long long pcid;
        id128 slotid;
        short belongingWorld;
        short job;
        short level;
        wchar_t name[33];
        long long deletionDelayTime;
        long long lastPlayEndTime;
        char jumpingCharacterState;
        char* showcase;
        short showcaseSize;
        int state;
        bool block;
    };

    struct SlotAttribute
    {
        int dummy;
    };

    struct Status
    {
        bool in_playing : 1;
        bool in_service : 1;
    };

    ErrCode IsPlayable() const;                                   // 0x31040
    ClientState GetClientState() const;                           // 0x31090
    bool FetchCharacterInfo(FragmentPacket* fp) const;            // 0x310c0
    bool FetchCharacterInfo(Packet* p, PacketComposer* pcr) const;  // 0x31380
    ErrCode TryCreation(GameAccount const& acb, id128 const& slotid, short wid, wchar_t const* characterName,
                        short characterNameLen);                  // 0x31550
    ErrCode FinishCreation(short job, short level, char const jumpingCharacterState,
                           bool const useJumpingCharacterCreationQuota, char const* showcase,
                           short showcaseSize);                   // 0x319b0
    ErrCode CancelCreation();                                     // 0x31c00
    ErrCode TryDeletion();                                        // 0x31cf0
    ErrCode FinishDeletion(long remain);                          // 0x31e60
    ErrCode CancelDeletion();                                     // 0x31fb0
    ErrCode TryRestore();                                         // 0x320a0
    ErrCode FinishRestore();                                      // 0x321e0
    ErrCode EndWaitDeletion();                                    // 0x322d0
    ErrCode UpgradeJumpingCharacterState(GameAccount const& acb, bool withCreationQuota);  // 0x32350
    bool SetLevel(short level);                                   // 0x32490
    bool SetShowcase(char const* showcase, short showcaseSize);   // 0x32510
    bool SetName(wchar_t const* name);                            // 0x32630
    bool StartGameWorldPlay(unsigned long ipv4);                  // 0x326c0
    bool EndGameWorldPlay();                                      // 0x32800
    void SetSlotId(id128 const& slotid);                          // 0x328f0
    // LIFT: PDB inline Character::SetServiceStatus(bool). It has no own RVA. Inlined in
    // ChangeCharacterRaceJob::registerServiceEntry (0x203b0) and releasePcServiceStatus (0x229a0).
    inline void SetServiceStatus(bool status);

    DB _db;
    char _right;
    SlotAttribute _slotattr;
    Status _status;
};
static_assert(sizeof(Character) == 0xA0, "sizeof Character");
static_assert(offsetof(Character, _db) == 0x0, "Character::_db");
static_assert(offsetof(Character, _right) == 0x90, "Character::_right");
static_assert(offsetof(Character, _slotattr) == 0x94, "Character::_slotattr");
static_assert(offsetof(Character, _status) == 0x98, "Character::_status");
static_assert(sizeof(Character::DB) == 0x90, "sizeof Character::DB");
static_assert(offsetof(Character::DB, slotid) == 0x8, "Character::DB::slotid");
static_assert(offsetof(Character::DB, belongingWorld) == 0x18, "Character::DB::belongingWorld");
static_assert(offsetof(Character::DB, job) == 0x1A, "Character::DB::job");
static_assert(offsetof(Character::DB, level) == 0x1C, "Character::DB::level");
static_assert(offsetof(Character::DB, name) == 0x1E, "Character::DB::name");
static_assert(offsetof(Character::DB, deletionDelayTime) == 0x60, "Character::DB::deletionDelayTime");
static_assert(offsetof(Character::DB, lastPlayEndTime) == 0x68, "Character::DB::lastPlayEndTime");
static_assert(offsetof(Character::DB, jumpingCharacterState) == 0x70, "Character::DB::jumpingCharacterState");
static_assert(offsetof(Character::DB, showcase) == 0x78, "Character::DB::showcase");
static_assert(offsetof(Character::DB, showcaseSize) == 0x80, "Character::DB::showcaseSize");
static_assert(offsetof(Character::DB, state) == 0x84, "Character::DB::state");
static_assert(offsetof(Character::DB, block) == 0x88, "Character::DB::block");
static_assert(sizeof(Character::SlotAttribute) == 0x4, "sizeof Character::SlotAttribute");
static_assert(sizeof(Character::Status) == 0x1, "sizeof Character::Status");

// LIFT: body of the PDB inline Character::SetServiceStatus(bool). From the inlined code in
// ChangeCharacterRaceJob::registerServiceEntry (0x203b0) and releasePcServiceStatus (0x229a0).
#include "Log.h"
inline void Character::SetServiceStatus(bool status)
{
    _status.in_service = status;
    Log::Write(Log::LT_DEBUG, L"Character.cpp", 590, L"[pc], set service status, status:%s, pcid:0x%I64X",
               status ? L"yes" : L"no", _db.pcid);
}
