// mentoring.h: mentoring.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class Mentoring
{
public:
    struct Mentee;
public:
    __cdecl Mentoring(void);  // 0x167e70
    virtual __cdecl ~Mentoring(void);  // 0x167f80
    int __cdecl GetMenteeCount(void);  // 0x168030
    unsigned __int64 __cdecl GetMentorPcDbId(void);  // 0x168120
    unsigned __int64 __cdecl GetMenteePcDbIdByIndex(char);  // 0x168200
    unsigned __int64 __cdecl GetMentorPcId(void);  // 0x168310
    bool __cdecl IsExistMentee(unsigned __int64);  // 0x1683f0
    void __cdecl GetMentoringInfoForGameLog(unsigned __int64, ::LoadMentoringInfo &);  // 0x168560
    bool __cdecl UpdateMentoring(::Pc *, char);  // 0x1686f0
    bool __cdecl UpdateMentoring(unsigned __int64, unsigned __int64, char);  // 0x168980
private:
    void __cdecl notifyMentoringInfo(::Pc *, char);  // 0x168ce0
    void __cdecl notifyMentoringInfo(::Pc *, int, char);  // 0x168fa0
    void __cdecl notifyMentoringInfo(char);  // 0x169260
    bool __cdecl addMentee(::LoadMentoringInfo const *);  // 0x1693e0
    bool __cdecl removeMentee(unsigned __int64);  // 0x1696f0
};

class MentoringManager
{
public:
    __cdecl ~MentoringManager(void);  // 0x169940
    bool __cdecl Initialize(void);  // 0x169a10
    void __cdecl Clear(void);  // 0x169ac0
private:
    void __cdecl removeMentoring(unsigned __int64);  // 0x169bf0
    void __cdecl removeMenteeList(unsigned __int64);  // 0x169c70
public:
    ::Pointer2< ::Mentoring> __cdecl GetMentoringPtr(char, unsigned __int64);  // 0x169cf0
    bool __cdecl AddMentoring(::LoadMentoringInfo const *);  // 0x169e90
    bool __cdecl LeaveMentoring(unsigned __int64, unsigned __int64, ::LeaveMentoringReason);  // 0x16a140
};

struct Mentoring::Mentee
{
public:
    bool __cdecl Compose(int, ::FragmentPacket *) const;  // 0x169320
};

