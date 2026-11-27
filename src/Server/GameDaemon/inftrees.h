// inftrees.h: inftrees.c (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
struct code;
enum codetype {
    CODES = 0x0,
    LENS = 0x1,
    DISTS = 0x2,
};
#ifdef __cplusplus
extern "C" {
#endif
int inflate_table(enum codetype, unsigned short*, unsigned, struct code**, unsigned*, unsigned short*);  // 0x78b0
#ifdef __cplusplus
}
#endif
