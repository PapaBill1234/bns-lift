// trees.h: trees.c (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
struct internal_state;
#ifdef __cplusplus
extern "C" {
#endif
void _tr_stored_block(struct internal_state*, char*, unsigned long, int);  // 0x8d10
void _tr_flush_block(struct internal_state*, char*, unsigned long, int);  // 0x8da0
#ifdef __cplusplus
}
#endif
