// aliasimpl.h: aliasimpl.cpp, aliasimpl.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DrAliasMapImpl
{
public:
    struct AliasArrayElement {};
public:
    virtual bool __cdecl WriteToBuffer(unsigned char *, unsigned __int64);  // 0x6f33a0
    virtual int __cdecl Count(void) const;  // 0x6f3610
    virtual bool __cdecl ReplaceIfChanged(wchar_t const *, ::DrAliasMap const &);  // 0x6f3630
    virtual bool __cdecl IsSubsetOf(wchar_t const *, ::DrAliasMap const &) const;  // 0x6f3c70
    virtual void __cdecl InsertInto(::DrAliasMap &) const;  // 0x6f3df0
private:
    void __cdecl clearElArray(void);  // 0x6f4280
    void __cdecl allocElArray(int);  // 0x6f4490
public:
    virtual bool __cdecl Find(wchar_t const *, unsigned __int64 *) const;  // 0x6f4860
private:
    void __cdecl rebuildElArray(void);  // 0x6f4a90
    void __cdecl clearTableFromAliasMap(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> >, ::DrStlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> >, 1> > const &);  // 0x6f5780
public:
    virtual void __cdecl Reconstruct(void);  // 0x6f5b30
    virtual bool __cdecl Insert(wchar_t const *, unsigned __int64);  // 0x6f5d50
    virtual void __cdecl Clear(void);  // 0x6f5f40
    virtual bool __cdecl ReadFromBuffer(unsigned char const *, unsigned __int64, unsigned __int64, bool);  // 0x6f5fa0
    __cdecl ~DrAliasMapImpl(void);  // 0x6f6320
    __cdecl DrAliasMapImpl(void);  // 0x6f6450
    virtual void __cdecl ClearTable(wchar_t const *, bool);  // 0x6f6490
};

class DrAliasStringTable
{
public:
    void __cdecl Clear(void);  // 0x6f33b0
    bool __cdecl Find(wchar_t const *, unsigned __int64 *) const;  // 0x6f3430
private:
    void __cdecl construct(int);  // 0x6f36d0
public:
    bool __cdecl ReadFromBuffer(unsigned char const *, unsigned __int64, unsigned __int64, bool);  // 0x6f3900
    bool __cdecl Build(::DrAliasMapImpl::AliasArrayElement const *, int);  // 0x6f3a10
};

struct ci_wchar_traits
{
public:
    static int __cdecl compare(wchar_t const *, wchar_t const *, unsigned __int64);  // 0x6f3310
};

