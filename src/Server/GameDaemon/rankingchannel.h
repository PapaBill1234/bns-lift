// rankingchannel.h: rankingchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RankingChannel
{
public:
    virtual __cdecl ~RankingChannel(void);  // 0x1aef40
    void __cdecl Initialize(void);  // 0x1aef50
    bool __cdecl InitSession(void);  // 0x1aefb0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x1af0f0
protected:
    virtual bool __cdecl onConnect(::Session const *, bool);  // 0x1af180
    virtual void __cdecl onClose(::Session const *, bool, bool);  // 0x1af210
public:
    bool __cdecl SendRetrievePlayerRankingInfo(unsigned __int64, char, unsigned __int64, char, int);  // 0x1af300
    bool __cdecl InsertPlayerRankingScore(__int64, __int64, short, char, int, char, __int64, char, int, wchar_t *, __int64, char, __int64, wchar_t const *, wchar_t const *);  // 0x1af370
    bool __cdecl InsertRankingScore(__int64, __int64, short, char, __int64, __int64, __int64, char, int, wchar_t *, char, __int64, wchar_t const *, wchar_t const *);  // 0x1af4b0
    void __cdecl SendLoadGuildRankingResultList(void);  // 0x1af5c0
    bool __cdecl SendLoadPlayerSeasonResultByPlayerTypeList(short, __int64);  // 0x1af660
};

bool __cdecl HandleRankingGame_HelloOk(::Session const *, ::Packet const *);  // 0x1af710
bool __cdecl HandleRankingGame_HelloFail(::Session const *, ::Packet const *);  // 0x1af940
bool __cdecl HandleRankingGame_PingOk(::Session const *, ::Packet const *);  // 0x1af9d0
bool __cdecl HandleRankingGame_RetrievePlayerRankingInfoOk(::Session const *, ::Packet const *);  // 0x1afa80
bool __cdecl HandleRankingGame_RetrievePlayerRankingInfoFail(::Session const *, ::Packet const *);  // 0x1b0020
bool __cdecl HandleRankingGame_RetrievePcRankingResultListOk(::Session const *, ::Packet const *);  // 0x1b0240
bool __cdecl HandleRankingGame_RetrievePcRankingResultListFail(::Session const *, ::Packet const *);  // 0x1b09e0
bool __cdecl HandleRankingGame_LoadGuildRankingResultListOk(::Session const *, ::Packet const *);  // 0x1b0ba0
bool __cdecl HandleRankingGame_LoadGuildRankingResultListFail(::Session const *, ::Packet const *);  // 0x1b0d20
bool __cdecl HandleRankingGame_LoadPlayerSeasonResultByPlayerTypeListOk(::Session const *, ::Packet const *);  // 0x1b0e30
bool __cdecl HandleRankingGame_LoadPlayerSeasonResultByPlayerTypeListFail(::Session const *, ::Packet const *);  // 0x1b1240
bool __cdecl HandleRankingGame_InsertPlayerRatingScoreOk(::Session const *, ::Packet const *);  // 0x1b1350
bool __cdecl HandleRankingGame_InsertPlayerRatingScoreFail(::Session const *, ::Packet const *);  // 0x1b1850
bool __cdecl HandleRankingGame_InsertRankingScoreOk(::Session const *, ::Packet const *);  // 0x1b1c50
bool __cdecl HandleRankingGame_InsertRankingScoreFail(::Session const *, ::Packet const *);  // 0x1b1f30
