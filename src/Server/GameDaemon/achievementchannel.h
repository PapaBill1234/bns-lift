// achievementchannel.h: achievementchannel.cpp, achievementchannel.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AchievementDaemonChannel
{
public:
    virtual __cdecl ~AchievementDaemonChannel(void);  // 0x32da0
    bool __cdecl InitSession(void);  // 0x32db0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x32f00
protected:
    virtual bool __cdecl onConnect(::Session const *, bool);  // 0x32f90
    virtual void __cdecl onClose(::Session const *, bool, bool);  // 0x33020
public:
    bool __cdecl IsConnected(void);  // 0x33110
    void __cdecl SendLoginAllPc(void);  // 0x33190
    bool __cdecl SendPing(void);  // 0x33340
    void __cdecl CheckPing(void);  // 0x33400
    void __cdecl Destroy(void);  // 0xa7870
protected:
    virtual ::Session * __cdecl getSession(void);  // 0x180c20
};

bool __cdecl HandleAchievementGameGameHelloOk(::Session const *, ::Packet const *);  // 0x334c0
bool __cdecl HandleAchievementGameGameHelloFail(::Session const *, ::Packet const *);  // 0x33520
bool __cdecl HandleAchievementGameGameUpdateDataNotify(::Session const *, ::Packet const *);  // 0x33590
bool __cdecl HandleAchievementGameGameCompleteTakeRewardOk(::Session const *, ::Packet const *);  // 0x33ae0
bool __cdecl HandleAchievementGameGameCompleteTakeRewardFail(::Session const *, ::Packet const *);  // 0x33d90
bool __cdecl HandleAchievementGameGamePingOk(::Session const *, ::Packet const *);  // 0x34030
bool __cdecl HandleAchievementGameGameLogAchievementStepCompleteNotify(::Session const *, ::Packet const *);  // 0x340e0
bool __cdecl HandleAchievementGameGameLogAchievementRegisterResetNotify(::Session const *, ::Packet const *);  // 0x34440
