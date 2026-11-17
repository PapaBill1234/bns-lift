/* zstd entry points for the exes when vendor/zstd/src is not present (CMake target lift_zstd_stub).
   With vendor/zstd/src (upstream zstd 1.3.5, see vendor/zstd/README.md), CMake builds lift_zstd and does not use this file. */
#include <stddef.h>

/* ZSTD_customMem is three pointers (customAlloc, customFree, opaque). It is passed by pointer on x64. */
typedef struct ZSTD_customMem_stub
{
    void* customAlloc;
    void* customFree;
    void* opaque;
} ZSTD_customMem_stub;

void* ZSTD_createCCtx_advanced(ZSTD_customMem_stub customMem)
{
    (void)customMem;
    return NULL; /* TODO(lift-cg-5) link upstream zstd */
}

/* 0x18380 */
size_t ZSTD_freeCDict(void* cdict)
{
    (void)cdict;
    return 0; /* TODO(lift-cg-5) link upstream zstd */
}

/* 0x30AA0 (LobbyGate). zstdPacketCompress calls it. The result is a zstd error code, thus FAILED_COMP. */
size_t ZSTD_compress_usingCDict(void* cctx, void* dst, size_t dstCapacity, void const* src, size_t srcSize,
                                void const* cdict)
{
    (void)cctx;
    (void)dst;
    (void)dstCapacity;
    (void)src;
    (void)srcSize;
    (void)cdict;
    return (size_t)-1; /* TODO(lift-lobbygate-4) link upstream zstd */
}
