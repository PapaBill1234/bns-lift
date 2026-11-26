# Handoff: lift-parity-lg-5b (LG: daemon, Client, config modules)

Branch: `slice/lift-parity-lg-5b`. The branch is not merged and not pushed.

## Result

`tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok. No exe has a MATCH -> DIFF change.

| Exe | MATCH before (main) | MATCH after | Change |
| --- | --- | --- | --- |
| CacheGate | 456/491 | 456/491 (92.9 %) | +0 |
| LobbyGate | 658/739 | 670/739 (90.7 %) | +12 |
| SmartCouponDaemon | 630/669 | 630/669 (94.2 %) | +0 |
| PostOfficeDaemon | 694/759 | 694/759 (91.4 %) | +0 |
| LobbyDaemon | 1024/2204 | 1024/2204 (excluded 127) | +0 |

## New MATCH (LobbyGate)

| Function | Score before | Commit |
| --- | --- | --- |
| wmain | 66.7 | 7d9c531 |
| wmain$dtor$0 | (not paired) | 7d9c531 |
| LobbyGate::FailedEventObjectHandler | 93.3 | 5a10f6d |
| LobbyGate::PrintDependency | 91.7 | 0dc8d1a |
| ClientSessionHandler::OnClose | 97.7 | f1b7dad |
| Client::SendTakeGoodsOk | 98.9 | f1b7dad |
| Client::SendListLobbyServiceItemInfoOk | 98.9 | f1b7dad |
| ContentsRuleConfig::LoadContentsRuleConfig | 93.6 | fc26022 |
| ContentsRuleConfig::MakeListPacket | 86.9 | fc26022 |
| ContentsRuleConfig::UpdateAllVariable | 81.8 | fc26022 |
| PcCafeMileageFeverTimeScheduleList::Set | 98.2 | 7149bc0 |
| ClientManager::BroadcastAnnounceNotify | 97.8 | 937960c |

## Lessons

The review merges these lessons into `Docs/Parity/lessons.md`. This card did not edit that file.

### lg-5b

#### Worked

| Function | Before | After | Count | Step |
| --- | --- | --- | --- | --- |
| wmain (+ wmain$dtor$0) | 66.7 | MATCH | 2 | Remove `extern "C"`. The EH state then is -2 and the dtor funclet exists. |
| FailedEventObjectHandler | 93.3 | MATCH | 1 | Use a switch. Read EventId again for the log. |
| PrintDependency | 91.7 | MATCH | 1 | The original prints minor version 0 with two `%d`. |
| OnClose | 97.7 | MATCH | 1 | Put `inline_depth(0)` around the function. Write out ~GateKeyEntry at the first site. The call lists really match (no STL calls), so A20 is valid. |
| SendTakeGoodsOk, SendListLobbyServiceItemInfoOk | 98.9 | MATCH | 2 | Call `reserveFragment(fp, 2)` before the first Compose. |
| LoadContentsRuleConfig | 93.6 | MATCH | 1 | Use one shared error tail (A17): set `line` and `message`, then `goto fail`. Use placement new with the null test. |
| MakeListPacket | 86.9 | MATCH | 1 | Use 260-element buffers, `Alloc` line 373, placement new, an unsigned loop index. |
| UpdateAllVariable | 81.8 | MATCH | 1 | Use 260-byte UTF-8 buffers and an unsigned loop. Read `_Def[i].offset` in each case. |
| PcCafeMileageFeverTimeScheduleList::Set | 98.2 | MATCH | 1 | Read `subTop` before `start[top]`. Make the `sub[]` store the fall-through block. |
| BroadcastAnnounceNotify | 97.8 | MATCH | 1 | Return after each failure log. Do not merge the error tails. |
| CheckMinMaxBoundary | 93.3 | 95.8 | 0 | Use the params (LTCG propagates them) and an `int` index. Only a data-layout ref stays. |

#### Failed

| Function | Before | After | Count | Try |
| --- | --- | --- | --- | --- |
| LobbyGate::reload | 87.1 | MATCH (funcdiff-only) | 0 | `inline_depth(0)`. Reverted: the MATCH comes from funcdiff `expand()`. The original has SetRunningInfo out of line. |
| LobbyGate::reload | 87.1 | 96.4 | 0 | Failure-first form + `wcscmp` + `swprintf_s<128>`. Not kept: score only. |
| GateKeyManager::MakeGateKey | 94.3 | MATCH (funcdiff-only) | 0 | lg-4 e55de2a `inline_depth(0)`. Dropped: the STL calls go out of line. Lessons line 901. |
| ~GateKeyEntry noinline | – | – | -2 | HandleEvent 96.8 -> 92.4, GateKeyManager::Finalize MATCH -> 97.4. Reverted. |
| ContentsRuleConfig::Dump | 99.2 | 98.7 | 0 | Unsigned loop. It fixed the refs but added const 0xd. Reverted. |
| SendGetCharacterInfoListOk | 99.0 | 99.0 | 0 | Copy slotId after the reserve. No change. |
| SendGetCharacterInfoListOk | 99.0 | 99.0 | 0 | do/while(false) + break with one fail block. No change. |

Rule: A20 (`inline_depth(0)`) is valid only when the original also has no inlined STL calls in the function. Check the call list in the original before you keep it.

## Unfixed DIFF (LobbyGate, card files)

| Function | Score | Signal | Cause | Stop reason |
| --- | --- | --- | --- | --- |
| ContentsRuleConfig::Dump | 99.2 | end-pointer ref FRAGMENT_PACKET_FILE | data layout; the original keeps zero in r12 (`lea esi,[r12+0xd]`) | 2 tries |
| ContentsRuleConfig::CheckMinMaxBoundary | 95.8 | end-pointer ref | data layout: the next .rdata object in ours is a FragmentPacket.cpp literal, in the original it is LobbyGateConfig::_Def | not fixable in the card files |
| GateKeyManager::MakeGateKey | 94.3 | call 0x3e80 at the second site | LTCG inline choice; `inline_depth(0)` is funcdiff-only (STL) | 3 tries |
| LobbyGate::AddJobTimer | 96.3 | `_instance` ref | LTCG this-propagation | stop list |
| ClientSessionTimerJob::HandleEvent | 96.8 | `_instance` ref, const 0x3 | LTCG this-propagation | stop list |
| LobbyGate::initialize | 91.5 | missing cert decode, memset, Dump | the original is patched: `jmp 0x13095` at 0x12faf | same cause as SCD; not a source fix |
| LobbyGate::reload | 87.1 | SetRunningInfo/SetInvalidInfo calls | LTCG inline choice; the honest form needs TimerQueue::Add (protected) | funcdiff-only otherwise |
| LobbyGateReloadInvalidRestoreTimer::restoreInvalid | 93.3 | end-of-array ref | HEX_PREFIXES vs bypassHandler (data layout) | not fixable in the card files |
| ClientManager::Finalize | 95.2 | const 0x18 vs 0x10 | TLS offset of `__delv_buf__` depends on TLS vars in other modules (Session.obj Thread_LastCryptError, prng _Instance) | outside scope |
| Client::SendGetCharacterInfoListOk | 99.0 | const 0x18 | original `add rdi,0x18`, ours `lea rbx,[r12+0x18]` | 2 tries + lg-4 |

## Notes

- IDA was not opened. The work used the Hex-Rays cache and `.scratch/dis2.py`.
- `src/Server/LobbyDaemon/` is not changed. The baselines, `progress.tsv` and `excluded.tsv` are not changed.

Turns: 282
