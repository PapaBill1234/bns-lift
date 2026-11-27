// boardgacha.h: boardgacha.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BoardGacha
{
public:
    __cdecl ~BoardGacha(void);  // 0xb3e0
    bool __cdecl Init(void);  // 0xb4b0
private:
    bool __cdecl setEmptyBoardParticipationInfoPacket(__int64);  // 0xb6e0
    void __cdecl broadcast(::Packet const *);  // 0xb8f0
public:
    bool __cdecl SetSeasonInfoPacketFromNotifyPacket(::FragmentPacket *);  // 0xbac0
    bool __cdecl SendSeasonInfoPacket(::Pc *);  // 0xbb50
    short __cdecl SessionOpen(::Pc *);  // 0xbbd0
    bool __cdecl SessionClose(unsigned __int64, unsigned __int64);  // 0xbe10
    void __cdecl BoardStart(::FragmentPacket *, __int64, int);  // 0xbfc0
    void __cdecl BoardEnd(__int64, int, ::FragmentPacket *);  // 0xc0d0
    void __cdecl ScheduleEnd(void);  // 0xc300
    bool __cdecl SendBoardInfo(::Pc *);  // 0xc3b0
    bool __cdecl SetBoardParticipationInfoPacket(::Packet *);  // 0xc430
    static void __cdecl SendPacketToWorldPc(::Packet const *);  // 0xc4e0
    static void __cdecl PostSessionClose(::Pc *);  // 0xc580
};

class BoardGachaBoardEndWSO
{
public:
    virtual bool __cdecl Initialize(::FragmentPacketConcatenater *);  // 0xd1d0
protected:
    virtual void __cdecl TimerExpired(long);  // 0xd2d0
};

class BoardGachaBoardInfoReqWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0xde70
public:
    static void __cdecl SendFail(::Pc *, short);  // 0xdff0
};

class BoardGachaBoardParticipationInfoNotifyWSO
{
public:
    bool __cdecl Initialize(::FragmentPacketConcatenater *);  // 0xd400
protected:
    virtual void __cdecl TimerExpired(long);  // 0xd790
};

class BoardGachaBoardStartWSO
{
public:
    __cdecl BoardGachaBoardStartWSO(void);  // 0xcc80
    virtual bool __cdecl Initialize(::FragmentPacketConcatenater *);  // 0xccf0
protected:
    bool __cdecl initializeBoardPacket(::FragmentPacketConcatenater *, __int64, __int64);  // 0xce00
    virtual void __cdecl TimerExpired(long);  // 0xd160
};

class BoardGachaRetrieveParticipationInfoAllWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0xe020
public:
    static void __cdecl SendFail(::Pc *, short);  // 0xe200
};

class BoardGachaRetrieveSeasonInfoWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0xd800
public:
    static void __cdecl SendFail(::Pc *, short);  // 0xd9e0
};

class BoardGachaScheduleEndWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0xd370
};

class BoardGachaSessionCloseWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0xdc20
public:
    static void __cdecl SendFail(::Pc *, short);  // 0xde40
};

class BoardGachaSessionOpenWSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0xda10
};

class BoardGachaUpdateSeasonScheduleWSO
{
public:
    bool __cdecl Initialize(::FragmentPacketConcatenater *);  // 0xc6f0
private:
    bool __cdecl initialize(::FragmentPacketConcatenater *);  // 0xc780
protected:
    virtual void __cdecl TimerExpired(long);  // 0xcc10
};

