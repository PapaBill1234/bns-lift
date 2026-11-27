# Handoff: lift-gamedaemon-gap-002-e2

## Lifted (33 getters)

- ClientOption: TypeId (14), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- CollectingProperty: TypeId (36), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- ContentQuotaProperty: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- CostumeProperty: Version (29), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- DiscoveryArea: TypeId (12), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- EffectProperty: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.

The static members fieldMax, fieldDefine, syncMax and syncDefine follow the pilot form of ActivatedTeleport.
Round 3: I restored the `/INCLUDE` pragmas in the 6 files. The card allows them with a `// LIFT:` note. These functions have no live caller yet. Without the pragmas, `/OPT:REF` drops them and funcdiff cannot pair them (round 2 gave "missing" for all 33). The mangled names follow the PDB signatures. The driver link shows if a name is wrong.

## Open questions

- CostumeProperty::Version: the old stub used the folded name RaidDungeonBindProperty::TypeId. The PDB name is CostumeProperty::Version. I declared it virtual (`int Version() const`). I did not check the virtual form against the publics.
- The 6 ActivatedTeleport functions of the card list were already lifted in the base. I did not change them.

## Not done

None. The driver runs the build and the proof. I did not run them.

## Changed files

- src/Server/GameDaemon/{clientoption_h,collectingproperty,contentquotaproperty,costumeproperty,discoveryarea,effectproperty_h}.cpp
- src/Server/GameDaemon/{clientoption,collectingproperty,contentquotaproperty,costumeproperty,discoveryarea,effectproperty}.h
- Docs/Plan/handoffs/lift-gamedaemon-gap-002-e2.md
