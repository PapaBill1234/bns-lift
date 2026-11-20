// GradeService.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <map>
#include "StlMemory.h"

class FragmentPacket;
class Grade;

// PDB layout (include/pdb/LobbyDaemon/types.h GradeLevel).
struct GradeLevel
{
    int level;
    int score;
    int minLevelScore;
    int maxLevelScore;
    int maxScore;
};
static_assert(sizeof(GradeLevel) == 0x14, "sizeof GradeLevel");

class Grade
{
public:
    bool FetchGame(FragmentPacket*) const;  // 0x53370
};

// PDB layout (include/pdb/LobbyDaemon/types.h GradeService). Size 0x40, CliSession::_gradeService at 0x830.
class GradeService
{
public:
    enum GradeChangedReasonType
    {
        GRADECHANGEDREASONTYPE_NONE = 0,
        GRADECHANGEDREASONTYPE_ACTIVATED = 1,
        GRADECHANGEDREASONTYPE_ACTIVATED_WITH_ADDING = 2,
        GRADECHANGEDREASONTYPE_ADDED = 3,
        GRADECHANGEDREASONTYPE_DELETED = 4,
        GRADECHANGEDREASONTYPE_DELETED_AND_EXAUSTED = 5,
        GRADECHANGEDREASONTYPE_MAX = 6,
    };

    GradeService();  // 0x53450
    GradeService(int);  // 0x534d0
    ~GradeService();  // 0x53550
    bool IsActivated(int, long long) const;  // 0x542e0
    Grade const* GetGrade(int) const;  // 0x54390
    bool FetchGradeLevel(FragmentPacket*) const;  // 0x54400
    bool FetchGameGradeList(FragmentPacket*) const;  // 0x544d0
private:
    void clearGradeList();  // 0x535c0

public:
    unsigned int _revision;
    GradeLevel _gradeLevel;
    // LIFT: the PDB dump shows std::map<int,Grade*>. The allocator is StlAllocator<,2> (StlMemory.h path in the
    // GradeService destructor path, HR CliSession.c line 696). ❓
    std::map<int, Grade*, std::less<int>, StlAllocator<std::pair<int const, Grade*>, 2> > _gradeList;
    bool _initGradeLevel;
    bool _initGradeList;
};
static_assert(sizeof(GradeService) == 0x40, "sizeof GradeService");
static_assert(offsetof(GradeService, _gradeList) == 0x18, "GradeService::_gradeList");
static_assert(offsetof(GradeService, _initGradeList) == 0x39, "GradeService::_initGradeList");
