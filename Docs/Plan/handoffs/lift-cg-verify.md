# lift-cg-verify handoff: CacheGate run and compare

## Done
- `tools/verify/run_cachegate.sh`: runs one exe (lifted or original) under wine64 (wineconsole, Xvfb :77,
  own prefix). Saves log, listen ports, peer and client bytes, pktlog records. Options `--pktlog --peer --client`.
- `tools/verify/compare_cachegate.sh`: runs both, normalizes, writes 5 diffs in `build/verify/compare/`.
- `tools/verify/replay.py`: CacheD peer (listen) and client (connect). No change in this session.
- Original exe: starts, listens on 20800, sends a 10-byte hello to CacheD, pktlog patch works.
- Self test (original against original, `--pktlog`): 0 changed lines in log, ports, peer, client, pkl.
- `Docs/Verify/CacheGate.md`: run facts, reference behaviour, noise, checks table.

## Not done
- All compare checks of the lifted exe. `build/CacheGate.exe` does not exist: no CMake target,
  `src/CacheGate/` has only `CacheD.h` (lift-cg-5 not done).
- Tests with packet data (Hello, Relay) from a captured stream.

## ❓
- If the 381 CacheDaemon accepts the 2019 hello. Not tested: the 381 set was not running.

## Blocked
- Lifted checks: blocked by lift-cg-5. Then run `tools/verify/compare_cachegate.sh 20 --pktlog`.

## Gate result
- `tools/gate.sh`: gate ok (rc 0). Only warnings (offsetof on non-standard-layout types in common code).
