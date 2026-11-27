// serializertimer.h: serializertimer.cpp, serializertimer.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class SerializerTimer
{
protected:
    virtual bool __cdecl HandleEvent(::EventContext *, unsigned long);  // 0x662ca0
    __cdecl SerializerTimer(void);  // 0x665e20
    virtual __cdecl ~SerializerTimer(void);  // 0x665fa0
    bool __cdecl Initialize(::Serializer *, int);  // 0x6660d0
    virtual unsigned __int64 __cdecl TimerId(void) const;  // 0x666180
private:
    virtual void __cdecl preprocessExpireEvent(void);  // 0x666190
    bool __cdecl timerExpired(void);  // 0x666200
protected:
    bool __cdecl Add(::SerializedObject *, long);  // 0x666760
public:
    bool __cdecl AddEvent(unsigned int, long);  // 0x6668c0
protected:
    bool __cdecl Remove(::SerializedObject *);  // 0x6669b0
    void __cdecl Clear(void);  // 0x666ac0
private:
    void __cdecl add(::SerializedObject *);  // 0x666bc0
    bool __cdecl stop(void);  // 0x666cf0
    void __cdecl addGlobalTimer(long, ::SerializedObjectQueue *);  // 0x666ed0
public:
    void __cdecl dump(void);  // 0x666f90
};

class TimerSlotList
{
protected:
    __cdecl ~TimerSlotList(void);  // 0x665a40
    void __cdecl Initialize(int, ::Serializer *);  // 0x665ae0
    ::SerializedObjectQueue * __cdecl Add(::SerializedObject *, long);  // 0x665bf0
    void __cdecl Clear(void);  // 0x665d20
};

class TimerSlotVector
{
protected:
    __cdecl ~TimerSlotVector(void);  // 0x665000
    void __cdecl Initialize(int, ::Serializer *);  // 0x665050
    ::SerializedObjectQueue * __cdecl Add(::SerializedObject *, int, int);  // 0x665100
    ::SerializedObjectQueue * __cdecl Add(::SerializedObjectQueue *, ::SerializedObjectQueue *);  // 0x665510
    ::SerializedObjectQueue * __cdecl AddEvent(unsigned int, int, int);  // 0x665610
    int __cdecl Expire(int, ::SerializedObjectQueue *, bool);  // 0x6656b0
};

