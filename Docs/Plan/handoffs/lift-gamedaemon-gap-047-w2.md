# lift-gamedaemon-gap-047-w2 handoff (round 2)

## Lifted

- `0x1cbc0` `AutoCS::~AutoCS` (lock.cpp). The body is a thunk to `AutoCS::Leave`. Round 1 gave DIFF because the compiler
  inlined `Leave` into the destructor. `Leave` is now `__declspec(noinline)` (lessons A4), so the destructor is a tail jump.
- `0xc0000` `LogoutOkParam::~LogoutOkParam` (nofile.cpp). The body destroys the 2 vectors (last member first), through a
  `LogoutOkParamView` with raw offsets (+0x28, +0x48). The file defines the complete PDB types `AccountContentQuota` and
  `AccountRecycleTime`. A keep pragma is added.
- `0x13fd20` `EnterWorldOkParam::~EnterWorldOkParam` (nofile.cpp). The body destroys the 2 vectors (+0xC38, +0xC18), then
  clears `timeBasedRewardInfoList` (+0xB70) with the inlined `clear()` stores, through view structs. A keep pragma is added.
- `0x157c0` `ZipPackedReaderIO::FileName::~FileName` (nofile.cpp, round 1 form, unchanged). It stays DIFF.

## Not done

- `0x157c0` `ZipPackedReaderIO::FileName::~FileName`: not a MATCH. The original frees the wide strings with the path
  `E:\DailyBuild02\GameDaemon-Common-...\StlMemory.h` (upper case). The lift build uses the `cachegate` path.
  The path comes from the COMDAT copy of `StlAllocator<wchar_t,2>::deallocate` that the linker picks. The original also
  calls `std::vector::_Destroy` where the lift calls `~vector`. No source form is known.
- `0x681060` `Json::Reader::~Reader`: `Json::Reader` has no members in `jsoncpp.h`. The strings in the original use the
  upper case path of the `StlMemory.h` COMDAT copy, the deques use the lower case path. One TU cannot give both
  with the shared `StlAllocator`.
- `0x6a8430` `Json::LogicError::~LogicError` and `0x6a85d0` `Json::LogicError::LogicError`: `Json::Exception` has no
  `std::exception` base and no `msg_` member. `Json::LogicError` has no base class. This blocks both bodies.
- `0xe230`, `0x1d120`, `0x8c2b0`, `0x1ed800` `Property::Set` / `Property::GetFlag`: `Field::Def` is an empty struct.
  `Property` has no virtual slots and no `updateSync` or `SyncBuffer::Set` declarations. The layout work comes first.
- `0x8b110` `Pointer2<ChallengeParty>::operator=`, `0x176380` `Pointer2<Guild>::Pointer2<Guild>`,
  `0x3466d0` `Pointer2<Pc>::operator=`, `0x42e5d0` `Pointer2<Creature>::operator=`: members of a class template. The
  pointee classes are incomplete in the repo, so the instances cannot compile. Needs complete types first.
- `0x68bab0`, `0x68bb40`, `0x68bcc0`, `0x68bd50`, `0x68bed0`, `0x68bf60`, `0x68c0d0` `f_ability<...>::Set`: the template
  `f_ability` does not exist in the repo. `Field::Def` has no layout (`minmax` at +0xA0). The PDB signature of
  `0x68bab0` (3 arguments in the code, 4 in the PDB) needs a check.

## Files changed

- `src/Server/GameDaemon/nofile.cpp`
- `src/Server/GameDaemon/datapacker.h`
- `src/Server/GameDaemon/lock.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-047-w2.md`
