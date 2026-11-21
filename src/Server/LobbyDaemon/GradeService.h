// GradeService.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from include/pdb/LobbyDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "StlMemory.h"

class CliSession;
class FragmentPacket;

namespace StsMsgLib
{
struct _StsMsgNotifyGradeNotifyGradeChanged;
struct _StsMsgNotifyGradeNotifyScoreChanged;
struct _StsMsgResponseGradeGetLevel;
struct _StsMsgResponseGradeListAllGrades;
}

class Grade
{
public:
    bool FetchGame(FragmentPacket*) const;  // 0x53370

    int _gameGradeKey;
    int _gradeId;
    bool _activation;
    int _gradeCount;
    long long _effectiveFrom;
    long long _effectiveTo;
};
static_assert(sizeof(Grade) == 0x20, "sizeof Grade");
static_assert(offsetof(Grade, _gameGradeKey) == 0x0, "Grade::_gameGradeKey");
static_assert(offsetof(Grade, _gradeId) == 0x4, "Grade::_gradeId");
static_assert(offsetof(Grade, _activation) == 0x8, "Grade::_activation");
static_assert(offsetof(Grade, _gradeCount) == 0xC, "Grade::_gradeCount");
static_assert(offsetof(Grade, _effectiveFrom) == 0x10, "Grade::_effectiveFrom");
static_assert(offsetof(Grade, _effectiveTo) == 0x18, "Grade::_effectiveTo");

class GradeLevel
{
public:
    int level;
    int score;
    int minLevelScore;
    int maxLevelScore;
    int maxScore;
};
static_assert(sizeof(GradeLevel) == 0x14, "sizeof GradeLevel");
static_assert(offsetof(GradeLevel, level) == 0x0, "GradeLevel::level");
static_assert(offsetof(GradeLevel, score) == 0x4, "GradeLevel::score");
static_assert(offsetof(GradeLevel, minLevelScore) == 0x8, "GradeLevel::minLevelScore");
static_assert(offsetof(GradeLevel, maxLevelScore) == 0xC, "GradeLevel::maxLevelScore");
static_assert(offsetof(GradeLevel, maxScore) == 0x10, "GradeLevel::maxScore");

class GradeService
{
public:
    enum GradeChangedReasonType : int
    {
        GRADECHANGEDREASONTYPE_NONE = 0x0,
        GRADECHANGEDREASONTYPE_ACTIVATED = 0x1,
        GRADECHANGEDREASONTYPE_ACTIVATED_WITH_ADDING = 0x2,
        GRADECHANGEDREASONTYPE_ADDED = 0x3,
        GRADECHANGEDREASONTYPE_DELETED = 0x4,
        GRADECHANGEDREASONTYPE_DELETED_AND_EXAUSTED = 0x5,
        GRADECHANGEDREASONTYPE_MAX = 0x6,
    };

    // LIFT: no typedef name in the PDB. Member type: std::map<int,Grade *,...,StlAllocator<...,2>>.
    typedef std::map<int, Grade*, std::less<int>, StlAllocator<std::pair<int, Grade*>, 2> > GradeList;

    GradeService();  // 0x53450
    GradeService(int);  // 0x534d0
    ~GradeService();  // 0x53550
    bool IsActivated(int, long long) const;  // 0x542e0
    Grade const* GetGrade(int) const;  // 0x54390
    bool FetchGradeLevel(FragmentPacket*) const;  // 0x54400
    bool FetchGameGradeList(FragmentPacket*) const;  // 0x544d0

    bool SetGradeLevel(CliSession* cs, StsMsgLib::_StsMsgResponseGradeGetLevel const* level);  // 0x53750
    bool SetGradeList(CliSession* cs, StsMsgLib::_StsMsgResponseGradeListAllGrades const* gradeList);  // 0x53800
    bool ApplyChangedGrade(CliSession* cs, StsMsgLib::_StsMsgNotifyGradeNotifyGradeChanged const* changed);  // 0x539d0
    bool ApplyChangedGradeLevel(CliSession* cs, StsMsgLib::_StsMsgNotifyGradeNotifyScoreChanged const* changed);  // 0x541f0

private:
    void clearGradeList();  // 0x535c0
    GradeChangedReasonType parseGradeChangedReason(wchar_t const*) const;  // 0x53670

public:
    unsigned int _revision;
    GradeLevel _gradeLevel;
    GradeList _gradeList;
    bool _initGradeLevel;
    bool _initGradeList;
};
static_assert(sizeof(GradeService) == 0x40, "sizeof GradeService");
static_assert(offsetof(GradeService, _revision) == 0x0, "GradeService::_revision");
static_assert(offsetof(GradeService, _gradeLevel) == 0x4, "GradeService::_gradeLevel");
static_assert(offsetof(GradeService, _gradeList) == 0x18, "GradeService::_gradeList");
static_assert(offsetof(GradeService, _initGradeLevel) == 0x38, "GradeService::_initGradeLevel");
static_assert(offsetof(GradeService, _initGradeList) == 0x39, "GradeService::_initGradeList");
