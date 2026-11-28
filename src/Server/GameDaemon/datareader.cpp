// datareader.cpp: datareader.cpp (GameDaemon PDB, 2019 + PDB).
#include "datareader.h"
#include "datareaderimpl.h"
#include "defmemory.h"
#include "LiftStub.h"
#include <new>

// LIFT: keep the lifted functions until the callers are lifted (the callers are stubs; /OPT:REF drops them). Card lift-gamedaemon-gap-005-e5.
#pragma comment(linker, "/INCLUDE:?GetDataReaderInterfaceVersion@@YAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Logger@@YAPEAVDrLog@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetupDataReader@@YA_NJPEAVDrLog@@PEAVDrMemory@@1@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CloseDataReader@@YAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CreateDataReader@@YAPEAVDrDataReader@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ReleaseDataReader@@YAXAEAPEAVDrDataReader@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x6eb2a0
wchar_t const * __cdecl GetDataReaderInterfaceVersion(void)
{
    return L"34";
}

// 0x6eb2b0
bool __cdecl SetupDataReader(long timerInterval, ::DrLog * logger, ::DrMemory * staticMem, ::DrMemory * dynamicMem)
{
    return DrDataReaderImpl::Setup(timerInterval, logger, staticMem, dynamicMem);
}

// 0x6eb2c0
void __cdecl CloseDataReader(void)
{
    DrDataReaderImpl::Close();
}

// 0x6eb2d0
::DrDataReader * __cdecl CreateDataReader(void)
{
    // LIFT: DrDataReaderImpl has no DrDataReader base yet, so the cast is a reinterpret_cast.
    void * mem = DrMemoryManager::Memory(DrMemoryManager::SECTION_STATIC)->Alloc(sizeof(DrDataReaderImpl), L"src\\DataReader.cpp", 74);
    return reinterpret_cast< ::DrDataReader *>(new (mem) DrDataReaderImpl());
}

// 0x6eb320
::DrLog * __cdecl Logger(void)
{
    return DrDataReaderImpl::_logger;
}

// 0x6eb330
void __cdecl ReleaseDataReader(::DrDataReader *& reader)
{
    DrDataReaderImpl * impl = reinterpret_cast<DrDataReaderImpl *>(reader);
    impl->~DrDataReaderImpl();
    DrMemoryManager::Memory(DrMemoryManager::SECTION_STATIC)->Free(impl, L"src\\DataReader.cpp", 81);
    reader = nullptr;
}

// LIFT: definition of the PDB static data member DrDataReaderImpl::_logger (set by DrDataReaderImpl::Setup, a later card).
::DrLog * DrDataReaderImpl::_logger;
