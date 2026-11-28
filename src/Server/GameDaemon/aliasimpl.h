// aliasimpl.h: aliasimpl.cpp, aliasimpl.h (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"
#include "defmemory.h"
#include "drstlmemory.h"
#include <cwctype>
#include <map>
#include <string>
#include <vector>

// PDB layout (size 0x1): base std::char_traits<wchar_t>. Case-insensitive traits.
struct ci_wchar_traits : public std::char_traits<wchar_t>
{
public:
    // ❓ eq, ne, lt and find are inlined in the 2019 build. The bodies follow compare (towupper).
    static bool __cdecl eq(wchar_t const c1, wchar_t const c2) { return towupper(c1) == towupper(c2); }
    static bool __cdecl ne(wchar_t const c1, wchar_t const c2) { return towupper(c1) != towupper(c2); }
    static bool __cdecl lt(wchar_t const c1, wchar_t const c2) { return towupper(c1) < towupper(c2); }
    static int __cdecl compare(wchar_t const *, wchar_t const *, unsigned __int64);  // 0x6f3310
    static wchar_t const * __cdecl find(wchar_t const * s, unsigned __int64 n, wchar_t const & a)
    {
        for (; n != 0; --n, ++s)
        {
            if (towupper(*s) == towupper(a))
                return s;
        }
        return nullptr;
    }
};

class DrAliasStringTable;

// PDB layout (size 0x48): base DrAliasMap +0, _aliasmap +8.
// LIFT: the class has no DrAliasMap base yet. WriteSize and Print (vtable slots 7 and 12) have no body in this card.
// The own vfptr keeps the member offsets of the PDB.
class DrAliasMapImpl
{
public:
    // PDB layout (size 0x30): alias +0, key +40.
    struct AliasArrayElement
    {
        AliasArrayElement() : key(0) {}
        std::basic_string<wchar_t, ci_wchar_traits, DrStlAllocator<wchar_t, 1> > alias;
        unsigned __int64 key;
    };
    typedef std::map<std::basic_string<wchar_t, ci_wchar_traits, DrStlAllocator<wchar_t, 1> >, unsigned __int64, std::less<std::basic_string<wchar_t, ci_wchar_traits, DrStlAllocator<wchar_t, 1> > >, DrStlAllocator<std::pair<std::basic_string<wchar_t, ci_wchar_traits, DrStlAllocator<wchar_t, 1> >, unsigned __int64>, 1> > Map;
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
private:
    Map _aliasmap;
    bool _reconstructed;
    bool _useStringTable;
    ::DrAliasStringTable * _stringTable;
    ::DrAliasMapImpl::AliasArrayElement * _elArray;
    int _elCount;
};

// PDB layout (size 0x20): _elCount +0, _elArray +8, _stringTable +16, _stringTableSize +24.
class DrAliasStringTable
{
public:
    // PDB layout (size 0x10): key +0, alias +8.
    struct ArrayElement
    {
        ArrayElement() : key(0), alias(nullptr) {}
        unsigned __int64 key;
        char * alias;
    };
public:
    int Count() const { return _elCount; }
    void __cdecl Clear(void);  // 0x6f33b0
    bool __cdecl Find(wchar_t const *, unsigned __int64 *) const;  // 0x6f3430
private:
    void __cdecl construct(int);  // 0x6f36d0
public:
    bool __cdecl ReadFromBuffer(unsigned char const *, unsigned __int64, unsigned __int64, bool);  // 0x6f3900
    bool __cdecl Build(::DrAliasMapImpl::AliasArrayElement const *, int);  // 0x6f3a10
private:
    int _elCount;
    ::DrAliasStringTable::ArrayElement * _elArray;
    char * _stringTable;
    int _stringTableSize;
};
