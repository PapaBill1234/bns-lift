// BannedWordFilterLoader.obj (LobbyDaemon PDB, 2019 + PDB): lines from the PDB line map.
// ❓ The folder name src/External/BannedWordFilter is not verified.
#include <stdio.h>
#include <string.h>
#include "BannedWordFilterLoader.h"

// LIFT: A6. __FILEW__ of the original build (rva 0x1e1d20).
#ifndef LIFT_BWF_LOADER_FILE
#define LIFT_BWF_LOADER_FILE L"src\\BannedWordFilterLoader.cpp"
#endif

// rva 0x209890. LIFT: the owner obj of the definition is not in the PDB (S_GDATA32 in globals).
BannedWordFilterLoader* BannedWordFilterLoader::_instance = NULL;

// 0x118fa0
BannedWordFilterLoader::~BannedWordFilterLoader()
{
    _chatFilter.clear();
    _nameFilter.clear();

    // Release the vector buffers.
    FilterRecordList().swap(_chatFilter);
    FilterRecordList().swap(_nameFilter);
}

// 0x119170
bool BannedWordFilterLoader::InitBannedWordFilterLoader()
{
    if (BannedWordFilterMemory::Memory() == NULL)
        return false;

    if (_instance != NULL)
        return false;

    _instance = new (BannedWordFilterMemory::Memory()->Alloc(sizeof(BannedWordFilterLoader), LIFT_BWF_LOADER_FILE, 54)) BannedWordFilterLoader;

    return true;
}

// Inlined in LoadNameFilter (line 93). The body has no line entries of its own.
// LIFT: the 3 sscanf_s targets are in 4-byte stack slots and the code reads only 16 bits of each.
// ❓ The type of ch is not verified. The code reads it as 16 bits.
void BannedWordFilterLoader::addFilterName(const char* line)
{
    unsigned short ch;
    unsigned short offset;
    unsigned short count;
    char level[16] = {0};

    // BUG: "%u" writes 32 bits into a 16-bit target.
    if (sscanf_s(line, "%u %hu %hu %s", &ch, &offset, &count, level, 16) != 4)
        return;

    // BUG: rec.level[1] and rec.level[2] are not set. push_back copies 2 uninitialized bytes.
    FilterRec rec;
    rec.ch = ch;
    rec.offset = offset;
    rec.count = count;

    // ❓ The PDB has no names for the match modes 0..4 (ConstFilterName reads them).
    switch (level[0])
    {
    case 'A':
        if (level[1] == 'D')
            rec.level[0] = 1;
        else if (level[1] == 'N')
            rec.level[0] = 2;
        else
            rec.level[0] = 3;
        break;
    case 'N':
        rec.level[0] = 0;
        break;
    case 'S':
        rec.level[0] = 3;
        break;
    case 'W':
        rec.level[0] = 4;
        break;
    default:
        rec.level[0] = 0;
        break;
    }

    _nameFilter.push_back(rec);
}

// 0x1191f0
bool BannedWordFilterLoader::LoadNameFilter(char* fileBuffer)
{
    char* next_token = NULL;

    if (fileBuffer != NULL)
    {
        // ❓ The name of the token variable is not in the PDB.
        char* token = strtok_s(fileBuffer, "\n", &next_token);

        while (token != NULL)
        {
            _instance->addFilterName(token);
            token = strtok_s(NULL, "\n", &next_token);
        }

        BannedWordFilterMemory::Memory()->Free(fileBuffer, LIFT_BWF_LOADER_FILE, 96);
        return true;
    }

    return false;
}

// 0x119430
char* BannedWordFilterLoader::CreateFileBuffer(wchar_t const* fileFullPath)
{
    if (fileFullPath == NULL)
        return NULL;

    char* buffer = NULL;
    FILE* fp = NULL;
    if (_wfopen_s(&fp, fileFullPath, L"rb") == 0)
    {
        fseek(fp, 0, SEEK_END);
        size_t size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (size != 0)
        {
            // BUG: no check of the Alloc result and no check of a negative ftell result.
            buffer = static_cast<char*>(BannedWordFilterMemory::Memory()->Alloc(size + 1, LIFT_BWF_LOADER_FILE, 171));
            fread(buffer, 1, size, fp);
            buffer[size] = 0;
        }

        fclose(fp);
    }

    return buffer;
}
