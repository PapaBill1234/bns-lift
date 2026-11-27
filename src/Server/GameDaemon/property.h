// property.h: property.cpp, property.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class Property
{
public:
    bool __cdecl Set(unsigned short, bool);  // 0xe230
    bool __cdecl GetFlag(unsigned short) const;  // 0x1d120
    bool __cdecl Set(unsigned short, wchar_t const *);  // 0x8c2b0
    bool __cdecl Set(unsigned short, unsigned char const *, short);  // 0x1ed800
    virtual __cdecl ~Property(void);  // 0x688a70
protected:
    void __cdecl self(unsigned __int64);  // 0x688b50
    void __cdecl init(::Property const *, unsigned __int64);  // 0x688ce0
public:
    bool __cdecl SetZero(unsigned char);  // 0x688ee0
    bool __cdecl Set(unsigned short, __int64, __int64, __int64, short);  // 0x689080
    bool __cdecl Set(unsigned short, ::f_flag8::Operation);  // 0x689240
private:
    bool __cdecl set(unsigned short, __int64, bool, bool *);  // 0x689320
    bool __cdecl set(unsigned short, ::id128 const *, bool, bool *);  // 0x6894e0
    bool __cdecl set(unsigned short, bool, bool, bool *);  // 0x689640
    bool __cdecl set(unsigned short, wchar_t const *, short, bool, bool *);  // 0x689740
    bool __cdecl set(unsigned short, unsigned char const *, short, bool, bool *);  // 0x689910
    bool __cdecl set(unsigned short, int, short, int, bool, bool *);  // 0x689af0
    bool __cdecl set(char const *, unsigned __int64, bool, bool, unsigned __int64 *, bool *);  // 0x689c70
    void __cdecl updateSync(::Field::Def const *, __int64, bool, bool *);  // 0x689f50
    void __cdecl updateSync(unsigned short, ::Field::Def const *const, bool, bool, bool *);  // 0x68a2e0
public:
    bool __cdecl Get(unsigned short, bool *) const;  // 0x68a700
    bool __cdecl Get(unsigned short, wchar_t *, unsigned __int64 *) const;  // 0x68a7c0
    bool __cdecl GetPureData(unsigned short, void *, unsigned __int64 *, bool) const;  // 0x68a880
    bool __cdecl GetPairData(unsigned short, void *, unsigned __int64 *, bool) const;  // 0x68ac60
private:
    bool __cdecl get(unsigned short, void *, unsigned __int64) const;  // 0x68ad50
    void __cdecl makeWhere(::Field::Def const *, __int64);  // 0x68af20
protected:
    static bool __cdecl initInstance(int, int, ::FieldDef const *const, int, ::SyncDef *const, int *, ::Field::Def **, int *, ::SyncBuffer::Def **);  // 0x68afb0
private:
    static ::Field::Def * __cdecl initFieldDefine(int, ::FieldDef const *const, int, void *);  // 0x68b100
    static unsigned short __cdecl findMaxId(int, ::FieldDef const *const);  // 0x68b510
    static short __cdecl initBitfield(int, ::FieldDef const *const, int, ::Field::Def *const, unsigned short, void *);  // 0x68b610
    static ::SyncBuffer::Def * __cdecl initSyncDefine(int, ::SyncDef const *const, int, bool, int, ::Field::Def *const, void *);  // 0x68b770
    static unsigned char __cdecl findMaxId(int, ::SyncDef const *const);  // 0x68ba10

    // PDB data members (size 0x30).
private:
    ::SyncBuffer * buffer[4];      // +0x08
    ::QueryString * whereClause;   // +0x28
};

