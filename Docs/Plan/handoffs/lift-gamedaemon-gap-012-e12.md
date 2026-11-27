# Handoff: lift-gamedaemon-gap-012-e12 (card lift-gamedaemon-e12)

Exe: GameDaemon (2019 + PDB). Round 2.

## Lifted

| RVA | PDB name | File |
| --- | --- | --- |
| `0x69dd00` | `StringBuilderW::~StringBuilderW` | `stringbuilder.cpp` |
| `0x69dd40` | `StringBuilderW::AppendFormat` | `stringbuilder.cpp` |
| `0x1dc1a0` | `SystemMultiEvent::~SystemMultiEvent` | `systemobject.cpp` |
| `0x699170` | `Session::IsConnected` | `session.cpp` |
| `0x695070` | `LogArchive::IsUnsentFileExist` | `source_logarchive.cpp` |
| `0x695870` | `LogArchive::isPingTimeExpired` | `source_logarchive.cpp` |
| `0x695aa0` | `LogArchive::startupWinSockLib` | `source_logarchive.cpp` |
| `0x686920` | `destroy` (file-local) | `source_alertsender.cpp` |
| `0x6761e0` | `Json::FastWriter::~FastWriter` | `include_jsoncpp.cpp` |
| `0x118e0` | `Data::SlateScrollCache::~SlateScrollCache` | `nofile.cpp` |
| `0x1b4030` | `RankingSeasonInfo::~RankingSeasonInfo` | `nofile.cpp` |

Decisions:

- `nofile.cpp` defines `LIFT_STLMEMORY_FILE` before its first include (A6). The inlined `StlAllocator::deallocate` then uses the GameDaemon build path. Other GameDaemon files still use the default path of `StlMemory.h`.
- `GameDaemonFwd.h` gets `Data::SlateStoneCache` and the `stones` member of `Data::SlateScrollCache` (PDB layout).
- `rankingseason.h` gets the PDB data members of `RankingSeasonInfo` (size 0xE0, static_assert).
- `jsoncpp.h` gives `Json::FastWriter` the base `Json::Writer` and its PDB members. `Json::Exception` keeps its stub form (see Not done).
- `destroy` (0x686920) has no public name. A `/INCLUDE` pragma cannot keep it. It pairs when a lifted caller (`AlertSender::fini`, `AlertSender::run`) calls it.
- The other lifted functions have a dead-strip `/INCLUDE` pragma with a `// LIFT:` note. They have no live caller yet.

## Not done

| RVA | PDB name | Reason |
| --- | --- | --- |
| `0x105620` | `Pointer2<ChallengeParty>::~Pointer2<ChallengeParty>` | Class template member. The linker folded many instantiations into this body. `Pointer2` is an empty stub template in `GameDaemonFwd.h`. Its definition is not lifted yet. |
| `0x1daca0` | `Data::ZoneTriggerEventCondRecordPtr::ZoneTriggerEventCondRecordPtr` | Folded with `Pointer2<...>` constructors. The base `DrRecordPtr` and the class are empty stubs in `GameDaemonFwd.h`. A change there needs the record pointer class family. |
| `0x346770` | `Pointer2<CraftInfo>::~Pointer2<CraftInfo>` | Same cause as `0x105620`. |
| `0x14a320` | `TakeTimeBasedPlayRewardResponseParam::~TakeTimeBasedPlayRewardResponseParam` | The body is the inlined `TimeBasedPlayInfoList::~TimeBasedPlayInfoList` (with `clear`). That destructor is a `LIFT_STUB` in `user_cpp.cpp` (another card). A lift now calls the stub. |
| `0x1ee8e0` | `ZoneCounterSet::~ZoneCounterSet` | Needs the base `WorldCounterSet` (vtable) and `PerfCounterProvider::Instance`. These are not lifted yet. |
| `0x4bfa70` | `InventoryCacheUpdate::~InventoryCacheUpdate` | The original inlines `Packet::~Packet` (direct `Packet::Clear` calls). The shared `Packet::~Packet` is out of line in `Packet.cpp`. The form needs a decision for all exes (pattern 35). |
| `0x4bfee0` | `InventoryClientUpdate::~InventoryClientUpdate` | Same cause as `0x4bfa70`. It also needs the `FragmentPacket` layout (size 0xF8). |
| `0x5b3750` | `FallDeathEffect::FallDeathEffect` | Needs the `InstantEffect` base layout, vtables and `GameObjectCounter::Instance`. These are not lifted yet. |
| `0x6a84d0` | `Json::Exception::Exception` (copy) | Needs the base `std::exception`. No other lifted file links the CRT `std::exception` symbols (`??0exception@std@@`, `??1exception@std@@`). The round 4 gate failed after the lift added this base, with no error line. Round 5 removed the base and the lift to isolate the fault. The body is a `LIFT_STUB` again. |
| `0x6eba80` | `LoadTableBinder::~LoadTableBinder` | Needs the base `DrDataReaderImpl::LoadFuncBinder`. It is not declared in the tree. The body is folded with `LoadTableMT_PostProcBinder`. |

## Files changed

- `src/Server/GameDaemon/stringbuilder.cpp`, `src/Server/GameDaemon/stringbuilder.h`
- `src/Server/GameDaemon/systemobject.cpp`, `src/Server/GameDaemon/systemobject.h`
- `src/Server/GameDaemon/session.cpp`
- `src/Server/GameDaemon/source_logarchive.cpp`, `src/Server/GameDaemon/logarchive.h`
- `src/Server/GameDaemon/source_alertsender.cpp`
- `src/Server/GameDaemon/include_jsoncpp.cpp`, `src/Server/GameDaemon/jsoncpp.h`
- `src/Server/GameDaemon/nofile.cpp`
- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/rankingseason.h`

## Gate and MATCH comparison

The driver builds and runs the gate and funcdiff after this session. This session did not build.

Round 3: the round 2 gate stopped with `XDG_RUNTIME_DIR is invalid or not set in the environment`. That message comes from the build host environment, not from a compiler. The build tree has no GameDaemon object logs and no `error C` line. This round checked each changed declaration against the shared headers (`Thread` 0x30 + `LogMedia` 0xB0 = 0xE0, `Connection::_socket`, `CriticalSection::Enter`/`Leave`, `MemoryManager::Free` const, `Log::Write` overloads, `StlMemory.h` `LIFT_STLMEMORY_FILE` guard) and found no compile fault. The code is not changed in round 3. Run the gate again with a valid `XDG_RUNTIME_DIR`.

Round 5: the round 4 gate failed again with the same message and no error line. The `std::exception` base of `Json::Exception` was the only new CRT link dependency in the tree. Round 5 removed it and put `0x6a84d0` back to a `LIFT_STUB`. If the gate still fails, the cause is probably in `logarchive.h` (new bases `Thread` and `LogMedia` pull `Thread.cpp` and `LogMedia.cpp` objects into the link). Get the real compiler or linker line before the next change.
