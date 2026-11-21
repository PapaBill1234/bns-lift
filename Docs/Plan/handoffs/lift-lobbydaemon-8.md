# lift-lobbydaemon-8: CliSessionTable part 2, LobbyToken

Source: LobbyDaemon 2019 + PDB. Do not use build 381 for this card.

| Result | Count |
| --- | ---: |
| New C++ bodies for card functions | 2 |
| STL instances in the built PDB | 2 |
| STL instance inlined into a lifted caller | 1 |
| STL instances covered by type, not emitted yet | 20 |
| Not done | 9 |
| Total | 34 |

`LobbyToken::~LobbyToken` releases the session reference. The original emits this body in the deleting destructor at `0x967d0`. The card does not count that compiler-generated function.

## Lifted

| Function | RVA | Funcdiff score | MATCH |
| --- | --- | ---: | --- |
| `CliSessionTable::Select_index_gate` | `0x3eef0` | 100.0 | Yes |
| `LobbyToken::LobbyToken` | `0x96750` | 100.0 | Yes |

The built PDB has both retained public symbols. No source variant was necessary.

## Covered by the STL

The `CliSessionTable` container types match the PDB. Their implementations come from `include/vs2010` when lifted callers use them. Type coverage does not mean that the compiler emits a separate function. The lift does not yet declare the `LobbyTokenDesk` map, so its two instances are in Not done. Funcdiff skips `std::` names. In this table, `u64` means `unsigned long long`.

| Function | Type | RVA | Separate procedure in built PDB |
| --- | --- | --- | --- |
| `std::map::map` | u64 key | `0x3f090` | No |
| `std::_Tree::clear` | u64 key | `0x3f0f0` | No |
| `std::map::map` | `id128` key | `0x3f180` | No |
| `std::_Tree::erase` | `id128` key, one iterator | `0x3f1e0` | No |
| `std::_Tree::clear` | `id128` key | `0x3f550` | No |
| `std::vector::push_back` | `CliSession*` | `0x3f5e0` | No, inlined into `Select_index_gate` |
| `std::_Tree::_Erase` | u64 key | `0x3f670` | No |
| `std::_Tree::_Erase` | `id128` key | `0x3f6e0` | No |
| `std::_Tree::_Lrotate` | `id128` key | `0x3f750` | No |
| `std::_Tree::_Rrotate` | `id128` key | `0x3f7b0` | No |
| `std::vector::_Reserve` | `CliSession*` | `0x3f810` | Yes |
| `std::_Tree::erase` | u64 key, iterator range | `0x3f8a0` | No |
| `std::_Tree::erase` | `id128` key, iterator range | `0x3f980` | No |
| `std::vector::reserve` | `CliSession*` | `0x3fa60` | Yes |
| `std::_Tree::_Linsert` | u64 key | `0x3fb50` | No |
| `std::_Tree::_Linsert` | `id128` key | `0x3fc80` | No |
| `std::_Tree::_Insert` | u64 key | `0x3fdd0` | No |
| `std::_Tree::_Insert` | `id128` key | `0x40080` | No |
| `std::_Tree_val::_Buynode` | `id128` key | `0x40330` | No |
| `std::map::~map` | u64 key | `0x40440` | No |
| `std::_Tree::erase` | u64 key, one iterator | `0x41380` | No |
| `std::_Tree_val::~_Tree_val` | `id128` key | `0x54660` | No |
| `std::_Tree_val::_Buynode` | u64 key | `0xc2510` | No |

## Not done

| Function | RVA | Reason |
| --- | --- | --- |
| `LobbyToken::Verify` | `0x96830` | The LobbyDaemon and LobbyConfig layouts do not expose the address policy yet. Do not replace the check with a fixed policy. |
| `LobbyToken::Expire` | `0x96b00` | The KickJob and LobbyDaemon stubs lack the job pool and manager members. |
| `LobbyTokenDesk::LobbyTokenDesk` | `0x96c30` | The PDB gives the desk layout. The lift needs the `LobbyTick::Listener` base from `lift-lobbydaemon-12`. |
| `LobbyTokenDesk::~LobbyTokenDesk` | `0x96d70` | The lift needs the `LobbyTick::Listener` base from `lift-lobbydaemon-12`. |
| `LobbyTokenDesk::Issue` | `0x96e20` | The lift needs the `LobbyTick::Listener` base from `lift-lobbydaemon-12`. The production key callback is a stub. |
| `LobbyTokenDesk::Verify` | `0x96fb0` | The lift needs the `LobbyTick::Listener` base from `lift-lobbydaemon-12`. The token validation path is not ready. |
| `LobbyTokenDesk::Tick` | `0x97240` | The lift needs the `LobbyTick::Listener` base from `lift-lobbydaemon-12`. The expiration job path is not ready. |
| `std::_Tree::_Linsert` (`LobbyToken*`) | `0x97860` | The lift does not declare the desk map or call its insert function. |
| `std::_Tree_val::_Buynode` (`LobbyToken*`) | `0x97990` | The lift does not declare the desk map or call its insert function. |

## Checks

`tools/gate.sh` and `tools/parity.sh` passed after the review fixes with `LIFT_BUILD_DIR=build-ld-8`. The rebuilt VS2010 PDB has separate procedures for `_Reserve` and `reserve`. No MATCH was lost. No baseline file changed.

| Server | Main MATCH | Branch MATCH | Original functions | Branch parity |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 491 | 92.9% |
| LobbyGate | 658 | 658 | 739 | 89.0% |
| SmartCouponDaemon | 630 | 630 | 669 | 94.2% |
| PostOfficeDaemon | 694 | 694 | 759 | 91.4% |
| LobbyDaemon | 82 | 85 | 2204 | 3.9% |

The two new card bodies and the `DynamicRefCntObj` destructor account for the three new MATCH results.
