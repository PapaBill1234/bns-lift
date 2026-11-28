// propertysync.cpp: propertysync.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "propertysync.h"
#include <stddef.h>
#include <string.h>
#include "LiftStub.h"

// LIFT: partial views of the PDB layouts (the classes in propertysync.h have no members yet).
// PDB: Field, size 2: valid : 1, index : 15.
struct SyncBufferFieldView
{
    unsigned short valid : 1;
    unsigned short index : 15;
};
// PDB: SyncBuffer::Def (size 0x18): fcount +12.
struct SyncBufferDefView
{
    char head[12];
    int fcount;
    void *field;
};
// PDB: SyncBuffer, size 0x28.
struct SyncBufferView
{
    SyncBufferDefView const *define;  // +0
    short curCount;                   // +8
    short curSize;                    // +10
    char *buffer;                     // +16
    SyncBufferFieldView *field;       // +24
    void *dbField;                    // +32
};
static_assert(sizeof(SyncBufferFieldView) == 2, "sizeof Field");
static_assert(offsetof(SyncBufferDefView, fcount) == 12, "SyncBuffer::Def::fcount");
static_assert(sizeof(SyncBufferView) == 0x28, "sizeof SyncBuffer");
static_assert(offsetof(SyncBufferView, curSize) == 0xA, "SyncBuffer::curSize");
static_assert(offsetof(SyncBufferView, buffer) == 0x10, "SyncBuffer::buffer");
static_assert(offsetof(SyncBufferView, field) == 0x18, "SyncBuffer::field");

// 0x687ce0
__cdecl SyncBuffer::~SyncBuffer(void)
{
    LIFT_STUB(0x687ce0);
}

// 0x687df0
bool __cdecl SyncBuffer::Initialize(::SyncBuffer::Def const *)
{
    LIFT_STUB(0x687df0);
}

// 0x687fc0
bool __cdecl SyncBuffer::Initialize(::SyncBuffer const *)
{
    LIFT_STUB(0x687fc0);
}

// 0x6880c0
bool __cdecl SyncBuffer::Clear(void) const
{
    LIFT_STUB(0x6880c0);
}

// 0x688130
short __cdecl SyncBuffer::Copy(char *, unsigned __int64, short *, bool) const
{
    LIFT_STUB(0x688130);
}

// 0x6881b0
bool __cdecl SyncBuffer::Set(::Field::Def const *, int, void const *, int, bool, bool *, int, int)
{
    LIFT_STUB(0x6881b0);
}

// 0x688560
char * __cdecl SyncBuffer::set(::Field::Def const *, int, char *, void const *, int, bool, short &)
{
    LIFT_STUB(0x688560);
}

// 0x688890
char * __cdecl SyncBuffer::setInt(char *, void const *, unsigned char)
{
    LIFT_STUB(0x688890);
}

// 0x6888d0
char * __cdecl SyncBuffer::setString(char *, wchar_t const *, short, int, bool, short &)
{
    LIFT_STUB(0x6888d0);
}

// 0x688990
void __cdecl SyncBuffer::realign(int findex, char *pos, short resize)
{
    SyncBufferView *self = reinterpret_cast<SyncBufferView *>(this);
    short from = static_cast<short>(pos - self->buffer);
    // LIFT: HR names the copy memcpy_0. The ranges overlap, so memmove is the safe form (same CRT body on x64).
    memmove(&pos[resize], pos, static_cast<short>(self->curSize - from));
    for (int i = 0; i < self->define->fcount; ++i)
    {
        if (findex != i)
        {
            SyncBufferFieldView *field = &self->field[i];
            if (field->valid != 0 && field->index >= from)
                field->index += resize;
        }
    }
}
