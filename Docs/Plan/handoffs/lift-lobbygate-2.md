# lift-lobbygate-2 handoff

## Done (about 60 functions)
- Base: PipeConsole::SetRunningInfo 0x2A5A0, AlertSender::init 0x19DA0. Other base gaps have no body in the exe (inline or STL).
- NumberTheory.cpp (now in lift_common): ExpMod 0x570D0, isPrimeMR 0x57190, IsPrime 0x561A0. biArithmetic Divide 0x59AB0.
- CryptoHash.h, ripemd160, ripemd128, mgf (generate 0x5EB40).
- oaep_encoder: 0x5A8F0, 0x5AB30, 0x5AAE0, 0x5AB10, 0x5ABA0, 0x5AC40, 0x5AEB0, i2os 0x5AA00, os2i 0x5A910.
- rsa: 0x4BF50, 0x52A40, 0x52A50, 0x52A60, 0x52DE0, 0x531F0, 0x532A0, 0x53370, 0x533D0, 0x534A0, 0x53560, 0x53660, 0x536C0.
- Crypto InstanceSize 0x55150, Create 0x55200, Destroy. Prng Generate 0x5A520, GeneratePrime 0x5A5C0.
- CryptoKey: Initialize 0x526E0, generateBigNumber 0x52750, generatePrimeNumber 0x52820, s_initializedCount 0x94108.
- Dh (vtable 0x86ED8): Setup 0x55610, Cleanup 0x55630, clear 0x55640, Start 0x556F0, Process 0x55980, GetKey 0x55A00, setupFactors 0x55BB0, getValue 0x55D80, ~Dh 0x555A0.
- CMakeLists.txt: lift_common adds ripemd128, mgf, oaep_encoder, rsa, CryptoKey, NumberTheory, LogFile.

## Not done
- ContentsRuleConfigDefinition (no src/common/ContentsRuleConfig.* yet): Load 0x08220, LoadContentsRuleConfig 0x082C0, DestroyContentsRuleConfig 0x084D0, Dump 0x08600, MakeListPacket 0x08800, ConvPacketElement 0x08CE0, CheckMinMaxBoundary 0x08EF0, UpdateAllVariable 0x09060. Pseudocode in .scratch/crcd.c. Notes in lift-lobbygate-2-progress.md.

## ❓
- Create/InstanceSize type values are GetType minus 1; nullparam 0x93F20 name; Ripemd128 byte at +24; Create parameter order.
- Scalar deleting dtors 0x53140, 0x53480, 0x5AB30, 0x5A8F0 do not free memory.
- Dh slot 0 (0x27FC0) GetType; CryptoKey +8 _alloc; all Dh member names; Dh PDB module unknown (in CryptoKey.cpp).
- Prng::instance() is new (no PDB symbol); the original reads the TLS slot inline. ~Aes128 0x54FD0 stays inline.

## BUG marks
- OaepEncoder::decode 0x5AEB0, RsaPublic::Setup 0x532A0, Dh::GetKey 0x55A00.

## Blocked
- None.

## Gate result
- `gate ok`. Fix: the gate failed because this handoff file was missing. Added it; build unchanged, gate ok.
