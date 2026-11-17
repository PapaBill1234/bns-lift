# lift-marketdealerdaemon-3: handoff

## Done
- SaleTimeContext.cpp/.h: 4 functions. ~SaleTimeContext 0x2d830, SaleTimeContextManager InitContextManager 0x2d8c0,
  AddContext 0x2da50, RemoveContext 0x2dd30. CompoundKey (ctor, operator<) and SaleTimeContext ctor are inline.
  The 11 std::map/_Tree instances (0x2d870, 0x2e000..0x2eaa0) come from include/vs2010 (std::map calls).
- AgentChannel.cpp/.h: 8 functions. AgentChannelManager initChannelManager 0x37c0, GetMarketAgentChannel 0x3860,
  SetMarketAgentChannel 0x38b0, RemoveMarketAgentChannel 0x39e0. AgentSessionHandler OnAccept 0x3a30,
  OnConnect 0x3a90, OnClose 0x3af0, PacketHandler 0x3cd0. 0x37b0 is a COMDAT copy of ~CriticalSection (no code).
- ManagerChannel.cpp/.h: 4 functions. ManagerSessionHandler OnAccept 0x1a4c0, OnConnect 0x1a520, OnClose 0x1a580,
  PacketHandler 0x1a6c0. New MDD class; the SmartCouponDaemon class is not used.
- CMake: 3 new files in lift_marketdealerdaemon.
- Total: 16 functions lifted (+ 11 STL instances from include/vs2010, + 1 COMDAT).

## Not done
- Later cards must define: AgentChannel and ManagerChannel virtuals (~dtor, GetId), the handler lists
  MarketDealerPacketServerSide*, MarketAgentPacketClientSide*, MarketManagerPacketServerSide* (declared extern
  with type Daemon::PacketHandler in AgentChannel.h and ManagerChannel.h).

## Notes
- TFPP_PumpPacket: LTCG folded the event id. The failure log in 0x3670 gives 0x82 = MARKETEVENT_PACKET_PUMP_EVENT.
- AddContext Alloc line 113 (read in IDA at 0x2dad5).
- BUG mark: 0x38b0 SetMarketAgentChannel reads _marketAgentChannel after the lock is released.

## ❓
- None new. AgentChannel::CONNECTION_MARKET_AGENT (= 1) is a LIFT name; there is no PDB enum.

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
