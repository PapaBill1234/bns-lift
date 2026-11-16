/* zstd entry points that CacheGate uses. vendor/zstd/src is not in the repo, so lift_zstd is not built.
   The original exe links upstream zstd (see vendor/zstd/README.md). */
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
