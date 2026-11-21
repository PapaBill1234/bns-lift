# lift-lobbydaemon-8: CliSessionTable part 2, LobbyToken

Source: LobbyDaemon 2019 + PDB. Do not use build 381 for this card.

| Result | Count |
| --- | ---: |
| Complete card functions | 25 |
| New C++ bodies for card functions | 2 |
| Covered by the existing VS2010 STL implementation | 23 |
| Not done | 9 |

`LobbyToken::~LobbyToken` releases the session reference. The original emits this body in the deleting destructor at `0x967d0`. The card does not count that compiler-generated function.

## Lifted

| Function | RVA | Funcdiff score | MATCH |
| --- | --- | ---: | --- |
| `CliSessionTable::Select_index_gate` | `0x3eef0` | 100.0 | Yes |
| `LobbyToken::LobbyToken` | `0x96750` | 100.0 | Yes |

The built PDB has both retained public symbols. No source variant was necessary.

## Covered by the STL

`CliSessionTable` already uses the VS2010 map and vector with the allocator types from the PDB. The compiler emits the required template instances when it uses those containers. Funcdiff skips `std::` names. `u64` means `unsigned long long` in this table.

| Function | Type | RVA | Funcdiff score | MATCH |
| --- | --- | --- | --- | --- |
| `std::map::map` | u64 key | `0x3f090` | Skipped | No |
| `std::_Tree::clear` | u64 key | `0x3f0f0` | Skipped | No |
| `std::map::map` | `id128` key | `0x3f180` | Skipped | No |
| `std::_Tree::erase` | `id128` key, one iterator | `0x3f1e0` | Skipped | No |
| `std::_Tree::clear` | `id128` key | `0x3f550` | Skipped | No |
| `std::vector::push_back` | `CliSession*` | `0x3f5e0` | Skipped | No |
| `std::_Tree::_Erase` | u64 key | `0x3f670` | Skipped | No |
| `std::_Tree::_Erase` | `id128` key | `0x3f6e0` | Skipped | No |
| `std::_Tree::_Lrotate` | `id128` key | `0x3f750` | Skipped | No |
| `std::_Tree::_Rrotate` | `id128` key | `0x3f7b0` | Skipped | No |
| `std::vector::_Reserve` | `CliSession*` | `0x3f810` | Skipped | No |
| `std::_Tree::erase` | u64 key, iterator range | `0x3f8a0` | Skipped | No |
| `std::_Tree::erase` | `id128` key, iterator range | `0x3f980` | Skipped | No |
| `std::vector::reserve` | `CliSession*` | `0x3fa60` | Skipped | No |
| `std::_Tree::_Linsert` | u64 key | `0x3fb50` | Skipped | No |
| `std::_Tree::_Linsert` | `id128` key | `0x3fc80` | Skipped | No |
| `std::_Tree::_Insert` | u64 key | `0x3fdd0` | Skipped | No |
| `std::_Tree::_Insert` | `id128` key | `0x40080` | Skipped | No |
| `std::_Tree_val::_Buynode` | `id128` key | `0x40330` | Skipped | No |
| `std::map::~map` | u64 key | `0x40440` | Skipped | No |
| `std::_Tree::erase` | u64 key, one iterator | `0x41380` | Skipped | No |
| `std::_Tree_val::~_Tree_val` | `id128` key | `0x54660` | Skipped | No |
| `std::_Tree_val::_Buynode` | u64 key | `0xc2510` | Skipped | No |

## Not done

| Function | RVA | Reason |
| --- | --- | --- |
| `LobbyToken::Verify` | `0x96830` | The LobbyDaemon and LobbyConfig layouts do not expose the address policy yet. Do not replace the check with a fixed policy. |
| `LobbyToken::Expire` | `0x96b00` | The KickJob and LobbyDaemon stubs lack the job pool and manager members. |
| `LobbyTokenDesk::LobbyTokenDesk` | `0x96c30` | The generated header lacks the desk layout. The PDB field query did not run. |
| `LobbyTokenDesk::~LobbyTokenDesk` | `0x96d70` | The desk map, list, and lock layout is not confirmed. |
| `LobbyTokenDesk::Issue` | `0x96e20` | The desk layout is not confirmed. The production key callback is a stub. |
| `LobbyTokenDesk::Verify` | `0x96fb0` | The desk layout and the token validation path are not ready. |
| `LobbyTokenDesk::Tick` | `0x97240` | The desk layout and expiration job path are not ready. |
| `std::_Tree::_Linsert` (`LobbyToken*`) | `0x97860` | The desk map insertion does not exist in the lift yet. |
| `std::_Tree_val::_Buynode` (`LobbyToken*`) | `0x97990` | The desk map insertion does not exist in the lift yet. |

## Checks

`tools/gate.sh` passed after each module. `tools/parity.sh` passed with the same comparison settings as main. No MATCH was lost. No baseline file changed.

| Server | Main MATCH | Branch MATCH | Original functions | Branch parity |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 491 | 92.9% |
| LobbyGate | 658 | 658 | 739 | 89.0% |
| SmartCouponDaemon | 630 | 630 | 669 | 94.2% |
| PostOfficeDaemon | 694 | 694 | 759 | 91.4% |
| LobbyDaemon | 82 | 85 | 2204 | 3.9% |

The two new card bodies and the `DynamicRefCntObj` destructor account for the three new MATCH results.
