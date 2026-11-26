# Modernize plan: C++ lift → Rust

Owner goal, 2026-11-26. Status: plan only. Do not start before the gate in step 1.

## Goal

Each server exe gets a modern Rust version.

| Need | Meaning |
| --- | --- |
| Memory safety | Safe Rust. `unsafe` only in small, reviewed FFI or crypto modules. |
| Headless | The server runs as a service with no window. Config file and log output. |
| Original GUI look | An optional window that looks like the original server window. ❓ Read the original window layout from the 2019 + PDB resources. |
| Platforms | Windows and Linux, from one code base. |
| Parity | The client sees the same packets, order, codes and timing. Internals are modern (see `parity-scope`). |

Rust has no garbage collector. It frees memory by ownership (RAII). This gives memory safety with no GC pauses, which is good for server tick time.

## Order

```
1. C++ lift of the 5 exes to 95 % MATCH     (now)
2. Rust port of the 5 exes                   (C++ lift = test oracle)
3. GameDaemon: direct 2019 + PDB → Rust      (no full C++ lift)
```

| Step | Exes | Gate to start |
| --- | --- | --- |
| 1 | LobbyDaemon, CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon | running |
| 2 | the same 5 | the 4 small exes at 95 %; LobbyDaemon at its checkpoint |
| 3 | GameDaemon | step 2 done for 1 exe, so that the method is proven |

## Why GameDaemon skips the full C++ lift

GameDaemon is much larger than the 5 exes. A full C++ lift and then a Rust port pays twice for the same logic. For GameDaemon:

1. Port each subsystem from 2019 + PDB straight to Rust.
2. Lift to C++ only the hard functions that need a MATCH oracle (formulas, crypto, packet encode and decode).
3. Test the Rust code against those C++ functions with the same inputs.

## Test method for the Rust port

| Test | Source of truth |
| --- | --- |
| Packet replay | Captured or generated client sessions. Compare the Rust replies with the C++ lift replies, byte for byte. |
| Function tests | Pure functions (crypto, formulas, parsers) called through FFI on the C++ lift. |
| Soak test | Many fake clients. Measure tick time and memory. |

The parity engine needs a new target type for this: a packet-replay gate in place of funcdiff.

## Structure

| Crate | Content |
| --- | --- |
| `core-<exe>` | Server logic. No I/O, no GUI. |
| `net` | Async network (tokio). Shared by all exes. |
| `proto` | Packet types and codecs. Shared. Official names only. |
| `host-headless` | Service main, config, logs. |
| `host-gui` | Optional window with the original look. ❓ GUI kit: egui or Slint; choose when step 2 starts. |

## Reuse

- `bns-server/` has Rust work for LobbyGate and LobbyDaemon (381). Reuse its `proto` and `net` parts when they pass the packet replay.
- Packets: 381 client decides. Logic: 2019 + PDB.
