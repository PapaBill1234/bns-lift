// trade.h: trade.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class CancelTradeTask
{
private:
    virtual void __cdecl start(void);  // 0x3dec70
};

class ConfirmTradeCompleteTask
{
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x3df170
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, unsigned __int64, ::Item **const, short);  // 0x3df1b0
private:
    virtual void __cdecl start(void);  // 0x3df2c0
};

class ConfirmTradeTask
{
private:
    virtual void __cdecl start(void);  // 0x3df080
};

class DeclineTradeTask
{
private:
    virtual void __cdecl start(void);  // 0x3dea40
};

class InviteTradeTask
{
private:
    virtual void __cdecl start(void);  // 0x3de740
};

class JoinTradeTask
{
private:
    virtual void __cdecl start(void);  // 0x3de870
};

class RetractTradeTask
{
private:
    virtual void __cdecl start(void);  // 0x3df000
};

class SubmitTradeTask
{
private:
    virtual void __cdecl start(void);  // 0x3def80
};

class SuggestTradeTask
{
public:
    __cdecl SuggestTradeTask(void);  // 0x3ded50
private:
    virtual void __cdecl start(void);  // 0x3dedf0
};

class TradeShelf2
{
public:
    __cdecl TradeShelf2(void);  // 0x3d8300
    bool __cdecl Invite(::Pc *, unsigned __int64);  // 0x3d83b0
    bool __cdecl Join(::Pc *);  // 0x3d9120
    bool __cdecl Decline(::Pc *, char);  // 0x3d9c30
    bool __cdecl Cancel(::Pc *, char);  // 0x3da350
    bool __cdecl SuggestMoney(::Pc *, __int64);  // 0x3daab0
    bool __cdecl AppendSuggestion(::Pc *, unsigned short, short);  // 0x3dae20
    bool __cdecl SendAppendSuggestionOk(::Pc *, ::Item *);  // 0x3db170
    bool __cdecl RemoveSuggestion(::Pc *, char);  // 0x3db5b0
    bool __cdecl Submit(::Pc *);  // 0x3db850
    bool __cdecl Retract(::Pc *);  // 0x3dbe90
    bool __cdecl RetractBySuggestion(::Pc *);  // 0x3dc310
    bool __cdecl Confirm(::Pc *, bool &);  // 0x3dc640
private:
    bool __cdecl sendTransitItem(__int64, unsigned __int64);  // 0x3dd2d0
public:
    void __cdecl ConfirmComplete(__int64, __int64, short);  // 0x3dd6e0
    void __cdecl Unlink(wchar_t const *);  // 0x3ddc60
private:
    bool __cdecl checkSuggestingTrader(::Pc *);  // 0x3dddb0
    void __cdecl transitMoney(::Pc *, ::Pc *, __int64);  // 0x3ddf90
};

void __cdecl GameLog_TradeItem(::GameLogID, ::Pc *, ::Pc *, ::Item *);  // 0x3df3d0
void __cdecl GameLog_TradeItemResult(::GameLogID, ::Pc *, __int64, __int64, ::Pc *, __int64, __int64, ::Item *);  // 0x3e0a60
void __cdecl TLOG_TradeItem(::Pc *, __int64, __int64, __int64, ::Pc *, __int64, __int64, __int64, ::Item **, ::Item **);  // 0x3e1470
