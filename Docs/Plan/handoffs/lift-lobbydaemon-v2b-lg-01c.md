# Handoff: lift-lobbydaemon-v2b-lg-01c (round 1)

Exe: LobbyGate (LG). The author did not build. The driver builds and runs the proof.

## Changes

### LG 0x8600 `ContentsRuleConfig::Dump`

- The loop body does not keep a common field pointer before the switch now.
  Each case reads `base + def.offset` again. The original reloads `[s1 - 8]` in each case.
- The data references (`ContentsRuleConfig::_Def+0x8`) stay open. See 0x8ef0.

### LG 0x3ec0 `GateKeyManager::MakeGateKey`

- The code uses the null-checked placement new on the result of `Alloc` (the original tests the new expression for null).
- The first fail path writes out the body of `~GateKeyEntry`. The original inlines it there.
- The second fail path keeps `entry->~GateKeyEntry()`. The original calls 0x3e80 there.
- The fail block of the `_sgkMap` insert comes first now. The success block (`Leave`, `return gateKey`) is last.
  The original has `jne` to the success block at the end.

### LG 0x5cf0 `ClientManager::Finalize`

- The loop keeps `CliMapType& cliMap = _cliMap[i]` and `Client* client = it->second` in locals.
  The original keeps both in registers. The lift reloaded `_cliMap` in each iteration.

### LG 0x4500 `Client::SendGetCharacterInfoListOk`

- The `ok &&` chain is gone. Each failed `Compose` goes to one fail block after the loop (`goto composeFail`).
  This is the shape of the pseudocode (one `break` per field, one fail block after the loop).

## Not done

- **LG 0x8ef0 `ContentsRuleConfig::CheckMinMaxBoundary`** (95.8). Cause: data layout, not code.
  Evidence: `-lea s2, [ContentsRuleConfig::_Def+0x20]`, `-lea s3, [LobbyGateConfig::_Def+0x18]`;
  the lift has `[<data>]` and `[L"agmentPacket.cpp"]`. The end pointer `&_Def[13] + 0x20` falls into the next object.
  In the original, `ContentsRuleConfigLoad::_Def`, `ContentsRuleConfig::_Def` and `LobbyGateConfig::_Def` are adjacent
  (0x92850, 0x92a60, 0x92d40). In the lift, a FragmentPacket string follows `ContentsRuleConfig::_Def`.
  The lift also shows no symbol name for `ContentsRuleConfig::_Def+0x20`. A source form that fixes the
  order of objects across two .obj files is not known. No form tried.
- **LG 0x5cf0 `ClientManager::Finalize`**, the constant 0x18 vs 0x10. Cause: TLS layout. The register holds the
  TLS offset of `__delv_buf__` (original +0x18, lift +0x10). A new or moved `__declspec(thread)` variable changes
  the TLS block of all exes. Not tried. The loop change above can still raise the score.
- **LG 0x126f0 `operator delete(void*)`** (3 bytes, miss). The PDB puts it in `ThreadFreePacketPump.obj`
  (type `void (void*)`). The lift has no file for this module. A global `operator delete(void*)` changes every
  `delete` expression in LG. Not added.
- `LobbyGate::initialize` 0x12e70 (`wcsncpy`), lead note: not in the scope table. Not looked at.

## Files changed

- `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp`
- `src/Server/LobbyGate/Client.cpp`
- `Docs/Plan/handoffs/lift-lobbydaemon-v2b-lg-01c.md`
