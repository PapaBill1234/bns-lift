// md5.h: md5.c (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
// PDB layout (size 0x58).
struct md5_state_s
{
    unsigned int count[2];
    unsigned int abcd[4];
    unsigned char buf[64];
};
#ifdef __cplusplus
extern "C" {
#endif
void md5_init(struct md5_state_s*);  // 0x6ff850
void md5_append(struct md5_state_s*, const unsigned char*, int);  // 0x6ff880
void md5_finish(struct md5_state_s*, unsigned char*);  // 0x6ff980
#ifdef __cplusplus
}
#endif
