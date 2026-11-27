// datareaderimpl.cpp: datareaderimpl.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "datareaderimpl.h"
#include "winserviceconsole_gd.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??0DrDataReaderImpl@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1DrDataReaderImpl@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Execute@LoadTableMT_PreProcBinder@@UEAA_NAEAVDrTable@@AEBVXmlReader@@AEBVDrElReader@@AEBUDrLoaderDef@@AEAVDrAliasMap@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Execute@LoadTableMT_PostProcBinder@@UEAA_NAEAVDrTable@@AEBVXmlReader@@AEBVDrElReader@@AEBUDrLoaderDef@@AEAVDrAliasMap@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Execute@LoadTableBinder@@UEAA_NAEAVDrTable@@AEBVXmlReader@@AEBVDrElReader@@AEBUDrLoaderDef@@AEAVDrAliasMap@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?loadTableWorker@@YAIPEAX@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x6eb470
__cdecl DrDataReaderImpl::~DrDataReaderImpl(void)
{
}

// 0x6eb480
void __cdecl DrDataReaderImpl::Close(void)
{
    LIFT_STUB(0x6eb480);
}

// 0x6eb4b0
::DrElReader * __cdecl DrDataReaderImpl::CreateElReader(void)
{
    LIFT_STUB(0x6eb4b0);
}

// 0x6eb500
::DrAliasMap * __cdecl DrDataReaderImpl::CreateAliasMap(void)
{
    LIFT_STUB(0x6eb500);
}

// 0x6eb550
::DrAliasMap * __cdecl DrDataReaderImpl::CreateAliasMapMT(void)
{
    LIFT_STUB(0x6eb550);
}

// 0x6eb5b0
void __cdecl DrDataReaderImpl::ReleaseAliasMapMT(::DrAliasMap *&)
{
    LIFT_STUB(0x6eb5b0);
}

// 0x6eb610
::QuestTable * __cdecl DrDataReaderImpl::CreateQuestTable(void)
{
    LIFT_STUB(0x6eb610);
}

// 0x6eb660
void __cdecl DrDataReaderImpl::ReleaseTable(::DrTable *&)
{
    LIFT_STUB(0x6eb660);
}

// 0x6eb6b0
bool __cdecl DrDataReaderImpl::loadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, bool, ::XmlReader const *)
{
    LIFT_STUB(0x6eb6b0);
}

// 0x6eb860
bool __cdecl XmlPieceAliasReader::Read(::XmlDoc *)
{
    LIFT_STUB(0x6eb860);
}

// 0x6eb9a0
unsigned int __cdecl loadAliasWorker(void *)
{
    LIFT_STUB(0x6eb9a0);
}

// 0x6eba00
bool __cdecl LoadTableMT_PreProcBinder::Execute(::DrTable & table, ::XmlReader const & xmlreader, ::DrElReader const & elreader, ::DrLoaderDef const & loaderdef, ::DrAliasMap & aliasmap)
{
    return table.LoadTableMT_PreProc(xmlreader, elreader, loaderdef, aliasmap);
}

// 0x6eba40
bool __cdecl LoadTableMT_PostProcBinder::Execute(::DrTable & table, ::XmlReader const & xmlreader, ::DrElReader const & elreader, ::DrLoaderDef const & loaderdef, ::DrAliasMap & aliasmap)
{
    return table.LoadTableMT_PostProc(xmlreader, elreader, loaderdef, aliasmap);
}

// 0x6ebac0
bool __cdecl DrDataReaderImpl::ReadBinaryDataFile(wchar_t const *, wchar_t const *, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, unsigned __int64)
{
    LIFT_STUB(0x6ebac0);
}

// 0x6ebb80
bool __cdecl DrDataReaderImpl::ReadBinaryDataFileStream(wchar_t const *, wchar_t const *, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, unsigned __int64)
{
    LIFT_STUB(0x6ebb80);
}

// 0x6ebc40
bool __cdecl DrDataReaderImpl::ReadBinaryDataFileFromMem(unsigned char *, int, ::DrElReader const &, ::DrLoaderDef *, int, bool, ::DrAliasMap &, unsigned __int64)
{
    LIFT_STUB(0x6ebc40);
}

// 0x6ebc90
unsigned int __cdecl loadTableWorker(void * args)
{
    // LIFT: 0x6ebc90. The PDB gives no type for the argument block. The fields follow the six pointer reads of the body.
    struct LoadTableWorkerArgs
    {
        ::DrDataReaderImpl::LoadFuncBinder * binder;
        ::DrTable * table;
        ::XmlReader const * xmlreader;
        ::DrElReader const * elreader;
        ::DrLoaderDef const * loaderdef;
        ::DrAliasMap * aliasmap;
    };
    LoadTableWorkerArgs * a = (LoadTableWorkerArgs *)args;
    return a->binder->Execute(*a->table, *a->xmlreader, *a->elreader, *a->loaderdef, *a->aliasmap);
}

// 0x6ebcd0
void __cdecl DrDataReaderImpl::clearDocument(::XmlReader const &, ::DrXmlDoc &)
{
    LIFT_STUB(0x6ebcd0);
}

// 0x6ebd70
void __cdecl DrDataReaderImpl::createTable(::DrLoaderDef *, bool)
{
    LIFT_STUB(0x6ebd70);
}

// 0x6ebe70
bool __cdecl XmlPieceTableReader::Read(::XmlDoc *)
{
    LIFT_STUB(0x6ebe70);
}

// 0x6ebfb0
__cdecl DrDataReaderImpl::DrDataReaderImpl(void)
{
}

// 0x6ebfc0
void __cdecl DrDataReaderImpl::ReleaseElReader(::DrElReader *&)
{
    LIFT_STUB(0x6ebfc0);
}

// 0x6ec010
void __cdecl DrDataReaderImpl::ReleaseAliasMap(::DrAliasMap *&)
{
    LIFT_STUB(0x6ec010);
}

// 0x6ec060
bool __cdecl DrDataReaderImpl::LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, bool, ::XmlReader const *)
{
    LIFT_STUB(0x6ec060);
}

// 0x6ec0d0
bool __cdecl DrDataReaderImpl::LoadAliasMT(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, void (__cdecl *)(void), bool, ::XmlReader const *)
{
    LIFT_STUB(0x6ec0d0);
}

// 0x6ec450
bool __cdecl LoadTableBinder::Execute(::DrTable & table, ::XmlReader const & xmlreader, ::DrElReader const & elreader, ::DrLoaderDef const & loaderdef, ::DrAliasMap & aliasmap)
{
    table.PrepareLoadTable();
    bool result = table.LoadTable(xmlreader, elreader, loaderdef, aliasmap);
    table.FinishLoadTable(elreader, loaderdef);
    return result;
}

// 0x6ec4c0
bool __cdecl DrDataReaderImpl::loadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, ::DrDataReaderImpl::LoadFuncBinder &)
{
    LIFT_STUB(0x6ec4c0);
}

// 0x6ec590
bool __cdecl DrDataReaderImpl::loadTableMT(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, ::DrDataReaderImpl::LoadFuncBinder &, ::DrDataReaderImpl::LoadFuncBinder &, void (__cdecl *)(void))
{
    LIFT_STUB(0x6ec590);
}

// 0x6ec920
bool __cdecl DrDataReaderImpl::loadTablePieceByPiece(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef &, ::DrAliasMap &, int, bool, ::XmlReader const *)
{
    LIFT_STUB(0x6ec920);
}

// 0x6ecb60
bool __cdecl DrDataReaderImpl::LoadDocument(::XmlReader const &, ::DrLoaderDef *, int, bool *, bool, ::XmlReader const *)
{
    LIFT_STUB(0x6ecb60);
}

// 0x6ed050
bool __cdecl DrDataReaderImpl::Setup(long, ::DrLog *, ::DrMemory *, ::DrMemory *)
{
    LIFT_STUB(0x6ed050);
}

// 0x6ed0f0
bool __cdecl DrDataReaderImpl::LoadAliasPieceByPiece(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, int, bool, ::XmlReader const *)
{
    LIFT_STUB(0x6ed0f0);
}

// 0x6ed400
bool __cdecl DrDataReaderImpl::LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &)
{
    LIFT_STUB(0x6ed400);
}

// 0x6ed450
bool __cdecl DrDataReaderImpl::LoadTableMT(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, void (__cdecl *)(void))
{
    LIFT_STUB(0x6ed450);
}

// 0x6ed4c0
bool __cdecl DrDataReaderImpl::LoadTablePieceByPiece(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, int, bool, ::XmlReader const *)
{
    LIFT_STUB(0x6ed4c0);
}
