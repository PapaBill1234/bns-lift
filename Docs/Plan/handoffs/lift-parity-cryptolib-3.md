# lift-parity-cryptolib-3 handoff

## Done
- New `src/Security/source/BloodPacketCrypt/PacketCrypt.{h,cpp}` (LG 0x4cc60-0x4da60). Stubs `PacketCrypt::InstanceSize`/`Create` removed from `Session.cpp`.
- New `src/Security/source/BloodCert/BloodCert.{h,cpp}`: 7 functions (LG 0x4bf70-0x4ca10). Key data = zero array, `keyhere`.
- `/INCLUDE` pragma of `BloodCert::IsValid` under LG/SCD/POD keeps the closed-lib object.
- `BigInteger::Set(int,uchar const*,int)` PDB signature (MATCH all 3 exes).
- Per-exe `noinline`: `CryptoKey::Initialize` (LG/SCD/POD); `Crypto::InstanceSize`, `RsaPrivate::RsaPrivate`, `BigInteger::IsPrime`, `Session::completeHandshake` (LG).
- Lessons in `Docs/Parity/lessons.md` (section lift-parity-cryptolib-3).

## Gate result
- `tools/gate.sh` ok. `tools/parity.sh` ok: CG 421 (+0), LG 574 (+41), SCD 540 (+28), POD 620 (+28). No MATCH lost.
- Crypto orig-only: 0 in LG, SCD, POD (card start: 72 / 47 / 47 total orig-only).

## Not done (misses left, not crypto, out of scope)
- LG `CriticalSection::CriticalSection` 0x3780, `FragmentPacket::FreeSize` 0x38a0, `PacketConcatenateBuffer::Decompose` 0x1bce0: inlined in ours; per-exe noinline not tried (not crypto).
- LG/SCD/POD `RefCntObject::operator delete`, `operator delete`, `operator delete[]`, `wmain$dtor$0`: folding / EH funclet naming; see triage.md.
- POD `DaemonConfig::Dump` 0x282d0, `Packet::Decompose` 0x220d0: inlined in ours; not crypto.
- LG `BigInteger::IsPrime` DIFF 82.2, `Session::completeHandshake` DIFF 55.6: paired now; body form not checked in disasm.
- LG `BroadcastPacketCrypt::*` (5) ONLY-OURS: the original has no PDB symbol for them; no effect on MATCH.

## ❓
- `SSN::Generate` "LBBG" literal in SCD/POD (can be other module code). IsValid map type != 16 -> code 5 (0x4c1e9) form is a guess.
- BloodCert enum value names and NIC member names.
- Vtable calls through base pointers in HandshakePacketCrypt not checked in disasm.

## Blocked
- None.

Turns: about 85
