# LegacyBin

Blade & Soul `datafile.bin` / `localfile.bin` unpack / repack tool (32-bit and 64-bit clients).

## Features

- **Schema from the client**: read all table definitions from an *unpacked* `Client.exe` / `Client64.exe` (PE32 or PE32+). Save them as a TableDefs JSON folder.
- **Schema unpack**: decode every table with real field names. Strings, native text, `seq` labels, `ref`/`tref`/`icon` links (to the target alias) are resolved. One readable XML per table.
- **Schema browser** (Tools → Schema browser, Ctrl+B): all tables and records in a grid, with filter and a per-record view.
- **`legacybin` CLI** (`LegacyBin.Cli`, .NET 8, Windows/Linux/macOS) for the same jobs headless.

- **Unpack** bin → per-table XML under `<file>.files/`
- **Repack** edited XML → bin (writes via temp file, then replaces the original)
- **32-bit** (`datafile.bin`, `localfile.bin`) and **64-bit** (`datafile64.bin`, `localfile64.bin`) layouts
- Bit-identical round-trip when content is unchanged (paddings and placeholders preserved)

## Binary format documentation

**Full structure reference for developers (32-bit vs 64-bit headers, tables, loose/archive, fields, paddings):**

### [docs/BIN_FORMAT.md](docs/BIN_FORMAT.md)

That doc covers file layout diagrams, field sizes, detection rules, XML mapping, and a repack safety checklist.

## 32-bit vs 64-bit (summary)

| Area | 32-bit | 64-bit |
|------|--------|--------|
| Header size fields | `int32` | `int64` |
| Table count | `int32` | `int64` |
| Name-table body | if `tableCount > 10` | same; entries 16-byte vs 12-byte in blob |
| Loose `FieldCount` | `int32` | `int32` + pad `int32` when `elementCount == 1` |
| List payload `Size` | `int32` | `int32` |
| Compressed tables | same | same |
| Field records | same | same |
| Trailing / region padding | preserve | preserve |

Mode is resolved by:

1. Filename containing `64.bin` / `datafile64` / `localfile64`, or  
2. Header layout detection if the file was renamed  

## Schema unpack (new)

GUI: **Tools → Schema browser** → *Schema from Client.exe…* → *Open .bin files…* (select datafile **and** localfile) → *Export XML…*.

CLI:

```sh
legacybin schema  Client.exe  defs/                 # dump table definitions (JSON per table)
legacybin unpack  defs/  out/  datafile.bin localfile.bin
legacybin unpack  Client.exe  out/  datafile.bin localfile.bin   # dump + unpack in one step
legacybin info    datafile64.bin
legacybin roundtrip datafile.bin                   # container write = byte-identical check
```

Use the 32-bit exe for `datafile.bin`/`localfile.bin`, the 64-bit exe for the `*64.bin` files, from the same client build.

Checked on client 0.0.381.8884 with the 2020 `Client.exe` (x86): 362 definitions, equal to the known TableDefs 0.0.381.8876 x86 dump
in all fields; `datafile.bin` + `localfile.bin` → 352 tables, 1,769,726 records, 0 size mismatches,
3,616,627 links, 107 with a missing target (dangling in the data itself). The four `.bin` files round-trip byte-identically.

Example output (`item.xml`):

```xml
<record type="grocery" id="100" level="1" alias="Test_N-ShopAccountShippingItem" game-category-1="consumable" ... />
```

## Build

```sh
dotnet build LegacyBin.sln -c Release
```

The GUI targets .NET Framework 4.8 (SDK-style project, builds in VS 2019+ or with `dotnet build` on any OS).
`LegacyBin.Core` is `netstandard2.0`, the CLI is `net8.0`.

## Usage

1. Build `LegacyBin.sln` (see *Build*)
2. Run **LegacyBin** → main window is **Bin U/R Tool** (Unpack / Repack)
3. **Open Bin Editor** → full in-app table/field/string editor (or from the editor: **Tools → Legacy Unpack/Repack…**)

### Bin Editor

1. **File → Open** a `datafile.bin` / `datafile64.bin` / `localfile*.bin`
2. Select a table (left). Edit **fields** (top-right) and **lookup strings** (bottom-right)
3. **File → Save** / **Save As** writes the `.bin` (temp file then replace)
4. Optional: **File → Export XML…** for external tools

**View → Field data as ints** toggles int vs hex field payloads (same as the “Int?” checkbox on the U/R form).  
**View → Dark mode** toggles the editor/dialog theme (on by default; U/R tool already uses MaterialSkin dark).

### Editor notes

- Large tables use a **virtual** field/string grid (safe for tens of thousands of rows).
- **Loose** tables are fully editable. **Archive** tables: pick a **sub-archive** block (or all merged); save recompresses.
- **Add / Delete** field & string rows (single block for archives — not “All blocks”).
- **Add block / Delete block** on the sub-archive bar (new empty block starts with one Size=0 placeholder field).
- **Edit → Undo / Redo** (Ctrl+Z / Ctrl+Y), **Find in all tables** (Ctrl+Shift+F).
- **View → File header**, **Name table (hex)**, **Region tail / padding (hex)** — region tail is **editable** (advanced).
- Region tail and list trailing padding are preserved on save.
- Open → Save with no edits should remain bit-identical for known good samples.

### Localfile translate

**Tools → Localfile Translate…** (BnsDatTool-compatible):

1. Open `localfile.bin` / `localfile64.bin` in the editor  
2. **Export XML** → Target `Translation.xml` (aliases + original text from the text/commons table)  
3. **Merge XMLs by alias** — Source = other region’s Translation XML (e.g. English), Target = current client export (e.g. Thai structure). Matched aliases copy source replacements in.  
4. **Fill gaps (auto-translate)** — After merge, many rows are already `original ≠ replacement`. The tool:  
   - samples those rows and **detects original language + replacement language** (e.g. `th` → `en`)  
   - locks that pair for the run  
   - only translates **gaps** still at `original == replacement` (alias missing in source)  
   - dedupes by original text; resumes via `Translation.xml.gtcache.{sl}-{tl}`  
5. **Apply XML → open bin** (matches by **alias**, then by original text)  
6. **File → Save** the bin  

Lookup layout for text records: `words[0]=alias`, `words[1]=display text`. Oversized compressed blocks can be auto-split after apply.

Fill gaps uses the unofficial Google Translate free endpoint (no API key). Prefer merge-first so only missing aliases hit the API.

**Markup safety:** before each MT call, `<font …>` tags and HTML entities (`&quot;`, `&lt;`, `&amp;`, …) are replaced with placeholders and restored afterward so Google cannot turn entities into raw `"` / `<` and break in-game UI.

**Speed:** set **Workers** (default 6, max 16) for parallel requests. ~6× is usually a good balance; if you see many errors/429s, drop to 3–4 or let retries/backoff handle it and re-run from cache.
