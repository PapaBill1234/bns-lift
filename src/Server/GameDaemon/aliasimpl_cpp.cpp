// aliasimpl_cpp.cpp: aliasimpl.cpp (GameDaemon PDB, 2019 + PDB).
#include "aliasimpl.h"
#include "elreaderimpl.h"
#include "LiftStub.h"
#include <windows.h>
#include <string.h>
#include <wchar.h>

#pragma comment(linker, "/INCLUDE:??0DrAliasMapImpl@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1DrAliasMapImpl@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ReadFromBuffer@DrAliasStringTable@@QEAA_NPEBE_K1_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Build@DrAliasStringTable@@QEAA_NPEBUAliasArrayElement@DrAliasMapImpl@@H@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?allocElArray@DrAliasMapImpl@@AEAAXH@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x6f33a0
bool __cdecl DrAliasMapImpl::WriteToBuffer(unsigned char * buffer, unsigned __int64 buffersize)
{
    return buffer != nullptr;
}

// 0x6f33b0
void __cdecl DrAliasStringTable::Clear(void)
{
    if (_elArray != nullptr)
    {
        DrMemoryManager::Memory(DrMemoryManager::SECTION_STATIC)->Free(_elArray, L"src\\AliasImpl.cpp", 2990);
        _elArray = nullptr;
    }
    if (_stringTable != nullptr)
    {
        DrMemoryManager::Memory(DrMemoryManager::SECTION_STATIC)->Free(_stringTable, L"src\\AliasImpl.cpp", 2996);
        _stringTable = nullptr;
    }
    _stringTableSize = 0;
    _elCount = 0;
}

// LIFT: inline helper (no PDB name). Copies at most size - 1 upper-case characters.
static inline void toUpperCopy(wchar_t * dst, wchar_t const * src, __int64 size)
{
    if (dst == nullptr)
        return;
    __int64 i = 0;
    while (*src != 0)
    {
        dst[i++] = static_cast<wchar_t>(towupper(*src++));
        if (i >= size - 1)
            break;
    }
}

// 0x6f3430
bool __cdecl DrAliasStringTable::Find(wchar_t const * alias, unsigned __int64 * key) const
{
    // LIFT: review reject P2_cc (build jge, original je). A later card lifts it.
    LIFT_STUB(0x6f3430);
}

// 0x6f3610
int __cdecl DrAliasMapImpl::Count(void) const
{
    if (_useStringTable && _stringTable != nullptr)
        return _stringTable->Count();
    if (_reconstructed)
        return _elCount;
    return (int)_aliasmap.size();
}

// 0x6f3630
bool __cdecl DrAliasMapImpl::ReplaceIfChanged(wchar_t const *, ::DrAliasMap const &)
{
    // LIFT: needs DrAliasMapImpl as a DrAliasMap (base class). WriteSize and Print have no body yet.
    LIFT_STUB(0x6f3630);
}

// 0x6f36d0
void __cdecl DrAliasStringTable::construct(int elCount)
{
    if (elCount > 0)
    {
        Clear();
        _elCount = elCount;
        _elArray = DrNewArray<ArrayElement>(elCount);
    }
}

// 0x6f3900
bool __cdecl DrAliasStringTable::ReadFromBuffer(unsigned char const * buffer, unsigned __int64 buffersize, unsigned __int64 aliascount, bool)
{
    if (buffer == nullptr)
        return false;
    if (aliascount == 0)
        return false;

    Clear();
    // BUG: the 2019 build reads each part of the buffer before it checks the size. The lift checks the size first.
    if (buffersize < 4)
        return false;
    _elCount = *reinterpret_cast<int const *>(buffer);
    if (_elCount < 0)
        return false;

    unsigned __int64 offset = sizeof(ArrayElement) * _elCount + 4;
    if (offset > buffersize)
        return false;
    construct(_elCount);
    memcpy(_elArray, buffer + 4, sizeof(ArrayElement) * _elCount);

    offset = sizeof(ArrayElement) * _elCount + 8;
    if (offset > buffersize)
        return false;
    _stringTableSize = *reinterpret_cast<int const *>(buffer + offset - 4);
    if (_stringTableSize < 0 || offset + _stringTableSize > buffersize)
        return false;

    _stringTable = static_cast<char *>(DrMemoryManager::Memory(DrMemoryManager::SECTION_STATIC)->Alloc(_stringTableSize, L"src\\AliasImpl.cpp", 3112));
    memcpy(_stringTable, buffer + offset, _stringTableSize);

    // ❓ The alias offsets are not checked against _stringTableSize (same in the 2019 build).
    for (int i = 0; i < _elCount; ++i)
        _elArray[i].alias += reinterpret_cast<unsigned __int64>(_stringTable);
    return true;
}

// 0x6f3a10
bool __cdecl DrAliasStringTable::Build(::DrAliasMapImpl::AliasArrayElement const * elArray, int elCount)
{
    if (elCount <= 0)
        return false;

    construct(elCount);

    unsigned int size = 0;
    for (int i = 0; i < elCount; ++i)
        size += WideCharToMultiByte(CP_ACP, 0, elArray[i].alias.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (size == 0)
        return false;

    char * p = static_cast<char *>(DrMemoryManager::Memory(DrMemoryManager::SECTION_STATIC)->Alloc(size, L"src\\AliasImpl.cpp", 3310));
    _stringTable = p;
    for (int i = 0; i < elCount; ++i)
    {
        _elArray[i].key = elArray[i].key;
        _elArray[i].alias = p;
        char ansiAlias[200] = { 0 };
        // ❓ An alias longer than 199 ANSI characters is not converted (WideCharToMultiByte fails); the server data has short aliases.
        WideCharToMultiByte(CP_ACP, 0, elArray[i].alias.c_str(), -1, ansiAlias, 200, nullptr, nullptr);
        memcpy(p, ansiAlias, strlen(ansiAlias));
        p += strlen(ansiAlias) + 1;
        *(p - 1) = 0;
    }
    _stringTableSize = size;
    return true;
}

// 0x6f3c70
bool __cdecl DrAliasMapImpl::IsSubsetOf(wchar_t const * tablename, ::DrAliasMap const & supersetAliasMap) const
{
    // BUG: the 2019 build tests (tablename == nullptr && wcslen(tablename) == 0) and reads a null pointer. The lift returns false.
    if (tablename == nullptr)
        return false;

    for (Map::const_iterator it = _aliasmap.begin(); it != _aliasmap.end(); ++it)
    {
        wchar_t tn[201];
        if (DrElReaderImpl::tokenize(it->first.c_str(), L':', tn, 201) != nullptr && _wcsicmp(tablename, tn) == 0)
        {
            unsigned __int64 key = 0;
            if (!supersetAliasMap.Find(it->first.c_str(), &key) || it->second != key)
                return false;
        }
    }
    return true;
}

// 0x6f3df0
void __cdecl DrAliasMapImpl::InsertInto(::DrAliasMap & targetAliasMap) const
{
    for (Map::const_iterator it = _aliasmap.begin(); it != _aliasmap.end(); ++it)
        targetAliasMap.Insert(it->first.c_str(), it->second);
}

// 0x6f4280
void __cdecl DrAliasMapImpl::clearElArray(void)
{
    if (_elArray != nullptr)
    {
        for (int i = 0; i < _elCount; ++i)
            _elArray[i].~AliasArrayElement();
        DrMemoryManager::Memory(DrMemoryManager::SECTION_STATIC)->Free(_elArray, L"src\\AliasImpl.cpp", 2967);
    }
    _elArray = nullptr;
    _reconstructed = false;
    _elCount = 0;
}

// 0x6f4490
void __cdecl DrAliasMapImpl::allocElArray(int size)
{
    if (_elArray != nullptr)
    {
        for (int i = 0; i < _elCount; ++i)
            _elArray[i].~AliasArrayElement();
        DrMemoryManager::Memory(DrMemoryManager::SECTION_STATIC)->Free(_elArray, L"src\\AliasImpl.cpp", 2891);
    }
    // ❓ With size <= 0, _elArray keeps the freed pointer (same in the 2019 build).
    if (size > 0)
    {
        _elCount = size;
        _elArray = DrNewArray<AliasArrayElement>(size);
    }
}

// 0x6f4860
bool __cdecl DrAliasMapImpl::Find(wchar_t const *, unsigned __int64 *) const
{
    LIFT_STUB(0x6f4860);
}

// 0x6f4a90
void __cdecl DrAliasMapImpl::rebuildElArray(void)
{
    LIFT_STUB(0x6f4a90);
}

// 0x6f5780
void __cdecl DrAliasMapImpl::clearTableFromAliasMap(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> >, ::DrStlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> >, 1> > const &)
{
    LIFT_STUB(0x6f5780);
}

// 0x6f5b30
void __cdecl DrAliasMapImpl::Reconstruct(void)
{
    rebuildElArray();
    _aliasmap.clear();
}

// 0x6f5d50
bool __cdecl DrAliasMapImpl::Insert(wchar_t const *, unsigned __int64)
{
    LIFT_STUB(0x6f5d50);
}

// 0x6f5f40
void __cdecl DrAliasMapImpl::Clear(void)
{
    if (_useStringTable && _stringTable != nullptr)
        _stringTable->Clear();
    clearElArray();
    _aliasmap.clear();
}

// 0x6f5fa0
bool __cdecl DrAliasMapImpl::ReadFromBuffer(unsigned char const *, unsigned __int64, unsigned __int64, bool)
{
    LIFT_STUB(0x6f5fa0);
}

// 0x6f6320
__cdecl DrAliasMapImpl::~DrAliasMapImpl(void)
{
    if (_useStringTable && _stringTable != nullptr)
        _stringTable->Clear();
    clearElArray();
    _aliasmap.clear();
}

// 0x6f6450
__cdecl DrAliasMapImpl::DrAliasMapImpl(void)
{
    _elArray = nullptr;
    _elCount = 0;
    _stringTable = nullptr;
    _reconstructed = false;
    _useStringTable = false;
}

// 0x6f6490
void __cdecl DrAliasMapImpl::ClearTable(wchar_t const *, bool)
{
    LIFT_STUB(0x6f6490);
}
