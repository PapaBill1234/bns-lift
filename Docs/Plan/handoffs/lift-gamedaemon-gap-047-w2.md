# lift-gamedaemon-gap-047-w2 handoff (round 1)

## Lifted

- `0x157c0` `ZipPackedReaderIO::FileName::~FileName` (nofile.cpp). The body is empty (compiler-generated destructor).
  The members `_pathW` and `_pathTokenW` in `datapacker.h` now use the PDB types with `StlAllocator<wchar_t, 2>`.
  A keep pragma is added.
- `0x1cbc0` `AutoCS::~AutoCS` (lock.cpp). The body is a thunk to `AutoCS::Leave`. A keep pragma is added.

## Not done

- `0xc0000` `LogoutOkParam::~LogoutOkParam`: the class has no members in the repo. `AccountExpInfo`,
  `AccountContentQuota` and `AccountRecycleTime` are empty structs. The layout is a wave 1 task.
- `0x13fd20` `EnterWorldOkParam::~EnterWorldOkParam`: the class has no members. The PDB layout (size 0xC58) needs
  many types (`GradeInfo`, `ContentsBan`, `TimeBasedPlayInfoList`, and others).
- `0x681060` `Json::Reader::~Reader`: the class `Json::Reader` has no members and no definition in `jsoncpp.h`.
- `0x6a8430` `Json::LogicError::~LogicError`: the class has no base class. `Json::Exception` has no `std::exception` base yet.
- `0x6a85d0` `Json::LogicError::LogicError`: same cause as `0x6a8430`.
- `0xe230`, `0x1d120`, `0x8c2b0`, `0x1ed800` `Property::Set` / `Property::GetFlag`: `Field::Def` is an empty struct.
  `Property` has no virtual slots `FieldDefine` and `FieldMax` in PDB order. `STRUCT_BIT_MASK`, `updateSync` and
  `SyncBuffer::Set` have no declarations. This needs the layout work first.
- `0x8b110` `Pointer2<ChallengeParty>::operator=`, `0x176380` `Pointer2<Guild>::Pointer2<Guild>`,
  `0x3466d0` `Pointer2<Pc>::operator=`, `0x42e5d0` `Pointer2<Creature>::operator=`: members of a class template.
  The repo has no `Pointer2` form for GameDaemon with these instances.
- `0x68bab0`, `0x68bb40`, `0x68bcc0`, `0x68bd50`, `0x68bed0`, `0x68bf60`, `0x68c0d0` `f_ability<...>::Set`:
  the template `f_ability` does not exist in the repo, and `Field::Def` has no layout.

## Files changed

- `src/Server/GameDaemon/nofile.cpp`
- `src/Server/GameDaemon/datapacker.h`
- `src/Server/GameDaemon/lock.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-047-w2.md`
