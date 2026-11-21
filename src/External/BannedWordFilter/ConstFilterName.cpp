// ConstFilterName.obj (LobbyDaemon PDB, 2019 + PDB): lines from the PDB line map.
// ❓ The folder name src/External/BannedWordFilter is not verified.
#include <string.h>
#include "ConstFilterName.h"
#include "BannedWordFilterLoader.h"

// LIFT: A6. __FILEW__ of the original build (rva 0x1e1d80).
#ifndef LIFT_BWF_CONSTFILTERNAME_FILE
#define LIFT_BWF_CONSTFILTERNAME_FILE L"src\\ConstFilterName.cpp"
#endif

// 0x119770 (file static). Lines 43-107.
// It writes a lower-case, space-separated and hiragana form of src to dst. dst has space for wcslen(src) + 1 characters.
static void StrNormalize(wchar_t* dst, const wchar_t* src)
{
    // PDB: static locals. The table is in .data (rva 0x208a10), not in .rdata.
    // Index: half-width katakana (U+FF66..U+FF9F) - U+FF66. Value: hiragana - U+3041.
    static unsigned char s_halfKatakana2Hiragana[58] = {
        0x51, 0x00, 0x02, 0x04, 0x06, 0x08, 0x42, 0x44, 0x46, 0x22, 0x5b, 0x01, 0x03, 0x05, 0x07, 0x09,
        0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x25, 0x27, 0x29,
        0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x31, 0x34, 0x37, 0x3a, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x43, 0x45,
        0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4e, 0x52, 0x5a, 0x5b,
    };
    static const wchar_t NORM_HALF_KATAKANA_BASE = 0xFF66;
    static const wchar_t NORM_HALF_KATAKANA_MAX = 0xFF9F;
    static const wchar_t NORM_KATAKANA_BASE = 0x30A1;
    static const wchar_t NORM_KATAKANA_MAX = 0x30F6;

    while (*src != 0)
    {
        unsigned int ch = *src++;

        // Full-width ASCII to ASCII.
        if (ch >= 0xFF01 && ch <= 0xFF5E)
            ch -= 0xFEE0;

        if (ch >= L'A' && ch <= L'Z')
        {
            ch += L'a' - L'A';
        }
        else if ((ch >= 0x20 && ch <= 0x2F) || (ch >= 0x3A && ch <= 0x40) || (ch >= 0x5B && ch <= 0x60) ||
                 (ch >= 0x7B && ch <= 0xBF))
        {
            ch = L' ';
        }
        else if (ch > 0xFF)
        {
            // CJK symbols, general punctuation to misc symbols, half-width CJK punctuation.
            if ((ch >= 0x3000 && ch <= 0x301F) || (ch >= 0x2010 && ch <= 0x2670) || (ch >= 0xFF61 && ch <= 0xFF65))
                ch = L' ';
            else if (ch >= NORM_KATAKANA_BASE && ch <= NORM_KATAKANA_MAX)
                ch -= 0x60;
            else if (ch >= NORM_HALF_KATAKANA_BASE && ch <= NORM_HALF_KATAKANA_MAX)
                ch = s_halfKatakana2Hiragana[ch - NORM_HALF_KATAKANA_BASE] + 0x3041;
        }

        *dst++ = static_cast<wchar_t>(ch);
    }

    *dst = 0;
}

// 0x119870. Lines 121-244.
// It replaces each filtered character of str with '*' (spaces stay). It returns true if it replaced a character.
// The filter is a trie in _nameFilter: record 0 gives the root count, each record gives the range of its children.
bool ConstFilterName(BannedWordFilterString& str)
{
    bool filtered = false;
    unsigned int index = 0;

    const BannedWordFilterLoader::FilterRecordList& filters = BannedWordFilterLoader::GetInstance()->_nameFilter;
    if (filters.empty())
        return false;

    const unsigned int rootCount = filters[0].offset;

    // PDB: ConstFilterName::__l4::State, sizeof 32.
    struct State
    {
        wchar_t* start;
        wchar_t* term;
        unsigned int count;
        unsigned int offset;
        bool startOfWord;
    };
    State state[26];
    memset(state, 0, sizeof(state));

    const size_t len = str.size();
    if (len == 0)
        return false;

    wchar_t* normalized = static_cast<wchar_t*>(BannedWordFilterMemory::Memory()->Alloc((len + 1) * sizeof(wchar_t), LIFT_BWF_CONSTFILTERNAME_FILE, 149));
    StrNormalize(normalized, str.c_str());

    bool startOfWord = true;
    for (wchar_t* pos = normalized; ; ++pos)
    {
        const wchar_t ch = *pos;
        if (ch == L' ')
        {
            startOfWord = true;
            continue;
        }

        // Start a new match at this position.
        state[index].start = pos;
        state[index].term = NULL;
        state[index].count = rootCount;
        state[index].offset = 0;
        state[index].startOfWord = startOfWord;
        index = (index + 1) % _countof(state);

        for (State* s = state; s != state + _countof(state); ++s)
        {
            if (s->start == NULL)
                continue;

            const BannedWordFilterLoader::FilterRecordList& list = BannedWordFilterLoader::GetInstance()->_nameFilter;

            // LIFT: an inlined binary search (lower bound on ch) with no name in the PDB.
            // ❓ The original can use a helper function or a macro.
            const FilterRec* lo = &list[0] + s->offset;
            const FilterRec* hi = lo + s->count;
            if (lo != hi)
            {
                for (;;)
                {
                    const FilterRec* mid = lo + (hi - lo) / 2;
                    if (ch > mid->ch)
                    {
                        if (mid == lo)
                            break;
                        lo = mid;
                    }
                    else
                    {
                        hi = mid;
                        if (mid == lo)
                            break;
                    }
                }
            }
            const unsigned int found = static_cast<unsigned int>(hi - (&list[0] + s->offset));

            if (found >= s->count || list[s->offset + found].ch != ch)
            {
                // No match continues here. Mask the matched part, if a word ends in it.
                if (s->term != NULL)
                {
                    wchar_t* dst = &str[0] + (s->start - normalized);
                    for (wchar_t* p = s->start; p != s->term; ++p, ++dst)
                    {
                        if (*p != L' ')
                        {
                            *dst = L'*';
                            filtered = true;
                        }
                    }
                }
                s->start = NULL;
            }
            else
            {
                const FilterRec& rec = list[s->offset + found];
                s->count = rec.count;
                s->offset = rec.offset;

                // ❓ The PDB has no names for the match modes (see BannedWordFilterLoader::addFilterName).
                switch (rec.level[0])
                {
                case 4:
                    // The word must end after ch.
                    if (pos[1] != 0 && pos[1] != L' ')
                        break;
                    // fall through
                case 3:
                    // The word must start at s->start.
                    if (!s->startOfWord)
                        break;
                    // fall through
                case 1:
                {
                    // The match must not contain a space.
                    bool hasSpace = false;
                    for (wchar_t* p = s->start; p != pos && !hasSpace; ++p)
                        hasSpace = (*p == L' ');
                    if (hasSpace)
                        break;
                }
                    // fall through
                case 2:
                    s->term = pos + 1;
                    break;
                default:
                    break;
                }
            }
        }

        if (ch == 0)
            break;

        startOfWord = false;
    }

    BannedWordFilterMemory::Memory()->Free(normalized, LIFT_BWF_CONSTFILTERNAME_FILE, 242);
    return filtered;
}
