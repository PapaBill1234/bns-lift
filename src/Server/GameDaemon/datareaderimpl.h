// datareaderimpl.h: datareaderimpl.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DrDataReaderImpl
{
public:
    // LIFT: slot 0 dtor, slot 1 Execute (loadTableWorker calls slot 1). The binders below do not derive from it yet.
    // Nothing constructs it, so the dtor has no definition here.
    struct LoadFuncBinder
    {
        virtual __cdecl ~LoadFuncBinder(void);
        virtual bool __cdecl Execute(::DrTable &, ::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &) = 0;
    };
public:
    __cdecl ~DrDataReaderImpl(void);  // 0x6eb470
    static void __cdecl Close(void);  // 0x6eb480
    virtual ::DrElReader * __cdecl CreateElReader(void);  // 0x6eb4b0
    virtual ::DrAliasMap * __cdecl CreateAliasMap(void);  // 0x6eb500
    virtual ::DrAliasMap * __cdecl CreateAliasMapMT(void);  // 0x6eb550
    virtual void __cdecl ReleaseAliasMapMT(::DrAliasMap *&);  // 0x6eb5b0
    virtual ::QuestTable * __cdecl CreateQuestTable(void);  // 0x6eb610
    virtual void __cdecl ReleaseTable(::DrTable *&);  // 0x6eb660
    bool __cdecl loadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, bool, ::XmlReader const *);  // 0x6eb6b0
    virtual bool __cdecl ReadBinaryDataFile(wchar_t const *, wchar_t const *, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, unsigned __int64);  // 0x6ebac0
    virtual bool __cdecl ReadBinaryDataFileStream(wchar_t const *, wchar_t const *, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, unsigned __int64);  // 0x6ebb80
    virtual bool __cdecl ReadBinaryDataFileFromMem(unsigned char *, int, ::DrElReader const &, ::DrLoaderDef *, int, bool, ::DrAliasMap &, unsigned __int64);  // 0x6ebc40
private:
    void __cdecl clearDocument(::XmlReader const &, ::DrXmlDoc &);  // 0x6ebcd0
    void __cdecl createTable(::DrLoaderDef *, bool);  // 0x6ebd70
public:
    __cdecl DrDataReaderImpl(void);  // 0x6ebfb0
    virtual void __cdecl ReleaseElReader(::DrElReader *&);  // 0x6ebfc0
    virtual void __cdecl ReleaseAliasMap(::DrAliasMap *&);  // 0x6ec010
    virtual bool __cdecl LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, bool, ::XmlReader const *);  // 0x6ec060
    virtual bool __cdecl LoadAliasMT(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, void (__cdecl *)(void), bool, ::XmlReader const *);  // 0x6ec0d0
private:
    bool __cdecl loadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, ::DrDataReaderImpl::LoadFuncBinder &);  // 0x6ec4c0
    bool __cdecl loadTableMT(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, ::DrDataReaderImpl::LoadFuncBinder &, ::DrDataReaderImpl::LoadFuncBinder &, void (__cdecl *)(void));  // 0x6ec590
    bool __cdecl loadTablePieceByPiece(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef &, ::DrAliasMap &, int, bool, ::XmlReader const *);  // 0x6ec920
public:
    virtual bool __cdecl LoadDocument(::XmlReader const &, ::DrLoaderDef *, int, bool *, bool, ::XmlReader const *);  // 0x6ecb60
    static bool __cdecl Setup(long, ::DrLog *, ::DrMemory *, ::DrMemory *);  // 0x6ed050
    virtual bool __cdecl LoadAliasPieceByPiece(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, int, bool, ::XmlReader const *);  // 0x6ed0f0
    virtual bool __cdecl LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &);  // 0x6ed400
    virtual bool __cdecl LoadTableMT(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, void (__cdecl *)(void));  // 0x6ed450
    virtual bool __cdecl LoadTablePieceByPiece(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, int, bool, ::XmlReader const *);  // 0x6ed4c0
    // LIFT: PDB static data member (read by Logger at 0x6eb320). Defined in datareader.cpp.
    static ::DrLog * _logger;
};

struct LoadTableBinder
{
public:
    virtual __cdecl ~LoadTableBinder(void);  // 0x6eba80
    virtual bool __cdecl Execute(::DrTable &, ::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6ec450
};

struct LoadTableMT_PostProcBinder
{
public:
    virtual bool __cdecl Execute(::DrTable &, ::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6eba40
};

struct LoadTableMT_PreProcBinder
{
public:
    virtual bool __cdecl Execute(::DrTable &, ::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6eba00
};

class XmlPieceAliasReader
{
public:
    virtual bool __cdecl Read(::XmlDoc *);  // 0x6eb860
};

class XmlPieceTableReader
{
public:
    virtual bool __cdecl Read(::XmlDoc *);  // 0x6ebe70
};

unsigned int __cdecl loadAliasWorker(void *);  // 0x6eb9a0
unsigned int __cdecl loadTableWorker(void *);  // 0x6ebc90
