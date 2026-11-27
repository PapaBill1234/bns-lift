// postbox.cpp: postbox.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "postbox.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x1922c0
__cdecl PostBox::~PostBox(void)
{
    LIFT_STUB(0x1922c0);
}

// 0x192330
bool __cdecl PostBox::AddPost(char, __int64, ::PostBox::PostHeader *, ::PostBox::PostBriefBody *)
{
    LIFT_STUB(0x192330);
}

// 0x192460
bool __cdecl PostBox::RemovePost(char, __int64)
{
    LIFT_STUB(0x192460);
}

// 0x192570
bool __cdecl PostBox::AddPostBody(char, __int64, ::PostBox::PostBody *)
{
    LIFT_STUB(0x192570);
}

// 0x1926d0
short __cdecl PostBox::TryDetachPostAttachment(__int64, char, __int64, __int64)
{
    LIFT_STUB(0x1926d0);
}

// 0x193a60
void __cdecl PostBox::FinishDetachPostAttachment(__int64, char, __int64, __int64, __int64, short)
{
    LIFT_STUB(0x193a60);
}

// 0x194140
void __cdecl PostBox::RollbackDetachPostAttachment(__int64, char, __int64, __int64, short)
{
    LIFT_STUB(0x194140);
}

// 0x194480
bool __cdecl PostBox::ReadPost(char, __int64)
{
    LIFT_STUB(0x194480);
}

// 0x194a80
void __cdecl PostBox::SendPostBody(char, __int64)
{
    LIFT_STUB(0x194a80);
}

// 0x195210
__cdecl RetreivePostBriefListTask::RetreivePostBriefListTask(void)
{
    LIFT_STUB(0x195210);
}

// 0x1952c0
__cdecl RetreivePostBriefListTask::~RetreivePostBriefListTask(void)
{
    LIFT_STUB(0x1952c0);
}

// 0x1953c0
bool __cdecl RetreivePostBriefListTask::Initialize(::Zone *, ::Pc *)
{
    LIFT_STUB(0x1953c0);
}

// 0x195430
void __cdecl RetreivePostBriefListTask::AddPostCapacity(int)
{
    LIFT_STUB(0x195430);
}

// 0x195620
bool __cdecl RetreivePostBriefListTask::AddPost(char, unsigned __int64, ::PostBox::PostHeader *, ::PostBox::PostBriefBody *)
{
    LIFT_STUB(0x195620);
}

// 0x1956f0
void __cdecl RetreivePostBriefListTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x1956f0);
}

// 0x195730
void __cdecl RetreivePostBriefListTask::start(void)
{
    LIFT_STUB(0x195730);
}

// 0x195f10
void __cdecl RetreivePostTask::start(void)
{
    LIFT_STUB(0x195f10);
}

// 0x195f50
void __cdecl ReadPostTask::start(void)
{
    LIFT_STUB(0x195f50);
}

// 0x195f90
bool __cdecl ArchivePostTask::Initialize(::Zone *, ::Pc *, char, unsigned __int64)
{
    LIFT_STUB(0x195f90);
}

// 0x196020
void __cdecl ArchivePostTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x196020);
}

// 0x196060
void __cdecl ArchivePostTask::start(void)
{
    LIFT_STUB(0x196060);
}
