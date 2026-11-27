// npservicetran.h: npservicetran.cpp, npservicetran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class NPGetChannelPropertyTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121970
    static ::GameTranDef _def;  // LIFT: PDB data NPGetChannelPropertyTran::_def
    __cdecl NPGetChannelPropertyTran(void);  // 0x170690
private:
    virtual bool __cdecl work(int, void *);  // 0x170730
    bool __cdecl getChannelProperty(void *);  // 0x170780
};

class NPGroupInfoTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121980
    static ::GameTranDef _def;  // LIFT: PDB data NPGroupInfoTran::_def
private:
    virtual bool __cdecl work(int, void *);  // 0x170a10
    bool __cdecl groupInfo(void *);  // 0x170a60
};

class NPRegisterServiceTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121950
    static ::GameTranDef _def;  // LIFT: PDB data NPRegisterServiceTran::_def
    __cdecl NPRegisterServiceTran(void);  // 0x16f530
private:
    bool __cdecl init(int, void *);  // 0x16f5a0
    virtual bool __cdecl work(int, void *);  // 0x16f640
    bool __cdecl request(void *);  // 0x16f6c0
    bool __cdecl response(void *);  // 0x16fa00
    bool __cdecl expire(void *);  // 0x16fc40
};

class NPValidateGroupTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121960
    static ::GameTranDef _def;  // LIFT: PDB data NPValidateGroupTran::_def
private:
    virtual bool __cdecl work(int, void *);  // 0x16fcc0
    bool __cdecl validateGroup(void *);  // 0x16fd10
};

char * __cdecl GetNPCustomProtocolStr(::NPCustomProtocolType);  // 0x16f4e0
