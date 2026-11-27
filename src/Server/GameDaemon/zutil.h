// zutil.h: zutil.c (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#ifdef __cplusplus
extern "C" {
#endif
void* zcalloc(void*, unsigned, unsigned);  // 0x96a0
void zcfree(void*, void*);  // 0x96b0
#ifdef __cplusplus
}
#endif
