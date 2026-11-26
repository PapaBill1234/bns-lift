# Modernize plan: C++ lift → Rust

Owner goal, 2026-11-26. Status: plan only.

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

Owner decision, 2026-11-26: every exe gets the full C++ lift, GameDaemon too. The lift is the parity oracle. The Rust version grows with the lift: one Rust step at every 10 % of MATCH.

```
C++ lift  ──10%──20%──30%── ... ──95%
              │    │    │          │
Rust port   R10  R20  R30   ...  R95    (port the newly matched functions)
```

| Item | Rule |
| --- | --- |
| Trigger | The exe passes a new 10 % step of its counted MATCH. |
| Scope | Port only the functions that reached MATCH since the last step. |
| Gate | Packet replay and function tests pass for all ported code. Earlier steps stay green. |
| Owner | A separate Rust card per step. It does not block the C++ lift. |
| Exes | LobbyDaemon, CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon, then GameDaemon. |

Why: one large port at the end costs too much for GameDaemon. Small steps port code while the lift context is fresh, and each step is tested against the C++ code that just matched.

The 4 small exes are already above 60 %. Their first Rust step covers all MATCH code up to the current 10 % step.

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

## Client target (owner change, 2026-11-26)

The Rust servers speak the packets of the 2016 client (KR 0.0.167.5864, the client C++ lift), not the 381 client.

| Layer | Source |
| --- | --- |
| Client wire format | 2016 client (167). One `ClientDialect` seam in the Rust `proto` crate. |
| Server ↔ server packets | 2019 + PDB lift (the client does not see them). |
| Server logic | 2019 + PDB lift, no change. |
| 2019 content (classes, skills, dungeons, raids, maps) | Later: converted into the 2016 datafile. The MODERN client build gets ready for it now. |

This C++ lift does not change. It stays the logic oracle for the 2019 + PDB servers.
