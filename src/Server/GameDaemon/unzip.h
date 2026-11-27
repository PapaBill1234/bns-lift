// unzip.h: unzip.c (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#ifdef __cplusplus
extern "C" {
#endif
int unzGoToFirstFile(void*);  // 0x25f0
int unzGoToNextFile(void*);  // 0x2660
int unzOpenCurrentFile3(void*, int*, int*, int, const char*);  // 0x2960
int unzReadCurrentFile(void*, void*, unsigned);  // 0x2b40
int unzCloseCurrentFile(void*);  // 0x2e50
#ifdef __cplusplus
}
#endif
