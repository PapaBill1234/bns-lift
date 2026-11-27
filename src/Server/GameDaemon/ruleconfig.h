// ruleconfig.h: ruleconfig.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RuleConfig
{
public:
    static ::RuleConfig * __cdecl Load(void);  // 0x3d72c0
    bool __cdecl Validation(void);  // 0x3d73f0
private:
    void __cdecl setMarketRegisterTimeTaxExtra(void);  // 0x3d7670
};

