// trade.cpp: trade.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "trade.h"
#include "item.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x3d8300
__cdecl TradeShelf2::TradeShelf2(void)
{
    LIFT_STUB(0x3d8300);
}

// 0x3d83b0
bool __cdecl TradeShelf2::Invite(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x3d83b0);
}

// 0x3d9120
bool __cdecl TradeShelf2::Join(::Pc *)
{
    LIFT_STUB(0x3d9120);
}

// 0x3d9c30
bool __cdecl TradeShelf2::Decline(::Pc *, char)
{
    LIFT_STUB(0x3d9c30);
}

// 0x3da350
bool __cdecl TradeShelf2::Cancel(::Pc *, char)
{
    LIFT_STUB(0x3da350);
}

// 0x3daab0
bool __cdecl TradeShelf2::SuggestMoney(::Pc *, __int64)
{
    LIFT_STUB(0x3daab0);
}

// 0x3dae20
bool __cdecl TradeShelf2::AppendSuggestion(::Pc *, unsigned short, short)
{
    LIFT_STUB(0x3dae20);
}

// 0x3db170
bool __cdecl TradeShelf2::SendAppendSuggestionOk(::Pc *, ::Item *)
{
    LIFT_STUB(0x3db170);
}

// 0x3db5b0
bool __cdecl TradeShelf2::RemoveSuggestion(::Pc *, char)
{
    LIFT_STUB(0x3db5b0);
}

// 0x3db850
bool __cdecl TradeShelf2::Submit(::Pc *)
{
    LIFT_STUB(0x3db850);
}

// 0x3dbe90
bool __cdecl TradeShelf2::Retract(::Pc *)
{
    LIFT_STUB(0x3dbe90);
}

// 0x3dc310
bool __cdecl TradeShelf2::RetractBySuggestion(::Pc *)
{
    LIFT_STUB(0x3dc310);
}

// 0x3dc640
bool __cdecl TradeShelf2::Confirm(::Pc *, bool &)
{
    LIFT_STUB(0x3dc640);
}

// 0x3dd2d0
bool __cdecl TradeShelf2::sendTransitItem(__int64, unsigned __int64)
{
    LIFT_STUB(0x3dd2d0);
}

// 0x3dd6e0
void __cdecl TradeShelf2::ConfirmComplete(__int64, __int64, short)
{
    LIFT_STUB(0x3dd6e0);
}

// 0x3ddc60
void __cdecl TradeShelf2::Unlink(wchar_t const *)
{
    LIFT_STUB(0x3ddc60);
}

// 0x3dddb0
bool __cdecl TradeShelf2::checkSuggestingTrader(::Pc *)
{
    LIFT_STUB(0x3dddb0);
}

// 0x3ddf90
void __cdecl TradeShelf2::transitMoney(::Pc *, ::Pc *, __int64)
{
    LIFT_STUB(0x3ddf90);
}

// 0x3de740
void __cdecl InviteTradeTask::start(void)
{
    LIFT_STUB(0x3de740);
}

// 0x3de870
void __cdecl JoinTradeTask::start(void)
{
    LIFT_STUB(0x3de870);
}

// 0x3dea40
void __cdecl DeclineTradeTask::start(void)
{
    LIFT_STUB(0x3dea40);
}

// 0x3dec70
void __cdecl CancelTradeTask::start(void)
{
    LIFT_STUB(0x3dec70);
}

// 0x3ded50
__cdecl SuggestTradeTask::SuggestTradeTask(void)
{
    LIFT_STUB(0x3ded50);
}

// 0x3dedf0
void __cdecl SuggestTradeTask::start(void)
{
    LIFT_STUB(0x3dedf0);
}

// 0x3def80
void __cdecl SubmitTradeTask::start(void)
{
    LIFT_STUB(0x3def80);
}

// 0x3df000
void __cdecl RetractTradeTask::start(void)
{
    LIFT_STUB(0x3df000);
}

// 0x3df080
void __cdecl ConfirmTradeTask::start(void)
{
    LIFT_STUB(0x3df080);
}

// 0x3df170
void __cdecl ConfirmTradeCompleteTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x3df170);
}

// 0x3df1b0
bool __cdecl ConfirmTradeCompleteTask::Initialize(::Zone *, ::Pc *, unsigned __int64, ::Item **const, short)
{
    LIFT_STUB(0x3df1b0);
}

// 0x3df2c0
void __cdecl ConfirmTradeCompleteTask::start(void)
{
    LIFT_STUB(0x3df2c0);
}

// 0x3df3d0
void __cdecl GameLog_TradeItem(::GameLogID, ::Pc *, ::Pc *, ::Item *)
{
    LIFT_STUB(0x3df3d0);
}

// 0x3e0a60
void __cdecl GameLog_TradeItemResult(::GameLogID, ::Pc *, __int64, __int64, ::Pc *, __int64, __int64, ::Item *)
{
    LIFT_STUB(0x3e0a60);
}

// 0x3e1470
void __cdecl TLOG_TradeItem(::Pc *, __int64, __int64, __int64, ::Pc *, __int64, __int64, __int64, ::Item **, ::Item **)
{
    LIFT_STUB(0x3e1470);
}
