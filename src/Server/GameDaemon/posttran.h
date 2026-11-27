// posttran.h: posttran.cpp, posttran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DeliverPostTran
{
public:
    enum CHECK_POST_ZS_RESULT_TYPE {};
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x196100
private:
    ::DeliverPostTran::CHECK_POST_ZS_RESULT_TYPE __cdecl checkAndPostForExecutingInZS(int, bool *);  // 0x1996c0
    virtual bool __cdecl work(int, void *);  // 0x199b40
    bool __cdecl init(int, void *);  // 0x199e40
    bool __cdecl checkPostTitleFromUicReq(void);  // 0x19a0c0
    bool __cdecl checkPostTitleFromUicOk(void *);  // 0x19a2c0
    bool __cdecl checkPostTitleFromUicFail(void *);  // 0x19a3a0
    bool __cdecl checkPostContentFromUicReq(void);  // 0x19a4a0
    bool __cdecl checkPostContentFromUicOk(void *);  // 0x19a6a0
    bool __cdecl checkPostContentFromUicFail(void *);  // 0x19a780
    bool __cdecl checkPcInven(void);  // 0x19a880
    bool __cdecl retrieveCharacterInfoReq(void);  // 0x19c650
    bool __cdecl retrieveCharacterInfoOk(void *);  // 0x19c9e0
    bool __cdecl retrieveCharacterInfoFail(void *);  // 0x19cac0
    bool __cdecl checkPostCapacityReq(void);  // 0x19cc50
    bool __cdecl checkPostCapacityOk(void *);  // 0x19cf60
    bool __cdecl checkPostCapacityFail(void *);  // 0x19d000
    bool __cdecl deliverPost(void);  // 0x19d1b0
    bool __cdecl cancel(void);  // 0x19ed50
    bool __cdecl expired(void);  // 0x19f160
};

class DeliverPostWithTranTask
{
public:
    virtual __cdecl ~DeliverPostWithTranTask(void);  // 0x19f1b0
    bool __cdecl Initialize(::Zone *, ::Pc *, ::DeliverPostTran *, int);  // 0x19f210
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x19f360
    virtual void __cdecl start(void);  // 0x19f3a0
};

class DetachPostAttachmentTran_IndetachFixed
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1960f0
private:
    virtual bool __cdecl work(int, void *);  // 0x1987a0
    bool __cdecl detachReq(void);  // 0x1988a0
    bool __cdecl reserveBagPosOk(void *);  // 0x198c50
    bool __cdecl detachOk(void *);  // 0x198cf0
    bool __cdecl detachFail(void *);  // 0x199130
    bool __cdecl abort(short);  // 0x199570
    short __cdecl getGameFailReason(short);  // 0x199600
};

class MarkExpressPostTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1960e0
private:
    virtual bool __cdecl work(int, void *);  // 0x197c10
    bool __cdecl charge(void);  // 0x197d50
    bool __cdecl markReq(void);  // 0x197fd0
    bool __cdecl markOk(void *);  // 0x198060
    bool __cdecl markFail(void *);  // 0x1983a0
    bool __cdecl abort(short);  // 0x1986e0
};

class ResumeDeliverPostTranAfterUICTask
{
public:
    __cdecl ResumeDeliverPostTranAfterUICTask(void);  // 0x196130
    bool __cdecl Initialize(::Zone *, ::Pc *, unsigned __int64, int, wchar_t const *);  // 0x19f410
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x19f500
    virtual void __cdecl start(void);  // 0x19f540
};

