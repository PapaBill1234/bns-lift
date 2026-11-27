// recycletimemanager.h: recycletimemanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RecycleTimeManager
{
public:
    __cdecl RecycleTimeManager(void);  // 0x60fa40
    void __cdecl InitializeRecycleTime2(char);  // 0x60fc80
    void __cdecl InitializeRecycleTime2(char, short);  // 0x60fe70
    void __cdecl SetRecycleTime2(char, short, long);  // 0x60ff70
    void __cdecl ExtendLimitTime2(char, short, long);  // 0x610090
    void __cdecl SetGlobalRecycleTime2(short, long);  // 0x6101c0
    void __cdecl ModifyRecycleTime2(char, long);  // 0x610220
    void __cdecl ModifyRecycleTime2(char, short, long);  // 0x610320
    bool __cdecl IsAvailableRecycleTime2(char, short);  // 0x610370
    bool __cdecl IsAvailableGlobalRecycleTime2(short);  // 0x610440
    short __cdecl FetchList(short *, char *, unsigned short);  // 0x6104f0
    int __cdecl SetDbList(short, char const *, int);  // 0x6105f0
    bool __cdecl ConfirmRecycleTime(short);  // 0x610860
    void __cdecl ApplyAccountRecycleTime(::std::vector< ::AccountRecycleTime, ::StlAllocator< ::AccountRecycleTime, 2> >);  // 0x610900
    __int64 __cdecl GetLimitTime2(char, short);  // 0x610a90
    __int64 __cdecl GetRemainRecycleTime2(char, short);  // 0x610af0
    __int64 __cdecl GetRemainGlobalRecycleTime2(short);  // 0x610be0
private:
    char __cdecl getRecycleTimeMaxId(char);  // 0x610ca0
    void __cdecl modifyRecycleTime2(char, short, long);  // 0x610cf0
    void __cdecl sendCache2(short, __int64);  // 0x610dd0
    void __cdecl confirmRecycleTime2(short);  // 0x610fd0
public:
    void __cdecl FetchAllAccountRecycleTime(::std::vector< ::AccountRecycleTime, ::StlAllocator< ::AccountRecycleTime, 2> > &);  // 0x611020
};

