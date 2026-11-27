// changeweaponappearancetran.h: changeweaponappearancetran.cpp, changeweaponappearancetran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ChangeWeaponAppearanceTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x714c0
private:
    virtual bool __cdecl work(int, void *);  // 0x71500
    bool __cdecl init(int, void *);  // 0x71560
    bool __cdecl changeWeaponAppearanceTranOk(void *);  // 0x717b0
    bool __cdecl changeWeaponAppearanceTranFail(void *);  // 0x71b40
    void __cdecl writeGameLog(::Pointer2< ::Pc>);  // 0x71eb0
};

