# LegacyBin (fork)

Source: fork `PapaBill1234/LegacyBin`, branch `schema-unpack`, commit `7c9e47c`.
Upstream: `RedDot-3ND7355/LegacyBin` (no licence file).

Our change: schema dump from the client exe and schema-based table unpack (`LegacyBin.Core`, CLI `legacybin`, GUI schema browser).

The upstream DLLs are not in this repo. `dotnet restore` gets them from NuGet:

| DLL | NuGet package | Version | Licence | SHA-256 of the DLL |
| --- | --- | --- | --- | --- |
| `DotNetZip.dll` | `DotNetZip` (`lib/net40`) | 1.13.8 | Ms-PL (DotNetZip.Semverd) | `00da1597d92235d3f84da979e2fa5dbf049bafb52c33bd6fc8ee7b29570c124c` |
| `MaterialSkin.dll` | `MaterialSkin.2` (`lib/net461`) | 2.1.3 | MIT | `bcee0a789f4c404e17d0220180d2ae99b8020892ed40f5a0341654b4786edf50` |

These hashes are the same as the DLLs of the upstream repo. The build embeds the DLLs as before (`LegacyBin.Resources.*.dll`).
