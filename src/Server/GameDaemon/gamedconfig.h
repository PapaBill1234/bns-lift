// gamedconfig.h: gamedconfig.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GamedConfig
{
public:
    static ::GamedConfig * __cdecl Load(void);  // 0x343940
    void __cdecl Reload(void);  // 0x343a20
    static void __cdecl Destroy(::GamedConfig *);  // 0x343f20
private:
    void __cdecl setPerfGeoZone(wchar_t const *);  // 0x343ff0
    void __cdecl setSkipActionPacketList(wchar_t const *);  // 0x344290
    void __cdecl setZoneRecommendPcCount(wchar_t const *, bool);  // 0x345cb0
protected:
    void __cdecl setExceptLastChangedPropertyList(wchar_t const *);  // 0x346060
public:
    bool __cdecl UsePerfGeoZone(::GeoZone const *) const;  // 0x346250

    // PDB data members (partial layout, size 0x660).
private:
    char _liftGamedConfigPad0[0xED];            // LIFT: members before _arenaEnabled, later waves
public:
    bool _arenaEnabled;                         // +0xED
private:
    char _liftGamedConfigPad1[0xF8 - 0xEE];     // LIFT: members, later waves
public:
    int _arenaId;                               // +0xF8
private:
    char _liftGamedConfigTail[0x660 - 0xFC];    // LIFT: members after _arenaId, later waves
};
static_assert(sizeof(GamedConfig) == 0x660, "sizeof GamedConfig");

