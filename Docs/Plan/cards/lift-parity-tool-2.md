# lift-parity-tool-2: funcdiff fixes for vtable refs and `.tls` offsets, build header dependencies

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough.

## Goal
funcdiff reads vtable refs and `.tls` offsets correctly. `tools/vs2010/build.sh` rebuilds an object after a header change. Each exe gets the measured gain of `review-1.md` section 1.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/review-1.md` (sections 1 and 3), `Docs/Parity/lessons.md` (section C) and `Docs/Parity/noise.md`.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- This is a tooling card. Change no source in `src/`.
- Fix V: in `tools/funcdiff.py` (data ref naming, near line 230), when a `??_7` (vtable) symbol is at the exact RVA, use the symbol before `Image.string_at()`. Measured: CG +4, LG +7, SCD +12, POD +9, 0 MATCH lost.
- Fix T: when a function reads `gs:` (TLS), name a `mov` immediate that is a `.tls` offset of a PDB `S_LTHREAD32` or `S_GTHREAD32` symbol by that symbol. Measured after Fix V: CG +10, LG +7, SCD +7, POD +7.
- The measured test copy is in `Docs/Parity/tool-2-fix.patch` (diff against `tools/funcdiff.py` of review 1). It switches each fix on with env `EXP_VT=1` and `EXP_TLS=1`. Apply it without the env switches (each fix always on). Delete the patch file when the fixes are in `tools/funcdiff.py`.
- Name forms (lessons C3): `<K const ,V>` against `<K const,V>`; `?Setup@PacketCrypt@@SA?AW4ErrCode@1@H@Z` not demangled in the original PDB.
- Expected gain: +63 in the 4 exes, shared 369 -> 394 of 489.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. Write the start counts.
2. Apply Fix V and Fix T in `tools/funcdiff.py`. Prove each in `Docs/Parity/noise.md` with one function (before, after, why the code is equal).
3. Make the name forms of lessons C3 equal on both sides. Prove it in `noise.md`.
4. Make `tools/vs2010/build.sh` rebuild an object when a header that it includes is newer (for example `/showIncludes` into a dependency file).
5. Remove each line of `Docs/Parity/allow-worse.txt` that the fixes make unnecessary.
6. Run `tools/parity.sh` and `tools/parity_shared.py --list`. Write the counts in the handoff and update `lessons.md` C1, C2, C4.

## Files
- `tools/funcdiff.py`
- `tools/vs2010/build.sh`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-tool-2.md`

## Done when
- Fix V and Fix T are in `tools/funcdiff.py` with proof in `noise.md`, and no exe loses a MATCH function.
- A header change rebuilds the objects that include it.
- `tools/parity.sh` passes.
