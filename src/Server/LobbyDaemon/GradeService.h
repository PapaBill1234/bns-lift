// GradeService.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class FragmentPacket;
class Grade;

class Grade
{
public:
    bool FetchGame(FragmentPacket*) const;  // 0x53370
};

class GradeService
{
public:
    GradeService();  // 0x53450
    GradeService(int);  // 0x534d0
    ~GradeService();  // 0x53550
    bool IsActivated(int, long long) const;  // 0x542e0
    Grade const* GetGrade(int) const;  // 0x54390
    bool FetchGradeLevel(FragmentPacket*) const;  // 0x54400
    bool FetchGameGradeList(FragmentPacket*) const;  // 0x544d0
private:
    void clearGradeList();  // 0x535c0
};
