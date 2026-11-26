# Rust port brief (lead session)

Owner order, 2026-11-26: "launch 10 fable agents and have them port what was so far ported for the server binaries with a clean foundation, highly optimized modern rust code with an architecture that you would be surprised by. we want it to support 100.000 people easily (by that I mean that's how clean it is)."

You are the lead. You run in the Claude Code CLI. Read `Docs/Plan/modernize.md` first.

## Rules (all agents)

| Rule | Detail |
| --- | --- |
| Secrets | No binaries, PDBs, IDA databases, keys, passwords or abuse notes. Write `keyhere` for a key. |
| Source of logic | The C++ lift in `src/` (2019 + PDB). Port only code that exists there now. Do not invent game logic. |
| Names | PDB names only, in Rust case (`OnClose` → `on_close`). Keep the PDB name in a doc comment. |
| Parity | The client sees the same packets, order, codes and timing. Internals are modern. Keep all server safety checks. Fix bugs marked `// BUG:`; write the fix reason. |
| Safety | `#![forbid(unsafe_code)]` in every crate except `runtime` and `crypto`. There, each `unsafe` block has a `// SAFETY:` comment. |
| Quality | `cargo fmt`, `cargo clippy -D warnings`, `cargo test` green before each commit. |
| Platforms | Linux and Windows from one code base. |
| Language | Docs and comments in ASD-STE100. |
| Commits | Author and committer `Claude <noreply@anthropic.com>`. `--no-verify`. No Co-Authored-By. |
| Never | Read `~/.claude/.credentials*`, auth files, gateway keys or the IDA licence. Open IDA. Touch `slice/*` branches of the parity wave. |

## Place

Owner order, 2026-11-26: the Rust code lives in a NEW PRIVATE repo, `bns-rust-emulator`. Not in bns-lift.

| Item | Value |
| --- | --- |
| Repo | GitHub `PapaBill1234/bns-rust-emulator` (private). Local: `/home/ubuntu/Documents/Codex/private-project/bns-rust-emulator` (remote `origin` is set, no commits yet). |
| Workspace | Cargo workspace at the repo root. |
| Lead branch | `main` in the local clone. |
| Agent worktrees | `/home/ubuntu/Documents/Codex/bns-wt/rust-<crate>`, branch `crate/<crate>`, from `main` after step 1. |
| C++ source | bns-lift `src/`. Read only. Do not commit to bns-lift. |
| Old Rust work | `~/Documents/Codex/private-project/bns-server/` (build 381). Ideas only. Do not copy its `secrets/` or logs. |

Even as a private repo: no binaries, PDBs, IDA databases, keys or passwords.

## Architecture goal

Design for 100 000 concurrent clients on one host. The target is clean design, not a load record.

| Idea | Why |
| --- | --- |
| Thread-per-core shards. Each session lives on one shard. No shared locks on the hot path. | No lock contention; linear scale with cores. |
| Message passing between shards and daemons (bounded queues, typed messages). | Back-pressure instead of unbounded memory. |
| Zero-copy packet codec. Packets decode as views into the receive buffer. | No allocation per packet. |
| Sans-IO server cores: `core-*` crates are pure state machines (input event → output actions). | Deterministic tests, packet replay, and fuzzing with no sockets. |
| Slab or generational-index session tables. | Fixed memory per session; no dangling ids. |
| One I/O layer for Linux (epoll or io_uring) and Windows (IOCP), behind one trait. | Same core code on both systems. |
| Host crates: `host-headless` (service, config, structured logs, metrics) and later `host-gui`. | Headless first; GUI is a thin view. |

The lead may change these ideas with a reason in `ARCHITECTURE.md`.

## Step 1: lead writes the foundation (before agents)

1. Make the worktree. Run `cargo new --lib` for the workspace members.
2. Write `ARCHITECTURE.md`: crates, data flow diagram, shard model, message types, error rules.
3. Write the shared contracts as code: the `Service` trait of a sans-IO core, the event and action types, the packet `Codec` trait, the session id type. Make them compile.
4. Commit to `main` of bns-rust-emulator.

## Step 2: launch 10 agents

Use the Agent tool with `model: "fable"` and `isolation` off (each agent makes its own worktree). Launch all 10 in one message. Give each agent this brief path and its row.

| # | Crate | Scope | C++ source |
| --- | --- | --- | --- |
| 1 | `runtime` | Shard executor, timers, cross-shard queues, I/O trait with Linux and Windows backends. | none (new) |
| 2 | `net` | Sessions, framing, back-pressure, connection limits, idle kick. | `src/Server/Shared`, `src/library`, `src/External` net parts |
| 3 | `proto` | Packet types and zero-copy codecs for all packets in the lift. | `src/Server/Packet` |
| 4 | `crypto` + `bloodlib` | BroadcastCrypt, Dh, other crypto; BloodLib utilities. Test vectors from the C++ lift. | `src/library`, `src/External`, `src/Server/BloodLib` (find the crypto files with grep) |
| 5 | `core-lobbygate` | LobbyGate logic as a sans-IO core. | `src/Server/LobbyGate` |
| 6 | `core-lobbydaemon` | LobbyDaemon logic as a sans-IO core. | `src/Server/LobbyDaemon` |
| 7 | `core-cachegate` | CacheGate logic. | `src/Server/Economy/CacheGate` |
| 8 | `core-smartcoupon` | SmartCouponDaemon logic. | `src/Server/SmartCouponDaemon` |
| 9 | `core-postoffice` + `economy` | PostOfficeDaemon logic and the shared Economy code. | `src/Server/Economy/PostOfficeDaemon`, `src/Server/Economy/Shared` |
| 10 | `host-headless` + `loadsim` | Service main per exe, config, logs, metrics. A load simulator that runs 100 000 fake sessions against a core. A packet-replay harness for later C++ comparison. | none (new) |

Each agent:
1. Reads this brief, `ARCHITECTURE.md` and its C++ source.
2. Ports only its crate. It asks the lead (in its final report) for any contract change; it does not edit other crates.
3. Writes unit tests. Cores get event-in, action-out tests from the C++ logic.
4. Commits on its branch. Final report: what is ported, what is left, contract change requests, test count.

## Step 3: lead integrates

1. Review each branch. Reject code that breaks a rule above.
2. Merge into `main` one at a time. Keep the build green.
3. Run `loadsim` with 100 000 sessions. Write the result (memory per session, p99 latency) in `BENCH.md`.
4. Push `main` of bns-rust-emulator to GitHub.
5. Write a short report to `docs/handoffs/rust-port-1.md` in bns-rust-emulator: done, left, next Rust step (see the 10 % rule in `modernize.md`).

The parity wave in the desktop app works in bns-lift. Do not stop it.

## Style handover (owner order, 2026-11-26)

Opus will continue this code later. It must copy the Fable style exactly. So:

1. The lead writes `STYLE.md` in step 1, before the agents start. Content:
   - Code style rules with a short good and bad example for each rule.
   - The design choices and WHY for each (shards, sans-IO cores, zero-copy codec, error types, naming, module layout, tests).
   - A "how to port one C++ function" recipe, step by step, with one worked example from the lift.
   - A checklist that a reviewer runs on a new change.
2. Each agent adds to `STYLE.md` (own section per crate): the choices it made, why, and patterns that a later agent must copy.
3. In step 3 the lead merges the sections into one clean document. It removes conflicts and gives one rule for each case.
4. Test: the document must be enough for an Opus agent with no other context to port a new function in the same style.
