# lift-lobbydaemon-1 handoff

Card: Common: filters, FsdReader, missing functions (wave 1). Source: LobbyDaemon.exe and LobbyDaemon.pdb (2019 + PDB, VS2010 SP1).
Branch: `slice/lift-lobbydaemon-1`, base `1d3def4`.

## Result

| Check | Result |
| --- | --- |
| `LIFT_BUILD_DIR=build-ld-1 tools/gate.sh` | gate ok (after each module) |
| `tools/parity.sh` (no `--accept`) | parity ok |
| Card functions | 46 |
| Lifted in this card | 39 |
| Covered by an existing lift (no new body) | 3 |
| Not done | 4 |

## MATCH comparison (`tools/parity.sh`, VS2010 /GL /LTCG)

| Exe | Baseline MATCH | Branch MATCH | New MATCH | MATCH -> DIFF | MATCH name gone |
| --- | --- | --- | --- | --- | --- |
| CacheGate | 456 | 456 (92.9 %) | 0 | 0 | 0 |
| LobbyGate | 658 | 658 (89.0 %) | 0 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 (94.2 %) | 0 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 (91.4 %) | 0 | 0 | 0 |
| LobbyDaemon | 49 | 49/2204 (2.2 %) | 0 | 0 | 0 |

LobbyDaemon gain is 0. Reason: the LobbyDaemon callers of these functions are still `LIFT_STUB` bodies.
LTCG removes code that has no caller, so the new bodies are not in the LD image (paired 70, as in ld-0).
The gain comes when later waves lift the callers.

## Lifted

| Module | Function | RVA | File |
| --- | --- | --- | --- |
| FsdDecomposer | `FsdDecomposer::Decompose` | 0x119c10 | `src/library/FsdReader/FsdDecomposer.cpp` |
| FsdDecomposer | `FsdDecomposer::GetByte` | 0x119d00 | same |
| FsdDecomposer | `FsdDecomposer::GetWord` | 0x119dd0 | same |
| FsdDecomposer | `FsdDecomposer::GetDword` | 0x119ea0 | same |
| FsdDecomposer | `FsdDecomposer::GetQword` | 0x119f70 | same |
| FsdDecomposer | `FsdDecomposer::GetString` | 0x11a040 | same |
| BannedWordFilterLib | `BannedWordFilterLib::FilterName` | 0x118a70 | `src/External/BannedWordFilter/BannedWordFilterLib.cpp` |
| BannedWordFilterLib | `std::basic_string<wchar_t,...,BannedWordFilterAllocator<wchar_t>>`: `~basic_string`, `assign` (2), `_Grow`, `erase`, `_Copy` | 0x118b40, 0x118b90, 0x118c80, 0x118d60, 0x118de0, 0x118e80 | STL template (`include/vs2010`) with `BannedWordFilterAllocator` (`STLMemory.h`) |
| BannedWordFilterLoader | `~BannedWordFilterLoader` | 0x118fa0 | `src/External/BannedWordFilter/BannedWordFilterLoader.cpp/.h` |
| BannedWordFilterLoader | `InitBannedWordFilterLoader` | 0x119170 | same |
| BannedWordFilterLoader | `LoadNameFilter` | 0x1191f0 | same |
| BannedWordFilterLoader | `CreateFileBuffer` | 0x119430 | same |
| BannedWordFilterLoader | `std::vector<FilterRec,...>`: `~vector`, `_Reserve`, `reserve`, `std::_Uninit_move` | 0x119500, 0x119540, 0x119600, 0x119720 | STL template |
| ConstFilterChat | `basic_string::operator[]` | 0x119760 | `src/External/BannedWordFilter/ConstFilterChat.cpp` |
| ConstFilterName | `StrNormalize` | 0x119770 | `src/External/BannedWordFilter/ConstFilterName.cpp` |
| ConstFilterName | `ConstFilterName` | 0x119870 | same |
| PerfCounterProvider | `loadLibrary` | 0xe7ae0 | `src/Server/BloodLib/source/PerfCounterProvider.cpp` |
| PerfCounterProvider | `setCounterSetInfo` | 0xe7cd0 | same |
| PerfCounterProvider | dynamic initializer of `Instance` | 0x11e700 | same |
| PerfCounterProvider | dynamic atexit destructor of `Instance` | 0x11f3a0 | same |
| SharedChannel | `SharedChannel::Send(format, ...)` | 0x4b70 | `src/Server/Shared/SharedChannel.cpp` |
| SharedChannel | `SharedChannel::Send(Packet const*)` | 0x4ba0 | same |
| SharedChannel | `SharedChannel::sendV` | 0x4c50 | same |
| SharedChannel | `SharedChannelList::~SharedChannelList` | 0x4d20 | same |
| SharedChannel | `SharedChannelList::Initialize` | 0x4d60 | same |
| SharedChannel | `SharedChannelList::Set` | 0x4e20 | same |
| NPChannel2 | `String::UnicodeToMultibyte` | 0x2700 | `src/Server/Shared/NPChannel2.cpp` |
| NPChannel2 | `Packet::FreeSize` | 0x29d0 | same |
| NPChannel2 | `NPMsgHelper::LocaleHourToUTCTime` | 0x2be0 | same |
| Db | `Db::ConvertTimeStamp` | 0xe81f0 | `src/Server/BloodLib/source/Db.cpp` |
| Network | `Network::GetAddress` | 0xe4900 | `src/Server/BloodLib/source/Network.cpp` |

## Covered by an existing lift (no new body)

| Function | RVA | Reason |
| --- | --- | --- |
| `EventObject::~EventObject` | 0x2a20 | Compiler-generated dtor (thunk to `RefCntObject::~RefCntObject`). `TimerQueue.h` has the `// LIFT:` note. No source body. |
| `BigInteger::BigInteger` | 0x10dfb0 | Already lifted inline in `BigInteger.h` (LobbyGate 0x46580). LD RVA added to the comment. |
| `BigInteger::~BigInteger` | 0x10dfe0 | Already lifted inline in `BigInteger.h` (LobbyGate 0x465B0). LD RVA added to the comment. |

## Not done

| Function | RVA | Reason |
| --- | --- | --- |
| `ContentsRuleConfigReload::Load` | 0x29730 | LD `ContentsRuleConfig` (PDB type size 0x18, `_useBotPriorityQueue` and others) is not the LobbyGate class. LD uses its own literals (`ContentsRule.lobbyd.config.xml`, `lobbyd-contents-rule-config`, `_Def` counts 2 and 7). LD does not link the LobbyGate file. A later wave must add the LD owner file. The LobbyGate behavior stays. |
| `ContentsRuleConfig::ReloadContentsRuleConfig` | 0x29980 | Same reason. |
| `ContentsRuleConfig::UpdateReloadedVariable` | 0x2a090 | Same reason. |
| `ContentsRuleConfig::CompareMatch` | 0x2a210 | Same reason. |

The 4 LD stubs stay in `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp`.

## Notes

- `SharedChannel.cpp` path literals are per exe (`#if defined(LIFT_EXE_LD)`), see lessons A6.
- `// BUG:` in `SharedChannel::Send`/`sendV`: when the session is not connected, the code returns false without
  `removeReferenceCount`. The session reference leaks.
- `NPChannel2.cpp` is not linked into LD yet (it includes the SCD `NPChannel.h`). SCD does not call the 3 new functions.
- `Network::GetAddress` has an inline copy of `String::UnicodeToMultibyte` (count 32). `// LIFT:` note at 0xe4900.
- `_mkgmtime64` is a msvcr100 export. The Wine headers do not declare it. `NPChannel2.cpp` declares it.

## ❓

- 0x2700 and 0xe4900: HR shows one 16-bit store of 0 at `dst[count - 2]`. The source form is not known.
- Folder names `src/External/BannedWordFilter` and `src/library/FsdReader` are not verified.

## Commits

| Commit | Content |
| --- | --- |
| 6560e2c | FsdDecomposer |
| 78df02e | BannedWordFilterLib, BannedWordFilterLoader, ConstFilterChat, ConstFilterName |
| 4b285b6 | PerfCounterProvider |
| a7b6ae0 | SharedChannel |
| a00800c | NPChannel2 |
| ad67c69 | Db, Network, BigInteger note |
