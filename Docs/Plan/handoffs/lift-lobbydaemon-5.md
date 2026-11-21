# lift-lobbydaemon-5 handoff

Source: LobbyDaemon 2019 + PDB. The retry started at `d7e21dd`. The local pseudocode index confirms the 30 RVAs in this handoff.

| Result | Count |
| --- | ---: |
| Lifted | 5 |
| Not done | 25 |

## Lifted

| Module | RVA | Function |
| --- | --- | --- |
| Mileage | `0x5d370` | `LobbyMessageAcceptor::~LobbyMessageAcceptor` |
| Mileage | `0x5d390` | `MileageInfo::check` |
| Mileage | `0x5d410` | `MileageConfig::MileageConfig` |
| Mileage | `0x5d460` | `MileageConfig::~MileageConfig` |
| Mileage | `0x5d760` | `MileageConfig::Check` |

The configuration checks keep the original value checks. They also reject incomplete arrays before later code can copy or sort them. The configuration owns the arrays and their records. Copy operations stay unavailable until the deep copy is safe.

## Not done

| Module | RVA | Function | Reason |
| --- | --- | --- | --- |
| Mileage | `0x5d5a0` | `MileageConfig::operator=` | Needs a checked deep copy and cleanup on allocation failure. |
| Mileage | `0x5d8a0` | `Mileage::~Mileage` | Needs the ownership contract for the fever array. |
| Mileage | `0x5d940` | `Mileage::Initialize` | Needs the deep copy and checked fever schedule creation. |
| Mileage | `0x5dbf0` | `Mileage::FetchFeverTimeList` | Needs the initialized schedule and packet contract. |
| Mileage | `0x5dd60` | `Mileage::settle` | Needs the checked schedule and limit types. |
| Mileage | `0x5df70` | `DepositMileageCallback::OnError` | Needs the callback and job lifetime contract. |
| Mileage | `0x5e050` | `DepositMileageCallback::OnSuccess` | Needs the job lifetime and database completion contract. |
| Mileage | `0x5e0f0` | `DepositMileageCallback::OnFail` | Needs the job lifetime and database completion contract. |
| Mileage | `0x5e170` | `DepositMileageCallback::OnTimeout` | Needs the callback and job lifetime contract. |
| Mileage | `0x5e1a0` | `Mileage::deposit` | Needs the checked database and job path. |
| Mileage | `0x5e660` | `Mileage::FeverTime::FeverTime` | Needs the typed section and its owning class. |
| Mileage | `0x5e680` | `Mileage::FeverTime::~FeverTime` | Needs the typed section and its allocation contract. |
| Mileage | `0x5e6c0` | `Mileage::FeverTime::Initiaize` | Needs the typed section and checked repeat schedule. |
| Mileage | `0x5f170` | `Mileage::FeverTime::makeRepeatSection` | Needs the typed section and checked time ranges. |
| Mileage | `0x5f2c0` | `MileageLimit::Fillin` | Needs the limit and boundary contract. |
| Mileage | `0x5f480` | `MileageManager::~MileageManager` | Needs the owned mileage types and allocator contract. |
| Mileage | `0x5f5a0` | `MileageManager::Initialize` | Needs the database loaders and checked mileage initialization. |
| Mileage | `0x5fc30` | `MileageManager::CreateSlot` | Needs the slot lifetime and database limit checks. |
| PcCafe | `0x62e90` | `TencentNetBar::CreateFromExternalAuthData` | Did not lift external authorization. |
| PcCafe | `0x63350` | `TencentNetBar::onSet` | Needs the PcCafe base and initialized session state. |
| PcCafeMileage | `0x633b0` | `PcCafeMileage::Accept` | Needs the matching `LobbyMessage::Dispatch` overload. |
| PcCafeMileage | `0x63400` | `PcCafeMileage::Start` | Needs the checked session and slot state. |
| PcCafeMileage | `0x636b0` | `PcCafeMileage::Stop` | Needs the checked session, settlement, and deposit paths. |
| MileageDailyLimit | `0x62560` | `MileageDailyLimit::getBoundary` | Needs the limit base and a contract for out-of-range times. |
| LobbyJSON | `0x2f830` | `lob_json_write_iso8601_datetime` | Needs the working formatter and daemon time-zone state. |

Compiler-generated deleting destructors are not separate lifts. The other part of Mileage stays unchanged.

## Verification

- Build directory: `build-ld-5-sol`.
- `tools/gate.sh`: `gate ok` on the retry worktree.
- The local synthetic fixture passed again. It checked default and valid configurations, rejection checks, and cleanup of owned records.
- The Mileage-only PDB layout check passed again: 21 classes, 55 members, and no errors. The earlier full layout check reported five errors in unchanged LobbyGate and MarketDealerDaemon code.
- `tools/parity.sh`: `parity ok` on the retry worktree. The saved pre-change run and the retry run used the same VS2010 settings and pinned zstd source.

| Server | MATCH before | MATCH after | MATCH identities lost |
| --- | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon | 49 | 49 | 0 |

The MATCH sets are identical. The tracked baselines stay unchanged.
