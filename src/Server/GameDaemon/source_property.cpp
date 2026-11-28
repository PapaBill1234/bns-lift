// source_property.cpp: property.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "property.h"
#include "propertysync.h"
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/CrashHandler.h"
#include "../BloodLib/include/Log.h"
#include "LiftStub.h"

// 0x688a70
__cdecl Property::~Property(void)
{
    LIFT_STUB(0x688a70);
}

// 0x688b50
void __cdecl Property::self(unsigned __int64)
{
    LIFT_STUB(0x688b50);
}

// 0x688ce0
void __cdecl Property::init(::Property const *, unsigned __int64)
{
    LIFT_STUB(0x688ce0);
}

// 0x688ee0
bool __cdecl Property::SetZero(unsigned char)
{
    LIFT_STUB(0x688ee0);
}

// 0x689080
bool __cdecl Property::Set(unsigned short, __int64, __int64, __int64, short)
{
    LIFT_STUB(0x689080);
}

// 0x689240
bool __cdecl Property::Set(unsigned short, ::f_flag8::Operation)
{
    LIFT_STUB(0x689240);
}

// 0x689320
bool __cdecl Property::set(unsigned short, __int64, bool, bool *)
{
    LIFT_STUB(0x689320);
}

// 0x6894e0
bool __cdecl Property::set(unsigned short, ::id128 const *, bool, bool *)
{
    LIFT_STUB(0x6894e0);
}

// 0x689640
bool __cdecl Property::set(unsigned short, bool, bool, bool *)
{
    LIFT_STUB(0x689640);
}

// 0x689740
bool __cdecl Property::set(unsigned short, wchar_t const *, short, bool, bool *)
{
    LIFT_STUB(0x689740);
}

// 0x689910
bool __cdecl Property::set(unsigned short, unsigned char const *, short, bool, bool *)
{
    LIFT_STUB(0x689910);
}

// 0x689af0
bool __cdecl Property::set(unsigned short, int, short, int, bool, bool *)
{
    LIFT_STUB(0x689af0);
}

// 0x689c70
bool __cdecl Property::set(char const *, unsigned __int64, bool, bool, unsigned __int64 *, bool *)
{
    LIFT_STUB(0x689c70);
}

// 0x689f50
void __cdecl Property::updateSync(::Field::Def const *, __int64, bool, bool *)
{
    LIFT_STUB(0x689f50);
}

// 0x68a2e0
void __cdecl Property::updateSync(unsigned short, ::Field::Def const *const, bool, bool, bool *)
{
    LIFT_STUB(0x68a2e0);
}

// 0x68a700
bool __cdecl Property::Get(unsigned short, bool *) const
{
    LIFT_STUB(0x68a700);
}

// 0x68a7c0
bool __cdecl Property::Get(unsigned short, wchar_t *, unsigned __int64 *) const
{
    LIFT_STUB(0x68a7c0);
}

// 0x68a880
bool __cdecl Property::GetPureData(unsigned short, void *, unsigned __int64 *, bool) const
{
    LIFT_STUB(0x68a880);
}

// 0x68ac60
bool __cdecl Property::GetPairData(unsigned short, void *, unsigned __int64 *, bool) const
{
    LIFT_STUB(0x68ac60);
}

// 0x68ad50
bool __cdecl Property::get(unsigned short, void *, unsigned __int64) const
{
    LIFT_STUB(0x68ad50);
}

// 0x68af20
void __cdecl Property::makeWhere(::Field::Def const *, __int64)
{
    LIFT_STUB(0x68af20);
}

// 0x68afb0
bool __cdecl Property::initInstance(int, int, ::FieldDef const *const, int, ::SyncDef *const, int *, ::Field::Def **, int *, ::SyncBuffer::Def **)
{
    LIFT_STUB(0x68afb0);
}

// 0x68b100
::Field::Def * __cdecl Property::initFieldDefine(int, ::FieldDef const *const, int, void *)
{
    LIFT_STUB(0x68b100);
}

// 0x68b510
unsigned short __cdecl Property::findMaxId(int, ::FieldDef const *const)
{
    LIFT_STUB(0x68b510);
}

// 0x68b610
short __cdecl Property::initBitfield(int, ::FieldDef const *const, int, ::Field::Def *const, unsigned short, void *)
{
    LIFT_STUB(0x68b610);
}

// 0x68b770
::SyncBuffer::Def * __cdecl Property::initSyncDefine(int, ::SyncDef const *const, int, bool, int, ::Field::Def *const, void *)
{
    LIFT_STUB(0x68b770);
}

#pragma comment(linker, "/INCLUDE:?findMaxId@Property@@CAEHQEBUSyncDef@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// LIFT: partial view of the PDB struct SyncDef (size 4). The header declares it without members.
struct SyncDefView
{
    unsigned char id;          // +0
    unsigned char type;        // +1
    unsigned char dynamic;     // +2
    unsigned char initupdate;  // +3
};
static_assert(sizeof(SyncDefView) == 4, "sizeof SyncDef");

static wchar_t const PROPERTY_FILE[] = L"source\\Property.cpp";

// 0x68ba10
unsigned char __cdecl Property::findMaxId(int sdefCnt, ::SyncDef const *const sdef)
{
    SyncDefView const *def = reinterpret_cast<SyncDefView const *>(sdef);
    int id = 0;
    for (int i = 0; i < sdefCnt; ++i, ++def)
    {
        if (def->id >= 4)
        {
            Log::Write(Log::LT_ERROR, PROPERTY_FILE, 1999, L"== CRASH == ASSERT CRASH");
            AlertSender::Write(PROPERTY_FILE, 1999, L"== CRASH == ASSERT CRASH");
            CrashHandler::MakeCrash("source\\Property.cpp", 1999, L"");
        }
        if (id < def->id)
            id = def->id;
    }
    return static_cast<unsigned char>(id + 1);
}
