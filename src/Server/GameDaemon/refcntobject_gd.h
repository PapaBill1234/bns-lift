// refcntobject_gd.h: refcntobject.cpp, refcntobject.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RelationalRefCntObject
{
protected:
    void __cdecl initRole(void);  // 0x6934a0
    void __cdecl clearRole(void);  // 0x6935c0
public:
    void __cdecl AddChild(::RelationalRefCntObject *, wchar_t const *, int);  // 0x693640
protected:
    void __cdecl removeChild(::RelationalRefCntObject *, wchar_t const *, int);  // 0x693800
    void __cdecl removeParent(wchar_t const *, int);  // 0x6939a0
private:
    void __cdecl remove_child(::RelationalRefCntObject *, wchar_t const *, int);  // 0x693a60
    virtual void __cdecl deallocate_object(wchar_t const *, int);  // 0x693ae0
};

