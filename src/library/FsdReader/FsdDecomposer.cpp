// FsdDecomposer.obj (LobbyDaemon PDB, 2019 + PDB).
#include "FsdDecomposer.h"
#include <wchar.h>

// Inline. The switch is copied into each Get function (fsddecomposer.cpp:152).
inline int FsdDecomposer::getDataSize(char format)
{
    switch (format)
    {
    case 'c':
        return sizeof(char);
    case 'w':
        return sizeof(short);
    case 'd':
    case 'f':
        return sizeof(int);
    case 'q':
        return sizeof(__int64);
    }
    return 0;
}

// Inline. The switch is copied into each Get function (fsddecomposer.cpp:160).
// The 'f' format has a size but no integer form, so this function returns false for it.
inline bool FsdDecomposer::decomposeIntByFmt(char format, __int64* value, char* data)
{
    switch (format)
    {
    case 'c':
        *value = *reinterpret_cast<char*>(data);
        return true;
    case 'd':
        *value = *reinterpret_cast<int*>(data);
        return true;
    case 'q':
        *value = *reinterpret_cast<__int64*>(data);
        return true;
    case 'w':
        *value = *reinterpret_cast<short*>(data);
        return true;
    }
    return false;
}

// 0x119c10
bool FsdDecomposer::Decompose()
{
    if (_ptr.GetRepeat() > 0)
    {
        if (_ptr.DecRepeat() > 0)
            return true;
        _repeat = 0;
    }

    if (_ptr.IsEndOfFormat(0))
        return false;
    if (_ptr.IsEndOfData(0))
        return false;
    if (_ptr.GetRemainDataSize() < sizeof(short))
        return false;

    _symbol = *reinterpret_cast<short*>(_ptr.GetCurrentData());
    _ptr.ForwardData(sizeof(short));
    _format = *_ptr.GetCurrentFormat();
    _ptr.ForwardFormat(1);

    if (_format == 'N')
    {
        // An 'N' format is a repeat. The next format byte is the item format, and the next data word is the count.
        if (_ptr.GetRepeat() > 0)
            return false;
        if (_ptr.IsEndOfFormat(0))
            return false;
        _format = *_ptr.GetCurrentFormat();
        _ptr.ForwardFormat(1);
        if (_ptr.GetRemainDataSize() < sizeof(short))
            return false;
        _repeat = *reinterpret_cast<short*>(_ptr.GetCurrentData());
        _ptr.SetRepeat(_repeat);
        _ptr.ForwardData(sizeof(short));
    }
    return true;
}

// 0x119d00
bool FsdDecomposer::GetByte(char* buffer)
{
    short size = static_cast<short>(getDataSize(_format));
    if (size == 0)
        return false;
    if (_ptr.GetRemainDataSize() < size)
        return false;
    if (buffer != NULL)
    {
        __int64 value;
        if (!decomposeIntByFmt(_format, &value, _ptr.GetCurrentData()))
            return false;
        *buffer = static_cast<char>(value);
    }
    _ptr.ForwardData(size);
    return true;
}

// 0x119dd0
bool FsdDecomposer::GetWord(short* buffer)
{
    short size = static_cast<short>(getDataSize(_format));
    if (size == 0)
        return false;
    if (_ptr.GetRemainDataSize() < size)
        return false;
    if (buffer != NULL)
    {
        __int64 value;
        if (!decomposeIntByFmt(_format, &value, _ptr.GetCurrentData()))
            return false;
        *buffer = static_cast<short>(value);
    }
    _ptr.ForwardData(size);
    return true;
}

// 0x119ea0
bool FsdDecomposer::GetDword(int* buffer)
{
    short size = static_cast<short>(getDataSize(_format));
    if (size == 0)
        return false;
    if (_ptr.GetRemainDataSize() < size)
        return false;
    if (buffer != NULL)
    {
        __int64 value;
        if (!decomposeIntByFmt(_format, &value, _ptr.GetCurrentData()))
            return false;
        *buffer = static_cast<int>(value);
    }
    _ptr.ForwardData(size);
    return true;
}

// 0x119f70
bool FsdDecomposer::GetQword(__int64* buffer)
{
    short size = static_cast<short>(getDataSize(_format));
    if (size == 0)
        return false;
    if (_ptr.GetRemainDataSize() < size)
        return false;
    if (buffer != NULL)
    {
        __int64 value;
        if (!decomposeIntByFmt(_format, &value, _ptr.GetCurrentData()))
            return false;
        *buffer = value;
    }
    _ptr.ForwardData(size);
    return true;
}

// 0x11a040
// Returns 0 on success, -1 if the data is too short, or the necessary count if the buffer is too small.
int FsdDecomposer::GetString(wchar_t* buffer, int count)
{
    wchar_t* str = reinterpret_cast<wchar_t*>(_ptr.GetCurrentData());
    int length = static_cast<int>(wcslen(str)) + 1;
    if (_ptr.GetRemainDataSize() < static_cast<short>(length * sizeof(wchar_t)))
        return -1;
    if (buffer != NULL)
    {
        if (count < length)
            return length;
        wcscpy_s(buffer, count, str);
    }
    _ptr.ForwardData(length * sizeof(wchar_t));
    return 0;
}
