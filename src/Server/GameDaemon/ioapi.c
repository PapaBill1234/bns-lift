// ioapi.c: ioapi.c (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LiftStub.h"

// 0x1040
static void* fopen64_file_func(void* a0, const void* a1, int a2)
{
    LIFT_STUB(0x1040);
}

// 0x1090
static unsigned long fread_file_func(void* a0, void* a1, void* a2, unsigned long a3)
{
    LIFT_STUB(0x1090);
}

// 0x10b0
static unsigned long fwrite_file_func(void* a0, void* a1, const void* a2, unsigned long a3)
{
    LIFT_STUB(0x10b0);
}

// 0x10d0
static unsigned __int64 ftell64_file_func(void* a0, void* a1)
{
    LIFT_STUB(0x10d0);
}

// 0x10e0
static long fseek64_file_func(void* a0, void* a1, unsigned __int64 a2, int a3)
{
    LIFT_STUB(0x10e0);
}

// 0x1140
static int fclose_file_func(void* a0, void* a1)
{
    LIFT_STUB(0x1140);
}

// 0x1150
static int ferror_file_func(void* a0, void* a1)
{
    LIFT_STUB(0x1150);
}
