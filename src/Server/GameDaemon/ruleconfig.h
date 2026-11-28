// ruleconfig.h: ruleconfig.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RuleConfig
{
public:
    static ::RuleConfig * __cdecl Load(void);  // 0x3d72c0
    bool __cdecl Validation(void);  // 0x3d73f0
    int FactionTransferLimitPercent(void) const { return _factionTransferLimitPercent; }  // PDB inline
    int FactionTransferLimitPcCount(void) const { return _factionTransferLimitPcCount; }  // PDB inline
private:
    void __cdecl setMarketRegisterTimeTaxExtra(void);  // 0x3d7670
    char lift_pad_0[76];  // ❓ no PDB name: members +0 to +75 are not declared yet
    int _factionTransferLimitPercent;  // +76
    int _factionTransferLimitPcCount;  // +80
    char lift_pad_54[540 - 84];  // ❓ no PDB name: members +84 to +539 are not declared yet
    int _styleScoreExpStep1;  // +540
    int _styleScoreExpStep2;  // +544
    int _styleScoreExpBonus1;  // +548
    int _styleScoreExpBonus2;  // +552
    friend class ::Pc;  // LIFT: Pc::CalculateStyleScoreBonus reads the _styleScoreExp* members (no PDB accessor found)
};

