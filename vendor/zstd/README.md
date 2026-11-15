# zstd (upstream, not lifted)

CacheGate links the zstd compression code (zstd_compress, zstd_fast,
zstd_double_fast, zstd_lazy, zstd_opt, fse_compress). We do not lift it.
We build the upstream source.

## Version

- Version: **1.3.5** (inferred, ❓).
- The binary has no version string and no `ZSTD_versionNumber`.
- The PDB symbols agree with 1.3.5:
  - `ZSTD_compressBlock_fast_dictMatchState` exists. The doubleFast and lazy
    strategies have no `dictMatchState` variant. 1.3.6 added those.
  - `ZSTD_compressBlock_btultra` exists. `btultra2` (1.3.8 and later) does not.
  - `ZSTD_CCtx_resetParameters` exists (1.3.8 and later changed this API).

## Source

- Upstream: https://github.com/facebook/zstd
- This repo does not include the source. Get it with this command:

```sh
git clone --depth 1 --branch v1.3.5 https://github.com/facebook/zstd vendor/zstd/src
```

`CMakeLists.txt` builds the `lift_zstd` static library from
`vendor/zstd/src/lib/` only if `vendor/zstd/src/` exists.
Do not commit `vendor/zstd/src/`.
