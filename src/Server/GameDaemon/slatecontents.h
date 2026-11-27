// slatecontents.h: slatecontents.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class Slate
{
public:
    bool __cdecl ComposePureSync(::FragmentPacket *);  // 0x10e50
    short const __cdecl FetchDbSync(char *, short) const;  // 0x10f30
    short __cdecl GetAmpValue(char) const;  // 0x10fb0
    void __cdecl GetStoneSlot(char, short &) const;  // 0x11110
    bool __cdecl CheckAmpSlot(int) const;  // 0x111a0
    bool __cdecl SetAmpSlot(char, int, char);  // 0x11220
    bool __cdecl DrawNewStone(__int64, char, short &);  // 0x11390
    void __cdecl SaveNewStone(char, short);  // 0x11920
    bool __cdecl SetNewStone(void);  // 0x11a80
    void __cdecl AttachAbilities(void);  // 0x11c50
private:
    void __cdecl setAmpSlot(char, int, char);  // 0x11cc0
    void __cdecl setStoneSlot(char, short);  // 0x11ec0
    bool __cdecl isActiveStoneSlot(char) const;  // 0x12030
    void __cdecl attachAbilities(::ChangedProperty &);  // 0x120e0
    void __cdecl detachAbilities(::ChangedProperty &);  // 0x121c0
    void __cdecl attachAbilities(char, ::ChangedProperty &);  // 0x122a0
    void __cdecl detachAbilities(char, ::ChangedProperty &);  // 0x12390
    void __cdecl attachAbility(char, short, ::ChangedProperty &);  // 0x12480
    void __cdecl detachAbility(char, short, ::ChangedProperty &);  // 0x12620
    void __cdecl clearSave(void);  // 0x127c0
};

class SlateContainer
{
public:
    __cdecl ~SlateContainer(void);  // 0x12850
    int __cdecl SetDbData(short, char const *, int);  // 0x128c0
    bool __cdecl ComposePureSync(::FragmentPacket *);  // 0x12d20
    bool __cdecl CheckPcRule(void) const;  // 0x12e10
};

