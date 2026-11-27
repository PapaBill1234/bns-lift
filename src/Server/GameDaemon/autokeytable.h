// autokeytable.h: autokeytable.cpp, autokeytable.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "tableimpl.h"
#include <vector>

// PDB layout (size 0x28): elArray +0, elCount +32.
struct DrAutoKeyElMap
{
public:
    // LIFT: the PDB type is std::vector<DrEl*, DrStlAllocator<DrEl*, 0> >. DrStlAllocator is not a full allocator yet.
    // The VS2010 std::vector with std::allocator has the same layout (_Myfirst, _Mylast, _Myend, _Alval; size 0x20).
    typedef std::vector< ::DrEl *> ElPtrArray;
public:
    void __cdecl destroy(void);  // 0x6fda40
    __cdecl ~DrAutoKeyElMap(void);  // 0x6fdb30
    void __cdecl construct(unsigned __int64);  // 0x6fe150
public:
    ElPtrArray elArray;
    unsigned __int64 elCount;
};

// PDB layout (size 0x20): base DrInnerIter, elPtrArray +8, beginIndex +16, index +20, elCount +24.
class DrAutoKeyInnerIter : public DrInnerIter
{
private:
    virtual bool __cdecl IsValid(void);  // 0x6fd300
    virtual ::DrEl * __cdecl Ptr(void);  // 0x6fd450
    virtual bool __cdecl Next(void);  // 0x6fd480
private:
    DrAutoKeyElMap::ElPtrArray const * elPtrArray;
    int beginIndex;
    int index;
    int elCount;
};

// PDB layout (size 0x60): base DrDataTableImpl (size 0x18), _elMap +24.
class DrAutoKeyTable : public DrDataTableImpl
{
    DrAutoKeyElMap _elMap;
    char * _tableBuffer;
    char * _tableExtraBuffer;
    int _tableSize;
    int _tableExtraSize;
    unsigned __int64 _nextAutoKey;
public:
    virtual bool __cdecl LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6fd320
    virtual void __cdecl FinishLoadAlias(void);  // 0x6fd410
private:
    void __cdecl constructExtraBuffer(::DrElReader const &, ::DrLoaderDef const &, bool);  // 0x6fd4c0
public:
    virtual void __cdecl FinishLoadTable(::DrElReader const &, ::DrLoaderDef const &);  // 0x6fd620
    virtual bool __cdecl LoadTableMT_PostProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6fd630
    virtual void __cdecl GetTableSummary(::DrTableSummary &);  // 0x6fd6c0
    virtual ::DrEl *const __cdecl Find(unsigned __int64) const;  // 0x6fd790
private:
    virtual ::DrInnerIter * __cdecl createInnerIter(::DrEl *const) const;  // 0x6fd7b0
    virtual void __cdecl removeInnerIter(::DrInnerIter *) const;  // 0x6fd8d0
    virtual ::DrInnerIter * __cdecl createInnerIter(void) const;  // 0x6fd920
    void __cdecl clearElMap(void);  // 0x6fdab0
public:
    virtual void __cdecl PrepareLoadTable(void);  // 0x6fdf80
    __cdecl DrAutoKeyTable(void);  // 0x6fe030
    virtual __cdecl ~DrAutoKeyTable(void);  // 0x6fe090
private:
    bool __cdecl setup(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &);  // 0x6fe220
public:
    virtual bool __cdecl LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6fe3d0
    virtual bool __cdecl LoadTableMT_PreProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6fe600
    virtual bool __cdecl ReadFromBuffer(::DrElReader const &, ::DrLoaderDef const &, unsigned char const *, unsigned __int64);  // 0x6fe7f0
};

