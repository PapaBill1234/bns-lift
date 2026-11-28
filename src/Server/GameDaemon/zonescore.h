// zonescore.h: zonescore.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: ZoneScore has its PDB layout (size 0x2E). Score is inline in the original (no PDB body).
#pragma once
#include "GameDaemonFwd.h"

class ZoneScore
{
public:
    struct ScoreInfo
    {
        char scoreType;  // +0
        short score;     // +2
    };

    void __cdecl AddScore(char, short);  // 0x25f710
    bool __cdecl FetchPartyBattleScore(::FragmentPacket &, char);  // 0x25f7a0
    bool __cdecl FetchScoreTypeHistory(::FragmentPacket &);  // 0x25f870

    // Inline in the original (inlined at Zone::GetZoneScore 0x258710).
    // LIFT: 6 is the score type count (PDB: _score[6]); type 6 gives the total.
    int Score(char scoreType)
    {
        if (scoreType < 0)
            return 0;
        if (scoreType <= 5)
            return _score[scoreType];
        if (scoreType != 6)
            return 0;
        int total = 0;
        for (char i = 0; i < 6; ++i)  // LIFT: a char counter keeps the loop (formtest: an int counter unrolls it)
            total += _score[i];
        return total;
    }

private:
    short _score[6];               // +0 (0x0)
    ScoreInfo _scoreHistory[8];    // +12 (0xC)
    char _historyCount;            // +44 (0x2C)
};
static_assert(sizeof(ZoneScore) == 0x2E, "sizeof ZoneScore");

