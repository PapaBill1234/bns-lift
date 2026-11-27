// deflate.c: deflate.c (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "deflate.h"
#include "LiftStub.h"

// 0x35f0
int deflateInit2_(struct z_stream_s* a0, int a1, int a2, int a3, int a4, int a5, const char* a6, int a7)
{
    LIFT_STUB(0x35f0);
}

// 0x37c0
int deflateResetKeep(struct z_stream_s* a0)
{
    LIFT_STUB(0x37c0);
}

// 0x38d0
static void flush_pending(struct z_stream_s* a0)
{
    LIFT_STUB(0x38d0);
}

// 0x3950
int deflate(struct z_stream_s* a0, int a1)
{
    LIFT_STUB(0x3950);
}

// 0x4210
int deflateEnd(struct z_stream_s* a0)
{
    LIFT_STUB(0x4210);
}

// 0x42f0
static int read_buf(struct z_stream_s* a0, unsigned char* a1, unsigned a2)
{
    LIFT_STUB(0x42f0);
}

// 0x43a0
static void lm_init(struct internal_state* a0)
{
    LIFT_STUB(0x43a0);
}

// 0x4460
static unsigned longest_match(struct internal_state* a0, unsigned a1)
{
    LIFT_STUB(0x4460);
}

// 0x4610
static void fill_window(struct internal_state* a0)
{
    LIFT_STUB(0x4610);
}

// 0x4860
static enum block_state deflate_stored(struct internal_state* a0, int a1)
{
    LIFT_STUB(0x4860);
}

// 0x4b10
static enum block_state deflate_fast(struct internal_state* a0, int a1)
{
    LIFT_STUB(0x4b10);
}

// 0x4f80
static enum block_state deflate_slow(struct internal_state* a0, int a1)
{
    LIFT_STUB(0x4f80);
}

// 0x54a0
static enum block_state deflate_rle(struct internal_state* a0, int a1)
{
    LIFT_STUB(0x54a0);
}

// 0x57f0
static enum block_state deflate_huff(struct internal_state* a0, int a1)
{
    LIFT_STUB(0x57f0);
}
