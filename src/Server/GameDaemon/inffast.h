// inffast.h: inffast.c (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
struct z_stream_s;
#ifdef __cplusplus
extern "C" {
#endif
void inflate_fast(struct z_stream_s*, unsigned);  // 0x59b0
#ifdef __cplusplus
}
#endif
