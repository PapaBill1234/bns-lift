# Source layout

The `src/` tree uses the folder layout of the original depot. The root of `src/` is the depot folder `Program\`.

## Source of the layout

| Source | What it gives |
| --- | --- |
| PDB line data (`~/.cache/bns-lift/pdbq/<Exe>.lines.txt`) | The full path of each source file with code. The PDB writes the path in lower case. |
| Exe strings (`__FILE__`, assert text) | Paths with the original case, for example `Program\Server\BloodLib\include\Channel.h`. |
| PDB S_OBJNAME / build info | Case of `Security`, `BloodCrypto` and the server folders. |

Build of all 4 PDBs: `348NC` branch, `E:\DailyBuild02\<Exe>-Common-0.0.348\depot\Branch\348NC\Program\`. The BloodCrypto paths come from `E:\pfa_5\Program\Security\`.

## Folders

| Folder | Files | Case proof |
| --- | --- | --- |
| `src/Security/source/BloodCrypto/crypto/` | 14 | `Security`, `BloodCrypto`: S_OBJNAME `Security\_intermediate\BloodCrypto`. ❓ Case of the other parts (PDB gives lower case only) |
| `src/Security/source/BloodCrypto/crypto/encoder/` | 4 | `Security`, `BloodCrypto`: S_OBJNAME `Security\_intermediate\BloodCrypto`. ❓ Case of the other parts (PDB gives lower case only) |
| `src/Security/source/BloodCrypto/crypto/mode/` | 2 | `Security`, `BloodCrypto`: S_OBJNAME `Security\_intermediate\BloodCrypto`. ❓ Case of the other parts (PDB gives lower case only) |
| `src/Security/source/BloodCrypto/hash/` | 5 | `Security`, `BloodCrypto`: S_OBJNAME `Security\_intermediate\BloodCrypto`. ❓ Case of the other parts (PDB gives lower case only) |
| `src/Security/source/BloodCrypto/key/` | 2 | `Security`, `BloodCrypto`: S_OBJNAME `Security\_intermediate\BloodCrypto`. ❓ Case of the other parts (PDB gives lower case only) |
| `src/Security/source/BloodCrypto/math/bignumber/` | 7 | `Security`, `BloodCrypto`: S_OBJNAME `Security\_intermediate\BloodCrypto`. ❓ Case of the other parts (PDB gives lower case only) |
| `src/Security/source/BloodCrypto/math/prng/` | 2 | `Security`, `BloodCrypto`: S_OBJNAME `Security\_intermediate\BloodCrypto`. ❓ Case of the other parts (PDB gives lower case only) |
| `src/Server/BloodLib/include/` | 33 | exe string `Program\Server\BloodLib\include\Channel.h` (all 4 exes) |
| `src/Server/BloodLib/source/` | 43 | case of `Server\BloodLib`: exe string. `source`: exe string `source\DelayedRelease.cpp` |
| `src/Server/Economy/CacheGate/` | 11 | PDB string `Server\Economy\CacheGate` (CacheGate) |
| `src/Server/Economy/PostOfficeDaemon/` | 56 | PDB string `Server\Economy\PostOfficeDaemon` (PostOfficeDaemon) |
| `src/Server/Economy/Shared/` | 2 | exe string `..\Economy\Shared` |
| `src/Server/LobbyDaemon/` | 2 | exe string `..\LobbyDaemon` |
| `src/Server/LobbyGate/` | 20 | PDB string `Server\LobbyGate` (LobbyGate) |
| `src/Server/Packet/` | 2 | exe string `..\Packet` |
| `src/Server/Shared/` | 7 | exe string `..\Shared` |
| `src/Server/SmartCouponDaemon/` | 23 | PDB string `Server\SmartCouponDaemon` (SmartCouponDaemon) |
| `src/crt/`, `src/selftest/` | lift only | Not in the original tree. |

## Placement rules

1. The PDB line data gives the folder of the file. This rule places most files.
2. A header with no code lines goes to the folder of its `.cpp`. A BloodLib header goes to `Server/BloodLib/include/`.
3. A lift-only file (`LinkStubs.cpp`, handler list `.cpp`) goes to the folder of its server.

These files have no PDB path. Their folder is a guess (❓):

| File | Folder | Reason |
| --- | --- | --- |
| `TimerQueue.h`, `SysInfo.h`, `XmlReader.h` | `Server/BloodLib/include/` | BloodLib code uses them. `StlMemory.h` has an exe string. |
| `CryptoHash.h` | `Security/source/BloodCrypto/hash/` | With `ripemd128.cpp`. |
| `Connection.h` | `Server/BloodLib/include/` | With `Session.cpp`. |
| `aes128TableData.inc`, `blowfishData.inc` | `Security/source/BloodCrypto/crypto/` | With their `.cpp`. |
| `BigInteger.h` | `Security/source/BloodCrypto/math/bignumber/` | The PDB has `bignumber.h` there. ❓ The original file name. |

## Build

CMake puts all folders in `LIFT_SRC_INCLUDE`. The original projects use include paths too, so `#include "X.h"` stays short.

