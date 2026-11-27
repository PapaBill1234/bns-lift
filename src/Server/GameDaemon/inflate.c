// inflate.c: inflate.c (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "inflate.h"
#include "LiftStub.h"

// 0x5ea0
int inflateResetKeep(struct z_stream_s* a0)
{
    LIFT_STUB(0x5ea0);
}

// 0x5f20
int inflateReset2(struct z_stream_s* a0, int a1)
{
    LIFT_STUB(0x5f20);
}

// 0x5fc0
int inflateInit2_(struct z_stream_s* a0, int a1, const char* a2, int a3)
{
    LIFT_STUB(0x5fc0);
}

// 0x6080
static int updatewindow(struct z_stream_s* a0, const unsigned char* a1, unsigned a2)
{
    LIFT_STUB(0x6080);
}

// 0x6180
int inflate(struct z_stream_s* a0, int a1)
{
    LIFT_STUB(0x6180);
}

// 0x7850
int inflateEnd(struct z_stream_s* a0)
{
    LIFT_STUB(0x7850);
}
