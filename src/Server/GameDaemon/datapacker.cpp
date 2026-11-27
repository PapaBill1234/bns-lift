// datapacker.cpp: datapacker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "datapacker.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Next@ZipPackedReaderIO@@UEAA?AW4ErrCode@XmlReaderIO@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Close@ZipPackedReaderIO@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x153d0
__cdecl ZipPackedReaderIO::FileName::FileName(char const *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned int)
{
    LIFT_STUB(0x153d0);
}

// 0x154f0
__cdecl ZipPackedReaderIO::~ZipPackedReaderIO(void)
{
    LIFT_STUB(0x154f0);
}

// 0x15580
bool __cdecl ZipPackedReaderIO::OpenZip(wchar_t const *)
{
    LIFT_STUB(0x15580);
}

// 0x15860
bool __cdecl ZipPackedReaderIO::Verify(char *, unsigned __int64)
{
    LIFT_STUB(0x15860);
}

// 0x16290
void __cdecl ZipPackedReaderIO::CloseZip(void)
{
    LIFT_STUB(0x16290);
}

// 0x16330
::XmlReaderIO::ErrCode __cdecl ZipPackedReaderIO::Open(wchar_t const *, wchar_t const *, bool)
{
    LIFT_STUB(0x16330);
}

// 0x169a0
::XmlReaderIO::ErrCode __cdecl ZipPackedReaderIO::Read(unsigned char *, unsigned int *) const
{
    LIFT_STUB(0x169a0);
}

// 0x16b60
// LIFT: Not done. Needs the GameDaemon forms of AlertSender::writev2 / Log::Write (shared card s2).
unsigned int __cdecl ZipPackedReaderIO::GetFileSize(void) const
{
    LIFT_STUB(0x16b60);
}

// 0x16bd0
// LIFT: Not done. Needs the GameDaemon forms of AlertSender::writev2 / Log::Write (shared card s2).
wchar_t const * __cdecl ZipPackedReaderIO::GetFileName(void) const
{
    LIFT_STUB(0x16bd0);
}

// 0x16c40
::XmlReaderIO::ErrCode __cdecl ZipPackedReaderIO::Next(void)
{
    // ❓ The PDB has no enumerators for XmlReaderIO::ErrCode. 3 is the end of the list, 0 is success.
    if (_openFileIdx < 0 || _openFileArray.size() <= (unsigned __int64)(_openFileIdx + 1))
        return (::XmlReaderIO::ErrCode)3;
    ++_openFileIdx;
    return (::XmlReaderIO::ErrCode)0;
}

// 0x16c70
void __cdecl ZipPackedReaderIO::Close(void)
{
    _openFileIdx = -1;
    _openFileArray.clear();
}

// 0x16cb0
void __cdecl PathUtil::Tokenlize(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > &, wchar_t *, wchar_t const *)
{
    LIFT_STUB(0x16cb0);
}

// 0x16db0
bool __cdecl PathUtil::MatchPath(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > const &, ::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > const &, bool)
{
    LIFT_STUB(0x16db0);
}

// 0x16ec0
bool __cdecl PathUtil::MatchFile(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > &, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > &)
{
    LIFT_STUB(0x16ec0);
}
