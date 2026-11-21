// BannedWordFilterLoader.obj (LobbyDaemon PDB, 2019 + PDB). BannedWordFilterLoader: field list 0x80DE, sizeof 64.
// ❓ The folder name src/External/BannedWordFilter is not verified.
#pragma once
#include <vector>
#include "STLMemory.h"

// PDB: sizeof 10.
struct FilterRec
{
    wchar_t ch;
    unsigned short offset;
    unsigned short count;
    unsigned char level[3];
};

class BannedWordFilterLoader
{
public:
    typedef BannedWordFilterAllocator<FilterRec> FilterRecAllocator;
    typedef std::vector<FilterRec, FilterRecAllocator> FilterRecordList;
    typedef FilterRecordList::iterator FilterRecordListIt;
    typedef FilterRecordList::const_iterator FilterRecordListConstIt;

    BannedWordFilterLoader() {}
    ~BannedWordFilterLoader();  // 0x118fa0

    static bool InitBannedWordFilterLoader();  // 0x119170
    static BannedWordFilterLoader* GetInstance() { return _instance; }
    // LIFT: LoadChatFilter and Clear are in the PDB, but not in this binary. They are not declared.
    static bool LoadNameFilter(char* fileBuffer);  // 0x1191f0
    static char* CreateFileBuffer(wchar_t const* fileFullPath);  // 0x119430

    static void* operator new(size_t, void* p) { return p; }
    static void operator delete(void*, void*) {}

    FilterRecordList _chatFilter;
    FilterRecordList _nameFilter;

private:
    void addFilterName(const char* line);  // inlined in LoadNameFilter

    static BannedWordFilterLoader* _instance;
};
