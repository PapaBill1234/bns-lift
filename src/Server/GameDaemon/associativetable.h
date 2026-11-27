// associativetable.h: associativetable.cpp, associativetable.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "tableimpl.h"
#include <map>

// PDB layout (size 0x40): vfptr, elMap +8, reconstructed +40, elArray +48, elCount +56.
// LIFT: the virtual order is not yet the PDB order (clearLink, construct, set, get, count). No body of this card calls them through the vtable.
struct DrMultiKeyElMap
{
public:
    struct MultiKeyArrayElement
    {
        unsigned __int64 key;
        ::DrEl * node;
    };
    // LIFT: the PDB type is std::map<unsigned __int64, DrEl*, std::less<unsigned __int64>, DrStlAllocator<std::pair<unsigned __int64, DrEl*>, 1> >.
    // DrStlAllocator is not a full allocator yet. The VS2010 std::map with std::allocator has the same layout (size 0x20).
    typedef std::map<unsigned __int64, ::DrEl *> ElPtrMap;
public:
    virtual int __cdecl count(void);  // 0x6fb440
    void __cdecl reconstruct(void);  // 0x6fc130
    void __cdecl destroy(void);  // 0x6fc2e0
    __cdecl ~DrMultiKeyElMap(void);  // 0x6fc870
    virtual ::DrEl *const __cdecl get(unsigned __int64) const;  // 0x6fcd10
    virtual ::DrEl * __cdecl set(unsigned __int64, ::DrEl *, bool);  // 0x6fd0f0
public:
    ElPtrMap elMap;
    bool reconstructed;
    MultiKeyArrayElement * elArray;
    int elCount;
};

// PDB layout (size 0x18): base DrInnerIter, elArray +8, it +16, elCount +20.
class DrMultiKeyInnerIter : public DrInnerIter
{
private:
    virtual ::DrEl * __cdecl Ptr(void);  // 0x6fb130
    virtual bool __cdecl Next(void);  // 0x6fb170
    virtual bool __cdecl IsValid(void);  // 0x6fb180
private:
    DrMultiKeyElMap::MultiKeyArrayElement * elArray;
    int it;
    int elCount;
};

// PDB layout (size 0x70): base DrDataTableImpl (size 0x18), _elMap +24.
class DrMultiKeyTable : public DrDataTableImpl
{
    DrMultiKeyElMap _elMap;
    char * _tableBuffer;
    char * _tableExtraBuffer;
    int _tableSize;
    int _tableExtraSize;
public:
    virtual bool __cdecl LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6fb1a0
    virtual void __cdecl GetTableSummary(::DrTableSummary &);  // 0x6fb280
    virtual ::DrEl *const __cdecl Find(unsigned __int64) const;  // 0x6fb330
private:
    virtual ::DrInnerIter * __cdecl createInnerIter(::DrEl *const) const;  // 0x6fb340
    virtual void __cdecl removeInnerIter(::DrInnerIter *) const;  // 0x6fb3f0
    virtual ::DrInnerIter * __cdecl createInnerIter(void) const;  // 0x6fb490
    bool __cdecl setup(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &);  // 0x6fb9f0
public:
    virtual bool __cdecl LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6fbc00
    virtual bool __cdecl LoadTableMT_PreProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6fbe40
    virtual bool __cdecl LoadTableMT_PostProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6fc060
private:
    void __cdecl clearElMap(void);  // 0x6fc370
    void __cdecl constructExtraBuffer(::DrElReader const &, ::DrLoaderDef const &);  // 0x6fc3f0
public:
    virtual void __cdecl FinishLoadTable(::DrElReader const &, ::DrLoaderDef const &);  // 0x6fc5c0
    virtual void __cdecl PrepareLoadTable(void);  // 0x6fc630
    virtual bool __cdecl ReadFromBuffer(::DrElReader const &, ::DrLoaderDef const &, unsigned char const *, unsigned __int64);  // 0x6fc640
    __cdecl DrMultiKeyTable(void);  // 0x6fd210
};

