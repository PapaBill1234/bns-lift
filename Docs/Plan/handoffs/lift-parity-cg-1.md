# lift-parity-cg-1 handoff

## Done
- CacheGate MATCH 374 -> 385/491 = 78.4 %. LG 462, SCD 429, POD 474 (+0, no MATCH lost).
- Changed: src/Server/Economy/CacheGate/ (CacheD, CacheDChannel, CacheGateSessionHandler, ClientManager). Lessons 22, 31, 32, 33 + "did not work" in Docs/Parity/lessons.md.
- 90 % (442) is not reachable in the exe-only scope: 18 DIFF are left in scope. Most of the gap is in shared code.

## Not done (exe-only DIFF left: function, signal, cause, why stopped)
- CacheD::Initialize 0x2430: consts 0x278. Inlined PipeConsole find: `add rbx,0x278` vs `lea r10`. Two source forms tested, no gain.
- CacheDChannel::onClose 0x3e40: consts 0x278. Same cause as CacheD::Initialize.
- CacheDList::Initialize 0x2660: consts 0x3c. Register allocation (zero kept in edi). Placement-new form tested, no gain.
- CacheD::Verify 0x2530: calls (Leave order). Block order. Two branch forms give the same score.
- CacheDChannel::~CacheDChannel 0x3be0: refs. Noise: vtable ref reads as a string.
- CacheGate::initNetwork, CacheGate::~CacheGate: refs. Same vtable-as-string noise.
- CacheDList::add 0x3490, ClientManager::AddSession 0x6120: calls. `_Buynode` name noise (`<K const ,V>`).
- ClientManager::~ClientManager 0x5d60: calls/refs. IndexMap dtor stays out of line.
- CacheDList::clear, CacheDList::RemoveSessionAll 0x2940: calls/refs. Ours inlines `_Tree::clear` (calls `_Erase`, StlMemory.h ref). noinline tested, no gain.
- CacheDList::MakeSessionAll 0x27d0: calls. Orig has GetAddressStringW in each branch and one merged Log::Write; ours merges the GetAddressStringW. Compiler tail merge, no source form found.
- CacheDList::LoadCachedListConfigFile 0x2b20: calls (extra wcsncmp, missing removeReferenceCount). Inline choice of XmlElement helpers; not settled.
- HandleCacheGateHello 0x4c00: calls/consts. Block order. Else-if form gave 88.9 but no MATCH; undone.
- HandleCacheGateHelloFail 0x5040: consts 0x66. Orig keeps zero in rdi across Decompose. Register allocation.
- HandleCacheGateRelay 0x51c0: consts 0x4/0x88 vs 0x20. Stack layout of the inlined decomposer; not settled.
- HandleCacheGateFragmentRelay 0x5880: calls/refs. Shared Packet::Add inline; out of scope.

## ❓
- None new.

## Blocked
- None.

## Tools card
- tools/vs2010/build.sh does not track headers (obj newer than .cpp is skipped). After a header edit: `rm -rf build-vs2010/obj`.

## Gate result
- After a clean rebuild: `tools/gate.sh` = gate ok. `tools/parity.sh` = parity ok (CG 385, LG 462, SCD 429, POD 474; MATCH -> DIFF 0).
