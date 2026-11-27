// aliasimpl_cpp.cpp: aliasimpl.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "aliasimpl.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??0DrAliasMapImpl@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6f33a0
bool __cdecl DrAliasMapImpl::WriteToBuffer(unsigned char * buffer, unsigned __int64 buffersize)
{
    return buffer != nullptr;
}

// 0x6f33b0
void __cdecl DrAliasStringTable::Clear(void)
{
    LIFT_STUB(0x6f33b0);
}

// 0x6f3430
bool __cdecl DrAliasStringTable::Find(wchar_t const *, unsigned __int64 *) const
{
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
    LIFT_STUB(0x6f3630);
}

// 0x6f36d0
void __cdecl DrAliasStringTable::construct(int)
{
    LIFT_STUB(0x6f36d0);
}

// 0x6f3900
bool __cdecl DrAliasStringTable::ReadFromBuffer(unsigned char const *, unsigned __int64, unsigned __int64, bool)
{
    LIFT_STUB(0x6f3900);
}

// 0x6f3a10
bool __cdecl DrAliasStringTable::Build(::DrAliasMapImpl::AliasArrayElement const *, int)
{
    LIFT_STUB(0x6f3a10);
}

// 0x6f3c70
bool __cdecl DrAliasMapImpl::IsSubsetOf(wchar_t const *, ::DrAliasMap const &) const
{
    LIFT_STUB(0x6f3c70);
}

// 0x6f3df0
void __cdecl DrAliasMapImpl::InsertInto(::DrAliasMap &) const
{
    LIFT_STUB(0x6f3df0);
}

// 0x6f4280
void __cdecl DrAliasMapImpl::clearElArray(void)
{
    LIFT_STUB(0x6f4280);
}

// 0x6f4490
void __cdecl DrAliasMapImpl::allocElArray(int)
{
    LIFT_STUB(0x6f4490);
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
    LIFT_STUB(0x6f5b30);
}

// 0x6f5d50
bool __cdecl DrAliasMapImpl::Insert(wchar_t const *, unsigned __int64)
{
    LIFT_STUB(0x6f5d50);
}

// 0x6f5f40
void __cdecl DrAliasMapImpl::Clear(void)
{
    LIFT_STUB(0x6f5f40);
}

// 0x6f5fa0
bool __cdecl DrAliasMapImpl::ReadFromBuffer(unsigned char const *, unsigned __int64, unsigned __int64, bool)
{
    LIFT_STUB(0x6f5fa0);
}

// 0x6f6320
__cdecl DrAliasMapImpl::~DrAliasMapImpl(void)
{
    LIFT_STUB(0x6f6320);
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
