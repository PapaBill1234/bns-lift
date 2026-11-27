// controlledcreature.h: controlledcreature.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ControlledCreature
{
public:
    __cdecl ControlledCreature(void);  // 0x5d28e0
    virtual __cdecl ~ControlledCreature(void);  // 0x5d2980
    bool __cdecl Initialize(unsigned __int64);  // 0x5d2a80
    virtual void __cdecl EnterZone(::EnterReason, bool, unsigned int);  // 0x5d2c50
    virtual void __cdecl LeaveZone(::LeaveReason);  // 0x5d2ca0
    bool __cdecl AddPrivateProperty(char, short, char *, short);  // 0x5d2eb0
    virtual void __cdecl SendChangedPrivateProperty(void);  // 0x5d2fe0
    bool __cdecl AddActionPrivate(char const *, short);  // 0x5d30a0
    virtual void __cdecl SendActionPrivatePacket(void);  // 0x5d31c0
    bool __cdecl SaveMove(::vector16, ::GeoCell const *, short, char const *const, int, long, short, ::MoveTypeList *);  // 0x5d3280
    bool __cdecl MergeMove(::vector16, ::GeoCell const *, short, char const *const, int, long, short, ::MoveTypeList *);  // 0x5d33d0
    void __cdecl BroadcastLastMove(void);  // 0x5d36a0
private:
    void __cdecl mergeMoveTypeEnd(::LastMove *);  // 0x5d37a0
    ::MoveType __cdecl convertMoveType(::MoveType);  // 0x5d3a20
public:
    bool __cdecl SetMoveTimeStamp(__int64, long);  // 0x5d3b40
    void __cdecl EnterAttraction(::EnterReason, unsigned int);  // 0x5d3be0
private:
    void __cdecl attachAttractionEffect(::dr_tref);  // 0x5d3fa0
};

class MoveHackChecker
{
public:
    bool __cdecl Initialize(void);  // 0x5d42c0
    bool __cdecl Check(long, unsigned __int64, wchar_t const *);  // 0x5d43a0
    void __cdecl OnTimer(::Pc *);  // 0x5d4500
    static bool __cdecl GetFailCountListString(::Pc *, wchar_t *, int);  // 0x5d47b0
};

