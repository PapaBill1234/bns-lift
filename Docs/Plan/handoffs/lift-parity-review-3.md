# lift-parity-review-3: handoff

## Done
- `tools/gate.sh` ok. `tools/parity.sh` ok (MATCH -> DIFF 0). No source change in this card.
- `Docs/Parity/review-3.md` (new): measure, what worked, what did not work, turn cost, DIFF by cause class, round 4 plan.
- `Docs/Parity/lessons.md` cleaned and sorted (A1 to A24, B, C, D, F). The header maps the review-2 numbers to the review-3 numbers.
  The manual notes are merged into A and B; the long manual notes stay in F.
- `Docs/Parity/rules-proposal.md`: section 5 (P1 to P11).
- Round 4: 10 cards in `Docs/Plan/cards/` and rows in `Docs/Plan/queue/lift-parity-review-3.tsv`.

## State of each exe (LG, SCD, POD below 90 %: round 4 queued; no 90+ round, no `plus-state.tsv`)
| Exe | Review 2 | Review 3 | Change | State |
| --- | --- | --- | --- | --- |
| CG | 420/491 (85.5 %) | 448/491 (91.2 %) | +28 | 90 % met; cg-4 works toward 95 % (467) |
| LG | 530/739 (71.7 %) | 627/739 (84.8 %) | +97 | below 90 %; needs 39 more (666) |
| SCD | 510/669 (76.2 %) | 582/669 (87.0 %) | +72 | below 90 %; needs 21 more (603) |
| POD | 588/759 (77.5 %) | 665/759 (87.6 %) | +77 | below 90 %; needs 19 more (684) |
| Shared | 421/499 (84.4 %) | 490/549 (89.3 %) | +69 | 59 names not MATCH in all 4 exes; 99 % needs 544 |

Each exe gained 2 % or more. No stall check is necessary.
The shared denominator went from 499 to 549 because the crypto functions now pair (cryptolib-3).

## Shared DIFF by cause (review-3 section 5)
By class (entries in 2 or more exes): constants only 57, refs 31, orig calls more 23, other callee 19, ours calls more 11, call order 9, call count 5, EH state const 4. Sum 159.

By named cause (59 shared names):
| Group | Functions | Round 4 card |
| --- | --- | --- |
| Crypto | 14 (`BigInteger::*`, `OaepEncoder::*`, `Rsa::decrypt`, `RsaPublic::*`) | crypto-4 |
| `aes128Table*` | 4 entries | stop list |
| EH state `-2` | `wmain` x4, `FragmentPacketConcatenater::Clone` | ehstate-4 |
| BloodLib network | `Session::*`, `IoWorker::run`, `clearPacketBufferList`, `Network::Clear`/`OpenPort` | net-4 |
| Packet | `PacketBuffer::Compose`/`Decompose`/`CheckCompose`, `PushRepeatCount`, `FragmentPacketConcatenater::Add` | packet-4 |
| Console and config | `PipeConsole::processCommand`, `PipeCommandProcess::processCommand`, `InitSymbol`, `UninstallService`, `DaemonConfig::Dump`, `BnsCommonConfig::Load`/`Reload` | console-4 |
| CacheGate handlers | `HandleCacheGate*` (5), `CacheGateSessionHandler::OnConnect`/`OnClose` | pod-4, cg-4 |
| Stop list | `Session::Session`, `StaticPageMemoryManager::Initialize`, `ThreadManager::Initialize`, `Daemon::Start`, `PipeConsole::run`, `SetInvalidInfo` | none |

Shared cards first (crypto-4, ehstate-4, net-4, packet-4, console-4), then the exe cards (lg-4, scd-4, pod-4, cg-4), then review-4.

Turn cost round 3: about 659 turns for 191 MATCH (3.5 turns per MATCH; 6.1 without cryptolib-3). The manual work gave 83 more MATCH.
Expected after round 4: CG about 463, LG about 665, SCD about 607, POD about 690, shared about 515/549.

## ❓
- dbbind-3 shows +0 in progress.tsv, but it made SCD `DbTransaction::BindCol` 0x20e40 MATCH. The manual work row counted it first. ❓ The order of the two rows in progress.tsv does not show the order of the commits.
- The classifier is a scratch script (rules of `triage.md`, plus the class "EH state const"). It is not in `tools/`. Counts can differ by a few from a later tool.
- LG has the smallest margin (estimate 665 against 666 needed). If crypto-4 or lg-4 gives less than half its estimate, review-4 must apply the stall check.

Blocked: none.
Turns: 45
