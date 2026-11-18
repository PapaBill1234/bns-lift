# lift-parity-pod-2 handoff
Turns: about 100 (4 stages, 25 turns each, plus this session)

## Done
- POD MATCH 570 -> 588 of 759 = 77.5 % (goal 90 % not reached). Full `tools/parity.sh`: ok, CG 420, LG 530, SCD 504 unchanged, 0 MATCH lost. Gate ok.
- Pattern 47 (+4), pattern 49 (in helpers-2), block order of `Get*` (+10), `RetrieveCharacterInfoRelayRequest` memset (+1),
  `SendRelayResponse` (+1), 2 x `initResponse` (+2). `ID128_GUID_ZERO` in `PostInfo` (score only).
- 2 x `ComposeResponsePacket` (Check 0x9570, Retrieve 0x1e230): score 77.8/75.2 -> 90.5, calls equal.
- Facts and tries that failed: `Docs/Parity/lessons.md` ("pod-2, stage 1" to "stage 4" and the end).

## DIFF and misses that stay open (function, signal, cause, why stopped)
- `ComposeResponsePacket` 0x9570, 0x1e230: consts (line numbers, unwind); no source form known.
- `CachedWatchdogManager::updateWorldList` (95.5), `UnsentPostContextManager::updateWorldList` (90.5), `WorldConfigManager::updateWorldList` (80.0):
  crash block after the loop in the original; not tried (same shape as the Compose fix: try the loop as the fall-through).
- `PostOfficeDaemon::initialize` (67.8), `initContextManager`: const -2 (unwind) and out-of-range exit; no source form found.
- `CacheGateChannel::combineFragmentRelayFormat` (53.9): not tried again, low value.
- `HandlePostOfficeRegisterPostReq` 0x1aaa0 (98.0): the compiler keeps the Log 208 block early; `goto` move failed.
- `PostOfficeDB` loaders 0x14e50, 0x15fa0, 0x18010, 0x190f0 (60 to 72): 17 + 70 inlined `BindCol` per loader; half edit in `.scratch/postofficedb-bindcol-macros.patch`.
- `SessionHandler::PacketHandler` (Agent, World, CacheGate, Management): Pattern 31 tail call, not tried.
- `PingRelayContext::processRelayResponse`: one `AlertSender::Write` missing in ours; cause not found.
- `PostInfo::CheckValidityPostData`: consts 0x2/0x7 vs 0x5; cause not found.
- `WorldChannelManager::RemoveWorldChannel`: linker folds `_Tree::erase`; not fixable in source.
- `TimerQueue::clearShortTermQueueSlot`, shared `operator delete[]` 0xb040: not fixable / not tried.
- 53 functions only in the original: STL/CRT code and string-literal ref noise; no source change possible.
