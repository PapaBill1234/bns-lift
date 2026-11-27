// unzip.c: unzip.c (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "unzip.h"
#include "LiftStub.h"

// 0x1160
static int unz64local_getShort(const struct zlib_filefunc64_32_def_s* a0, void* a1, unsigned long* a2)
{
    LIFT_STUB(0x1160);
}

// 0x1210
static int unz64local_getLong(const struct zlib_filefunc64_32_def_s* a0, void* a1, unsigned long* a2)
{
    LIFT_STUB(0x1210);
}

// 0x1340
static int unz64local_getLong64(const struct zlib_filefunc64_32_def_s* a0, void* a1, unsigned __int64* a2)
{
    LIFT_STUB(0x1340);
}

// 0x1570
static unsigned __int64 unz64local_SearchCentralDir(const struct zlib_filefunc64_32_def_s* a0, void* a1)
{
    LIFT_STUB(0x1570);
}

// 0x1730
static unsigned __int64 unz64local_SearchCentralDir64(const struct zlib_filefunc64_32_def_s* a0, void* a1)
{
    LIFT_STUB(0x1730);
}

// 0x19f0
static void* unzOpenInternal(const void* a0, struct zlib_filefunc64_32_def_s* a1, int a2)
{
    LIFT_STUB(0x19f0);
}

// 0x2140
static int unz64local_GetCurrentFileInfoInternal(void* a0, struct unz_file_info64_s* a1, struct unz_file_info64_internal_s* a2, char* a3, unsigned long a4, void* a5, unsigned long a6, char* a7, unsigned long a8)
{
    LIFT_STUB(0x2140);
}

// 0x25f0
int unzGoToFirstFile(void* a0)
{
    LIFT_STUB(0x25f0);
}

// 0x2660
int unzGoToNextFile(void* a0)
{
    LIFT_STUB(0x2660);
}

// 0x2710
static int unz64local_CheckCurrentFileCoherencyHeader(struct unz64_s* a0, unsigned* a1, unsigned __int64* a2, unsigned* a3)
{
    LIFT_STUB(0x2710);
}

// 0x2960
int unzOpenCurrentFile3(void* a0, int* a1, int* a2, int a3, const char* a4)
{
    LIFT_STUB(0x2960);
}

// 0x2b40
int unzReadCurrentFile(void* a0, void* a1, unsigned a2)
{
    LIFT_STUB(0x2b40);
}

// 0x2e50
int unzCloseCurrentFile(void* a0)
{
    LIFT_STUB(0x2e50);
}
