# lift-marketdealerdaemon-8: handoff

## Done
- New JobContext.cpp (JobContext.obj part 1, pseudocode lines 1 to 2,188). 27 functions lifted:
  - RetrieveSaleListJob (10): ctor 0x8890, dtor 0x8a10, Initialize 0x8a80, ReplySuccess 0x8c60, ReplyFailure 0x9060,
    verifyParameter 0x91e0, handleJob 0x92e0, addMySaleInfo 0x93c0, composeResponsePacket 0x9540, composeResponsePacketReversely 0x9930.
  - RetrieveBidListJob (9): ctor 0x9d10, dtor 0x9e90, Initialize 0x9f00, ReplySuccess 0xa060, ReplyFailure 0xa340,
    verifyParameter 0xa470, handleJob 0xa4f0, addMyBidInfo 0xa5a0, composeResponsePacket 0xa6e0.
  - RetrieveBidRankStatusJob (7): dtor 0xaae0, Initialize 0xab50, ReplySuccess 0xaf90, ReplyFailure 0xb2c0,
    verifyParameter 0xb3f0, handleJob 0xb4f0, composeResponsePacket 0xb590.
  - AutoCS::~AutoCS 0x8770 and AutoCS::Leave 0x8800 (Lock.h COMDAT copies, same code as PostOfficeDaemon CachedWatchdog.cpp).
- The 3 scalar deleting dtors (0x89a0, 0x9e20, 0xaa70) are compiler code. Not lifted.
- RepeatPacketDecomposer::Reset 0x8880 is already in src/Server/BloodLib/source/PacketUtil.cpp. Not lifted again.
- JobContext.h: member functions of the 3 jobs, new MyBidRankStatusInfo and RetrieveBidRankStatusJob (PDB layout, static_assert).
  LIFT ctors MySaleInfo/MyBidInfo/MyBidRankStatusInfo (inlined zero init in the array new).
- MarketDealerDefine.h: enums MarketDealerPacketCommand (values 4..0xC), MarketDealerBidRankStatus, MarketDealerOrderType,
  MarketDealerSearchType (PDB values).
- CMake: JobContext.cpp added to lift_marketdealerdaemon.

## Not done
- AutoCS::Enter 0x8780: Lock.h has no declaration, and Lock.h is not in the files of this card. Add it to Lock.h in a BloodLib card.
- JobContext::~JobContext (AgentPacketHandler.obj, later card).

## BUG marks
- 0xab50 RetrieveBidRankStatusJob::Initialize: no null check after the array new.

## ❓
- The array delete of the 3 dtors also writes the pointer to a TLS slot (TLS block + 0x10) before Free. Not in the C++.
- RetrieveBidRankStatusJob ctor is inlined at the call site (later card). The inline ctor sets all fields to zero (guess).
- addMy*Info and composeResponsePacket: const& / & or pointer (same ABI). ReplySuccess returns bool here (char in the exe).
- Packet::Compose(PacketComposer*, int, ...) is not in Packet.h. LIFT helper composeWith calls ComposeV.

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
