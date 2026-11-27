// datapacker.h: datapacker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class PathUtil
{
public:
    static void __cdecl Tokenlize(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > &, wchar_t *, wchar_t const *);  // 0x16cb0
    static bool __cdecl MatchPath(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > const &, ::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > const &, bool);  // 0x16db0
    static bool __cdecl MatchFile(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > &, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > &);  // 0x16ec0
};

class ZipPackedReaderIO
{
public:
    struct FileName;
public:
    __cdecl ~ZipPackedReaderIO(void);  // 0x154f0
    bool __cdecl OpenZip(wchar_t const *);  // 0x15580
    bool __cdecl Verify(char *, unsigned __int64);  // 0x15860
    void __cdecl CloseZip(void);  // 0x16290
    virtual ::XmlReaderIO::ErrCode __cdecl Open(wchar_t const *, wchar_t const *, bool);  // 0x16330
    virtual ::XmlReaderIO::ErrCode __cdecl Read(unsigned char *, unsigned int *) const;  // 0x169a0
    virtual unsigned int __cdecl GetFileSize(void) const;  // 0x16b60
    virtual wchar_t const * __cdecl GetFileName(void) const;  // 0x16bd0
    virtual ::XmlReaderIO::ErrCode __cdecl Next(void);  // 0x16c40
    virtual void __cdecl Close(void);  // 0x16c70
};

struct ZipPackedReaderIO::FileName
{
public:
    __cdecl FileName(char const *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned int);  // 0x153d0
    __cdecl ~FileName(void);  // 0x157c0
};

