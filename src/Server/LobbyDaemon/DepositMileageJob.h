// DepositMileageJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
#pragma once
#include <stddef.h>
#include "LobbyJob.h"
#include "StringUtil.h"

class ObjPool;
struct LobbyJobDef;

// PDB DepositMileageReqParam (sizeof 0x5A8). The caller fills it and gives it to work(5, param).
struct DepositMileageReqParam
{
    char depositType;
    char requestLocation;
    char requestType;
    unsigned long long requestId;
    id128 userId;
    short virtualCurrencyId;
    long long virtualCurrencyAmount;
    long long virtualCurrencyExpireTime;
    int requestCode;
    int depositReasonCode;
    char depositReason[201];
    bool refundable;
    bool notification;
    wchar_t notificationName[65];
    wchar_t notificationContent[513];
    long long pcDbId;
    unsigned long long requestSubId;
    char locationHint;
    char pcRace;
    char pcSex;
    char pcJob;
};
static_assert(sizeof(DepositMileageReqParam) == 0x5A8, "sizeof DepositMileageReqParam");
static_assert(offsetof(DepositMileageReqParam, userId) == 0x10, "DepositMileageReqParam::userId");
static_assert(offsetof(DepositMileageReqParam, depositReason) == 0x40, "DepositMileageReqParam::depositReason");
static_assert(offsetof(DepositMileageReqParam, refundable) == 0x109, "DepositMileageReqParam::refundable");
static_assert(offsetof(DepositMileageReqParam, notificationName) == 0x10C, "DepositMileageReqParam::notificationName");
static_assert(offsetof(DepositMileageReqParam, notificationContent) == 0x18E, "DepositMileageReqParam::notificationContent");
static_assert(offsetof(DepositMileageReqParam, pcDbId) == 0x590, "DepositMileageReqParam::pcDbId");
static_assert(offsetof(DepositMileageReqParam, locationHint) == 0x5A0, "DepositMileageReqParam::locationHint");

// PDB layout (sizeof 0x600, LobbyJob base).
class DepositMileageJob : public LobbyJob
{
public:
    enum State
    {
        INIT = 0,
        DEPOSIT = 1,
        FIN = 2,
    };

    // PDB DepositMileageJob::CallbackParam (sizeof 0x30). The constructor and the operators are PDB inline methods
    // (no RVA). The constructor is inlined at the top of depositAck (0x4aa40): userId copies ID128_GUID_ZERO.
    struct CallbackParam
    {
        unsigned long long requestId;
        unsigned long long externalKey;
        id128 userId;
        long long virtualCurrencyAmount;
        short virtualCurrencyId;
        char depositType;
        char locationHint;

        CallbackParam() : requestId(0), externalKey(0), userId(ID128_GUID_ZERO), virtualCurrencyAmount(0), virtualCurrencyId(0)
        {
        }
        CallbackParam const& operator()(DepositMileageReqParam* param)
        {
            requestId = param->requestId;
            userId = param->userId;
            virtualCurrencyAmount = param->virtualCurrencyAmount;
            virtualCurrencyId = param->virtualCurrencyId;
            depositType = param->depositType;
            externalKey = param->requestSubId;
            locationHint = param->locationHint;
            return *this;
        }
        CallbackParam const& operator()(DepositMileageJob* job)
        {
            requestId = job->_requestId;
            userId = job->_userId;
            virtualCurrencyAmount = job->_virtualCurrencyAmount;
            virtualCurrencyId = job->_virtualCurrencyId;
            depositType = job->_depositType;
            externalKey = job->_requestSubId;
            locationHint = job->_locationHint;
            return *this;
        }
    };

    // PDB DepositMileageJob::Callback (sizeof 8): an interface. The owner of the job gives an instance from
    // Memory::_Manager[2]. The job destructor deletes it.
    class Callback
    {
    public:
        virtual ~Callback() {}
        virtual void OnError(CallbackParam const&) = 0;
        virtual void OnSuccess(CallbackParam const&, long long, int) = 0;
        virtual void OnFail(CallbackParam const&, int) = 0;
        virtual void OnTimeout(CallbackParam const&) = 0;
    };

    static void* _vtbl();  // PDB declaration. LIFT: not lifted.
    DepositMileageJob(Callback* callback);  // 0x49ba0
    virtual ~DepositMileageJob();  // 0x49c90
    virtual LobbyJobDef const* GetDefinition() const;  // 0x49b40
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x49b50
    virtual bool work(int, void*);  // 0x49d20
    bool init(void*);  // 0x49da0
    bool depositReq();  // 0x4a3e0
    bool depositAck(void*);  // 0x4aa40
    bool depositExpire();  // 0x4aee0

private:
    friend struct DepositMileageJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    char _depositType;  // +0x50
    char _requestLocation;  // +0x51
    char _requestType;  // +0x52
    long long _requestId;  // +0x58
    id128 _userId;  // +0x60
    short _virtualCurrencyId;  // +0x70
    long long _virtualCurrencyAmount;  // +0x78
    long long _virtualCurrencyExpireTime;  // +0x80
    int _requestCode;  // +0x88
    int _depositReasonCode;  // +0x8c
    char _depositReason[201];  // +0x90
    bool _refundable;  // +0x159
    bool _notification;  // +0x15a
    wchar_t _notificationName[65];  // +0x15c
    wchar_t _notificationContent[513];  // +0x1de
    long long _pcDbId;  // +0x5e0
    long long _requestSubId;  // +0x5e8
    char _locationHint;  // +0x5f0
    char _pcRace;  // +0x5f1
    char _pcSex;  // +0x5f2
    char _pcJob;  // +0x5f3
    Callback* _callback;  // +0x5f8

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(DepositMileageJob) == 0x600, "sizeof DepositMileageJob");
struct DepositMileageJobLayoutCheck
{
    static_assert(offsetof(DepositMileageJob, _depositType) == 0x50, "DepositMileageJob::_depositType");
    static_assert(offsetof(DepositMileageJob, _requestId) == 0x58, "DepositMileageJob::_requestId");
    static_assert(offsetof(DepositMileageJob, _userId) == 0x60, "DepositMileageJob::_userId");
    static_assert(offsetof(DepositMileageJob, _virtualCurrencyId) == 0x70, "DepositMileageJob::_virtualCurrencyId");
    static_assert(offsetof(DepositMileageJob, _requestCode) == 0x88, "DepositMileageJob::_requestCode");
    static_assert(offsetof(DepositMileageJob, _depositReason) == 0x90, "DepositMileageJob::_depositReason");
    static_assert(offsetof(DepositMileageJob, _refundable) == 0x159, "DepositMileageJob::_refundable");
    static_assert(offsetof(DepositMileageJob, _notificationName) == 0x15c, "DepositMileageJob::_notificationName");
    static_assert(offsetof(DepositMileageJob, _notificationContent) == 0x1de, "DepositMileageJob::_notificationContent");
    static_assert(offsetof(DepositMileageJob, _pcDbId) == 0x5e0, "DepositMileageJob::_pcDbId");
    static_assert(offsetof(DepositMileageJob, _locationHint) == 0x5f0, "DepositMileageJob::_locationHint");
    static_assert(offsetof(DepositMileageJob, _callback) == 0x5f8, "DepositMileageJob::_callback");
};
