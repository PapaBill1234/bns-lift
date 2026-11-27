// guildtran_h.cpp: guildtran.h (GameDaemon PDB, 2019 + PDB). The GetDefinition getters are lifted.
// LIFT: the _def data is not lifted yet. The empty GameTranDef of the header stands in for the PDB data.
#include "guildtran.h"
#include "LiftStub.h"

// 0x121260
::GameTranDef const * __cdecl TryRegisterGuildTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121270
::GameTranDef const * __cdecl RenameGuildTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121280
::GameTranDef const * __cdecl DeleteGuildTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121290
::GameTranDef const * __cdecl DepositInGuildBankTranEx::GetDefinition(void) const
{
    return &_def;
}

// 0x1212a0
::GameTranDef const * __cdecl ContractGuildCraftTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1212b0
::GameTranDef const * __cdecl AssentGuildCraftTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1212c0
::GameTranDef const * __cdecl MakeGuildCraftTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1212d0
::GameTranDef const * __cdecl DonateGuildCraftNormalMaterialTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1212e0
::GameTranDef const * __cdecl DonateGuildCraftBrandMaterialTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1212f0
::GameTranDef const * __cdecl UpdateGuildLevelTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121300
::GameTranDef const * __cdecl ContractGuildUniformTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121310
::GameTranDef const * __cdecl DonateGuildUniformTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121320
::GameTranDef const * __cdecl MakeGuildUniformTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121330
::GameTranDef const * __cdecl RegisterGuildUniformTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121340
::GameTranDef const * __cdecl PutOnGuildUniformTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121350
::GameTranDef const * __cdecl RegisterGuildUniformWithDeletionTran::GetDefinition(void) const
{
    return &_def;
}

// 0x121360
::GameTranDef const * __cdecl IncreaseUniformRegistrationQuotaTran::GetDefinition(void) const
{
    return &_def;
}

::GameTranDef TryRegisterGuildTran::_def;
::GameTranDef RenameGuildTran::_def;
::GameTranDef DeleteGuildTran::_def;
::GameTranDef DepositInGuildBankTranEx::_def;
::GameTranDef ContractGuildCraftTran::_def;
::GameTranDef AssentGuildCraftTran::_def;
::GameTranDef MakeGuildCraftTran::_def;
::GameTranDef DonateGuildCraftNormalMaterialTran::_def;
::GameTranDef DonateGuildCraftBrandMaterialTran::_def;
::GameTranDef UpdateGuildLevelTran::_def;
::GameTranDef ContractGuildUniformTran::_def;
::GameTranDef DonateGuildUniformTran::_def;
::GameTranDef MakeGuildUniformTran::_def;
::GameTranDef RegisterGuildUniformTran::_def;
::GameTranDef PutOnGuildUniformTran::_def;
::GameTranDef RegisterGuildUniformWithDeletionTran::_def;
::GameTranDef IncreaseUniformRegistrationQuotaTran::_def;
