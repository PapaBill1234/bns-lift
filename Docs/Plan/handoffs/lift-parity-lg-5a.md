# Handoff: lift-parity-lg-5a (LG: LobbyD channel and handlers)

Branch: `slice/lift-parity-lg-5a`. Commits: `6c57146`, `e86b356`, and this handoff.
`tools/gate.sh` and `tools/parity.sh` pass after each code commit. No MATCH is lost in any exe.

## Result

| Exe | MATCH before (main) | MATCH after | Change |
| --- | --- | --- | --- |
| CacheGate | 456/491 | 456/491 (92.9 %) | +0 |
| LobbyGate | 658/739 | 672/739 (90.9 %) | +14 |
| SmartCouponDaemon | 630/669 | 630/669 (94.2 %) | +0 |
| PostOfficeDaemon | 694/759 | 694/759 (91.4 %) | +0 |
| LobbyDaemon | 1024 (excluded 127) | 1024 (excluded 127) | +0 |

New MATCH (14): `BypassPacket`, `ContentsRuleListReq`, `GetPcCafeMileageFeverTimeScheduleListReq`, `GetWorldInfoListReq`,
`InitSessionWithLobbyTokenFail`/`Ok`, `InitSessionWithNPTokenFail`/`Ok`, `StartSessionWithLobbyTokenFail`,
`StartSessionWithNPTokenFail`, `LobbyD::hello`, `LobbyD::Hello`, `LobbyDSessionHandler::OnConnect`, `LobbyDSessionHandler::OnClose`.

The card target (703 LG MATCH) is not reached.

## Steps

| Step | Commit | LG MATCH |
| --- | --- | --- |
| Fold the unmerged `slice/lift-parity-lg-4` diff for the 3 card files | `6c57146` | 658 -> 669 |
| `findDisconnectedNode` with `wcscmp`, `LobbyD::Hello` Leave per branch, `StartSession*Ok` compose form | `e86b356` | 669 -> 672 |

## Functional fixes (kept, client-visible)

- `StartSessionWithLobbyTokenOk` (0xf230) and `StartSessionWithNPTokenOk` (0xcd00): the lift did not call `IncRepeatCount` after each repeat compose.
  The client got repeat counts of 0 for the grade lists. The new form does the inlined `FragmentPacket::IncRepeatCount` (0x3840).
- The reload notify in both handlers now sets `*extraData = 0` after the send (HR 0xf230, 0xcd00).
- 0xf230 passes 7 as the first `Compose` value (`mov r8d, 7` at 0xf8b1). The lift keeps it with a `// BUG:` note.
- These changes give a score gain only, but they fix the packet content. The parity scope is client-visible behaviour, so they are kept.

## Lessons

### Worked

| Function | Before | After | Count | Pattern |
| --- | --- | --- | --- | --- |
| `LobbyDSessionHandler::OnConnect`, `OnClose` | 94.4, 95.2 | MATCH | 2 | A string compare against a literal (`repe cmpsw`, count = length + 1) is `wcscmp(p, L"literal") == 0`. A hand loop gives other code and consts. |
| `LobbyD::Hello` | 93.5 | MATCH | 1 | Two `LeaveCriticalSection` calls in the original mean one Leave in each branch, not one Leave before the test. |
| lg-4 forms (10 handlers and `LobbyD::hello`) | various | MATCH | 11 | Unmerged branch work: apply the diff on the new base and measure. |
| `StartSessionWith*TokenOk` | 88.7, 89.5 | 97.3, 96.7 | 2 | `#pragma inline_depth(0)` keeps the `FragmentPacket` ctor, `Allocate` and `PopRepeatCount` out of line. A `__forceinline` helper still inlines. Compose-fail branch first (`if (Compose(...) == 0) {fail} else {...}`). Per-exit `removeReferenceCount(line); goto cleanup`. |

### Failed

| Function | Before | After | Count | Pattern |
| --- | --- | --- | --- | --- |
| `StartSessionWith*TokenOk` | 97.3, 96.7 | not MATCH | 2 | With `inline_depth(0)` the `~FragmentPacket` call is shared. The original inlines it to one `Packet::Clear` per exit. Without the pragma the ctor and `PopRepeatCount` inline (91.3). |
| `HandleLobbyLobbyGate_HelloOk` | 87.3 | 99.3 | 1 | Log text as an argument (`// BUG:` 0xaf20), loops in `if (count > 0)`. Score only, reverted (rule 3). Left: the original loads `L"yes"` again at lines 158 and 170. |
| `HandleLobbyGate_HelloReq` | 93.3 | 94.1 | 1 | `Packet reply;` with field stores, no explicit Clear. Score only, reverted. The rest is register choice for 0 (r12 against rbx). |
| `HandleLobbyLobbyGate_CloseSessionNotify` | 96.8 | 92.3 | 1 | Success branch first. Worse, reverted. |

## Remaining DIFF functions in scope

| Function | Score | Signal | Cause | Why stopped |
| --- | --- | --- | --- | --- |
| `HandleLobbyLobbyGate_StartSessionWithLobbyTokenOk` | 97.3 | c96 r98 k98 | `~FragmentPacket` not inlined under `inline_depth(0)`; the 1113/1133 log merge sits at the other site | 4 tries; no form gives both the out-of-line ctor and the inlined dtor |
| `HandleLobbyLobbyGate_StartSessionWithNPTokenOk` | 96.7 | c95 r99 k97 | Same as the line above | Same form as LobbyTokenOk |
| `HandleLobbyGate_HelloReq` | 93.3 | c91 k89 | Register for 0, `memset` from `Packet reply = {}` | lg-4 and lg-5a forms gave score only |
| `HandleLobbyLobbyGate_HelloOk` | 87.3 | c92 r78 k92 | Log arguments and `L"yes"` reload | Rewrite gave 99.3 only; reverted by rule 3. Patch idea: the handoff row above |
| `HandleLobbyLobbyGate_CloseSessionNotify` | 96.8 | c93 r97 | `LobbyGate::_instance` reload (lessons D) | Stop list; 1 new form was worse |
| `HandleLobbyLobbyGate_KickNotify` | 99.4 | r98 | `LobbyGate::_instance` reload (lessons D) | Stop list; no new idea |
| `HandleLobbyLobbyGate_GetEnterWorldTokenOk` | 98.1 | c97 r97 | Same `_instance` reload | lg-4 tried 3 forms; no new idea |

## Notes

- The card says "Do not edit `Docs/Parity/lessons.md`". The harness asked for a `## lg-5a` section. This branch adds a short section at the end. The review can move it into A and B.
- Do not edit sources while a background `tools/parity.sh` runs. The build reads the files late.
- A new worktree needs `vendor/zstd/src` (copy from another worktree, `bb6eaf64`) and `LIFT_IDA_DIR`.

Turns: 75
