// LobbyDB.obj (LobbyDaemon PDB, 2019 + PDB). Card ld-14 lifts 0x9fdb0, 0x9fe00, 0xa0a40, 0xa1580, 0xa17f0, 0xa24c0, 0xa2dd0, 0xa37e0, 0xa39b0, 0xa3da0 and 0xa4150. A stub is not a lift.
#include <winsock2.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>
#include <wchar.h>
#include "LobbyDB.h"
#include "Db.h"
#include "Log.h"
#include "LiftStub.h"
#include "GameWorld.h"
#include "Memory.h"
#include "StlMemory.h"
#include <vector>

#define LOBBYDB_FILE L"LobbyDB.cpp"

namespace
{
// LIFT: the original compares the column length with the literal -1 (SQL_NULL_DATA). This name is not in the PDB
// (0x9fe00, 0xa17f0, 0xa24c0). The name keeps the constant readable.
unsigned long long const kNullData = static_cast<unsigned long long>(-1);  // SQL_NULL_DATA

// LIFT: the original compares both qwords with the PDB global ID128_ID_ZERO (0x12d870, StringUtil.h) in
// LoadGameAccount (0x9fe00), UpdateGameAccountTimeBasedPlayInfo (0xa0a40), UpdateLastLogout (0xa1580),
// LoadCharacterList (0xa17f0) and TryCharacterCreation (0xa39b0). Codegen trial A8 of card ld-14.
bool IsIdZero(id128 const& id) { return id.id[0] == ID128_ID_ZERO.id[0] && id.id[1] == ID128_ID_ZERO.id[1]; }
}  // namespace

// 0x9fdb0
AutoDbTran::~AutoDbTran()
{
    if (Tran != nullptr)
    {
        if (TimeoutSec != 10)
            SQLSetStmtAttrW(Tran->StmtHandle, SQL_QUERY_TIMEOUT,
                            reinterpret_cast<SQLPOINTER>(static_cast<long long>(TimeoutSec)), 0);
        Db::ReleaseTransaction(Tran);
        Tran = nullptr;
    }
}

// 0x9fe00
#pragma comment(linker, "/INCLUDE:?LoadGameAccount@LobbyDB@@SA_NAEAHAEBTid128@@AEA_NAEAUDB@GameAccount@@@Z")   // LIFT: keep until the caller is lifted (0x33f00)
bool LobbyDB::LoadGameAccount(int& dbrtn, id128 const& gameAccountId, bool& exists, GameAccount::DB& out)
{
    // PDB local enums LobbyDB::LoadGameAccount::__l11::Param and Column. The PDB data ParamDesc and ColDesc (0x207928,
    // 0x207938) hold the enumerator names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_GAME_ACCOUNT_ID = 1,
        PARAM_MAX = 2
    };
    enum Column
    {
        COL_GAME_ACCOUNT_ID = 0,
        COL_GAME_ACCOUNT_NAME = 1,
        COL_GAME_ACCOUNT_RIGHT = 2,
        COL_REPRESENTATIVE_PCID = 3,
        COL_GAME_ACCOUNT_BOT_SCORE = 4,
        COL_GAME_ACCOUNT_BOT_SCORE_IGNORE = 5,
        COL_MAX = 6
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {L"PARAM_RETURN", L"PARAM_GAME_ACCOUNT_ID"};
    static wchar_t const* const ColDesc[COL_MAX] = {L"COL_GAME_ACCOUNT_ID",         L"COL_GAME_ACCOUNT_NAME",
                                                    L"COL_GAME_ACCOUNT_RIGHT",      L"COL_REPRESENTATIVE_PCID",
                                                    L"COL_GAME_ACCOUNT_BOT_SCORE", L"COL_GAME_ACCOUNT_BOT_SCORE_IGNORE"};
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadGameAccount(?)}";

    if (IsIdZero(gameAccountId))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 73, L"[lobbydb], load game-account fail; invalid parameter");
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 79, L"[lobbydb], load game-account fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 85,
                   L"[lobbydb], load game-account fail; failed to prepare sql, query:%s", query);
        return false;
    }
    dbrtn = 0;
    exists = false;
    int param = PARAM_RETURN;
    int column = COL_GAME_ACCOUNT_ID;
    unsigned long long paramlen[PARAM_MAX];
    unsigned long long collen[COL_MAX];
    memset(paramlen, 0, sizeof(paramlen));
    memset(collen, 0, sizeof(collen));
    id128 dbGameAccountId;
    GameAccount::DB db;
    memset(&dbGameAccountId, 0, sizeof(dbGameAccountId));
    memset(&db, 0, sizeof(db));
    collen[COL_GAME_ACCOUNT_NAME] = SQL_NTS;
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]) ||
        (param = PARAM_GAME_ACCOUNT_ID,
         !tran.Tran->BindParam(2, SQL_PARAM_INPUT, const_cast<id128*>(&gameAccountId), 0, 0, SQL_GUID, SQL_C_GUID,
                               &paramlen[1])))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 183, L"[lobbydb], load game-account fail; bind parameter fail, param:%s",
                   ParamDesc[param]);
        return false;
    }
    // LIFT: the original has the DbTransaction::BindCol body inline (null StmtHandle, SQLBindCol, statmentErrorLog).
    // The "Not initialized" log is one block for all 6 columns (same as PostOfficeDaemon 0x14e50).
    DB_BIND_COL_NI(tran.Tran, 1, &dbGameAccountId, 0, SQL_C_GUID, &collen[0], NOT_INIT, BIND_ERROR);
    column = COL_GAME_ACCOUNT_NAME;
    DB_BIND_COL_NI(tran.Tran, 2, db.name, 130, SQL_C_WCHAR, &collen[1], NOT_INIT, BIND_ERROR);
    column = COL_GAME_ACCOUNT_RIGHT;
    DB_BIND_COL_NI(tran.Tran, 3, &db.right, 0, SQL_C_TINYINT, &collen[2], NOT_INIT, BIND_ERROR);
    column = COL_REPRESENTATIVE_PCID;
    DB_BIND_COL_NI(tran.Tran, 4, &db.representativePcid, 0, SQL_C_SBIGINT, &collen[3], NOT_INIT, BIND_ERROR);
    column = COL_GAME_ACCOUNT_BOT_SCORE;
    DB_BIND_COL_NI(tran.Tran, 5, &db.botScore, 0, SQL_C_LONG, &collen[4], NOT_INIT, BIND_ERROR);
    column = COL_GAME_ACCOUNT_BOT_SCORE_IGNORE;
    DB_BIND_COL_NI(tran.Tran, 6, &db.botScoreIgnore, 0, SQL_C_BIT, &collen[5], NOT_INIT, BIND_ERROR);
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 146, L"[lobbydb], load game-account fail; execute fail, dbrtn:%d",
                   dbrtn);
        return false;
    }
    for (;;)
    {
        int const fetched = tran.Tran->Fetch(0);  // LIFT: Fetch never reads edx (see SmartCouponDB.cpp)
        if (fetched == -1)
        {
            Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 154, L"[lobbydb], load game-account fail; fetch fail");
            return false;
        }
        if (fetched == 0)
            break;
        unsigned long long representativePcid = db.representativePcid;
        if (collen[COL_REPRESENTATIVE_PCID] == kNullData)
            representativePcid = 0;
        db.representativePcid = representativePcid;
        if (collen[COL_GAME_ACCOUNT_NAME] == kNullData)
            out.name[0] = 0;
        else
            wcscpy_s(out.name, 65, db.name);
        out.right = db.right;
        out.representativePcid = db.representativePcid;
        out.botScore = db.botScore;
        out.botScoreIgnore = db.botScoreIgnore;
        exists = true;
    }
    if (dbrtn != 0)
        return false;
    return true;

NOT_INIT:
    Log::Write(Log::LT_ERROR, L"source\\Db.cpp", 286, L"DbTransaction::BindCol(), Not initialized");
BIND_ERROR:
    Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 187, L"[lobbydb], load game-account fail; bind column fail, column:%s",
               ColDesc[column]);
    return false;
}

// 0xa03e0
// LIFT: not lifted. Needs LobbyDaemon::_instance, _timeBasedPlaySeasonSchedule and TimeBasedPlaySeasonSchedule::Data::GetNextResetTimeUTC. No layout in src yet. ❓
bool LobbyDB::LoadGameAccountTimeBasedPlayInfo(int&, id128 const&, TimeBasedPlayInfoList&)
{
    LIFT_STUB(0xa03e0);
}

// 0xa0a40
#pragma comment(linker, "/INCLUDE:?UpdateGameAccountTimeBasedPlayInfo@LobbyDB@@SA_NAEAHAEBTid128@@AEBVTimeBasedPlayInfoList@@@Z")   // LIFT: keep until the caller is lifted (0x38500)
bool LobbyDB::UpdateGameAccountTimeBasedPlayInfo(int& dbrtn, id128 const& gameAccountId, TimeBasedPlayInfoList const& in)
{
    // PDB local enum LobbyDB::UpdateGameAccountTimeBasedPlayInfo::__l11::Param. ParamDesc (PDB data) holds the names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_GAME_ACCOUNT_ID = 1,
        PARAM_SCHEDULE_NUMBER = 2,
        PARAM_TARGET_TYPE = 3,
        PARAM_EXPIRE_TIME = 4,
        PARAM_DURATION = 5,
        PARAM_LAST_UPDATE = 6,
        PARAM_MAX = 7
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {
        L"PARAM_RETURN",   L"PARAM_GAME_ACCOUNT_ID", L"PARAM_SCHEDULE_NUMBER", L"PARAM_TARGET_TYPE",
        L"PARAM_EXPIRE_TIME", L"PARAM_DURATION",      L"PARAM_LAST_UPDATE"};
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateGameAccountTimeBasedPlayInfo(?, ?, ?, ?, ?, ?)}";

    if (IsIdZero(gameAccountId))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 333,
                   L"[lobbydb], update game-account-time-based-reward fail; invalid parameter");
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 339,
                   L"[lobbydb], update game-account-time-based-reward fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 345,
                   L"[lobbydb], update game-account-time-based-reward fail; failed to prepare sql, query:%s", query);
        return false;
    }
    // LIFT: the original runs the procedure for target type 0 and 1 (the two entries of the list).
    char targetType = 0;
    do
    {
        tagTIMESTAMP_STRUCT dbExpireTime;
        tagTIMESTAMP_STRUCT dbLastUpdateTime;
        memset(&dbExpireTime, 0, sizeof(dbExpireTime));
        memset(&dbLastUpdateTime, 0, sizeof(dbLastUpdateTime));
        TimeBasedPlayInfo const& info = in._timeBasedPlayInfo[targetType];
        // LIFT: Db::ConvertTimeStamp (0xe81f0) is inline in the original (_localtime64_s and the field copy).
        Db::ConvertTimeStamp(info.expireTimeUTC, &dbExpireTime);
        Db::ConvertTimeStamp(info.lastUpdateTimeUTC, &dbLastUpdateTime);
        dbrtn = 0;
        int param = PARAM_RETURN;
        unsigned long long paramlen[PARAM_MAX];
        memset(paramlen, 0, sizeof(paramlen));
        // LIFT: the schedule number is the first member of TimeBasedPlayInfo (the original binds the struct address).
        if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]) ||
            (param = PARAM_GAME_ACCOUNT_ID,
             !tran.Tran->BindParam(2, SQL_PARAM_INPUT, const_cast<id128*>(&gameAccountId), 0, 0, SQL_GUID, SQL_C_GUID,
                                   &paramlen[1])) ||
            (param = PARAM_SCHEDULE_NUMBER,
             !tran.Tran->BindParam(3, SQL_PARAM_INPUT, const_cast<int*>(&info.scheduleNumber), 0, 0, SQL_INTEGER,
                                   SQL_C_SLONG, &paramlen[2])) ||
            (param = PARAM_TARGET_TYPE,
             !tran.Tran->BindParam(4, SQL_PARAM_INPUT, &targetType, 0, 0, SQL_TINYINT, SQL_C_TINYINT, &paramlen[3])) ||
            (param = PARAM_EXPIRE_TIME,
             !tran.Tran->BindParam(5, SQL_PARAM_INPUT, &dbExpireTime, 0, 19, SQL_TIMESTAMP, SQL_C_TYPE_TIMESTAMP,
                                   &paramlen[4])) ||
            (param = PARAM_DURATION,
             !tran.Tran->BindParam(6, SQL_PARAM_INPUT, const_cast<int*>(&info.duration), 0, 0, SQL_INTEGER,
                                   SQL_C_SLONG, &paramlen[5])) ||
            (param = PARAM_LAST_UPDATE,
             !tran.Tran->BindParam(7, SQL_PARAM_INPUT, &dbLastUpdateTime, 0, 19, SQL_TIMESTAMP, SQL_C_TYPE_TIMESTAMP,
                                   &paramlen[6])))
        {
            Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 415,
                       L"[lobbydb], update game-account-time-based-reward fail; bind parameter fail, param:%s",
                       ParamDesc[param]);
            return false;
        }
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 401,
                       L"[lobbydb], update game-account-time-based-reward fail; execute fail, dbrtn:%d", dbrtn);
            return false;
        }
        if (dbrtn != 0)
            return false;
        ++targetType;
    } while (targetType < 2);
    return true;
}

// 0xa0eb0
// LIFT: not lifted. Needs LobbyDaemon::_instance->_config (_storeUserIpAddress, _storeGameAccountName). LobbyDaemon and LobbyConfig have no layout in src yet. ❓
bool LobbyDB::RegisterGameAccount(int&, id128 const&, wchar_t const*, int, char, unsigned long)
{
    LIFT_STUB(0xa0eb0);
}

// 0xa12a0
// LIFT: not lifted. Needs LobbyDaemon::_instance->_config->_storeUserIpAddress. LobbyDaemon and LobbyConfig have no layout in src yet. ❓
bool LobbyDB::UpdateLastLogin(int&, id128 const&, unsigned long)
{
    LIFT_STUB(0xa12a0);
}

// 0xa1580
#pragma comment(linker, "/INCLUDE:?UpdateLastLogout@LobbyDB@@SA_NAEAHAEBTid128@@H@Z")   // LIFT: keep until the caller is lifted (0x34750)
bool LobbyDB::UpdateLastLogout(int& dbrtn, id128 const& gameAccountId, int botScore)
{
    // PDB local enum LobbyDB::UpdateLastLogout::__l11::Param. ParamDesc (PDB data) holds the names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_GAME_ACCOUNT_ID = 1,
        PARAM_GAME_ACCOUNT_BOT_SCORE = 2,
        PARAM_MAX = 3
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {L"PARAM_RETURN", L"PARAM_GAME_ACCOUNT_ID",
                                                        L"PARAM_GAME_ACCOUNT_BOT_SCORE"};
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateLastLogout(?,?)}";

    if (IsIdZero(gameAccountId))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 585, L"[lobbydb], update last logout fail; invalid parameter");
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 591, L"[lobbydb], update last logout fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 597,
                   L"[lobbydb], update last logout fail; failed to prepare sql, query:%s", query);
        return false;
    }
    dbrtn = 0;
    int param = PARAM_RETURN;
    unsigned long long paramlen[PARAM_MAX];
    memset(paramlen, 0, sizeof(paramlen));
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]) ||
        (param = PARAM_GAME_ACCOUNT_ID,
         !tran.Tran->BindParam(2, SQL_PARAM_INPUT, const_cast<id128*>(&gameAccountId), 0, 0, SQL_GUID, SQL_C_GUID,
                               &paramlen[1])) ||
        (param = PARAM_GAME_ACCOUNT_BOT_SCORE,
         !tran.Tran->BindParam(3, SQL_PARAM_INPUT, &botScore, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[2])))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 639,
                   L"[lobbydb], update last logout fail; bind parameter fail, param:%s", ParamDesc[param]);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 626, L"[lobbydb], update last logout fail; execute fail, dbrtn:%d",
                   dbrtn);
        return false;
    }
    if (dbrtn != 0)
        return false;
    return true;
}

// 0xa17f0
#pragma comment(linker, "/INCLUDE:?LoadCharacterList@LobbyDB@@SA_NAEAHAEBTid128@@AEAPEAPEAUDB@Character@@0@Z")   // LIFT: keep until the caller is lifted (0x349a0)
bool LobbyDB::LoadCharacterList(int& dbrtn, id128 const& gameAccountId, Character::DB**& out, int& count)
{
    // PDB local enums LobbyDB::LoadCharacterList::__l11::Param and Column. ParamDesc and ColDesc (PDB data) hold the
    // enumerator names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_GAME_ACCOUNT_ID = 1,
        PARAM_MAX = 2
    };
    enum Column
    {
        COL_PCID = 0,
        COL_GAME_ACCOUNT_ID = 1,
        COL_SLOT_ID = 2,
        COL_WORLD_ID = 3,
        COL_JOB = 4,
        COL_LEVEL = 5,
        COL_CHARACTER_NAME = 6,
        COL_CHARACTER_RIGHT = 7,
        COL_CHARACTER_STATE = 8,
        COL_DELETION_DELAY_TIME = 9,
        COL_LAST_PLAY_END_TIME = 10,
        COL_JUMPING_CHARACTER_STATE = 11,
        COL_SHOWCASE_DATA = 12,
        COL_BLOCKED = 13,
        COL_MAX = 14
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {L"PARAM_RETURN", L"PARAM_GAME_ACCOUNT_ID"};
    static wchar_t const* const ColDesc[COL_MAX] = {
        L"COL_PCID",
        L"COL_GAME_ACCOUNT_ID",
        L"COL_SLOT_ID",
        L"COL_WORLD_ID",
        L"COL_JOB",
        L"COL_LEVEL",
        L"COL_CHARACTER_NAME",
        L"COL_CHARACTER_RIGHT",
        L"COL_CHARACTER_STATE",
        L"COL_DELETION_DELAY_TIME",
        L"COL_LAST_PLAY_END_TIME",
        L"COL_JUMPING_CHARACTER_STATE",
        L"COL_SHOWCASE_DATA",
        L"COL_BLOCKED"};
    typedef std::vector<Character::DB*, StlAllocator<Character::DB*, 2> > DBList;  // PDB local UDT DBList
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadCharacterList(?)}";

    if (IsIdZero(gameAccountId))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 646, L"[lobbydb], load character list fail; invalid parameter");
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 652, L"[lobbydb], load character list fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 658,
                   L"[lobbydb], load character list fail; failed to prepare sql, query:%s", query);
        return false;
    }
    dbrtn = 0;
    int param = PARAM_RETURN;
    int column = COL_PCID;
    unsigned long long paramlen[PARAM_MAX];
    unsigned long long collen[COL_MAX];
    memset(paramlen, 0, sizeof(paramlen));
    memset(collen, 0, sizeof(collen));
    char db_right = 0;
    DBList dblist;
    collen[COL_CHARACTER_NAME] = SQL_NTS;
    collen[COL_SHOWCASE_DATA] = 512;
    Character::DB dbfield;
    tagTIMESTAMP_STRUCT db_lastPlayEndTime;
    tagTIMESTAMP_STRUCT db_deletionDelayTime;
    id128 db_gameAccountId;
    char db_showcaseData[512];
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]) ||
        (param = PARAM_GAME_ACCOUNT_ID,
         !tran.Tran->BindParam(2, SQL_PARAM_INPUT, const_cast<id128*>(&gameAccountId), 0, 0, SQL_GUID, SQL_C_GUID,
                               &paramlen[1])))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 803,
                   L"[lobbydb], load character list fail; bind parameter fail, param:%s", ParamDesc[param]);
        return false;
    }
    // LIFT: the original has the DbTransaction::BindCol body inline (see LoadGameAccount 0x9fe00).
    DB_BIND_COL_NI(tran.Tran, 1, &dbfield.pcid, 0, SQL_C_SBIGINT, &collen[0], NOT_INIT, BIND_ERROR);
    column = COL_GAME_ACCOUNT_ID;
    DB_BIND_COL_NI(tran.Tran, 2, &db_gameAccountId, 0, SQL_C_GUID, &collen[1], NOT_INIT, BIND_ERROR);
    column = COL_SLOT_ID;
    DB_BIND_COL_NI(tran.Tran, 3, &dbfield.slotid, 0, SQL_C_GUID, &collen[2], NOT_INIT, BIND_ERROR);
    column = COL_WORLD_ID;
    DB_BIND_COL_NI(tran.Tran, 4, &dbfield.belongingWorld, 0, SQL_C_SHORT, &collen[3], NOT_INIT, BIND_ERROR);
    column = COL_JOB;
    DB_BIND_COL_NI(tran.Tran, 5, &dbfield.job, 0, SQL_C_SSHORT, &collen[4], NOT_INIT, BIND_ERROR);
    column = COL_LEVEL;
    DB_BIND_COL_NI(tran.Tran, 6, &dbfield.level, 0, SQL_C_SSHORT, &collen[5], NOT_INIT, BIND_ERROR);
    column = COL_CHARACTER_NAME;
    DB_BIND_COL_NI(tran.Tran, 7, dbfield.name, 66, SQL_C_WCHAR, &collen[6], NOT_INIT, BIND_ERROR);
    column = COL_CHARACTER_RIGHT;
    DB_BIND_COL_NI(tran.Tran, 8, &db_right, 0, SQL_C_TINYINT, &collen[7], NOT_INIT, BIND_ERROR);
    column = COL_CHARACTER_STATE;
    DB_BIND_COL_NI(tran.Tran, 9, &dbfield.state, 0, SQL_C_TINYINT, &collen[8], NOT_INIT, BIND_ERROR);
    column = COL_DELETION_DELAY_TIME;
    DB_BIND_COL_NI(tran.Tran, 10, &db_deletionDelayTime, 16, SQL_C_TYPE_TIMESTAMP, &collen[9], NOT_INIT, BIND_ERROR);
    column = COL_LAST_PLAY_END_TIME;
    DB_BIND_COL_NI(tran.Tran, 11, &db_lastPlayEndTime, 16, SQL_C_TYPE_TIMESTAMP, &collen[10], NOT_INIT, BIND_ERROR);
    column = COL_JUMPING_CHARACTER_STATE;
    DB_BIND_COL_NI(tran.Tran, 12, &dbfield.jumpingCharacterState, 0, SQL_C_TINYINT, &collen[11], NOT_INIT,
                   BIND_ERROR);
    column = COL_SHOWCASE_DATA;
    DB_BIND_COL_NI(tran.Tran, 13, db_showcaseData, 512, SQL_C_BINARY, &collen[12], NOT_INIT, BIND_ERROR);
    column = COL_BLOCKED;
    DB_BIND_COL_NI(tran.Tran, 14, &dbfield.block, 0, SQL_C_BIT, &collen[13], NOT_INIT, BIND_ERROR);
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 747, L"[lobbydb], load character list fail; execute fail, dbrtn:%d",
                   dbrtn);
        return false;
    }
    for (;;)
    {
        memset(&dbfield, 0, sizeof(dbfield));
        memset(&db_gameAccountId, 0, sizeof(db_gameAccountId));
        db_right = 0;
        memset(&db_deletionDelayTime, 0, sizeof(db_deletionDelayTime));
        memset(&db_lastPlayEndTime, 0, sizeof(db_lastPlayEndTime));
        memset(db_showcaseData, 0, sizeof(db_showcaseData));
        int const fetched = tran.Tran->Fetch(0);  // LIFT: Fetch never reads edx (see SmartCouponDB.cpp)
        if (fetched == -1)
        {
            Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 762, L"[lobbydb], load character list fail; fetch fail");
            break;
        }
        if (fetched == 0)
        {
            if (dbrtn != 0)
                break;
            out = nullptr;
            count = 0;
            long long const n = static_cast<long long>(dblist.size());
            if (n != 0)
            {
                out = static_cast<Character::DB**>(Memory::_Manager[2]->AllocZero(8 * n, LOBBYDB_FILE, 791));
                count = static_cast<int>(n);
                for (long long i = 0; i < n; ++i)
                    out[i] = dblist[static_cast<size_t>(i)];
            }
            return true;  // LIFT: the original frees the vector buffer here (StlMemory.h 64), dblist does it.
        }
        if (collen[COL_DELETION_DELAY_TIME] != kNullData)
            dbfield.deletionDelayTime = Db::ConvertTime(&db_deletionDelayTime);
        if (collen[COL_LAST_PLAY_END_TIME] != kNullData)
            dbfield.lastPlayEndTime = Db::ConvertTime(&db_lastPlayEndTime);
        if (collen[COL_SHOWCASE_DATA] != kNullData)
        {
            dbfield.showcaseSize = static_cast<short>(collen[COL_SHOWCASE_DATA]);
            dbfield.showcase = static_cast<char*>(
                Memory::_Manager[2]->AllocZero(static_cast<long long>(dbfield.showcaseSize), LOBBYDB_FILE, 774));
            // LIFT: the driver reports the full length. The bound buffer has 512 bytes. Copy at most 512 bytes.
            // The original copies showcaseSize bytes without a limit.
            long long copySize = dbfield.showcaseSize;
            if (copySize > static_cast<long long>(sizeof(db_showcaseData)))
                copySize = sizeof(db_showcaseData);
            if (dbfield.showcase != nullptr && copySize > 0)
                memcpy(dbfield.showcase, db_showcaseData, static_cast<size_t>(copySize));
        }
        Character::DB* loaded = static_cast<Character::DB*>(Memory::_Manager[2]->Alloc(144, LOBBYDB_FILE, 778));
        memcpy(loaded, &dbfield, sizeof(Character::DB));
        dblist.push_back(loaded);
    }
    // $_error_0: free the rows read so far.
    for (DBList::iterator it = dblist.begin(); it != dblist.end(); ++it)
    {
        Character::DB* row = *it;
        if (row != nullptr)
        {
            if (row->showcase != nullptr)
                Memory::_Manager[2]->Free(row->showcase, LOBBYDB_FILE, 815);
            Memory::_Manager[2]->Free(row, LOBBYDB_FILE, 816);
        }
    }
    return false;

NOT_INIT:
    Log::Write(Log::LT_ERROR, L"source\\Db.cpp", 286, L"DbTransaction::BindCol(), Not initialized");
BIND_ERROR:
    Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 807, L"[lobbydb], load character list fail; bind column fail, column:%s",
               ColDesc[column]);
    return false;
}

// 0xa24c0
#pragma comment(linker, "/INCLUDE:?LoadGameWorldCluster@LobbyDB@@SA_NAEAHAEAPEAPEAUDB@GameWorldCluster@@0@Z")   // LIFT: keep until the caller is lifted (0x4ed00)
bool LobbyDB::LoadGameWorldCluster(int& dbrtn, GameWorldCluster::DB**& out, int& count)
{
    // PDB local enums LobbyDB::LoadGameWorldCluster::__l8::Param and Column (types.h). The PDB data ParamDesc and
    // ColumnDesc hold the enumerator names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_MAX = 1
    };
    enum Column
    {
        COL_RETURN = 0,
        COL_WORLD_CLUSTER_ID = 1,
        COL_GAME_PUBLIC_IPv4_ADDRESS = 2,
        COL_GAME_PRIVATE_IPv4_ADDRESS = 3,
        COL_GAME_PUBLIC_PORT = 4,
        COL_GAME_INTERNAL_PORT = 5,
        COL_MAX_PLAYER_COUNT = 6,
        COL_MAX_WAITING_COUNT = 7,
        COL_MAX = 8
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {L"PARAM_RETURN"};
    static wchar_t const* const ColumnDesc[COL_MAX] = {
        L"COL_RETURN",           L"COL_WORLD_CLUSTER_ID",     L"COL_GAME_PUBLIC_IPv4_ADDRESS",
        L"COL_GAME_PRIVATE_IPv4_ADDRESS", L"COL_GAME_PUBLIC_PORT", L"COL_GAME_INTERNAL_PORT",
        L"COL_MAX_PLAYER_COUNT", L"COL_MAX_WAITING_COUNT"};
    typedef std::vector<GameWorldCluster::DB*, StlAllocator<GameWorldCluster::DB*, 2> > DBList;
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadGameWorldCluster}";

    out = nullptr;
    count = 0;
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 829, L"[lobbydb], load game-world-cluster fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 835,
                   L"[lobbydb], load game-world-cluster fail; failed to prepare sql, query:%s", query);
        return false;
    }
    dbrtn = 0;
    // BUG: the PDB Column enum starts with COL_RETURN, so each bind-column error logs the name of the column
    // before it (0xa24c0, ColumnDesc[v8]). Kept.
    int column = COL_RETURN;
    unsigned long long paramlen[PARAM_MAX];
    unsigned long long collen[COL_MAX];
    paramlen[0] = 0;
    memset(collen, 0, sizeof(collen));
    DBList dblist;
    collen[COL_GAME_PUBLIC_IPv4_ADDRESS] = static_cast<unsigned long long>(SQL_NTS);
    collen[COL_GAME_PRIVATE_IPv4_ADDRESS] = static_cast<unsigned long long>(SQL_NTS);
    GameWorldCluster::DB dbfield;
    wchar_t db_pubip4str[16];
    wchar_t db_privip4str[16];
    // LIFT: the PDB has no name for this 32-byte buffer (0xa24c0). The original converts db_pubip4str and
    // db_privip4str into it for inet_addr (LobbyDB.c). The name is the Hex-Rays one.
    char MultiByteStr[32];
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]))
    {
        // BUG: the original text says "game world group" for this function (copy of another log line). Kept.
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 953,
                   L"[lobbydb], load game world group fail; bind parameter fail, param:%s", ParamDesc[PARAM_RETURN]);
        return false;
    }
    // LIFT: the original has the DbTransaction::BindCol body inline (see LoadGameAccount 0x9fe00).
    DB_BIND_COL_NI(tran.Tran, 1, &dbfield, 0, SQL_C_SHORT, &collen[0], NOT_INIT, BIND_ERROR);
    column = COL_WORLD_CLUSTER_ID;
    DB_BIND_COL_NI(tran.Tran, 2, db_pubip4str, 32, SQL_C_WCHAR, &collen[1], NOT_INIT, BIND_ERROR);
    column = COL_GAME_PUBLIC_IPv4_ADDRESS;
    DB_BIND_COL_NI(tran.Tran, 3, db_privip4str, 32, SQL_C_WCHAR, &collen[2], NOT_INIT, BIND_ERROR);
    column = COL_GAME_PRIVATE_IPv4_ADDRESS;
    DB_BIND_COL_NI(tran.Tran, 4, &dbfield.pub_port, 0, SQL_C_USHORT, &collen[3], NOT_INIT, BIND_ERROR);
    column = COL_GAME_PUBLIC_PORT;
    DB_BIND_COL_NI(tran.Tran, 5, &dbfield.mobile_port, 0, SQL_C_USHORT, &collen[4], NOT_INIT, BIND_ERROR);
    column = COL_GAME_INTERNAL_PORT;
    DB_BIND_COL_NI(tran.Tran, 6, &dbfield.maxPlayerCount, 0, SQL_C_LONG, &collen[5], NOT_INIT, BIND_ERROR);
    column = COL_MAX_PLAYER_COUNT;
    DB_BIND_COL_NI(tran.Tran, 7, &dbfield.maxWaitingCount, 0, SQL_C_LONG, &collen[6], NOT_INIT, BIND_ERROR);
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 900, L"[lobbydb], load game-world-cluster fail; execute fail, dbrtn:%d",
                   dbrtn);
        return false;
    }
    for (;;)
    {
        memset(&dbfield, 0, sizeof(dbfield));
        db_pubip4str[0] = 0;
        db_privip4str[0] = 0;
        int const fetched = tran.Tran->Fetch(0);  // LIFT: Fetch never reads edx (see SmartCouponDB.cpp)
        if (fetched == -1)
        {
            Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 912, L"[lobbydb], load game-world-cluster fail; fetch fail");
            break;
        }
        if (fetched == 0)
        {
            if (dbrtn != 0)
                break;
            out = nullptr;
            count = 0;
            long long const n = static_cast<long long>(dblist.size());
            if (n != 0)
            {
                out = static_cast<GameWorldCluster::DB**>(Memory::_Manager[2]->AllocZero(8 * n, LOBBYDB_FILE, 941));
                count = static_cast<int>(n);
                for (long long i = 0; i < n; ++i)
                    out[i] = dblist[static_cast<size_t>(i)];
            }
            return true;  // LIFT: the original frees the vector buffer here (StlMemory.h 64), dblist does it.
        }
        if (dbfield.maxPlayerCount > 10000)
        {
            Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 921,
                       L"[lobbydb], load game-world-cluster, loaded max-player-count is forcibly truncated to %d, "
                       L"because the value %d is too large, world-cluster-id:%d",
                       10000, dbfield.maxPlayerCount, dbfield.clusterId);
            dbfield.maxPlayerCount = 10000;
        }
        MultiByteStr[30] = 0;
        MultiByteStr[31] = 0;
        WideCharToMultiByte(CP_ACP, 0, db_pubip4str, -1, MultiByteStr, 31, nullptr, nullptr);
        dbfield.pub_IPv4 = inet_addr(MultiByteStr);
        MultiByteStr[30] = 0;
        MultiByteStr[31] = 0;
        WideCharToMultiByte(CP_ACP, 0, db_privip4str, -1, MultiByteStr, 31, nullptr, nullptr);
        dbfield.internal_IPv4 = inet_addr(MultiByteStr);
        GameWorldCluster::DB* loaded =
            static_cast<GameWorldCluster::DB*>(Memory::_Manager[2]->AllocZero(24, LOBBYDB_FILE, 928));
        *loaded = dbfield;
        dblist.push_back(loaded);
    }
    // $_error_1: free the rows read so far.
    for (DBList::iterator it = dblist.begin(); it != dblist.end(); ++it)
    {
        if (*it != nullptr)
            Memory::_Manager[2]->Free(*it, LOBBYDB_FILE, 964);
    }
    return false;

NOT_INIT:
    Log::Write(Log::LT_ERROR, L"source\\Db.cpp", 286, L"DbTransaction::BindCol(), Not initialized");
BIND_ERROR:
    // BUG: same copied "game world group" text as the bind parameter log above. Kept.
    Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 957, L"[lobbydb], load game world group fail; bind column fail, column:%s",
               ColumnDesc[column]);
    return false;
}

// 0xa2dd0
#pragma comment(linker, "/INCLUDE:?LoadGameWorld@LobbyDB@@SA_NAEAHAEAPEAPEAUDB@GameWorld@@0@Z")   // LIFT: keep until the caller is lifted (0x4ed00)
bool LobbyDB::LoadGameWorld(int& dbrtn, GameWorld::DB**& out, int& count)
{
    // PDB local enums LobbyDB::LoadGameWorld::__l8::Param and Column (types.h). The PDB data ParamDesc and ColumnDesc
    // hold the enumerator names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_MAX = 1
    };
    enum Column
    {
        COL_WORLD_ID = 0,
        COL_WORLD_CLUSTER_ID = 1,
        COL_WORLD_NAME = 2,
        COL_WORLD_TYPE = 3,
        COL_PLAY_TYPE = 4,
        COL_USABLE = 5,
        COL_ENTERABLE = 6,
        COL_CHARACTER_CREATION_LIMIT = 7,
        COL_CHARACTER_OF_NEW_ACCOUNT_CREATION_LIMIT = 8,
        COL_BRAND_NEW = 9,
        COL_RECOMMENDATION = 10,
        COL_CROWDNESS = 11,
        COL_MAX = 12
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {L"PARAM_RETURN"};
    static wchar_t const* const ColumnDesc[COL_MAX] = {
        L"COL_WORLD_ID",
        L"COL_WORLD_CLUSTER_ID",
        L"COL_WORLD_NAME",
        L"COL_WORLD_TYPE",
        L"COL_PLAY_TYPE",
        L"COL_USABLE",
        L"COL_ENTERABLE",
        L"COL_CHARACTER_CREATION_LIMIT",
        L"COL_CHARACTER_OF_NEW_ACCOUNT_CREATION_LIMIT",
        L"COL_BRAND_NEW",
        L"COL_RECOMMENDATION",
        L"COL_CROWDNESS"};
    typedef std::vector<GameWorld::DB*, StlAllocator<GameWorld::DB*, 2> > DBList;
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadGameWorld}";

    out = nullptr;
    count = 0;
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 976, L"[lobbydb], load game world fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 982,
                   L"[lobbydb], load game world fail; failed to prepare sql, query:%s", query);
        return false;
    }
    dbrtn = 0;
    int column = COL_WORLD_ID;
    unsigned long long paramlen[PARAM_MAX];
    unsigned long long collen[COL_MAX];
    paramlen[0] = 0;
    memset(collen, 0, sizeof(collen));
    DBList dblist;
    collen[COL_WORLD_NAME] = static_cast<unsigned long long>(SQL_NTS);
    GameWorld::DB dbfield;
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]))
    {
        // BUG: the original text says "load character list" for this function (copy of another log line). Kept.
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1098,
                   L"[lobbydb], load character list fail; bind parameter fail, param:%s", ParamDesc[PARAM_RETURN]);
        return false;
    }
    // LIFT: the original has the DbTransaction::BindCol body inline (see LoadGameAccount 0x9fe00).
    DB_BIND_COL_NI(tran.Tran, 1, &dbfield, 0, SQL_C_SHORT, &collen[0], NOT_INIT, BIND_ERROR);
    column = COL_WORLD_CLUSTER_ID;
    DB_BIND_COL_NI(tran.Tran, 2, &dbfield.clusterId, 0, SQL_C_SHORT, &collen[1], NOT_INIT, BIND_ERROR);
    column = COL_WORLD_NAME;
    DB_BIND_COL_NI(tran.Tran, 3, dbfield.name, 66, SQL_C_WCHAR, &collen[2], NOT_INIT, BIND_ERROR);
    column = COL_WORLD_TYPE;
    DB_BIND_COL_NI(tran.Tran, 4, &dbfield.worldType, 0, SQL_C_TINYINT, &collen[3], NOT_INIT, BIND_ERROR);
    column = COL_PLAY_TYPE;
    DB_BIND_COL_NI(tran.Tran, 5, &dbfield.playType, 0, SQL_C_TINYINT, &collen[4], NOT_INIT, BIND_ERROR);
    column = COL_USABLE;
    DB_BIND_COL_NI(tran.Tran, 6, &dbfield.use, 0, SQL_C_BIT, &collen[5], NOT_INIT, BIND_ERROR);
    column = COL_ENTERABLE;
    DB_BIND_COL_NI(tran.Tran, 7, &dbfield.entrance, 0, SQL_C_BIT, &collen[6], NOT_INIT, BIND_ERROR);
    column = COL_CHARACTER_CREATION_LIMIT;
    DB_BIND_COL_NI(tran.Tran, 8, &dbfield.characterCreationLimited, 0, SQL_C_BIT, &collen[7], NOT_INIT, BIND_ERROR);
    column = COL_CHARACTER_OF_NEW_ACCOUNT_CREATION_LIMIT;
    DB_BIND_COL_NI(tran.Tran, 9, &dbfield.characterCreationLimitedOnNewAccount, 0, SQL_C_BIT, &collen[8], NOT_INIT,
                   BIND_ERROR);
    column = COL_BRAND_NEW;
    DB_BIND_COL_NI(tran.Tran, 10, &dbfield.brandnew, 0, SQL_C_BIT, &collen[9], NOT_INIT, BIND_ERROR);
    column = COL_RECOMMENDATION;
    DB_BIND_COL_NI(tran.Tran, 11, &dbfield.recommend, 0, SQL_C_BIT, &collen[10], NOT_INIT, BIND_ERROR);
    column = COL_CROWDNESS;
    DB_BIND_COL_NI(tran.Tran, 12, &dbfield.crowdness, 0, SQL_C_TINYINT, &collen[11], NOT_INIT, BIND_ERROR);
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1057, L"[lobbydb], load game world fail; execute fail, dbrtn:%d",
                   dbrtn);
        return false;
    }
    for (;;)
    {
        memset(&dbfield, 0, sizeof(dbfield));
        int const fetched = tran.Tran->Fetch(0);  // LIFT: Fetch never reads edx (see SmartCouponDB.cpp)
        if (fetched == -1)
        {
            Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1067, L"[lobbydb], load game world fail; fetch fail");
            break;
        }
        if (fetched == 0)
        {
            if (dbrtn != 0)
                break;
            out = nullptr;
            count = 0;
            long long const n = static_cast<long long>(dblist.size());
            if (n != 0)
            {
                out = static_cast<GameWorld::DB**>(Memory::_Manager[2]->AllocZero(8 * n, LOBBYDB_FILE, 1086));
                count = static_cast<int>(n);
                for (long long i = 0; i < n; ++i)
                    out[i] = dblist[static_cast<size_t>(i)];
            }
            return true;  // LIFT: the original frees the vector buffer here (StlMemory.h 64), dblist does it.
        }
        GameWorld::DB* loaded = static_cast<GameWorld::DB*>(Memory::_Manager[2]->Alloc(88, LOBBYDB_FILE, 1073));
        memcpy(loaded, &dbfield, sizeof(GameWorld::DB));
        dblist.push_back(loaded);
    }
    // $_error_2: free the rows read so far.
    for (DBList::iterator it = dblist.begin(); it != dblist.end(); ++it)
    {
        if (*it != nullptr)
            Memory::_Manager[2]->Free(*it, LOBBYDB_FILE, 1109);
    }
    return false;

NOT_INIT:
    Log::Write(Log::LT_ERROR, L"source\\Db.cpp", 286, L"DbTransaction::BindCol(), Not initialized");
BIND_ERROR:
    Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1102, L"[lobbydb], load game world fail; bind column fail, column:%s",
               ColumnDesc[column]);
    return false;
}

// 0xa37e0
#pragma comment(linker, "/INCLUDE:?CheckValidityOfCharacterName@LobbyDB@@SA_NAEAHPEB_WH@Z")   // LIFT: keep until the caller is lifted (0x41b10)
bool LobbyDB::CheckValidityOfCharacterName(int& dbrtn, wchar_t const* name, int)
{
    // PDB local enum LobbyDB::CheckValidityOfCharacterName::__l11::Param. ParamDesc (0x207b60) holds the names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_CHARACTER_NAME = 1,
        PARAM_MAX = 2
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {L"PARAM_RETURN", L"PARAM_CHARACTER_NAME"};
    wchar_t const* const query = L"{?=CALL dbo.usp_CheckValidityOfCharacterName(?)}";

    // LIFT: the third argument (tran, int) is not read in the binary (0xa37e0). The PDB keeps it in the signature.
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1123,
                   L"[lobbydb], check validity of character name fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1129,
                   L"[lobbydb], check validity of character name fail; failed to prepare sql, query:%s", query);
        return false;
    }
    int param = PARAM_RETURN;
    dbrtn = 0;
    unsigned long long paramlen[PARAM_MAX];
    paramlen[0] = 0;
    paramlen[1] = static_cast<unsigned long long>(SQL_NTS);
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]) ||
        (param = PARAM_CHARACTER_NAME,
         !tran.Tran->BindParam(2, SQL_PARAM_INPUT, const_cast<wchar_t*>(name), 66, 32, SQL_WVARCHAR, SQL_C_WCHAR,
                               &paramlen[1])))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1169,
                   L"[lobbydb], check validity of character name fail; bind parameter fail, param:%s",
                   ParamDesc[param]);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1158,
                   L"[lobbydb], check validity of character name fail; execute fail, dbrtn:%d", dbrtn);
        return false;
    }
    return dbrtn == 0;
}

// 0xa39b0
#pragma comment(linker, "/INCLUDE:?TryCharacterCreation@LobbyDB@@SA_NAEAHAEBTid128@@1FPEB_WHDPEA_K@Z")   // LIFT: keep until the caller is lifted (0x31550)
bool LobbyDB::TryCharacterCreation(int& dbrtn, id128 const& gameAccountId, id128 const& slotid, short wid,
                                   wchar_t const* name, int nameBufSizeInBytes, char right, unsigned long long* outpcid)
{
    // PDB local enum LobbyDB::TryCharacterCreation::__l11::Param (types.h). ParamDesc (0x207b70) holds the names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_GAME_ACCOUNT_ID = 1,
        PARAM_SLOT_ID = 2,
        PARAM_WORLD_ID = 3,
        PARAM_CHARACTER_NAME = 4,
        PARAM_CHARACTER_RIGHT = 5,
        PARAM_PCID = 6,
        PARAM_MAX = 7
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {
        L"PARAM_RETURN",         L"PARAM_GAME_ACCOUNT_ID",  L"PARAM_SLOT_ID", L"PARAM_WORLD_ID",
        L"PARAM_CHARACTER_NAME", L"PARAM_CHARACTER_RIGHT", L"PARAM_PCID"};
    wchar_t const* const query = L"{?=CALL dbo.usp_TryCharacterCreation(?, ?, ?, ?, ?, ?)}";

    // LIFT: LTCG removed the char argument (0xa39b0 stores the constant 1 into the bound local). The lift binds the
    // parameter. Character::TryCreation passes 1. The outpcid pointer is the 7th stack-passed argument in the binary.
    if (IsIdZero(gameAccountId) || IsIdZero(slotid) || wid == 0 || name == nullptr || nameBufSizeInBytes <= 0)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1237, L"[lobbydb], try character creation fail; invalid parameter");
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1243, L"[lobbydb], try character creation fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1249,
                   L"[lobbydb], try character creation fail; failed to prepare sql, query:%s", query);
        return false;
    }
    dbrtn = 0;
    int param = PARAM_RETURN;
    unsigned long long paramlen[PARAM_MAX];
    memset(paramlen, 0, sizeof(paramlen));
    paramlen[PARAM_CHARACTER_NAME] = static_cast<unsigned long long>(SQL_NTS);
    unsigned long long pcid = 0;
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]) ||
        (param = PARAM_GAME_ACCOUNT_ID,
         !tran.Tran->BindParam(2, SQL_PARAM_INPUT, const_cast<id128*>(&gameAccountId), 0, 0, SQL_GUID, SQL_C_GUID,
                               &paramlen[1])) ||
        (param = PARAM_SLOT_ID,
         !tran.Tran->BindParam(3, SQL_PARAM_INPUT, const_cast<id128*>(&slotid), 0, 0, SQL_GUID, SQL_C_GUID,
                               &paramlen[2])) ||
        (param = PARAM_WORLD_ID,
         !tran.Tran->BindParam(4, SQL_PARAM_INPUT, &wid, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &paramlen[3])) ||
        (param = PARAM_CHARACTER_NAME,
         !tran.Tran->BindParam(5, SQL_PARAM_INPUT, const_cast<wchar_t*>(name), nameBufSizeInBytes, 32, SQL_WVARCHAR,
                               SQL_C_WCHAR, &paramlen[4])) ||
        (param = PARAM_CHARACTER_RIGHT,
         !tran.Tran->BindParam(6, SQL_PARAM_INPUT, &right, 0, 0, SQL_TINYINT, SQL_C_TINYINT, &paramlen[5])) ||
        (param = PARAM_PCID,
         !tran.Tran->BindParam(7, SQL_PARAM_INPUT_OUTPUT, &pcid, 0, 0, SQL_BIGINT, SQL_C_UBIGINT, &paramlen[6])))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1310,
                   L"[lobbydb], try character creation fail; bind parameter fail, param:%s", ParamDesc[param]);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1294, L"[lobbydb], try character creation fail; execute fail, dbrtn:%d",
                   dbrtn);
        return false;
    }
    if (dbrtn != 0)
        return false;
    if (outpcid != nullptr)
        *outpcid = pcid;
    return true;
}

// 0xa3da0
#pragma comment(linker, "/INCLUDE:?FinishCharacterCreation@LobbyDB@@SA_NAEAH_KFFD_NPEBDH@Z")   // LIFT: keep until the caller is lifted (0x319b0)
bool LobbyDB::FinishCharacterCreation(int& dbrtn, unsigned long long pcid, short job, short level,
                                      char jumpingCharacterState, bool consumptionJumpingCharacterCreationQuota,
                                      char const* showcaseData, int showcaseDataSize)
{
    // PDB local enum LobbyDB::FinishCharacterCreation::__l11::Param. ParamDesc (0x207bb0) holds the names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_PCID = 1,
        PARAM_JOB = 2,
        PARAM_LEVEL = 3,
        PARAM_JUMPING_CHARACTER_STATE = 4,
        PARAM_IS_CONSUMPTION_JUMPING_CHARACTER_CREATION_QUOTA = 5,
        PARAM_SHOWCASE_DATA = 6,
        PARAM_MAX = 7
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {
        L"PARAM_RETURN",
        L"PARAM_PCID",
        L"PARAM_JOB",
        L"PARAM_LEVEL",
        L"PARAM_JUMPING_CHARACTER_STATE",
        L"PARAM_IS_CONSUMPTION_JUMPING_CHARACTER_CREATION_QUOTA",
        L"PARAM_SHOWCASE_DATA"};
    wchar_t const* const query = L"{?=CALL dbo.usp_FinishCharacterCreation(?, ?, ?, ?, ?, ?)}";

    // LIFT: the original checks showcaseDataSize != 0 only (the size is sign-extended for the bind). Kept as is.
    if (job < 0 || level <= 0 || showcaseData == nullptr || showcaseDataSize == 0)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1317, L"[lobbydb], finish character creation fail; invalid parameter");
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1323, L"[lobbydb], finish character creation fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1329,
                   L"[lobbydb], finish character creation fail; failed to prepare sql, query:%s", query);
        return false;
    }
    dbrtn = 0;
    int param = PARAM_RETURN;
    unsigned long long paramlen[PARAM_MAX];
    memset(paramlen, 0, sizeof(paramlen));
    paramlen[PARAM_SHOWCASE_DATA] = static_cast<unsigned long long>(static_cast<long long>(showcaseDataSize));
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]) ||
        (param = PARAM_PCID,
         !tran.Tran->BindParam(2, SQL_PARAM_INPUT, &pcid, 0, 0, SQL_BIGINT, SQL_C_UBIGINT, &paramlen[1])) ||
        (param = PARAM_JOB,
         !tran.Tran->BindParam(3, SQL_PARAM_INPUT, &job, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &paramlen[2])) ||
        (param = PARAM_LEVEL,
         !tran.Tran->BindParam(4, SQL_PARAM_INPUT, &level, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &paramlen[3])) ||
        (param = PARAM_JUMPING_CHARACTER_STATE,
         !tran.Tran->BindParam(5, SQL_PARAM_INPUT, &jumpingCharacterState, 0, 0, SQL_TINYINT, SQL_C_TINYINT,
                               &paramlen[4])) ||
        (param = PARAM_IS_CONSUMPTION_JUMPING_CHARACTER_CREATION_QUOTA,
         !tran.Tran->BindParam(6, SQL_PARAM_INPUT, &consumptionJumpingCharacterCreationQuota, 0, 0, SQL_BIT,
                               SQL_C_BIT, &paramlen[5])) ||
        (param = PARAM_SHOWCASE_DATA,
         !tran.Tran->BindParam(7, SQL_PARAM_INPUT, const_cast<char*>(showcaseData),
                               static_cast<long long>(showcaseDataSize), 4096, SQL_VARBINARY, SQL_C_BINARY,
                               &paramlen[6])))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1387,
                   L"[lobbydb], finish character creation fail; bind parameter fail, param:%s", ParamDesc[param]);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1374,
                   L"[lobbydb], finish character creation fail; execute fail, dbrtn:%d", dbrtn);
        return false;
    }
    if (dbrtn == 0)
        return true;
    return false;
}

// 0xa4150
#pragma comment(linker, "/INCLUDE:?CancelCharacterCreation@LobbyDB@@SA_NAEAH_K@Z")   // LIFT: keep until the caller is lifted (0x31c00)
bool LobbyDB::CancelCharacterCreation(int& dbrtn, unsigned long long pcid)
{
    // PDB local enum LobbyDB::CancelCharacterCreation::__l11::Param. ParamDesc holds the names.
    enum Param
    {
        PARAM_RETURN = 0,
        PARAM_PCID = 1,
        PARAM_MAX = 2
    };
    static wchar_t const* const ParamDesc[PARAM_MAX] = {L"PARAM_RETURN", L"PARAM_PCID"};
    wchar_t const* const query = L"{?=CALL dbo.usp_CancelCharacterCreation(?)}";

    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1400, L"[lobbydb], cancel character creation fail; get transaction fail");
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1406,
                   L"[lobbydb], cancel character creation fail; failed to prepare sql, query:%s", query);
        return false;
    }
    dbrtn = 0;
    int param = PARAM_RETURN;
    unsigned long long paramlen[PARAM_MAX] = {0, 0};
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbrtn, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramlen[0]) ||
        (param = PARAM_PCID,
         !tran.Tran->BindParam(2, SQL_PARAM_INPUT, &pcid, 0, 0, SQL_BIGINT, SQL_C_UBIGINT, &paramlen[1])))
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1448,
                   L"[lobbydb], cancel character creation fail; bind parameter fail, param:%s", ParamDesc[param]);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 1435,
                   L"[lobbydb], cancel character creation fail; execute fail, dbrtn:%d", dbrtn);
        return false;
    }
    return dbrtn == 0;
}

// 0xa4320
bool LobbyDB::TryCharacterDeletion(int&, unsigned long long)
{
    LIFT_STUB(0xa4320);
}

// 0xa44f0
bool LobbyDB::FinishCharacterDeletion(int&, unsigned long long, long, long long*)
{
    LIFT_STUB(0xa44f0);
}

// 0xa47c0
bool LobbyDB::CancelCharacterDeletion(int&, unsigned long long)
{
    LIFT_STUB(0xa47c0);
}

// 0xa4990
bool LobbyDB::TryCharacterRestoration(int&, unsigned long long)
{
    LIFT_STUB(0xa4990);
}

// 0xa4b60
bool LobbyDB::FinishCharacterRestoration(int&, unsigned long long)
{
    LIFT_STUB(0xa4b60);
}

// 0xa5220
bool LobbyDB::ExpireCharacterDeletionWaiting(int&, unsigned long long)
{
    LIFT_STUB(0xa5220);
}

// 0xa53f0
bool LobbyDB::UpdateLastPlayStart(int&, unsigned long long, unsigned long)
{
    LIFT_STUB(0xa53f0);
}

// 0xa5690
bool LobbyDB::UpdateLastPlayEnd(int&, unsigned long long)
{
    LIFT_STUB(0xa5690);
}

// 0xa58b0
bool LobbyDB::UpdateCharacterData(int&, unsigned long long, short, short, char*, int)
{
    LIFT_STUB(0xa58b0);
}

// 0xa5ca0
bool LobbyDB::UpdateCharacterLevel(int&, unsigned long long, short)
{
    LIFT_STUB(0xa5ca0);
}

// 0xa5f80
bool LobbyDB::TryGuildRegistration(int&, short, short, char, wchar_t const*, int, unsigned long long*)
{
    LIFT_STUB(0xa5f80);
}

// 0xa6310
bool LobbyDB::FinishGuildRegistration(int&, unsigned long long)
{
    LIFT_STUB(0xa6310);
}

// 0xa64e0
bool LobbyDB::CancelGuildRegistration(int&, unsigned long long)
{
    LIFT_STUB(0xa64e0);
}

// 0xa66b0
bool LobbyDB::DeleteGuild(int&, unsigned long long, long)
{
    LIFT_STUB(0xa66b0);
}

// 0xa68f0
bool LobbyDB::TryRenameGuild(int&, unsigned long long, int, wchar_t const*, int, long, unsigned long long*)
{
    LIFT_STUB(0xa68f0);
}

// 0xa6c60
bool LobbyDB::FinishRenameGuild(int&, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xa6c60);
}

// 0xa6ec0
bool LobbyDB::CancelRenameGuild(int&, unsigned long long)
{
    LIFT_STUB(0xa6ec0);
}

// 0xa7570
bool LobbyDB::BindCharacterSlot(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xa7570);
}

// 0xa77e0
bool LobbyDB::UpdateJumpingCharacterStateComplete(int&, unsigned long long, bool)
{
    LIFT_STUB(0xa77e0);
}

// 0xa95f0
bool LobbyDB::LoadRandomStoreInitializationSchedule(int&, RandomStoreInitializationSchedule*)
{
    LIFT_STUB(0xa95f0);
}

// 0xaa1d0
bool LobbyDB::LoadCharacterCosmesisService(int&, unsigned long long, unsigned long long*)
{
    LIFT_STUB(0xaa1d0);
}

// 0xaa670
bool LobbyDB::TryCharacterCosmesisService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, char*, int, unsigned long long*)
{
    LIFT_STUB(0xaa670);
}

// 0xaadb0
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_CharacterCosmesisService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xaadb0);
}

// 0xab070
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_CharacterCosmesisService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xab070);
}

// 0xab330
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_CharacterCosmesisService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xab330);
}

// 0xab5f0
bool LobbyDB::FinishCharacterCosmesisService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xab5f0);
}

// 0xab8b0
bool LobbyDB::LoadChangeCharacterSexService(int&, unsigned long long, unsigned long long*)
{
    LIFT_STUB(0xab8b0);
}

// 0xabdc0
bool LobbyDB::TryChangeCharacterSexService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, char, char*, int, unsigned long long*)
{
    LIFT_STUB(0xabdc0);
}

// 0xac5c0
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_ChangeCharacterSexService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xac5c0);
}

// 0xac880
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_ChangeCharacterSexService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xac880);
}

// 0xacb40
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_ChangeCharacterSexService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xacb40);
}

// 0xace00
bool LobbyDB::FinishChangeCharacterSexService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xace00);
}

// 0xad0c0
bool LobbyDB::LoadChangeCharacterRaceService(int&, unsigned long long, unsigned long long*)
{
    LIFT_STUB(0xad0c0);
}

// 0xad650
bool LobbyDB::TryChangeCharacterRaceService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, char, char, char*, int, unsigned long long*)
{
    LIFT_STUB(0xad650);
}

// 0xadf10
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_ChangeCharacterRaceService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xadf10);
}

// 0xae1d0
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_ChangeCharacterRaceService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xae1d0);
}

// 0xae490
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_ChangeCharacterRaceService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xae490);
}

// 0xae750
bool LobbyDB::FinishChangeCharacterRaceService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xae750);
}

// 0xaea10
bool LobbyDB::LoadRenameCharacterService(int&, unsigned long long, unsigned long long*, wchar_t*, int, wchar_t*, int)
{
    LIFT_STUB(0xaea10);
}

// 0xaee70
bool LobbyDB::TryCharacterRenameService(int&, id128 const&, unsigned long long, unsigned long long, unsigned int, wchar_t*, int, int, unsigned long long*)
{
    LIFT_STUB(0xaee70);
}

// 0xaf630
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_CharacterRenameService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xaf630);
}

// 0xafb60
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_CharacterRenameService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xafb60);
}

// 0xb0090
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_CharacterRenameService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb0090);
}

// 0xb05c0
bool LobbyDB::FinishCharacterRenameService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb05c0);
}

// 0xb0880
bool LobbyDB::LoadSlotAdditionService(int&, unsigned long long, id128*)
{
    LIFT_STUB(0xb0880);
}

// 0xb0c30
bool LobbyDB::TrySlotAdditionService(int&, id128 const&, unsigned long long, unsigned int, unsigned long long*)
{
    LIFT_STUB(0xb0c30);
}

// 0xb11d0
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_SlotAdditionService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb11d0);
}

// 0xb1700
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_SlotAdditionService(int&, unsigned long long, id128 const&, id128 const&)
{
    LIFT_STUB(0xb1700);
}

// 0xb1f60
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_SlotAdditionService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb1f60);
}

// 0xb2490
bool LobbyDB::FinishSlotAdditionService(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb2490);
}

// 0xb2750
bool LobbyDB::WriteUserRenameServiceLog(int&, id128 const&, unsigned long long, unsigned int, wchar_t*, int, wchar_t*, int)
{
    LIFT_STUB(0xb2750);
}

// 0xb2e40
bool LobbyDB::TryExtendJumpingCharacterCreationQuota(int&, id128 const&, unsigned long long, unsigned int, unsigned long long*)
{
    LIFT_STUB(0xb2e40);
}

// 0xb33e0
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_ExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb33e0);
}

// 0xb3910
bool LobbyDB::UpdateLobbyServiceStateToTaskDoneState_ExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb3910);
}

// 0xb3e40
bool LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_ExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb3e40);
}

// 0xb4370
bool LobbyDB::FinishExtendJumpingCharacterCreationQuota(int&, unsigned long long, id128 const&)
{
    LIFT_STUB(0xb4370);
}

// 0xb4630
bool LobbyDB::TryAuctionEscrow(int&, id128 const&, id128 const&, short, unsigned long long, long long, unsigned long long&)
{
    LIFT_STUB(0xb4630);
}

// 0xb4e70
bool LobbyDB::CancelAuctionEscrow(int&, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xb4e70);
}

// 0xb5140
bool LobbyDB::FinishAuctionEscrow(int&, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xb5140);
}

// 0xb5a30
bool LobbyDB::FinishAuctionEscrowRollback(int&, unsigned long long, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xb5a30);
}

// 0xb5d50
bool LobbyDB::TryAuctionResultDelivery(int&, wchar_t const*, int, id128 const&, id128 const&, short, unsigned long long, unsigned long long&, wchar_t*, int, unsigned long long&)
{
    LIFT_STUB(0xb5d50);
}

// 0xb67f0
bool LobbyDB::FinishAuctionResultDelivery(int&, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xb67f0);
}

// 0xb6ad0
bool LobbyDB::LoadMileage(int&, MileageInfo**&, int&)
{
    LIFT_STUB(0xb6ad0);
}

// 0xb77b0
bool LobbyDB::LoadMileagePolicy(int&, int, MileagePolicy&, MileagePolicyCondition**&, int&)
{
    LIFT_STUB(0xb77b0);
}

// 0xb80a0
bool LobbyDB::LoadMileageFeverTime(int&, int, long long, MileageFeverTimeInfo**&, int&)
{
    LIFT_STUB(0xb80a0);
}

// 0xb8db0
bool LobbyDB::LoadMileageAccumulatedTimePerDay(int&, id128 const&, int* const, int, MileageLimitInfo**&, int&)
{
    LIFT_STUB(0xb8db0);
}

// 0xb9630
bool LobbyDB::LoadRetryMileageDeposit(int&, int, unsigned long long, unsigned long long*, unsigned long long*, MileageDepositInfo**&, int&)
{
    LIFT_STUB(0xb9630);
}

// 0xba390
bool LobbyDB::RetrieveMileageDeposit(int&, unsigned long long, MileageDepositInfo&)
{
    LIFT_STUB(0xba390);
}

// 0xbaac0
bool LobbyDB::TryMileageDepost(int&, id128 const&, int, long long, long long, long long, long long*, short*, unsigned long long&)
{
    LIFT_STUB(0xbaac0);
}

// 0xbb3b0
bool LobbyDB::FinishMileageDeposit(int&, unsigned long long, bool)
{
    LIFT_STUB(0xbb3b0);
}
