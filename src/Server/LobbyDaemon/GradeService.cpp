// GradeService.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <utility>
#include "GradeService.h"
#include "CliSession.h"
#include "FragmentPacket.h"
#include "LiftStub.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "StsMsgGrade.h"

static wchar_t const kFile[] = L"GradeService.cpp";

// 0x53370
bool Grade::FetchGame(FragmentPacket* fp) const
{
    if (fp == nullptr)
    {
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    if (fp->FreeSize() < 0x1D)
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(6, _gameGradeKey, _gradeId, _activation, _gradeCount, _effectiveFrom, _effectiveTo) == 0)
    {
        TLobbyError = LOBERR_SYSTEM;
        return false;
    }
    return true;
}

// 0x53450
GradeService::GradeService()
    : _revision(0)
    , _gradeList()
    , _initGradeLevel(false)
    , _initGradeList(false)
{
    _gradeLevel.level = 0;
    _gradeLevel.score = 0;
    _gradeLevel.minLevelScore = 0;
    _gradeLevel.maxLevelScore = 0;
    _gradeLevel.maxScore = 0;
}

// 0x534d0
// LIFT: the binary stores the constant 1 into _gradeLevel.level (0x534d0). LTCG removed the use of
// the parameter (PDB name: defaultLevel). The source probably assigns defaultLevel.
GradeService::GradeService(int defaultLevel)
    : _revision(0)
    , _gradeList()
    , _initGradeLevel(false)
    , _initGradeList(false)
{
    _gradeLevel.level = 0;
    _gradeLevel.score = 0;
    _gradeLevel.minLevelScore = 0;
    _gradeLevel.maxLevelScore = 0;
    _gradeLevel.maxScore = 0;
    _gradeLevel.level = defaultLevel;
}

// 0x53550
GradeService::~GradeService()
{
    clearGradeList();
}

// 0x535c0
void GradeService::clearGradeList()
{
    for (GradeList::iterator it = _gradeList.begin(); it != _gradeList.end(); ++it)
    {
        if (it->second != nullptr)
            Memory::_Manager[2]->Free(it->second, kFile, 181);
    }
    _gradeList.clear();
}

// 0x53670
// LIFT: the binary has no this parameter (LTCG removed it). The PDB keeps the const member signature.
GradeService::GradeChangedReasonType GradeService::parseGradeChangedReason(wchar_t const* reason) const
{
    if (reason == nullptr)
        return GRADECHANGEDREASONTYPE_NONE;
    if (wcscmp(reason, L"Activated") == 0)
        return GRADECHANGEDREASONTYPE_ACTIVATED;
    if (wcscmp(reason, L"ActivatedWithAdding") == 0)
        return GRADECHANGEDREASONTYPE_ACTIVATED_WITH_ADDING;
    if (wcscmp(reason, L"Added") == 0)
        return GRADECHANGEDREASONTYPE_ADDED;
    if (wcscmp(reason, L"Deleted") == 0)
        return GRADECHANGEDREASONTYPE_DELETED;
    if (wcscmp(reason, L"DeletedAndExhausted") == 0)
        return GRADECHANGEDREASONTYPE_DELETED_AND_EXAUSTED;
    return GRADECHANGEDREASONTYPE_NONE;
}

// 0x53750
bool GradeService::SetGradeLevel(CliSession* cs, StsMsgLib::_StsMsgResponseGradeGetLevel const* level)
{
    _gradeLevel.level = level->nLevelId;
    _gradeLevel.score = level->nAccumulateGradeScore;
    _gradeLevel.minLevelScore = level->nMinimumLevelScore;
    _gradeLevel.maxLevelScore = level->nMaximumLevelScore;
    _gradeLevel.maxScore = level->nMaximumGradeScore;
    ++_revision;
    _initGradeLevel = true;

    unsigned int const state = cs != nullptr ? cs->_state : 0;
    unsigned long long const clikey = cs != nullptr ? cs->_clikey : 0;
    Log::Write(Log::LT_DEBUG, kFile, 221,
               L"[grade], set grade level, cli-key:0x%I64X, cli-state:%d.%d, level:%d, score:%d", clikey,
               state >> 16, state & 0xFFFF, level->nLevelId, level->nAccumulateGradeScore);
    return true;
}

// 0x53800
// 0x54680 _Linsert and 0x547b0 _Buynode<std::pair<int,Grade *>> come from the insert call.
bool GradeService::SetGradeList(CliSession* cs, StsMsgLib::_StsMsgResponseGradeListAllGrades const* gradeList)
{
    clearGradeList();
    for (int i = 0; i < gradeList->nGradeListCount; ++i)
    {
        StsMsgLib::_StsMsgResponseGradeListAllGrades::_GradeListItem const& item = gradeList->pGradeList[i];
        int const gameGradeKey = _wtoi(item.GameGradeKey);
        if (gameGradeKey > 0)
        {
            Grade* grade = static_cast<Grade*>(Memory::_Manager[2]->Alloc(sizeof(Grade), kFile, 247));
            if (grade != nullptr)
            {
                grade->_gameGradeKey = gameGradeKey;
                grade->_gradeId = item.nGradeId;
                grade->_activation = item.bActivation;
                grade->_gradeCount = item.nGradeCount;
                grade->_effectiveFrom = item.tTotalEffectiveFrom;
                grade->_effectiveTo = item.tTotalEffectiveTo;
            }
            // BUG: when gameGradeKey is already in _gradeList, insert does not add the pair and the Grade leaks.
            _gradeList.insert(std::pair<int, Grade*>(gameGradeKey, grade));
        }
        else
        {
            unsigned int const state = cs != nullptr ? cs->_state : 0;
            unsigned long long const clikey = cs != nullptr ? cs->_clikey : 0;
            Log::Write(Log::LT_ERROR, kFile, 237,
                       L"[grade], set grade exception; invalid game-grade-key, cli-key:0x%I64X, cli-state:%d.%d, "
                       L"grade-id:%d",
                       clikey, state >> 16, state & 0xFFFF, item.nGradeId);
        }
    }

    ++_revision;
    _initGradeList = true;

    unsigned int const state = cs != nullptr ? cs->_state : 0;
    unsigned long long const clikey = cs != nullptr ? cs->_clikey : 0;
    Log::Write(Log::LT_DEBUG, kFile, 258,
               L"[grade], set grade list ok, cli-key:0x%I64X, cli-state:%d.%d, grade-list-count:%d", clikey,
               state >> 16, state & 0xFFFF, gradeList->nGradeListCount);
    return true;
}

// 0x539d0
// LIFT: not lifted in card ld-4 (0x539d0). The body posts a CliSessionGradeChangedMessage (CliSessionMessage base,
// RefCntObject reference count, LobbyMessage.cpp lines 21 and 27). It calls
// LobbyDaemon::_instance->_mileageManager->Accept and AlertSender::Write. The layouts of LobbyMessage, MileageManager
// and the LobbyDaemon instance members are not in src/ yet. Log lines: 290, 301, 313, 316, 333, 350.
bool GradeService::ApplyChangedGrade(CliSession*, StsMsgLib::_StsMsgNotifyGradeNotifyGradeChanged const*)
{
    LIFT_STUB(0x539d0);
}

// 0x541f0
bool GradeService::ApplyChangedGradeLevel(CliSession* cs,
                                          StsMsgLib::_StsMsgNotifyGradeNotifyScoreChanged const* changed)
{
    if (changed->nLevelId < 0 || changed->nAccumulateGradeScore < 0
        || (_gradeLevel.level == changed->nLevelId && _gradeLevel.score == changed->nAccumulateGradeScore))
    {
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }

    _gradeLevel.level = changed->nLevelId;
    _gradeLevel.score = changed->nAccumulateGradeScore;
    _gradeLevel.minLevelScore = changed->nMinimumLevelScore;
    _gradeLevel.maxLevelScore = changed->nMaximumLevelScore;
    _gradeLevel.maxScore = changed->nMaximumGradeScore;
    ++_revision;

    unsigned int const state = cs != nullptr ? cs->_state : 0;
    unsigned long long const clikey = cs != nullptr ? cs->_clikey : 0;
    Log::Write(Log::LT_DEBUG, kFile, 383,
               L"[grade], grade level info updated, revision:%u, cli-key:0x%I64X, cli-state:%d.%d, level-id:%d, "
               L"accumulate-grade-score:%d, minimum-level-score:%d, maximum-level-score:%d, maximum-grade-score:%d",
               _revision, clikey, state >> 16, state & 0xFFFF, changed->nLevelId, changed->nAccumulateGradeScore,
               changed->nMinimumLevelScore, changed->nMaximumLevelScore, changed->nMaximumGradeScore);
    return true;
}

// 0x542e0
bool GradeService::IsActivated(int gameGradeKey, long long now) const
{
    if (gameGradeKey <= 0)
        return false;

    GradeList::const_iterator it = _gradeList.find(gameGradeKey);
    if (it == _gradeList.end())
        return false;

    Grade const* grade = it->second;
    if (grade != nullptr
        && grade->_gameGradeKey > 0
        && grade->_gradeId > 0
        && grade->_gradeCount > 0
        && grade->_activation
        && grade->_effectiveTo >= now)
    {
        return true;
    }
    return false;
}

// 0x54390
Grade const* GradeService::GetGrade(int gameGradeKey) const
{
    if (gameGradeKey <= 0)
        return nullptr;

    GradeList::const_iterator it = _gradeList.find(gameGradeKey);
    if (it == _gradeList.end())
        return nullptr;
    return it->second;
}

// 0x54400
bool GradeService::FetchGradeLevel(FragmentPacket* fp) const
{
    if (fp == nullptr)
    {
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    if (fp->FreeSize() < 0x14)
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(5, _gradeLevel.level, _gradeLevel.score, _gradeLevel.minLevelScore, _gradeLevel.maxLevelScore,
                    _gradeLevel.maxScore) == 0)
    {
        TLobbyError = LOBERR_SYSTEM;
        return false;
    }
    return true;
}

// 0x544d0
bool GradeService::FetchGameGradeList(FragmentPacket* fp) const
{
    if (fp == nullptr)
    {
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }

    long long const now = _time64(nullptr);
    fp->StartRepeat();
    for (GradeList::const_iterator it = _gradeList.begin(); it != _gradeList.end(); ++it)
    {
        Grade const* grade = it->second;
        if (grade != nullptr && grade->_gameGradeKey > 0 && grade->_gradeId > 0 && grade->_gradeCount > 0
            && (!grade->_activation || grade->_effectiveTo >= now))
        {
            grade->FetchGame(fp);
            fp->IncRepeatCount();
        }
    }
    fp->composer.PopRepeatCount();
    return true;
}
