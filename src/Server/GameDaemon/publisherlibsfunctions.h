// publisherlibsfunctions.h: publisherlibsfunctions.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

bool __cdecl packetBufferAlloc(void);  // 0x1a4350
int __cdecl getPacketCommand(void const *);  // 0x1a4360
bool __cdecl createPacketComposer(void **, char const *);  // 0x1a4370
bool __cdecl createPacketDecomposer(void **, char const *);  // 0x1a4420
bool __cdecl createPacket(void **, void *);  // 0x1a44d0
bool __cdecl deletePacketComposer(void *);  // 0x1a4540
bool __cdecl deletePacketDecomposer(void *);  // 0x1a4570
bool __cdecl deletePacket(void *);  // 0x1a45a0
bool __cdecl compose(void *, void *, int, ...);  // 0x1a45e0
bool __cdecl decompose(void *, void *, int, ...);  // 0x1a4660
bool __cdecl composeV(void *, void *, int, char *);  // 0x1a46e0
bool __cdecl decomposeV(void *, void *, int, char *);  // 0x1a4770
bool __cdecl startRepeat(void *, void *);  // 0x1a4800
bool __cdecl endRepeat(void *, void *);  // 0x1a4820
bool __cdecl incRepeat(void *, void *);  // 0x1a4840
int __cdecl openRepeat(void *, void *);  // 0x1a4890
int __cdecl closeRepeat(void *, void *);  // 0x1a48b0
int __cdecl decRepeat(void *, void *);  // 0x1a48d0
bool __cdecl growAdd(void *, void const *, short);  // 0x1a48f0
int __cdecl freeSize(void *);  // 0x1a4900
char const * __cdecl allocate(void *);  // 0x1a4920
bool __cdecl copyPacket(void *, void const *);  // 0x1a4930
bool __cdecl setRecvBuffer(void *, char const *);  // 0x1a4940
bool __cdecl sendToPc(unsigned __int64, unsigned __int64, void const *);  // 0x1a4950
bool __cdecl fpCreatePacket(void **, int, char const *);  // 0x1a4b50
bool __cdecl fpDeletePacket(void *);  // 0x1a4bd0
bool __cdecl fpCompose(void *, int, ...);  // 0x1a4c10
bool __cdecl fpComposeV(void *, int, char *);  // 0x1a4c60
bool __cdecl fpStartRepeat(void *);  // 0x1a4cb0
bool __cdecl fpEndRepeat(void *);  // 0x1a4d00
bool __cdecl fpIncRepeat(void *);  // 0x1a4d20
bool __cdecl fpCreateConcatenater(void **);  // 0x1a4d30
bool __cdecl fpAddFragmentPacket(void *, void *, bool *);  // 0x1a4de0
bool __cdecl fpInitDecomposer(void *, char const *, int, int);  // 0x1a4df0
int __cdecl fpOpenRepeat(void *);  // 0x1a4e20
int __cdecl fpCloseRepeat(void *);  // 0x1a4e50
int __cdecl fpDecRepeat(void *);  // 0x1a4e70
bool __cdecl fpDecompose(void *, int, ...);  // 0x1a4e90
bool __cdecl fpDecomposeV(void *, int, char *);  // 0x1a4ec0
bool __cdecl fpClearConcatenater(void *);  // 0x1a4ed0
bool __cdecl fpDeleteConcatenater(void *);  // 0x1a4ee0
bool __cdecl fpFinalize(void *);  // 0x1a4f20
bool __cdecl fpGetPacket(void *, void **);  // 0x1a4f50
bool __cdecl fpClear(void *);  // 0x1a4f60
int __cdecl fpFreeSize(void *);  // 0x1a4fb0
char const * __cdecl fpAllocate(void *);  // 0x1a4fd0
unsigned long __cdecl getInternalAddress(void);  // 0x1a4fe0
unsigned long __cdecl getPublicAddress(void);  // 0x1a4ff0
bool __cdecl logBufferAlloc(void);  // 0x1a5000
bool __cdecl errorWrite(wchar_t const *, int, wchar_t const *, ...);  // 0x1a5010
bool __cdecl noticeWrite(wchar_t const *, int, wchar_t const *, ...);  // 0x1a5040
bool __cdecl debugWrite(wchar_t const *, int, wchar_t const *, ...);  // 0x1a5080
bool __cdecl traceWrite(wchar_t const *, int, wchar_t const *, ...);  // 0x1a50c0
bool __cdecl Kick(unsigned __int64, unsigned __int64);  // 0x1a5100
void __cdecl SetPublisherLibsSideHandle(::PublisherLibsInterface::PublisherLibsSideHandleFunc *);  // 0x1a5270
bool __cdecl setGamePlayRestrictLevel(unsigned __int64, unsigned __int64, int, int);  // 0x1a5540
bool __cdecl SetSafeMode(unsigned __int64, unsigned __int64, int, int);  // 0x1a5820
int __cdecl UIC_CallBack_proc(unsigned __int64, unsigned __int64, int, int, unsigned __int64, char, __int64, int, char, short, char, wchar_t const *, wchar_t const *);  // 0x1a5b60
bool __cdecl TLogWrite(int, char const *, ...);  // 0x1a60c0
bool __cdecl getQQGroupIDByPc(unsigned __int64, unsigned __int64, __int64 *);  // 0x1a6130
bool __cdecl getQQGroupIDByGuildId(unsigned __int64, __int64 *);  // 0x1a63e0
bool __cdecl getGuildLeaderIdByPc(unsigned __int64, unsigned __int64, unsigned __int64 *);  // 0x1a6510
bool __cdecl getGuildLeaderIdByGuildId(unsigned __int64, unsigned __int64 *);  // 0x1a6750
bool __cdecl getGuildLeaderQQIdByGuildId(unsigned __int64, __int64 *);  // 0x1a6870
bool __cdecl bindQQGroup(unsigned __int64, unsigned __int64, unsigned __int64, __int64, char);  // 0x1a69f0
bool __cdecl unbindQQGroup(unsigned __int64, unsigned __int64, unsigned __int64, __int64);  // 0x1a6bb0
bool __cdecl changeQQGroupMemberStatus(unsigned __int64, unsigned __int64, unsigned __int64, __int64, __int64, char);  // 0x1a6d50
