// FsdDecomposer.obj (LobbyDaemon PDB, 2019 + PDB).
// The PDB source path is program\library\fsdreader\src\fsddecomposer.cpp. The case of the folder name is not verified. // ❓
#pragma once

class Fsd;

// FsdPointer (PDB size 0x28). All methods are inline. The PDB has no address for them.
class FsdPointer
{
public:
    bool Initialize(Fsd&);  // LIFT: not lifted; the only caller (DecomposeShowcaseFsd 0x2e0b0) is not lifted yet.
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
    bool Initialize(Fsd&);  // LIFT: not lifted; inline in DecomposeShowcaseFsd 0x2e0b0, which is not lifted yet.
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

    // LIFT: the original Decompose is private and its friend is not known. The callers
    // (DecomposeShowcaseFsd 0x2e0b0) call it directly. // ❓
    bool Decompose();  // 0x119c10

private:
    bool decomposeIntByFmt(char format, __int64* value, char* data);  // inline in each Get function
    int getDataSize(char format);  // inline in each Get function

    FsdPointer _ptr;
    short _symbol;
    char _format;
    int _repeat;
};
