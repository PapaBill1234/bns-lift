# lift-postofficedaemon-3 handoff

## Done
- 8 modules, 62 functions: CacheGateChannel (12), CacheGatePacketHandler (9), AgentChannel (9),
  AgentPacketHandler (3), ManagementSessionHandler (4), ManagementPacketHandler (5), WorldChannel (11),
  WorldPacketHandler (9: 0x1f650, 0x1f770, 0x1f800 + folded copy, 0x1f810, 0x1f890, 0x1fdd0, 0x20250, 0x20720).
- Handler tables: CacheGateClientSideHandlerList, PostOfficePacketServerSideHandlerList (0x97268, 0x97308),
  PostOfficeManagementPacketHandlerList, PostOfficeServicePacketServerSideHandlerList (0x97340, 0x973b0).
- Headers: WorldConfig.h (WorldConfigManager layout), RelayContext.h (RESULTSTATE_INVALID), Session.h (friends).

## Not done
- Inline dtors 0x1f7a0, 0x1f840 are in the class bodies (no out-of-line copy).
- Later card: RetrieveCharacterInfoRelay (0x1de30..0x1e410), CheckPostCapacityRelay (0x9180..0x9740) virtuals,
  WorldConfigManager::CheckWorldConfig 0xe430. These are declarations only.

## ❓
- RESULTSTATE_INVALID value (guess 4).
- Alloc line numbers that are not in the pseudocode: 0x1f890 line 91, 0x1fdd0 line 180, 0x20250 line 256.
- 0x1fdd0 name check is `wcslen(name) == 1` (possible BUG: empty name is probable).
- 0x1aaa0 and 0x20720: item list not freed on the delivery path.
- TFPP_PumpPacket eventId 128 and offset 0 (AgentChannel 0x3a00, CacheGate, WorldChannel).
- Folded vtables and code: Retrieve GetRequestWid = 0x1f800; WorldChannel dtor 0x1f620; GetId 0x1a6e0.
- Handler-list file names and SendTextReply, Session.h friends, liftNextRelayTid are not in the PDB.
- PostOfficeDB.h stray `_pdb_tail` member. GetWid release line 37 is a guess.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: gate ok (48/48, lift_postofficedaemon.lib links). No `__int64`/`_DWORD` in new files.
