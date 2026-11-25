# lift-cg-4: CacheGate lift: crypto and zstd

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/CacheGate/CacheGate.exe`. PDB: `<work-root>/Service_348_8349/Service/CacheGate/bin/CacheGate.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards for the state of `src/common/`.

## Modules (one `.cpp` + `.h` per PDB module)
- blowfish, aes128, aes128Table, aes128NI, ctr, prng, ripemd160, Crypto (about 40). Lift these.
- zstd_compress, zstd_fast, zstd_double_fast, zstd_lazy, zstd_opt, fse_compress: do NOT lift. Find the zstd version (strings, constants such as `ZSTD_VERSION_NUMBER`, function set). Write `vendor/zstd/README.md` with the version and the upstream URL. Add a CMake rule that builds upstream zstd from `vendor/zstd/src/` if it exists. Do not download it in this card. Write the download command in the README.

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -symbols`, section of the module) or from IDA.
2. Decompile them in batches to `.scratch/`. Lift them to C++ with the PDB types (`include/pdb/CacheGate/types.h`).
3. Add the files to the CMake target `lift_common` (static library; create it if it does not exist).
4. Run `tools/gate.sh` after each module.

## Files
- `src/common/`
- `vendor/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
