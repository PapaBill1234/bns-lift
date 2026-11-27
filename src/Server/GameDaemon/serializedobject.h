// serializedobject.h: serializedobject.cpp, serializedobject.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LtExpireSO
{
protected:
    virtual void __cdecl TimerExpired(long);  // 0x4307b0
};

class SerializedObject
{
public:
    virtual __cdecl ~SerializedObject(void);  // 0x663090
protected:
    void __cdecl Set(::Serializer *, long);  // 0x6630c0
public:
    static void __cdecl CheckValid(::SerializedObject *, ::SerializedObject *, ::SerializedObjectQueue *, ::SourceLocation const &);  // 0x663ba0
};

class SerializedObjectHistory
{
private:
    bool __cdecl add(::SerializedObjectQueue *, ::SerializedObjectQueue *, wchar_t const *, int);  // 0x662cb0
    void __cdecl dump(::SerializedObject *);  // 0x662da0
};

class SerializedObjectQueue
{
protected:
    __cdecl ~SerializedObjectQueue(void);  // 0x6631a0
public:
    static wchar_t const * __cdecl GetQueueTypeString(char);  // 0x6632b0
protected:
    bool __cdecl Add(::SerializedObject *);  // 0x663340
    bool __cdecl Add(::SerializedObjectQueue *, bool);  // 0x6635d0
    bool __cdecl Remove(::SerializedObject *);  // 0x6637f0
public:
    ::SerializedObject * __cdecl Clear(bool);  // 0x663930
    ::SerializedObject * __cdecl DetachList(void);  // 0x663a80
};

