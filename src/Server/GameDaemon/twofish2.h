// twofish2.h: twofish2.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

int __cdecl ParseHexDword(int, char *, unsigned long *, char *);  // 0x39d410
unsigned long __cdecl RS_MDS_Encode(unsigned long, unsigned long);  // 0x39d4e0
void __cdecl BuildMDS(void);  // 0x39d680
void __cdecl ReverseRoundSubkeys(::keyInstance *, unsigned char);  // 0x39db80
void __cdecl Xor256(void *, void *, unsigned char);  // 0x39dbd0
int __cdecl reKey(::keyInstance *);  // 0x39dee0
int __cdecl blockEncrypt(::cipherInstance *, ::keyInstance *, unsigned char *, int, unsigned char *);  // 0x39ead0
