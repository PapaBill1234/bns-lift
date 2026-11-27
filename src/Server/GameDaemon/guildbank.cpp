// guildbank.cpp: guildbank.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "guildbank.h"
#include "LiftStub.h"

// 0x110820
bool __cdecl GuildBank::Initialize(void)
{
    LIFT_STUB(0x110820);
}

// 0x1109b0
bool __cdecl GuildBank::InitializeDBData(short, ::GuildBank::GuildBankBalanceInfo *const)
{
    LIFT_STUB(0x1109b0);
}

// 0x110b10
bool __cdecl GuildBank::HandleBalance(short, ::GuildBank::GuildBankItem const *const, bool, __int64 *const)
{
    LIFT_STUB(0x110b10);
}

// 0x110d20
bool __cdecl GuildBank::DepositByManager(unsigned int, short, __int64, __int64 &, __int64 &)
{
    LIFT_STUB(0x110d20);
}

// 0x110ec0
bool __cdecl GuildBank::WithdrawByManager(unsigned int, short, __int64, __int64 &, __int64 &)
{
    LIFT_STUB(0x110ec0);
}

// 0x111070
bool __cdecl GuildBank::IsComputable(short, ::GuildBank::GuildBankItem *const)
{
    LIFT_STUB(0x111070);
}

// 0x111150
bool __cdecl GuildBank::FetchGuildBankBalance(::FragmentPacket &)
{
    LIFT_STUB(0x111150);
}

// 0x1112e0
short __cdecl GuildBank::EnableDeposit(int, short, __int64, __int64 *)
{
    LIFT_STUB(0x1112e0);
}

// 0x111640
__int64 __cdecl GuildBank::EnableDepositCount(int, short)
{
    LIFT_STUB(0x111640);
}

// 0x111700
short __cdecl GuildBank::EnableSubtract(short, ::GuildBank::GuildBankItem *const)
{
    LIFT_STUB(0x111700);
}

// 0x111940
bool __cdecl GuildBank::EnableWithdrawByManager(unsigned int, short, __int64)
{
    LIFT_STUB(0x111940);
}
