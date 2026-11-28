# lift-gamedaemon-gap-049-w5 handoff (round 3)

## Lifted

- `LogArchiveSession`: `Connect` (0x6b9d60), `Send` (0x6b9fd0), `Recv` (0x6ba1f0), `recv` (0x6ba300). Added the `SessionType` enumerators and the `sessionNames` static.
- `LogServer`: `Initialize` (0x6ba6b0), `ClearLogData` (0x6ba870), `AsyncSend` (0x6ba900), `SendComplete` (0x6bab30), `RecvComplete` (0x6bad70), `waitComplete` (0x6baf30), `HandlePacket` (0x6bb0a0).
- `LogAgent::HandlePacket` (0x6bb200).
- `LogArchiveWriteBuffer`: constructor (0x6d8560), `PushNetworkData` (0x6d8650), `PushFileData` (0x6d8860), `ClearNetworkBuffer` (0x6d89e0), `ClearFileBuffer` (0x6d8aa0), `growBufferChunkSize` (0x6d8b30), `growBufferCount` (0x6d8ca0).
- `LogArchiveWriteContext`: `SwitchStatus` (0x6d8f20), `GetWritingBuffer` (0x6d8fa0).

## Not done

- `LogServer::Connect` (0x6ba780): the review rejected it (P1_calls, P2_cc). The build makes a tail call to `LogArchiveSession::Connect`. The original makes a normal call. The body is a `LIFT_STUB` again and its `/INCLUDE` pragma is removed. A later card will lift it.
- `LogArchiveWriteContext::LogArchiveWriteContext` (0x6d8de0): the review rejected it. The original stores `[rsp+0x50]` before the null test on every path. The build stores it after the `test`/`je`. The body is a `LIFT_STUB` again and its `/INCLUDE` pragma is removed. A later card will lift it.
- `LogServer::~LogServer` (0x6ba5a0): the class has no PDB layout yet. The body needs the vtable stores, `~LogArchiveWriteContext` and the handler destructor. Needs the layout card first.
- `LogServer::Close` (0x6ba7a0): the body needs `LogArchive::_instance`, `LogArchive::ChangeFileMode` and the `LogArchive` field at +776. These are not declared in the clone.

## Notes

- This round changed only the two rejected functions. All other bodies are unchanged.
- The message literals of the log calls in `logarchivesession.cpp`, `logserver.cpp` and `logagent.cpp` are hidden in the HR cache (`pipe.chReply[...]`). The format strings are assumed and marked with `❓`. The `sessionNames` strings are assumed too.
- `LogArchiveWriteContext::~LogArchiveWriteContext` (0x6d8e80) is out of this card. It stays a stub.
- Safety changes: `Send` checks the packet size against the 4000 byte buffer. `Recv` rejects a negative body size. `recv` retries after a wait instead of adding -1 to the offset. `RecvComplete` rejects a size below 2.
- `/INCLUDE` keep pragmas stay for the other leaf functions with no live caller.

## Files changed

- `src/Server/GameDaemon/logserver.cpp`
- `src/Server/GameDaemon/logarchivecontext.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-049-w5.md`
