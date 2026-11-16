# lift-postofficedaemon-1: handoff

## Done
- `include/pdb/PostOfficeDaemon/types.h` generated. CMakeLists.txt updated.
- Moved to `src/common/`: Db (19), FragmentPacket (23), ThreadFreePacketPump (21). LobbyGate and SmartCouponDaemon targets updated.
- Network: StopPort 0x28F10. Memory: GrowingBuffer::Add 0x29750.
- PacketBufferHandler: TextStreamPacketBufferHandler, 7 (0x2C3E0, 0x2C3F0, 0x2C4A0, 0x2C560, MinimalPacketSize = 0x5D860, 0x2C570, 0x2C730).
- PacketBuffer: ComposeText 0x2F530, isHex 0x2F7D0, parseHexInt 0x2F850, parseDecInt 0x2F940, parseString 0x2FA20, DecomposeText 0x2FAB0.
- Packet: ComposeText 0x21EB0, DecomposeText 0x22220.
- Already in source (inline, no new code): HeapMemoryManager::Clear, MemoryManager::DumpLeak, ~LogMedia 0x30E70, Rsa::Rsa 0x53F40, Port deque (0x36C70, 0x36CC0, 0x36D80, 0x36DA0, 0x36EE0, 0x36F90, 0x36FD0), Timer priority_queue (0x338B0, 0x34140, 0x341D0, 0x342C0, 0x34370) through `include/vs2010/`.
- Total: 19 new functions, 63 moved.

## Not done
- None.

## Module differences (PostOfficeDaemon vs LobbyGate)
- FragmentPacket file path: CacheGate/PostOfficeDaemon `..\..\Packet\`, LobbyGate `..\Packet\`. Shared file uses the first. ❓
- ThreadFreePacketPump path: LobbyGate `..\Economy\Shared\`, PostOfficeDaemon `..\Shared\`. Shared file keeps LobbyGate (TFPP_FILE). ❓ In PostOfficeDaemon, LTCG folds eventId=130 and offset=0.
- Db: 19 functions in both (PostOfficeDaemon 0x2C860-0x2D720). Logic compare not done. ❓

## ❓
- HEX_PREFIXES type. PacketBuffer::ComposeText/DecomposeText are public (PDB: protected).
- LTCG-removed args (fmtCount, Packet::DecomposeText count = size - 2). TextStream ctor is inlined in Clone.
- DecomposeText range log passes only v for '%C' and '%I64d' (❓ BUG 0x2FAB0).

## BUG marks
- ToPacket 0x2C570 reads buffer[bufferSize]. ToBuffer 0x2C730 size uses the wrong base pointer.

## Blocked
- None.

## Gate result
- `gate ok`. CacheGate, LobbyGate, SmartCouponDaemon and lift_selftest link.
