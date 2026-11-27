// trees.c: trees.c (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "trees.h"
#include "LiftStub.h"

// 0x7d30
static void init_block(struct internal_state* a0)
{
    LIFT_STUB(0x7d30);
}

// 0x7db0
static void pqdownheap(struct internal_state* a0, struct ct_data_s* a1, int a2)
{
    LIFT_STUB(0x7db0);
}

// 0x7ea0
static void gen_bitlen(struct internal_state* a0, struct tree_desc_s* a1)
{
    LIFT_STUB(0x7ea0);
}

// 0x80c0
static void gen_codes(struct ct_data_s* a0, int a1, unsigned short* a2)
{
    LIFT_STUB(0x80c0);
}

// 0x8170
static void build_tree(struct internal_state* a0, struct tree_desc_s* a1)
{
    LIFT_STUB(0x8170);
}

// 0x83c0
static void scan_tree(struct internal_state* a0, struct ct_data_s* a1, int a2)
{
    LIFT_STUB(0x83c0);
}

// 0x84b0
static void send_tree(struct internal_state* a0, struct ct_data_s* a1, int a2)
{
    LIFT_STUB(0x84b0);
}

// 0x8a20
static int build_bl_tree(struct internal_state* a0)
{
    LIFT_STUB(0x8a20);
}

// 0x8aa0
static void send_all_trees(struct internal_state* a0, int a1, int a2, int a3)
{
    LIFT_STUB(0x8aa0);
}

// 0x8d10
void _tr_stored_block(struct internal_state* a0, char* a1, unsigned long a2, int a3)
{
    LIFT_STUB(0x8d10);
}

// 0x8da0
void _tr_flush_block(struct internal_state* a0, char* a1, unsigned long a2, int a3)
{
    LIFT_STUB(0x8da0);
}

// 0x8fd0
static void compress_block(struct internal_state* a0, const struct ct_data_s* a1, const struct ct_data_s* a2)
{
    LIFT_STUB(0x8fd0);
}

// 0x9440
static int detect_data_type(struct internal_state* a0)
{
    LIFT_STUB(0x9440);
}

// 0x94c0
static void bi_flush(struct internal_state* a0)
{
    LIFT_STUB(0x94c0);
}

// 0x9550
static void bi_windup(struct internal_state* a0)
{
    LIFT_STUB(0x9550);
}

// 0x95b0
static void copy_block(struct internal_state* a0, char* a1, unsigned a2, int a3)
{
    LIFT_STUB(0x95b0);
}
