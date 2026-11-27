# lift-gamedaemon-gap-007-e7 handoff

## Lifted

All 15 card functions are lifted as 11 bodies. Some RVAs share one body (identical code folding). The source uses the first PDB name of each body.

- `0x35f20` ChallengePartyAttractionState::GetType (also AirDashAction::getPriority). Returns 9.
- `0x35f30` ChallengePartyAttractionState::GetTypeName.
- `0x35f40` ChallengePartyAttractionState::SetAttractionOption. Sets `_attractionOption` (+16).
- `0x97740` DuelBotChallengeAttractionState::GetTypeName.
- `0x180ba0` PcPublicRaidState::GetResetCombatModeCoolTime (also NpcContribution::TotalDamage).
- `0x180bb0` SetAddScoreCoolTime, `0x180bc0` IsEventAttendee, `0x180bd0` SetEventAttendee, `0x180be0` ResetEventAttendee, `0x180bf0` GetAddScoreCount, `0x180c00` IncrementAddScoreCount.
- `0x4535a0` PcPublicRaidState::GetAddScroeCoolTime (also DuelBotActionQueue::GetMovement).
- `0x6fd280` PcPublicRaidState::SetResetCombatModeCoolTime (also DrDataTableImpl::Setup).
- `0x1ee750` WarFieldAttractionState::GetTypeName.
- `0x6f86d0` QuestTableImpl::GetTableType (also AcquiredSkill1::Version). Returns 11.

## Not done

None.

## Notes

- The member offsets of PcPublicRaidState come from the PDB. The pseudocode uses wrong class names for shared bodies. The offsets of the three shared PcPublicRaidState getters and setters (+8, +16) follow the PDB method names. I did not check the instruction bytes.
- ChallengePartyAttractionState has a pad member so `_attractionOption` sits at +16.
- No dead-strip pragma added. The driver build shows if any is needed.
- Build, gate and MATCH counts are not run in this session.

## Round 3

I added `/INCLUDE` dead-strip pragmas for all 11 bodies. The bodies had no live caller, so `/OPT:REF` removed them. I built the mangled names by hand from the PDB signatures. I did not run a build.

## Files changed

- `src/Server/GameDaemon/challengepartyattractionstate_h.cpp`, `challengepartyattractionstate.h`
- `src/Server/GameDaemon/duelbotchallengeattractionstate_h.cpp`
- `src/Server/GameDaemon/pcattractionstate_h.cpp`, `pcattractionstate.h`
- `src/Server/GameDaemon/warfieldattractionstate_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-007-e7.md`
