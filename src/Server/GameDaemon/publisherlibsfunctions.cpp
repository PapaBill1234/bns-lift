// publisherlibsfunctions.cpp: publisherlibsfunctions.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "publisherlibsfunctions.h"
#include "LiftStub.h"

// 0x1a4350
bool __cdecl packetBufferAlloc(void)
{
    LIFT_STUB(0x1a4350);
}

// 0x1a4360
int __cdecl getPacketCommand(void const *)
{
    LIFT_STUB(0x1a4360);
}

// 0x1a4370
bool __cdecl createPacketComposer(void **, char const *)
{
    LIFT_STUB(0x1a4370);
}

// 0x1a4420
bool __cdecl createPacketDecomposer(void **, char const *)
{
    LIFT_STUB(0x1a4420);
}

// 0x1a44d0
bool __cdecl createPacket(void **, void *)
{
    LIFT_STUB(0x1a44d0);
}

// 0x1a4540
bool __cdecl deletePacketComposer(void *)
{
    LIFT_STUB(0x1a4540);
}

// 0x1a4570
bool __cdecl deletePacketDecomposer(void *)
{
    LIFT_STUB(0x1a4570);
}

// 0x1a45a0
bool __cdecl deletePacket(void *)
{
    LIFT_STUB(0x1a45a0);
}

// 0x1a45e0
bool __cdecl compose(void *, void *, int, ...)
{
    LIFT_STUB(0x1a45e0);
}

// 0x1a4660
bool __cdecl decompose(void *, void *, int, ...)
{
    LIFT_STUB(0x1a4660);
}

// 0x1a46e0
bool __cdecl composeV(void *, void *, int, char *)
{
    LIFT_STUB(0x1a46e0);
}

// 0x1a4770
bool __cdecl decomposeV(void *, void *, int, char *)
{
    LIFT_STUB(0x1a4770);
}

// 0x1a4800
bool __cdecl startRepeat(void *, void *)
{
    LIFT_STUB(0x1a4800);
}

// 0x1a4820
bool __cdecl endRepeat(void *, void *)
{
    LIFT_STUB(0x1a4820);
}

// 0x1a4840
bool __cdecl incRepeat(void *, void *)
{
    LIFT_STUB(0x1a4840);
}

// 0x1a4890
int __cdecl openRepeat(void *, void *)
{
    LIFT_STUB(0x1a4890);
}

// 0x1a48b0
int __cdecl closeRepeat(void *, void *)
{
    LIFT_STUB(0x1a48b0);
}

// 0x1a48d0
int __cdecl decRepeat(void *, void *)
{
    LIFT_STUB(0x1a48d0);
}

// 0x1a48f0
bool __cdecl growAdd(void *, void const *, short)
{
    LIFT_STUB(0x1a48f0);
}

// 0x1a4900
int __cdecl freeSize(void *)
{
    LIFT_STUB(0x1a4900);
}

// 0x1a4920
char const * __cdecl allocate(void *)
{
    LIFT_STUB(0x1a4920);
}

// 0x1a4930
bool __cdecl copyPacket(void *, void const *)
{
    LIFT_STUB(0x1a4930);
}

// 0x1a4940
bool __cdecl setRecvBuffer(void *, char const *)
{
    LIFT_STUB(0x1a4940);
}

// 0x1a4950
bool __cdecl sendToPc(unsigned __int64, unsigned __int64, void const *)
{
    LIFT_STUB(0x1a4950);
}

// 0x1a4b50
bool __cdecl fpCreatePacket(void **, int, char const *)
{
    LIFT_STUB(0x1a4b50);
}

// 0x1a4bd0
bool __cdecl fpDeletePacket(void *)
{
    LIFT_STUB(0x1a4bd0);
}

// 0x1a4c10
bool __cdecl fpCompose(void *, int, ...)
{
    LIFT_STUB(0x1a4c10);
}

// 0x1a4c60
bool __cdecl fpComposeV(void *, int, char *)
{
    LIFT_STUB(0x1a4c60);
}

// 0x1a4cb0
bool __cdecl fpStartRepeat(void *)
{
    LIFT_STUB(0x1a4cb0);
}

// 0x1a4d00
bool __cdecl fpEndRepeat(void *)
{
    LIFT_STUB(0x1a4d00);
}

// 0x1a4d20
bool __cdecl fpIncRepeat(void *)
{
    LIFT_STUB(0x1a4d20);
}

// 0x1a4d30
bool __cdecl fpCreateConcatenater(void **)
{
    LIFT_STUB(0x1a4d30);
}

// 0x1a4de0
bool __cdecl fpAddFragmentPacket(void *, void *, bool *)
{
    LIFT_STUB(0x1a4de0);
}

// 0x1a4df0
bool __cdecl fpInitDecomposer(void *, char const *, int, int)
{
    LIFT_STUB(0x1a4df0);
}

// 0x1a4e20
int __cdecl fpOpenRepeat(void *)
{
    LIFT_STUB(0x1a4e20);
}

// 0x1a4e50
int __cdecl fpCloseRepeat(void *)
{
    LIFT_STUB(0x1a4e50);
}

// 0x1a4e70
int __cdecl fpDecRepeat(void *)
{
    LIFT_STUB(0x1a4e70);
}

// 0x1a4e90
bool __cdecl fpDecompose(void *, int, ...)
{
    LIFT_STUB(0x1a4e90);
}

// 0x1a4ec0
bool __cdecl fpDecomposeV(void *, int, char *)
{
    LIFT_STUB(0x1a4ec0);
}

// 0x1a4ed0
bool __cdecl fpClearConcatenater(void *)
{
    LIFT_STUB(0x1a4ed0);
}

// 0x1a4ee0
bool __cdecl fpDeleteConcatenater(void *)
{
    LIFT_STUB(0x1a4ee0);
}

// 0x1a4f20
bool __cdecl fpFinalize(void *)
{
    LIFT_STUB(0x1a4f20);
}

// 0x1a4f50
bool __cdecl fpGetPacket(void *, void **)
{
    LIFT_STUB(0x1a4f50);
}

// 0x1a4f60
bool __cdecl fpClear(void *)
{
    LIFT_STUB(0x1a4f60);
}

// 0x1a4fb0
int __cdecl fpFreeSize(void *)
{
    LIFT_STUB(0x1a4fb0);
}

// 0x1a4fd0
char const * __cdecl fpAllocate(void *)
{
    LIFT_STUB(0x1a4fd0);
}

// 0x1a4fe0
unsigned long __cdecl getInternalAddress(void)
{
    LIFT_STUB(0x1a4fe0);
}

// 0x1a4ff0
unsigned long __cdecl getPublicAddress(void)
{
    LIFT_STUB(0x1a4ff0);
}

// 0x1a5000
bool __cdecl logBufferAlloc(void)
{
    LIFT_STUB(0x1a5000);
}

// 0x1a5010
bool __cdecl errorWrite(wchar_t const *, int, wchar_t const *, ...)
{
    LIFT_STUB(0x1a5010);
}

// 0x1a5040
bool __cdecl noticeWrite(wchar_t const *, int, wchar_t const *, ...)
{
    LIFT_STUB(0x1a5040);
}

// 0x1a5080
bool __cdecl debugWrite(wchar_t const *, int, wchar_t const *, ...)
{
    LIFT_STUB(0x1a5080);
}

// 0x1a50c0
bool __cdecl traceWrite(wchar_t const *, int, wchar_t const *, ...)
{
    LIFT_STUB(0x1a50c0);
}

// 0x1a5100
bool __cdecl Kick(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x1a5100);
}

// 0x1a5270
void __cdecl SetPublisherLibsSideHandle(::PublisherLibsInterface::PublisherLibsSideHandleFunc *)
{
    LIFT_STUB(0x1a5270);
}

// 0x1a5540
bool __cdecl setGamePlayRestrictLevel(unsigned __int64, unsigned __int64, int, int)
{
    LIFT_STUB(0x1a5540);
}

// 0x1a5820
bool __cdecl SetSafeMode(unsigned __int64, unsigned __int64, int, int)
{
    LIFT_STUB(0x1a5820);
}

// 0x1a5b60
int __cdecl UIC_CallBack_proc(unsigned __int64, unsigned __int64, int, int, unsigned __int64, char, __int64, int, char, short, char, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x1a5b60);
}

// 0x1a60c0
bool __cdecl TLogWrite(int, char const *, ...)
{
    LIFT_STUB(0x1a60c0);
}

// 0x1a6130
bool __cdecl getQQGroupIDByPc(unsigned __int64, unsigned __int64, __int64 *)
{
    LIFT_STUB(0x1a6130);
}

// 0x1a63e0
bool __cdecl getQQGroupIDByGuildId(unsigned __int64, __int64 *)
{
    LIFT_STUB(0x1a63e0);
}

// 0x1a6510
bool __cdecl getGuildLeaderIdByPc(unsigned __int64, unsigned __int64, unsigned __int64 *)
{
    LIFT_STUB(0x1a6510);
}

// 0x1a6750
bool __cdecl getGuildLeaderIdByGuildId(unsigned __int64, unsigned __int64 *)
{
    LIFT_STUB(0x1a6750);
}

// 0x1a6870
bool __cdecl getGuildLeaderQQIdByGuildId(unsigned __int64, __int64 *)
{
    LIFT_STUB(0x1a6870);
}

// 0x1a69f0
bool __cdecl bindQQGroup(unsigned __int64, unsigned __int64, unsigned __int64, __int64, char)
{
    LIFT_STUB(0x1a69f0);
}

// 0x1a6bb0
bool __cdecl unbindQQGroup(unsigned __int64, unsigned __int64, unsigned __int64, __int64)
{
    LIFT_STUB(0x1a6bb0);
}

// 0x1a6d50
bool __cdecl changeQQGroupMemberStatus(unsigned __int64, unsigned __int64, unsigned __int64, __int64, __int64, char)
{
    LIFT_STUB(0x1a6d50);
}
