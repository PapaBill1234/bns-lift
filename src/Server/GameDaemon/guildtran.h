// guildtran.h: guildtran.cpp, guildtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AssentGuildCraftTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1212b0
private:
    virtual bool __cdecl work(int, void *);  // 0x1279c0
    bool __cdecl init(int, void *);  // 0x127a40
    bool __cdecl tryAssentGuildCraft(void);  // 0x127d10
    bool __cdecl assentGuildCraftOk(void);  // 0x127ee0
    bool __cdecl assentGuildCraftFail(short);  // 0x1284a0
};

class ContractGuildCraftTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1212a0
private:
    virtual bool __cdecl work(int, void *);  // 0x126160
    bool __cdecl init(int, void *);  // 0x126240
    bool __cdecl tryContractGuildCraft(void);  // 0x1264f0
    bool __cdecl contractGuildCraftOk(void *);  // 0x1267a0
    bool __cdecl contractGuildCraftFail(void *);  // 0x1275d0
};

class ContractGuildUniformTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121300
private:
    virtual bool __cdecl work(int, void *);  // 0x12bc20
    bool __cdecl init(int, void *);  // 0x12bca0
    bool __cdecl tryContractGuildUniform(void);  // 0x12bf80
    bool __cdecl contractGuildUniformOk(void *);  // 0x12c180
    bool __cdecl contractGuildUniformFail(short);  // 0x12cbf0
};

class DeleteGuildTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121280
    __cdecl DeleteGuildTran(::User *);  // 0x124560
private:
    virtual bool __cdecl work(int, void *);  // 0x1245d0
    bool __cdecl init(int, void *);  // 0x124650
    bool __cdecl tryDeleteGuild(void);  // 0x124760
    bool __cdecl deleteGuildOk(void);  // 0x1248c0
    bool __cdecl deleteGuildFail(short);  // 0x124f90
};

class DepositInGuildBankTranEx
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121290
    __cdecl DepositInGuildBankTranEx(::User *);  // 0x1251c0
private:
    virtual bool __cdecl work(int, void *);  // 0x1252b0
    bool __cdecl init(int, void *);  // 0x125310
    bool __cdecl depositInGuildBankOk(void *);  // 0x125560
    bool __cdecl depositInGuildBankFail(void *);  // 0x125db0
};

class DonateGuildCraftBrandMaterialTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1212e0
    __cdecl DonateGuildCraftBrandMaterialTran(::User *);  // 0x12a330
private:
    virtual bool __cdecl work(int, void *);  // 0x12a440
    bool __cdecl init(int, void *);  // 0x12a500
    bool __cdecl donateGuildCraftBrandMaterialOk(void);  // 0x12a7a0
    bool __cdecl donateGuildCraftBrandMaterialFail(void *);  // 0x12ae90
};

class DonateGuildCraftNormalMaterialTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1212d0
    __cdecl DonateGuildCraftNormalMaterialTran(::User *);  // 0x129490
private:
    virtual bool __cdecl work(int, void *);  // 0x129590
    bool __cdecl init(int, void *);  // 0x129650
    bool __cdecl donateGuildCraftNormalMaterialOk(void);  // 0x1298e0
    bool __cdecl donateGuildCraftNormalMaterialFail(void *);  // 0x129fc0
};

class DonateGuildUniformTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121310
private:
    virtual bool __cdecl work(int, void *);  // 0x12cd90
    bool __cdecl init(int, void *);  // 0x12cdf0
    bool __cdecl donateGuildUniformOk(void);  // 0x12d030
    bool __cdecl donateGuildUniformFail(void *);  // 0x12d750
};

class IncreaseUniformRegistrationQuotaTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121360
private:
    virtual bool __cdecl work(int, void *);  // 0x1300b0
    bool __cdecl init(int, void *);  // 0x130110
    bool __cdecl increaseUniformRegistrationQuotaOk(void);  // 0x130310
    bool __cdecl increaseUniformRegistrationQuotaFail(void *);  // 0x130880
};

class MakeGuildCraftTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1212c0
    __cdecl MakeGuildCraftTran(::User *);  // 0x1285d0
private:
    virtual bool __cdecl work(int, void *);  // 0x1286a0
    bool __cdecl init(int, void *);  // 0x128720
    bool __cdecl tryMakeGuildCraft(void);  // 0x128a80
    bool __cdecl makeGuildCraftOk(void *);  // 0x128c80
    bool __cdecl makeGuildCraftFail(short);  // 0x1292e0
};

class MakeGuildUniformTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121320
private:
    virtual bool __cdecl work(int, void *);  // 0x12db80
    bool __cdecl init(int, void *);  // 0x12dc00
    bool __cdecl tryMakeGuildUniform(void);  // 0x12deb0
    bool __cdecl makeGuildUniformOk(void *);  // 0x12e050
    bool __cdecl makeGuildUniformFail(short);  // 0x12e330
};

class PutOnGuildUniformTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121340
private:
    virtual bool __cdecl work(int, void *);  // 0x12edc0
    bool __cdecl init(int, void *);  // 0x12ee40
    bool __cdecl tryPutOnGuildUniform(void);  // 0x12f110
    bool __cdecl putOnGuildUniformOk(__int64);  // 0x12f2b0
    bool __cdecl putOnGuildUniformFail(short);  // 0x12f580
};

class RegisterGuildUniformTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121330
private:
    virtual bool __cdecl work(int, void *);  // 0x12e4a0
    bool __cdecl init(int, void *);  // 0x12e520
    bool __cdecl tryRegisterGuildUniform(void);  // 0x12e7d0
    bool __cdecl registerGuildUniformOk(void);  // 0x12e970
    bool __cdecl registerGuildUniformFail(short);  // 0x12ec30
};

class RegisterGuildUniformWithDeletionTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121350
private:
    virtual bool __cdecl work(int, void *);  // 0x12f710
    bool __cdecl init(int, void *);  // 0x12f790
    bool __cdecl tryRegisterGuildUniformWithDeletion(void);  // 0x12fa40
    bool __cdecl registerGuildUniformWithDeletionOk(__int64);  // 0x12fc10
    bool __cdecl registerGuildUniformWithDeletionFail(short);  // 0x12ff10
};

class RenameGuildTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121270
    __cdecl RenameGuildTran(::User *);  // 0x122720
private:
    virtual bool __cdecl work(int, void *);  // 0x122880
    bool __cdecl init(int, void *);  // 0x122960
    bool __cdecl renameGuildTranStart(void);  // 0x122ae0
    bool __cdecl renameGuildTranOkFromLobby(unsigned __int64);  // 0x122bc0
    bool __cdecl renameGuildTranFailFromLobby(short);  // 0x1230c0
    bool __cdecl renameGuildTranOkFromCache(__int64 *);  // 0x123190
    bool __cdecl renameGuildTranFailFromCache(void *);  // 0x123dc0
    bool __cdecl renameGuildTranAbort(short);  // 0x123ed0
};

class TryRegisterGuildTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x121260
    __cdecl TryRegisterGuildTran(::User *);  // 0x1219c0
private:
    virtual bool __cdecl work(int, void *);  // 0x121a70
    bool __cdecl init(int, void *);  // 0x121b50
    bool __cdecl tryRegisterGuild(void);  // 0x121c80
    bool __cdecl registerGuildNameOk(unsigned __int64);  // 0x121d60
    bool __cdecl registerGuildNameFail(short);  // 0x121fe0
    bool __cdecl registerGuildOkFromCache(void *);  // 0x122120
    bool __cdecl registerGuildFailFromCache(short);  // 0x1224a0
    bool __cdecl abort(short);  // 0x122660
};

class UpdateGuildLevelTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1212f0
private:
    virtual bool __cdecl work(int, void *);  // 0x12b230
    bool __cdecl init(int, void *);  // 0x12b2b0
    bool __cdecl tryUpdateGuildLevel(void);  // 0x12b4b0
    bool __cdecl updateGuildLevelOk(void);  // 0x12b750
    bool __cdecl updateGuildLevelFail(short);  // 0x12b950
};

