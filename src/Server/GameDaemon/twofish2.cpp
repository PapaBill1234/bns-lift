// twofish2.cpp: twofish2.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "twofish2.h"
#include "LiftStub.h"

// 0x39d410
int __cdecl ParseHexDword(int, char *, unsigned long *, char *)
{
    LIFT_STUB(0x39d410);
}

// 0x39d4e0
unsigned long __cdecl RS_MDS_Encode(unsigned long, unsigned long)
{
    LIFT_STUB(0x39d4e0);
}

// 0x39d680
void __cdecl BuildMDS(void)
{
    LIFT_STUB(0x39d680);
}

// 0x39db80
void __cdecl ReverseRoundSubkeys(::keyInstance *, unsigned char)
{
    LIFT_STUB(0x39db80);
}

// 0x39dbd0
void __cdecl Xor256(void *, void *, unsigned char)
{
    LIFT_STUB(0x39dbd0);
}

// 0x39dee0
int __cdecl reKey(::keyInstance *)
{
    LIFT_STUB(0x39dee0);
}

// 0x39ead0
int __cdecl blockEncrypt(::cipherInstance *, ::keyInstance *, unsigned char *, int, unsigned char *)
{
    LIFT_STUB(0x39ead0);
}
