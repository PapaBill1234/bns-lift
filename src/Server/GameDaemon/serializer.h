// serializer.h: serializer.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class SerializedObjectList
{
private:
    bool __cdecl grow(void);  // 0x664ec0
};

class Serializer
{
public:
    virtual __cdecl ~Serializer(void);  // 0x663e00
    void __cdecl dump(void);  // 0x663ed0
    ::SerializedObjectQueue * __cdecl GetNextExpire(void);  // 0x664020
    bool __cdecl Initialize(unsigned __int64, long, long);  // 0x664090
    // PDB: public, inlined (no RVA).
    unsigned __int64 Id() const { return _id; }
protected:
    void __cdecl execute(long, ::SerializedObjectQueue *, unsigned int *);  // 0x664280
public:
    bool __cdecl Post(::SerializedObject *, long);  // 0x664d10
protected:
    bool __cdecl post(::SerializedObject *);  // 0x664d80
private:
    // LIFT: Serializer has only part of its PDB members yet (size 0x98).
    unsigned __int64 _id;  // +8
    long _interval;  // +16
    ::SerializerTimer *_timer;  // +24
};
