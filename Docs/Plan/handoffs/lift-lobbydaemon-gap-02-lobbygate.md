# Handoff: lift-lobbydaemon-gap-02-lobbygate

| Item | Value |
| --- | --- |
| Card | `design/parity-v2/gap-cards/gap-02-lobbygate.md` (private project) |
| Branch | `gap-02-lobbygate` (scratch clone only, not pushed) |
| Base | `1b0f305` (`gap-01-core`) |
| Code commits | `c2f26e1`, `8afc150`, `f81744d` |
| Source | Logic: LobbyDaemon 2019 + PDB (VS2010 SP1), HR pseudocode. Packets: 381 client. IDA was not opened. |
| Author and committer | `Claude <noreply@anthropic.com>` |

## Result

| Check | Result |
| --- | --- |
| Gate `pilot.py gate --rev f81744d` | 35 of 35 card IDs have no reason. Eligible pool: 197 -> 232. |
| Full 5-exe build (`gate_full.sh`, cold, fresh clone of `f81744d`) | rc 0, "parity ok", 466 s |
| Proof (`proof.py` vs `1b0f305`, strict rules not changed) | verdict `review`: 0 lost MATCH, 0 strict regress in all 5 exes. The proof counts against the committed parity baseline (LobbyDaemon 645), so its 30 new MATCH include the 28 of gap-01. For this card: 2 new REF MATCH. `PacketFormatIterator::Reset` is credited (strict full). `LobbyGateChannel::SendGetServiceEntryListFail` needs review. |
| Lost MATCH, LobbyDaemon REF | 0 (673 -> 675) |
| Lost MATCH, LobbyDaemon NOREF | 0 (927 -> 957) |

## MATCH per exe (cold gate build)

| Exe | Before (`1b0f305`) | After (`f81744d`) | Delta | Lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 | 0 |
| LobbyGate | 658 | 658 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 | 0 |
| LobbyDaemon | 673 | 675 | +2 | 0 |

LobbyDaemon NOREF build (preview, overlay): 927 -> 957 MATCH (+30), 0 lost. Paired: 1143 -> 1175.

The manager and most `Send*` bodies have no caller in the REF build. /OPT:REF removes them. They pair only in NOREF. No `/INCLUDE` was added.

## Classes and layouts

| Class | Size | File |
| --- | ---: | --- |
| `LobbyGateChannelManager` | 0x48 | `LobbyGateChannel.h` (`_channels` at 0x8, `_lock` at 0x20) |
| `LobbyLobbyGatePacketHandlerDef` | 0x10 | `LobbyLobbyGatePacketHandler.h` |

## Data

| Name | RVA | File |
| --- | --- | --- |
| `LobbyLobbyGatePacketLobbySideHandlerList` | 0x202640 | `LobbyLobbyGatePacketLobbySideHandlerList.cpp` (new). 111 entries. Entry 1 (`HelloReq`) has auth false. 34 entries have auth true. The other entries are null. |

## Bodies

Status: funcdiff of the NOREF and REF builds with the overlay of `f81744d`. "-" = not in the build (no caller, /OPT:REF removes it).

| Name | RVA | NOREF | REF |
| --- | --- | --- | --- |
| `LobbyGateChannel::SendListLobbyServiceItemInfoFail` | 0xbf080 | MATCH | - |
| `LobbyGateChannel::SendGetLobbyServiceItemInfoOk` | 0xbf160 | DIFF 89.6 | - |
| `LobbyGateChannel::SendGetLobbyServiceItemInfoFail` | 0xbf2e0 | MATCH | - |
| `LobbyGateChannel::SendGetServiceEntryListFail` | 0xbf3c0 | MATCH | MATCH |
| `LobbyGateChannel::SendChangeCharacterAppearanceWithAccountInventoryItemOk` | 0xbf490 | MATCH | - |
| `LobbyGateChannel::SendChangeCharacterAppearanceWithAccountInventoryItemFail` | 0xbf5a0 | MATCH | - |
| `LobbyGateChannel::SendChangeCharacterSexWithAccountInventoryItemOk` | 0xbf6b0 | MATCH | - |
| `LobbyGateChannel::SendChangeCharacterSexWithAccountInventoryItemFail` | 0xbf7c0 | MATCH | - |
| `LobbyGateChannel::SendChangeCharacterRaceWithAccountInventoryItemOk` | 0xbf8d0 | MATCH | - |
| `LobbyGateChannel::SendChangeCharacterRaceWithAccountInventoryItemFail` | 0xbf9e0 | MATCH | - |
| `LobbyGateChannel::SendRenameCharacterWithAccountInventoryItemOk` | 0xbfaf0 | MATCH | - |
| `LobbyGateChannel::SendRenameCharacterWithAccountInventoryItemFail` | 0xbfc00 | MATCH | - |
| `LobbyGateChannel::SendAddSlotWithAccountInventoryItemOk` | 0xbfd10 | MATCH | - |
| `LobbyGateChannel::SendAddSlotWithAccountInventoryItemFail` | 0xbfe10 | MATCH | - |
| `LobbyGateChannel::SendChangeUserNameWithAccountInventoryItemOk` | 0xbff00 | MATCH | - |
| `LobbyGateChannel::SendChangeUserNameWithAccountInventoryItemFail` | 0xc0050 | MATCH | - |
| `LobbyGateChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk` | 0xc0160 | MATCH | - |
| `LobbyGateChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail` | 0xc0250 | MATCH | - |
| `LobbyGateChannel::SendCreateInitialUserNameOk` | 0xc0340 | MATCH | - |
| `LobbyGateChannel::SendCreateInitialUserNameFail` | 0xc0460 | MATCH | - |
| `LobbyGateChannel::SendActivateGradeOk` | 0xc0550 | MATCH | - |
| `LobbyGateChannel::SendActivateGradeFail` | 0xc0670 | MATCH | - |
| `LobbyGateChannel::SendChangedGradeNotify` | 0xc0790 | MATCH | - |
| `LobbyGateChannel::SendChangedGradeLevelNotify` | 0xc0970 | MATCH | - |
| `LobbyGateChannelManager::~LobbyGateChannelManager` | 0xc0aa0 | MATCH | - |
| `LobbyGateChannelManager::Add` | 0xc0b80 | MATCH | - |
| `LobbyGateChannelManager::Remove` | 0xc0c40 | MATCH | - |
| `LobbyGateChannelManager::Acquire` | 0xc0d50 | MATCH | - |
| `LobbyGateChannelManager::BroadcastAnnounceNotify` | 0xc0e20 | MATCH | - |
| `LobbyGateChannelManager::OnAccept` | 0xc0f20 | MATCH | - |
| `LobbyGateChannelManager::OnConnect` | 0xc0f80 | MATCH | - |
| `LobbyGateChannelManager::OnClose` | 0xc1030 | DIFF 89.0 | - |
| `LobbyGateChannelManager::PacketHandler` | 0xc11d0 | DIFF 98.8 | - |
| `HandleLobbyLobbyGate_GetCharacterInfoListReq` | 0xc5360 | DIFF 89.9 | DIFF 89.9 |
| `HandleLobbyLobbyGate_GetCharacterInfoReq` | 0xc5630 | DIFF 96.5 | DIFF 96.5 |

Side effects:

- REF: `PacketFormatIterator::Reset` went from DIFF to MATCH (strict full, credited by the proof).
- NOREF: `AuctionRollbackEscrowJob::AuctionRollbackEscrowJob` now pairs (DIFF 22.2). Before, ICF folded it. It is a `LIFT_STUB`.

## Open DIFFs (card IDs that pair but do not MATCH)

| Name | RVA | Score | Cause |
| --- | --- | ---: | --- |
| `LobbyGateChannel::SendGetLobbyServiceItemInfoOk` | 0xbf160 | 89.6 | The original inlines the `PacketComposer(char const*, int)` ctor and calls `PacketFormatIterator::SetFormat` out of line. BloodLib has no such ctor. Ours inlines `SetFormat`. A fix needs a BloodLib ctor (not owned by this card). |
| `HandleLobbyLobbyGate_GetCharacterInfoReq` | 0xc5630 | 96.5 | The same `SetFormat` inlining as above. |
| `HandleLobbyLobbyGate_GetCharacterInfoListReq` | 0xc5360 | 89.9 | The original calls the `FragmentPacket` ctor and `Packet::Allocate` out of line. Ours inlines them. The sibling `HandleLobbyLobbyGate_GetServiceEntryListReq` has the same DIFF (88.0). |
| `LobbyGateChannelManager::OnClose` | 0xc1030 | 89.0 | `CliSessionManager::OnCloseLobbyGateChannel` (0x3cbd0) is still a `LIFT_STUB` in `CliSessionManager.cpp` (not owned by this card). /LTCG marks it noreturn, so our tail becomes `import:abort`. It will MATCH when that body is lifted. |
| `LobbyGateChannelManager::PacketHandler` | 0xc11d0 | 98.8 | Block layout of the null-param log block (the original puts it at the end). The siblings `InfoGateChannelManager::PacketHandler` and `GamedChannelManager::PacketHandler` have the same DIFF. |

## Notes

- `LobbyGateChannelManager::BroadcastAnnounceNotify` calls `Broadcast` through `InfoGateChannelManager::Broadcast` (0x2ef40). The two bodies are folded in the original (ICF). The PDB has no `LobbyGateChannelManager::Broadcast`. The cast has a `LIFT` comment.
- `OnClose` reads the wid two times, as the original does: the 2nd `GetId` goes to `OnCloseLobbyGateChannel`, the 3rd goes to `Remove`.
- `PacketHandler` keeps the server checks: the cmd range check (`> 109`), the handler null check, the auth check and the session checks.

## Original bugs kept (`// BUG:`)

| Function | Bug |
| --- | --- |
| `LobbyGateChannelManager::OnAccept` | The null check on the session covers only the id read. |
| `LobbyGateChannelManager::OnConnect` | The null check on the session covers only the id read. |
| `LobbyGateChannelManager::PacketHandler` | Two allocation results are not checked for null (the fragment path), as in `InfoGateChannelManager::PacketHandler`. |
| `HandleLobbyLobbyGate_GetCharacterInfoReq` | The fetch fail path does not release the cli-session reference. |

## Not done

| Name | RVA | Reason |
| --- | --- | --- |
| `CliSessionManager::OnCloseLobbyGateChannel` | 0x3cbd0 | Not in the card ID table. Still `LIFT_STUB`. It blocks the `OnClose` MATCH. |
| `PacketComposer::PacketComposer(char const*, int)` | - | BloodLib. Not in the card ID table. |

All 35 card IDs are done (they pair and the gate gives no reason). 5 of them are DIFF (see the table above).

## Rules kept

- No inline asm, no byte tricks, no `/INCLUDE`. funcdiff, strict and proof are not changed.
- PDB names only. Packets follow the 381 client.
- No binaries, PDBs, IDBs or keys in this commit.
