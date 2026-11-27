// deflate.h: deflate.c (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
struct z_stream_s;
#ifdef __cplusplus
extern "C" {
#endif
int deflateInit2_(struct z_stream_s*, int, int, int, int, int, const char*, int);  // 0x35f0
int deflateResetKeep(struct z_stream_s*);  // 0x37c0
int deflate(struct z_stream_s*, int);  // 0x3950
int deflateEnd(struct z_stream_s*);  // 0x4210
#ifdef __cplusplus
}
#endif
