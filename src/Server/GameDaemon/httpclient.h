// httpclient.h: httpclient.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class HTTPClient
{
public:
    enum RequestMethod {};
public:
    virtual __cdecl ~HTTPClient(void);  // 0x6a1af0
    bool __cdecl Request(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::HTTPClient::RequestMethod, wchar_t const *, bool);  // 0x6a1c00
private:
    bool __cdecl connect(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, wchar_t const *, unsigned short, wchar_t const *, wchar_t const *);  // 0x6a1e80
    bool __cdecl requestOfURI(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::INTERNET_SCHEME, ::HTTPClient::RequestMethod, bool);  // 0x6a2080
    unsigned long __cdecl responseOfBytes(unsigned char *, unsigned long);  // 0x6a20b0
    bool __cdecl queryHttpInfo(unsigned long, wchar_t const *, unsigned char *&, unsigned long &, unsigned long &);  // 0x6a2180
    unsigned long __cdecl queryContentLength(void);  // 0x6a2300
    bool __cdecl response(void);  // 0x6a23a0
public:
    ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > __cdecl GetHttpResponseUnicodeString(void);  // 0x6a2810
private:
    void __cdecl parseURL(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > &, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > &, unsigned short &, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > &);  // 0x6a29c0
    bool __cdecl requestPostBody(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::INTERNET_SCHEME, bool);  // 0x6a2d30
};

class WebUtil
{
public:
    static ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > __cdecl ConvertMultiByteToWideChar(::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > const &, unsigned int);  // 0x6a2e70
    static ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl ConvertWideCharToMultiByte(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, unsigned int);  // 0x6a30a0
};

