# Handoff: lift-gamedaemon-gap-002-e2

## Lifted (33 getters)

- ClientOption: TypeId (14), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- CollectingProperty: TypeId (36), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- ContentQuotaProperty: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- CostumeProperty: Version (29), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- DiscoveryArea: TypeId (12), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- EffectProperty: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.

The static members fieldMax, fieldDefine, syncMax and syncDefine follow the pilot form of ActivatedTeleport.
Round 2: I removed the `/INCLUDE` pragmas from the 6 files. The source guard sends them to review, and the hard rules forbid them. These functions have no live caller yet. `/OPT:REF` may drop them, and funcdiff may not pair them. The reviewer can decide on dead-strip keep lines.

## Open questions

- CostumeProperty::Version: the old stub used the folded name RaidDungeonBindProperty::TypeId. The PDB name is CostumeProperty::Version. I declared it virtual (`int Version() const`). I did not check the virtual form against the publics.
- The 6 ActivatedTeleport functions of the card list were already lifted in the base. I did not change them.

## Not done

None. The driver runs the build and the proof. I did not run them.

## Changed files

- src/Server/GameDaemon/{clientoption_h,collectingproperty,contentquotaproperty,costumeproperty,discoveryarea,effectproperty_h}.cpp
- src/Server/GameDaemon/{clientoption,collectingproperty,contentquotaproperty,costumeproperty,discoveryarea,effectproperty}.h
- Docs/Plan/handoffs/lift-gamedaemon-gap-002-e2.md
