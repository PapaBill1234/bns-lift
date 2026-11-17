# zstd (upstream, not lifted)

CacheGate links the zstd compression code (zstd_compress, zstd_fast,
zstd_double_fast, zstd_lazy, zstd_opt, fse_compress). We do not lift it.
We build the upstream source.

## Version

- Version: upstream `dev` commit **bb6eaf64** ("Merge pull request #1153
  from facebook/dynThreshold", 2018-05). This is between 1.3.4 and 1.3.5.
- Set by lift-parity-s3 with funcdiff. With bb6eaf64, all zstd functions are
  MATCH in the 4 exes. One exception: LobbyGate `ZSTD_compressBegin_internal`
  (98.8, LTCG inlines `ZSTD_compress_insertDictionary`).
- v1.3.5 gave DIFF in zstd_opt.c and other files.
- Commit ac4f7ead (#1154, altOpt) gives 3 `ZSTD_litLengthContribution`
  calls in zstd_opt.c. The original has 4, as bb6eaf64 has.
- The binary has no version string and no `ZSTD_versionNumber`.

## Source

- Upstream: https://github.com/facebook/zstd
- This repo does not include the source. Get it with these commands.
  A shallow fetch of a short hash fails, so fetch by date:

```sh
git clone --depth 1 https://github.com/facebook/zstd vendor/zstd/src
cd vendor/zstd/src
git fetch --shallow-since=2018-05-01 origin dev
git checkout bb6eaf64
```

`CMakeLists.txt` builds the `lift_zstd` static library from
`vendor/zstd/src/lib/` only if `vendor/zstd/src/` exists.
Do not commit `vendor/zstd/src/`.
After a change of `vendor/zstd/src/`, delete `build-vs2010/obj/vendor`.
