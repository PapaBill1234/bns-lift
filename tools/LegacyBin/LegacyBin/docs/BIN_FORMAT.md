# Blade & Soul `datafile.bin` / `localfile.bin` format (TADBOSLB v5)

Short reference for `LegacyBin.Core`. The full research, with sources and addresses, is in
[slopemulator `bns-server/Docs/DataFile`](https://github.com/PapaBill1234/slopemulator/tree/main/bns-server/Docs/DataFile)
(`02-tadboslb.md`, `06-client-body.md`, `07-client-exe-tabledefs.md`, `08-strings.md`, `10-schema-from-exe.md`).

All values are little-endian. Verified on client 0.0.381.8884 (`datafile.bin`, `datafile64.bin`, `localfile.bin`, `localfile64.bin`).

## 1. Container

```
header (99 B x86 / 119 B x64)
alias block (main datafile only; localfile has none)
table 0 .. table N-1   (11-byte header + body each)
```

| Field | x86 | x64 | Offset x86 / x64 |
| --- | --- | --- | --- |
| magic `TADBOSLB` | 8 | 8 | 0 / 0 |
| file version (= 5) | u8 | u8 | 8 / 8 |
| game version | 4 × u16 | 4 × u16 | 9 / 9 |
| total table size | u32 | u64 | 17 / 17 |
| table count | u32 | u64 | 21 / 25 |
| alias block size | u32 | u64 | 25 / 33 |
| alias count | u32 | u64 | 29 / 41 |
| max buffer size | u32 | u64 | 33 / 49 |
| save time (Unix) | u32 | u32 | 37 / 57 |
| compressed, encrypted flags | 2 × u8 | 2 × u8 | 41 / 61 |
| reserved | 56 | 56 | 43 / 63 |

Notes:

- The localfile header repeats the alias fields of the datafile, but the localfile has **no** alias block.
- LegacyBin.Core finds width and role by walking all tables: only the right layout ends exactly at the file size.
- The container has no encryption and no compression. Both flags are 0.

Table header (11 bytes): `u8 kind` (1 = auto-key, 2 = multi-key), `u16 type`, `u16 major`, `u16 minor`, `u32 body size`.

## 2. Table body

The body starts with `u8 compressed`.

**Plain (0)**

| Field | Kind 2 | Kind 1 x86 | Kind 1 x64 |
| --- | --- | --- | --- |
| count | u32 | u32 | u64 |
| fixed region size | u32 | u32 | u32 |
| extra region size | u32 | u32 | u32 |
| low-memory flag | u8 | u8 | u8 |

Then the fixed region (records back to back), then the extra region (string pool).
Kind 1 stores `count − 1` records (slot 0 is not stored).

**Compressed (1)**: `u32 block count`, `u16 8`, then per block:
`i64 first key`, `i64 last key`, `u16 csize`, zlib stream, `u16 dsize`, `u32 record count`, `u16 offset[record count]`.
A record span in a block = fixed record + its own string pool.

**Record** = 6-byte `DrEl` header (`i8 element`, `u8 pad`, `i16 subtype`, `u16 size`) + fields.
The key is the 8 bytes at the element's `keyoffset`.

## 3. Field types and strings

The schema gives name, type, offset, size and repeat count of each field.

| Type | Value in the record |
| --- | --- |
| `string` | u32 (x86) / u64 (x64) offset into the pool → UTF-16LE, zero-terminated |
| `native` | u32 byte size + u32 offset (+ u32 0 on x64) → UTF-16LE text |
| `ref` | 8 key bytes of the target record (`reftable` = target type). 0 = no link |
| `tref` | i16 target table type, pad, 8 key bytes |
| `icon` | 8 key bytes into `icontexture`, i16 index |
| `seq`, `seq16`, `prop_seq` | index into the attribute's label list |
| `int*`, `msec`, `distance`, `velocity`, `time64` | signed integer of the field size |

Pool base: the table extra region (plain tables) or the record's own span (compressed tables).
Fields with size 0 are server-only and have no bytes in the client file.

## 4. Schema (table definitions)

The client has no schema file. The definitions are a static array inside the executable:
slot 0 = null, slot *i* = pointer to `DrTableDef` with `type == i` and a UTF-16 name.
`SchemaDumper` scans the data sections for the longest such array and reads the structs with these layouts:

| Struct | x86 (2020 `Client.exe`) | x64 packed-4 (2026 `BNSR.exe`) |
| --- | --- | --- |
| DrTableDef | name 0, type 4, major 6, minor 8, el 12, elcount 16, maxid 20, autokey 28, module 32 | name 0, type 8, major 10, minor 12, el 16, elcount 24, maxid 28, autokey 36, module 40 |
| DrElDef | stride 44: name 0, type 4, body 8, child[32] 12 | stride 52: name 0, type 8, body 12, child[32] 20 |
| DrElBodyDef | stride 20: attr 0, sub 4, defrec 8, attrcount 12, subcount 14, size 16, keyoffset 18 | stride 32: attr 0, sub 8, defrec 16, attrcount 24, subcount 26, size 28, keyoffset 30 |
| DrSubDef | stride 16: name 0, attr 4, defrec 8, attrcount 12, size 14 | stride 28: name 0, attr 8, defrec 16, attrcount 24, size 26 |
| DrAttrDef | stride 64: name 0, namehash 4, type 8, key 9, repeat 10, …, reftable 46, offset 52, size 54 | stride 84: name 0, namehash 8, type 16, key 17, repeat 18, …, reftable 62, offset 68, size 70 |

The executable must be **unpacked**. A protected executable (Themida/WinLicense, VMProtect, high-entropy sections)
is refused, because its data sections are encrypted on disk.

Rule: the schema must come from the **same build** as the `.bin` files. Table versions are checked; a table with a
different version is exported raw.
