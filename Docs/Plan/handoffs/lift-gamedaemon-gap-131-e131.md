# lift-gamedaemon-gap-131-e131: handoff

Card `lift-gamedaemon-e131`. Log-path callers in GameDaemon. Round 1.

## Lifted

Formtest (VS2010, no /GL) result is in brackets.

| RVA | Function | Formtest |
| --- | --- | --- |
| 0x32f90 | `AchievementDaemonChannel::onConnect` | SAME |
| 0x33520 | `HandleAchievementGameGameHelloFail` | SAME |
| 0x1af180 | `RankingChannel::onConnect` | SAME after the full `Send` argument list (see the note) |
| 0x1af940 | `HandleRankingGame_HelloFail` | DIFF 6 in formtest only. The body calls `GameDaemon::SetEventReplyCacheHello` (0x180e10, lifted). The original has this call inlined. The real build uses LTCG, so it inlines the call. |
| 0xd26d0 | `GameSideArenaLobbySessionHandler::OnAccept` | SAME |
| 0x1618f0 | `MarketReaderAgentSessionHandler::OnAccept` | SAME |

Notes:

- `AchievementDaemonChannel` and `RankingChannel` now have the PDB base `ClientSideDaemonChannel` and the members `_clusterId`, `_pingSent` and `_pingReceived` (size 0x40). Static asserts check the offsets.
- The hello `Send` calls use the literal values from the original: `"hiih", 1, 10, 33, _clusterId` (achievement) and `"hhh", 1, 10, _clusterId` (ranking). Hex-Rays dropped these arguments. Formtest gave the values.
- Each lifted body has a `/INCLUDE` keep pragma (no live caller yet).
- I did not run a build, the gate or funcdiff. The driver does these. The MATCH comparison is not recorded here.

## Not done

- 0xd3720 `GameArenaLobbyManager::ResetIsInitializeGuildInfo`: the body uses the inlined `AutoCS` constructor (Lock.h line 113 null check with `Log::Write`, `AlertSender::Write` and `CrashHandler::MakeCrash`). The shared `Lock.h` declares this constructor but has no inline body. The message strings of the check are not in the Hex-Rays cache (they show as `zone` offsets). The class also has no member layout in `gamearenachannel.h` yet. Keep the `LIFT_STUB`.
- 0x161d40 `MarketReaderAgentSessionHandler::PacketHandler`: the body indexes the global `MarketServicePacketClientSideHandlerList` (rva 0xE8F880). No source file defines this global, and the PDB query does not give the array size. A lift without the definition fails at link time. Keep the `LIFT_STUB`. A later card must add the handler list.

## Repair round 2

Review rejected 2 shared BloodLib bodies. Both fixes use a GameDaemon form under `#if defined(LIFT_EXE_GD)` (lesson A22). Other exes keep their old form.

- 0x699940 `Session::send`: the async-send failure path now reads `_connection->_socket` and `_id` into locals before `WSAGetLastError()`. I did not run formtest on this body (private members).
- 0x69cc40 `PacketBuffer::encrypt`: the body now has one `return true` exit (outer `if (crypt != nullptr)`), computes `&Buffer[6]` before the 3rd-party branch and reads `encBufSize` before the `sendBuffer` store. Formtest result: SAME.

Changed in round 2: `src/Server/BloodLib/source/Session.cpp`, `src/Server/BloodLib/source/PacketBuffer.cpp`.

## Changed files

- `src/Server/GameDaemon/achievementchannel.h`
- `src/Server/GameDaemon/achievementchannel_cpp.cpp`
- `src/Server/GameDaemon/rankingchannel.h`
- `src/Server/GameDaemon/rankingchannel.cpp`
- `src/Server/GameDaemon/gamearenachannel_cpp_2.cpp`
- `src/Server/GameDaemon/marketreaderagentchannel.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-131-e131.md`
