# lift-parity-cgscd-5 handoff

## Done
- CacheGate: +6 MATCH. SmartCouponDaemon: +3 MATCH. The other exes: +0. MATCH -> DIFF: 0 in each exe.
- The goal (95 % in CG and SCD) is not met. CG needs 5 more MATCH (467). SCD needs 3 more MATCH (636).
- Status: partial.

## MATCH per exe (main 8778485 -> this branch)
| Exe | Before | After | Parity after |
| --- | ---: | ---: | ---: |
| CacheGate | 456/491 | 462/491 | 94.1 % |
| LobbyGate | 658/739 | 658/739 | 89.0 % |
| SmartCouponDaemon | 630/669 | 633/669 | 94.6 % |
| PostOfficeDaemon | 694/759 | 694/759 | 91.4 % |
| LobbyDaemon | 1024/2204 | 1024/2204 | 46.5 % (excl 127) |

## Lessons

Note: The task text asks for a section "## cgscd-5" in `Docs/Parity/lessons.md`. The card says: do not edit `Docs/Parity/lessons.md`. I obeyed the card. The lessons are here. The integrate step can copy them.

### Worked
| Function | Before | After | Change | Count |
| --- | ---: | ---: | --- | ---: |
| ClientManager::~ClientManager | 88.6 | MATCH | The delete form tests the pointer again before the explicit destructor (PDB lines 19, 23). | 1 |
| CacheDList::clear | 61.1 | MATCH | while loop with `it++;` as a separate statement. | 1 |
| CacheDList::RemoveSessionAll | 85.7 | MATCH | The same while/`it++;` form. | 1 |
| CacheD::Verify | 91.7 | MATCH | Two field tests with separate exits. | 1 |
| CacheD::Initialize | 93.3 | MATCH | Inlined SetInvalidInfo: take the list by reference, walk to `&list._tail`, `wcscmp` with break. | 1 |
| CacheDChannel::onClose | 97.4 | MATCH | The same list-reference form, `if (node == &list._tail)`. | 1 |
| SendRetryCouponPublicationOk | 96.3 | MATCH | Inlined Session::Send form (buffer in a local, `list[1]`, Enter/send/Leave). The ternary `session != nullptr ? session->_id : 0` for the log id. | 1 |
| NPServiceChannelManager::HandleMessage | 92.3 | MATCH | Dispatch as a `switch` (two signed compares). The NPMsgHandleEvent ctor out of line, with the addReferenceCount (line 141) in the body. | 1 |
| SendRequestEventNoti | 95.2 | MATCH | Branch order from the PDB lines: the event-noti path is the fall-through (line 91). | 1 |
| CacheDList::LoadCachedListConfigFile | 98.5 | 98.8 | `wcscmp(element->Name(), L"cached")` gives the `rep cmpsw` at 0x2d48. | 0 |
| HandleCacheGateHello | 87.2 | 94.1 | Order from PDB lines 42 to 69 (add path, duplicate path, hello ok). Correct error codes. | 0 |

### Failed
| Function | Before | After | Try | Count |
| --- | ---: | ---: | --- | ---: |
| NPServiceChannelManager::HandleMessage | 92.3 | 84.1 | Dispatch as a range `if` (gives `lea`/`ja`). Replaced by the switch. | 0 |
| CacheDList::LoadCachedListConfigFile | 98.8 | 99.1 | for/continue/goto loop from PDB lines 266 to 347, and an else-if chain. No MATCH. Reverted to keep the source simple. | 0 |
| CacheDList::Initialize | 93.3 | 93.3 | 3 forms. Register allocation. | 0 |
| CacheDList::MakeSessionAll | 96.3 | 96.3 | 3 forms. TryConnect inline and hoist. | 0 |
| HandleCacheGateHelloFail | 97.4 | 97.4 | 2 forms. The zero stays in edi. | 0 |
| DaemonPacketHandler (SCD) | - | - | `<= 0` decompose test, errorCode order, GetChannel call, channel-id ternary. No change. | 0 |

## DIFF functions left (CG and SCD, outside the stop list)
| Exe | Function | Score | Signal | Cause | Why I stopped |
| --- | --- | ---: | --- | --- | --- |
| CG | wmain | 61.9 | consts 0, refs 86 | EH state table (A14). | Not tried. Known open cause. |
| CG | HandleCacheGateFragmentRelay | 81.4 | calls 73, refs 74 | Inline and tail-merge difference. | Not tried. Time. |
| CG | ClientSideDaemonChannel::~ClientSideDaemonChannel | 88.8 | calls 80 | Dtor inline chain (A18). | Not tried. Known open cause. |
| CG | CacheDList::Initialize | 93.3 | consts 80 | Register-held constant. | 3 tries, no gain. |
| CG | HandleCacheGateHello | 94.1 | consts 87 | Constant rematerialization and Log tail merge. | No source form left. |
| CG | CacheDList::MakeSessionAll | 96.3 | calls 89 | The original does not inline TryConnect. A non-inlined call gives MATCH, but that only fools funcdiff. I rejected it. | 3 tries. |
| CG | HandleCacheGateHelloFail | 97.4 | consts 92 | The zero stays in edi. | 2 tries, no new idea. |
| CG | HandleCacheGateRelay | 98.4 | consts 95 | Register allocation. | Not tried. |
| CG | CacheDList::LoadCachedListConfigFile | 98.8 | calls 98, refs 98 | The original has two removeReferenceCount call sites (0x2f83 for lines 296/308, 0x3032 for 316/329). Our build merges all four. | 3 tries. |
| SCD | wmain | 66.7 | consts 0 | EH state table (A14). | Not tried. |
| SCD | BigInteger::Divide, invMod, InvMod; Rsa::decrypt | 76.7-91.7 | calls, refs | Crypto (shared stop list). | Stop list. |
| SCD | NPChannel::SendMsg | 90.1 | calls 94, refs 87 | Source in Shared/. | Out of scope. |
| SCD | HandleSmartCoupon_HelloReq | 96.1 | calls 97 | Shrink-wrap and Send tail merge. | No source form left. |
| SCD | RetryCouponPublicationEvent::HandleEvent | 97.5 | calls 95 | r12 shrink-wrap. | No source form left. |
| SCD | Session::Connect | 98.0 | consts 94 | Shared session code. | Out of scope. |
| SCD | ObjPool::Finalize, ObjPool::ObjPool | 99.0 | refs 97 | Source in LobbyDaemon/ or Shared/. | Out of scope. |
| SCD | HandleSmartCoupon_GameEventByCharacterReq | 99.1 | consts 97 | Zero in rbx (`lea r8d,[rbx+0x7b]`). | No source form left. |

The shared DIFF functions (aes128*, IoWorker::run, ThreadManager, Session::Session, WindowConsole, PipeConsole::*, StaticPageMemoryManager, Daemon::Start, DaemonConfig::Dump, Network::OpenPort, Session::HandleEvent, PipeCommandProcess) and the SCD stop list (JobManager::Execute/ExecuteW, EventNotiJob::finalize, SmartCouponDaemon::initialize, HandleSmartCoupon_GameEventByAccountReq, GameEventConfig::SetupGameEventListFromXml) are unchanged.

## Behaviour fix
- HandleCacheGateHello now sends the error codes from the original: CACHEGATE_HELLOFAIL_INVALID_PACKET_VERSION (both version tests), CACHEGATE_SYSTEM_ERROR (add fail), CACHEGATE_HELLOFAIL_DUPLICATE_SERVER_ID (duplicate).

## ❓
- `DispatchNPMessageHandler`: the name comes from the log text (NPMessageHandler.cpp line 36). The PDB has no symbol for it.

## Gate result
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0 in each of the 5 exes.

Turns: 280
