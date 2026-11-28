// guilduniform.cpp: guilduniform.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "guilduniform.h"
#include "LiftStub.h"

// 0x130c50
::NamingRule::CheckNameResult __cdecl NamingRule::CheckName(::GameLocaleSet const &, wchar_t const *, int, int, int, bool, bool, bool, wchar_t const *)
{
    LIFT_STUB(0x130c50);
}

// 0x130fd0
__cdecl GuildUniform::GuildUniform(void)
{
    LIFT_STUB(0x130fd0);
}

// 0x1310b0
void __cdecl GuildUniform::Initialize(unsigned __int64, wchar_t const *, __int64, char const *const, char const *const, int const *const, short, ::GuildUniform::Material const *const)
{
    LIFT_STUB(0x1310b0);
}

// 0x131260
bool __cdecl GuildUniform::InitializeFromDBData(::GuildUniformInfo const *)
{
    LIFT_STUB(0x131260);
}

// 0x131560
bool __cdecl GuildUniform::fetchUniformInfo(::FragmentPacket &)
{
    LIFT_STUB(0x131560);
}

// 0x131610
bool __cdecl GuildUniform::fetchUniformParams(::FragmentPacket &)
{
    LIFT_STUB(0x131610);
}

// 0x131920
bool __cdecl GuildUniform::fetchUniformMaterials(::FragmentPacket &)
{
    LIFT_STUB(0x131920);
}

// 0x131aa0
bool __cdecl GuildUniform::FetchGuildUniformInfo(::FragmentPacket &)
{
    LIFT_STUB(0x131aa0);
}

// 0x131b30
short __cdecl GuildUniform::EnableDonation(unsigned int, short, int, short &)
{
    LIFT_STUB(0x131b30);
}

// 0x131ca0
short __cdecl GuildUniform::TryAbandonGuildUniform(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x131ca0);
}

// 0x131db0
#pragma comment(linker, "/INCLUDE:?EnableRegisterGuildUniform@GuildUniform@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl GuildUniform::EnableRegisterGuildUniform(void)
{
    AcquireSRWLockShared(&_srwLock);
    bool const enable = _state == GUILDUNIFORMSTATE_MAKED;
    ReleaseSRWLockShared(&_srwLock);
    return enable;
}

// 0x131e00
unsigned __int64 __cdecl GuildUniform::AddDonationMaterial(unsigned int, short, int)
{
    LIFT_STUB(0x131e00);
}

// 0x131eb0
__cdecl GuildUniformManager::~GuildUniformManager(void)
{
    LIFT_STUB(0x131eb0);
}

// 0x131ff0
bool __cdecl GuildUniformManager::InitializeFromDBData(short, ::GuildUniformInfo *const)
{
    LIFT_STUB(0x131ff0);
}

// 0x132190
::Pointer2< ::GuildUniform> __cdecl GuildUniformManager::AcquireGuildUniform(unsigned __int64)
{
    LIFT_STUB(0x132190);
}

// 0x132340
bool __cdecl GuildUniformManager::AddGuildUniform(::GuildUniform *)
{
    LIFT_STUB(0x132340);
}

// 0x1323c0
bool __cdecl GuildUniformManager::DelGuildUniform(unsigned __int64)
{
    LIFT_STUB(0x1323c0);
}

// 0x1324a0
#pragma comment(linker, "/INCLUDE:?GetRegisteredUniformCount@GuildUniformManager@@QEAAHXZ")  // LIFT: dead-strip keep (no live caller yet)
int __cdecl GuildUniformManager::GetRegisteredUniformCount(void)
{
    char count = 0;
    AcquireSRWLockExclusive(&_srwLock);
    for (char i = 0; i < _uniformTotalCount; ++i)
    {
        if (_uniformList[i] != NULL && _uniformList[i]->_state == GUILDUNIFORMSTATE_REGISTERED)
            ++count;
    }
    ReleaseSRWLockExclusive(&_srwLock);
    return count;
}

// 0x132500
bool __cdecl GuildUniformManager::FetchGuildUniformList(::FragmentPacket &)
{
    LIFT_STUB(0x132500);
}
