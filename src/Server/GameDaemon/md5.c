// md5.c: md5.c (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "md5.h"
#include "LiftStub.h"

// 0x6feff0
static void md5_process(struct md5_state_s* a0, const unsigned char* a1)
{
    LIFT_STUB(0x6feff0);
}

#pragma comment(linker, "/INCLUDE:md5_init")  // LIFT: dead-strip keep (no live caller yet)

// 0x6ff850
void md5_init(struct md5_state_s* pms)
{
    pms->count[0] = pms->count[1] = 0;
    pms->abcd[0] = 0x67452301;
    pms->abcd[1] = 0xefcdab89;
    pms->abcd[2] = 0x98badcfe;
    pms->abcd[3] = 0x10325476;
}

// 0x6ff880
void md5_append(struct md5_state_s* a0, const unsigned char* a1, int a2)
{
    LIFT_STUB(0x6ff880);
}

// 0x6ff980
void md5_finish(struct md5_state_s* a0, unsigned char* a1)
{
    LIFT_STUB(0x6ff980);
}
