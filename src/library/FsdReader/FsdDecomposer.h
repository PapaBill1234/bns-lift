// FsdDecomposer.obj (LobbyDaemon PDB, 2019 + PDB).
// The PDB source path is program\library\fsdreader\src\fsddecomposer.cpp. The case of the folder name is not verified. // ❓
#pragma once

#include <string.h>

struct FsdShowcaseRecord;

// LIFT: The frame accessors are inlined in DecomposeShowcaseFsd (0x2e0b0).
class Fsd
{
public:
    static int const FORMAT_SIZE_OFFSET = 2;
    static int const FORMAT_OFFSET = 4;

    Fsd(char* buffer, short size) : _buffer(buffer), _size(size) {}
    char* GetBuffer() const { return _buffer; }
    short GetBufferSize() const { return _size; }
    char const* GetFormat() const { return _buffer + FORMAT_OFFSET; }
    short GetFormatSize() const
    {
        short size;
        memcpy(&size, _buffer + FORMAT_SIZE_OFFSET, sizeof(size));
        return size;
    }

private:
    char* _buffer;
    short _size;
};
static_assert(sizeof(Fsd) == 0x10, "sizeof Fsd");

// FsdPointer (PDB size 0x28). All methods are inline. The PDB has no address for them.
class FsdPointer
{
public:
    bool Initialize(Fsd& fsd)
    {
        if (fsd.GetBuffer() == nullptr || fsd.GetBufferSize() <= Fsd::FORMAT_OFFSET)
            return false;
        _formatSize = fsd.GetFormatSize();
        int size = fsd.GetBufferSize() - Fsd::FORMAT_OFFSET;
        // BUG: The original accepts negative sizes (0x2e0b0).
        if (_formatSize < 0 || size <= _formatSize)
            return false;
        _format = const_cast<char*>(fsd.GetFormat());
        _formatIndex = 0;
        _data = _format + _formatSize;
        _dataIndex = 0;
        _dataSize = size - _formatSize;
        _repeat = 0;
        return true;
    }
    char* GetCurrentFormat() const { return _format + _formatIndex; }
    char* GetCurrentData() const { return _data + _dataIndex; }
    void ForwardFormat(int size) { _formatIndex += size; }
    void BackwardFormat(int size) { _formatIndex -= size; }
    void ForwardData(int size) { _dataIndex += size; }
    void BackwardData(int size) { _dataIndex -= size; }
    // ❓ The meaning of the int argument is not verified. Decompose 0x119c10 compares the index with the size only.
    bool IsEndOfFormat(int offset) const { return _formatIndex + offset >= _formatSize; }
    bool IsEndOfData(int offset) const { return _dataIndex + offset >= _dataSize; }
    int GetRemainFormatSize() const { return _formatSize - _formatIndex; }
    int GetRemainDataSize() const { return _dataSize - _dataIndex; }
    void SetRepeat(int repeat) { _repeat = repeat; }
    int GetRepeat() const { return _repeat; }
    int IncRepeat() { return ++_repeat; }
    int DecRepeat() { return --_repeat; }

private:
    char* _format;
    int _formatIndex;
    int _formatSize;
    char* _data;
    int _dataIndex;
    int _dataSize;
    int _repeat;
};

// FsdDecomposer (PDB size 0x30).
class FsdDecomposer
{
public:
    // LIFT: Inlined in DecomposeShowcaseFsd (0x2e0b0).
    bool Initialize(Fsd& fsd)
    {
        _symbol = 0;
        _format = 0;
        _repeat = 0;
        return _ptr.Initialize(fsd);
    }
    bool Skip();  // LIFT: not lifted; the PDB has no address for it.
    short GetSymbol() const { return _symbol; }
    char GetFormat() const { return _format; }
    int GetRepeat() const { return _repeat; }
    bool IsRepeat() const { return _repeat > 0; }  // ❓ The body is not verified.
    bool GetByte(char* buffer);  // 0x119d00
    bool GetWord(short* buffer);  // 0x119dd0
    bool GetDword(int* buffer);  // 0x119ea0
    bool GetQword(__int64* buffer);  // 0x119f70
    bool GetFloat(float*);  // LIFT: not lifted; the PDB has no address for it.
    int GetString(wchar_t* buffer, int count);  // 0x11a040
    int GetBinary(char*, int);  // LIFT: not lifted; the PDB has no address for it.

private:
    // LIFT: The caller reads both repeat values at 0x2e0b0.
    friend bool DecomposeShowcaseFsd(char const*, short, FsdShowcaseRecord&);
    bool Decompose();  // 0x119c10
    bool decomposeIntByFmt(char format, __int64* value, char* data);  // inline in each Get function
    int getDataSize(char format);  // inline in each Get function

    FsdPointer _ptr;
    short _symbol;
    char _format;
    int _repeat;
};
