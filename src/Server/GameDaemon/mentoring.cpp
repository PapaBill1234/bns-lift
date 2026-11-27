// mentoring.cpp: mentoring.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "mentoring.h"
#include "pc.h"
#include "LiftStub.h"

// 0x167e70
__cdecl Mentoring::Mentoring(void)
{
    LIFT_STUB(0x167e70);
}

// 0x167f80
__cdecl Mentoring::~Mentoring(void)
{
    LIFT_STUB(0x167f80);
}

// 0x168030
int __cdecl Mentoring::GetMenteeCount(void)
{
    LIFT_STUB(0x168030);
}

// 0x168120
unsigned __int64 __cdecl Mentoring::GetMentorPcDbId(void)
{
    LIFT_STUB(0x168120);
}

// 0x168200
unsigned __int64 __cdecl Mentoring::GetMenteePcDbIdByIndex(char)
{
    LIFT_STUB(0x168200);
}

// 0x168310
unsigned __int64 __cdecl Mentoring::GetMentorPcId(void)
{
    LIFT_STUB(0x168310);
}

// 0x1683f0
bool __cdecl Mentoring::IsExistMentee(unsigned __int64)
{
    LIFT_STUB(0x1683f0);
}

// 0x168560
void __cdecl Mentoring::GetMentoringInfoForGameLog(unsigned __int64, ::LoadMentoringInfo &)
{
    LIFT_STUB(0x168560);
}

// 0x1686f0
bool __cdecl Mentoring::UpdateMentoring(::Pc *, char)
{
    LIFT_STUB(0x1686f0);
}

// 0x168980
bool __cdecl Mentoring::UpdateMentoring(unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x168980);
}

// 0x168ce0
void __cdecl Mentoring::notifyMentoringInfo(::Pc *, char)
{
    LIFT_STUB(0x168ce0);
}

// 0x168fa0
void __cdecl Mentoring::notifyMentoringInfo(::Pc *, int, char)
{
    LIFT_STUB(0x168fa0);
}

// 0x169260
void __cdecl Mentoring::notifyMentoringInfo(char)
{
    LIFT_STUB(0x169260);
}

// 0x169320
bool __cdecl Mentoring::Mentee::Compose(int, ::FragmentPacket *) const
{
    LIFT_STUB(0x169320);
}

// 0x1693e0
bool __cdecl Mentoring::addMentee(::LoadMentoringInfo const *)
{
    LIFT_STUB(0x1693e0);
}

// 0x1696f0
bool __cdecl Mentoring::removeMentee(unsigned __int64)
{
    LIFT_STUB(0x1696f0);
}

// 0x169940
__cdecl MentoringManager::~MentoringManager(void)
{
    LIFT_STUB(0x169940);
}

// 0x169a10
bool __cdecl MentoringManager::Initialize(void)
{
    LIFT_STUB(0x169a10);
}

// 0x169ac0
void __cdecl MentoringManager::Clear(void)
{
    LIFT_STUB(0x169ac0);
}

// 0x169bf0
void __cdecl MentoringManager::removeMentoring(unsigned __int64)
{
    LIFT_STUB(0x169bf0);
}

// 0x169c70
void __cdecl MentoringManager::removeMenteeList(unsigned __int64)
{
    LIFT_STUB(0x169c70);
}

// 0x169cf0
::Pointer2< ::Mentoring> __cdecl MentoringManager::GetMentoringPtr(char, unsigned __int64)
{
    LIFT_STUB(0x169cf0);
}

// 0x169e90
bool __cdecl MentoringManager::AddMentoring(::LoadMentoringInfo const *)
{
    LIFT_STUB(0x169e90);
}

// 0x16a140
bool __cdecl MentoringManager::LeaveMentoring(unsigned __int64, unsigned __int64, ::LeaveMentoringReason)
{
    LIFT_STUB(0x16a140);
}
