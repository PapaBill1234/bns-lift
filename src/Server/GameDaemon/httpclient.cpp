// httpclient.cpp: httpclient.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "httpclient.h"
#include "LiftStub.h"

// 0x6a1af0
__cdecl HTTPClient::~HTTPClient(void)
{
    LIFT_STUB(0x6a1af0);
}

// 0x6a1c00
bool __cdecl HTTPClient::Request(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::HTTPClient::RequestMethod, wchar_t const *, bool)
{
    LIFT_STUB(0x6a1c00);
}

// 0x6a1e80
bool __cdecl HTTPClient::connect(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, wchar_t const *, unsigned short, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x6a1e80);
}

// 0x6a2080
bool __cdecl HTTPClient::requestOfURI(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::INTERNET_SCHEME, ::HTTPClient::RequestMethod, bool)
{
    LIFT_STUB(0x6a2080);
}

// 0x6a20b0
unsigned long __cdecl HTTPClient::responseOfBytes(unsigned char *, unsigned long)
{
    LIFT_STUB(0x6a20b0);
}

// 0x6a2180
bool __cdecl HTTPClient::queryHttpInfo(unsigned long, wchar_t const *, unsigned char *&, unsigned long &, unsigned long &)
{
    LIFT_STUB(0x6a2180);
}

// 0x6a2300
unsigned long __cdecl HTTPClient::queryContentLength(void)
{
    LIFT_STUB(0x6a2300);
}

// 0x6a23a0
bool __cdecl HTTPClient::response(void)
{
    LIFT_STUB(0x6a23a0);
}

// 0x6a2810
::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > __cdecl HTTPClient::GetHttpResponseUnicodeString(void)
{
    LIFT_STUB(0x6a2810);
}

// 0x6a29c0
void __cdecl HTTPClient::parseURL(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > &, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > &, unsigned short &, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > &)
{
    LIFT_STUB(0x6a29c0);
}

// 0x6a2d30
bool __cdecl HTTPClient::requestPostBody(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, ::INTERNET_SCHEME, bool)
{
    LIFT_STUB(0x6a2d30);
}

// 0x6a2e70
::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > __cdecl WebUtil::ConvertMultiByteToWideChar(::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > const &, unsigned int)
{
    LIFT_STUB(0x6a2e70);
}

// 0x6a30a0
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl WebUtil::ConvertWideCharToMultiByte(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > const &, unsigned int)
{
    LIFT_STUB(0x6a30a0);
}
