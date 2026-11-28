// nofile.cpp: no source file in the PDB (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
// LIFT: per-exe StlMemory.h path (A6). The inlined StlAllocator::deallocate of this exe uses the GameDaemon build path.
#define LIFT_STLMEMORY_FILE \
    L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"
#include "GameDaemonFwd.h"
#include "datapacker.h"
#include "datareaderimpl.h"
#include "effectcontent.h"
#include "inventory.h"
#include "jsoncpp.h"
#include "lobbytokenauthtran.h"
#include "rankingseason.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1SlateScrollCache@Data@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1RankingSeasonInfo@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
// 0x118e0
// PDB: compiler-generated. The body is the inlined destructor of stones.
__cdecl Data::SlateScrollCache::~SlateScrollCache(void)
{
}

// 0x157c0
// PDB: compiler-generated. The body is the inlined destructor of _pathTokenW and _pathW (StlAllocator<..., 2>).
#pragma comment(linker, "/INCLUDE:??1FileName@ZipPackedReaderIO@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl ZipPackedReaderIO::FileName::~FileName(void)
{
}

// 0x191c0 EventObject::~EventObject: LIFT: no body in wave 0 (shared class DynamicEventObject has another form or the change needs codegen (W1, pattern 35)).

// 0xc0000
__cdecl LogoutOkParam::~LogoutOkParam(void)
{
    LIFT_STUB(0xc0000);
}

// 0x13fd20
__cdecl EnterWorldOkParam::~EnterWorldOkParam(void)
{
    LIFT_STUB(0x13fd20);
}

// 0x14a320
__cdecl TakeTimeBasedPlayRewardResponseParam::~TakeTimeBasedPlayRewardResponseParam(void)
{
    LIFT_STUB(0x14a320);
}

// 0x1b4030
// PDB: compiler-generated. The body is the inlined destructor of resultScheduleList.
__cdecl RankingSeasonInfo::~RankingSeasonInfo(void)
{
}

// 0x1ee8e0
__cdecl ZoneCounterSet::~ZoneCounterSet(void)
{
    LIFT_STUB(0x1ee8e0);
}

// 0x3408d0 TextStreamPacketBufferHandler::~TextStreamPacketBufferHandler: LIFT: no body in wave 0 (shared class TextStreamPacketBufferHandler has another form or the change needs codegen (W1, pattern 35)).

// 0x340920 RawPacketBufferHandler::~RawPacketBufferHandler: LIFT: no body in wave 0 (shared class RawPacketBufferHandler has another form or the change needs codegen (W1, pattern 35)).

// 0x4bfa70
__cdecl InventoryCacheUpdate::~InventoryCacheUpdate(void)
{
    LIFT_STUB(0x4bfa70);
}

// 0x4bfee0
__cdecl InventoryClientUpdate::~InventoryClientUpdate(void)
{
    LIFT_STUB(0x4bfee0);
}

// 0x5b3750
__cdecl FallDeathEffect::FallDeathEffect(void)
{
    LIFT_STUB(0x5b3750);
}

// 0x681060
__cdecl Json::Reader::~Reader(void)
{
    LIFT_STUB(0x681060);
}

// 0x6a8430
__cdecl Json::LogicError::~LogicError(void)
{
    LIFT_STUB(0x6a8430);
}

// 0x6a84d0
__cdecl Json::Exception::Exception(::Json::Exception const &)
{
    LIFT_STUB(0x6a84d0);
}

// 0x6a85d0
__cdecl Json::LogicError::LogicError(::Json::LogicError const &)
{
    LIFT_STUB(0x6a85d0);
}

// 0x6eba80
__cdecl LoadTableBinder::~LoadTableBinder(void)
{
    LIFT_STUB(0x6eba80);
}

// 0x720df0 wmain$dtor$0: LIFT: no body in wave 0 (unwind funclet; no source function).
