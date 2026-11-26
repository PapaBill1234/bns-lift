// AuctionDeliverJob.obj (LobbyDaemon PDB, 2019 + PDB). RefCntPoolObj has its symbols in this object.
// LIFT: own header (fix7). LobbyJob.h needs RefCntPoolObj, and AuctionDeliverJob needs LobbyJob. One header for both made an include cycle.
#pragma once
#include <stddef.h>
#include "RefCntObject.h"
#include "Log.h"
#include "AlertSender.h"

// PDB: RefCntPoolObj : RefCntObject (no own members). Same form as SmartCouponDaemon CouponJob.h.
// The PDB class has the pool operators below. The original declares them in ObjectPool.h (the delete log names that file).
class RefCntPoolObj : public RefCntObject
{
public:
    virtual ~RefCntPoolObj();  // 0x12230

    // PDB: public static operator new(size_t, void*). Inline; no own symbol. The handlers test the result for null
    // (HandleLobbyGame_AbandonChargeNotify 0x8c06a), so the form is throw(). ❓
    static void* operator new(size_t, void* where) throw() { return where; }
    // PDB: public static operator delete(void*, void*) (0x4f30). A pool object must not be deleted. The callers
    // that construct with the placement form above get an unwind action that calls this function.
    static void operator delete(void*, void*)
    {
        Log::Write(Log::LT_ERROR,
                   L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\lobbydaemon\\ObjectPool.h", 205,
                   L"== CRASH == [poolobj], do not call 'delete' on PoolObj instance!!!");
        AlertSender::Write(
            L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\lobbydaemon\\ObjectPool.h", 205,
            L"== CRASH == [poolobj], do not call 'delete' on PoolObj instance!!!");
    }
#if defined(__clang__)
    // LIFT: clang only (portable gate build). clang needs a usual operator delete for a virtual dtor. VS2010 has no
    // such need: its deleting dtors call the global ::operator delete (the original calls 0x4f30 only from the
    // EH unwind actions). This member keeps that behaviour. The PDB has no such member.
    static void operator delete(void* p) { ::operator delete(p); }
#endif

private:
    // PDB: private and not defined. They hide the other forms.
    static void* operator new(size_t, wchar_t const*, int);
    static void* operator new[](size_t, wchar_t const*, int);
};
static_assert(sizeof(RefCntPoolObj) == 0x18, "sizeof RefCntPoolObj");
