// guildbank.h: guildbank.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GuildBank
{
public:
    struct GuildBankBalanceInfo {};
    struct GuildBankItem {};
public:
    bool __cdecl Initialize(void);  // 0x110820
    bool __cdecl InitializeDBData(short, ::GuildBank::GuildBankBalanceInfo *const);  // 0x1109b0
    bool __cdecl HandleBalance(short, ::GuildBank::GuildBankItem const *const, bool, __int64 *const);  // 0x110b10
    bool __cdecl DepositByManager(unsigned int, short, __int64, __int64 &, __int64 &);  // 0x110d20
    bool __cdecl WithdrawByManager(unsigned int, short, __int64, __int64 &, __int64 &);  // 0x110ec0
    bool __cdecl IsComputable(short, ::GuildBank::GuildBankItem *const);  // 0x111070
    bool __cdecl FetchGuildBankBalance(::FragmentPacket &);  // 0x111150
    short __cdecl EnableDeposit(int, short, __int64, __int64 *);  // 0x1112e0
    __int64 __cdecl EnableDepositCount(int, short);  // 0x111640
    short __cdecl EnableSubtract(short, ::GuildBank::GuildBankItem *const);  // 0x111700
    bool __cdecl EnableWithdrawByManager(unsigned int, short, __int64);  // 0x111940
};

