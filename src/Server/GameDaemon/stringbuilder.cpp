// stringbuilder.cpp: stringbuilder.cpp (GameDaemon PDB, 2019 + PDB).
#include "stringbuilder.h"
#include "../BloodLib/include/Memory.h"
#include <stdarg.h>
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1StringBuilderW@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?AppendFormat@StringBuilderW@@QEAA_NPEB_WZZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x69dd00
__cdecl StringBuilderW::~StringBuilderW(void)
{
    if (_str != nullptr && _delete)
        Memory::_Manager[2]->Free(_str, L"source\\StringBuilder.cpp", 54);
}

// 0x69dd40
bool __cdecl StringBuilderW::AppendFormat(wchar_t const * format, ...)
{
    if (_str == nullptr)
        return false;

    va_list args;
    va_start(args, format);
    int written = _vsnwprintf_s(&_str[_len], _capacity - _len - 1, _TRUNCATE, format, args);
    va_end(args);
    if (written < 0)
    {
        _str[_len] = 0;
        return false;
    }
    _len += written;
    _str[_len] = 0;
    return true;
}
