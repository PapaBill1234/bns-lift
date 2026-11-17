#pragma once
// VS2010 CRT C++ overloads of the secure functions (crtdefs.h
// __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST). The Wine headers do not have them.
// The original exes call these templates as out-of-line functions, for example
// swprintf_s<520> (CacheGate WinServiceConsole::ServiceMain 0x177d0).
#include <stdarg.h>
#include <stddef.h>
#include <wchar.h>

template <size_t _Size>
int __cdecl swprintf_s(wchar_t (&_Dest)[_Size], const wchar_t* _Format, ...)
{
    va_list _ArgList;
    va_start(_ArgList, _Format);
    int _Ret = vswprintf_s(_Dest, _Size, _Format, _ArgList);
    va_end(_ArgList);
    return _Ret;
}
