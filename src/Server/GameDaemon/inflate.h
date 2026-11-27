// inflate.h: inflate.c (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
struct z_stream_s;
#ifdef __cplusplus
extern "C" {
#endif
int inflateResetKeep(struct z_stream_s*);  // 0x5ea0
int inflateReset2(struct z_stream_s*, int);  // 0x5f20
int inflateInit2_(struct z_stream_s*, int, const char*, int);  // 0x5fc0
int inflate(struct z_stream_s*, int);  // 0x6180
int inflateEnd(struct z_stream_s*);  // 0x7850
#ifdef __cplusplus
}
#endif
