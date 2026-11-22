// MembershipMileage.obj (LobbyDaemon PDB, 2019 + PDB).
#include "PlacementNew.h"
#define LIFT_STLMEMORY_FILE \
    L"E:\\DailyBuild02\\LobbyDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\StlMemory.h"
#include "MembershipMileage.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyMessage.h"
#include "Log.h"
#include "Memory.h"
#include <wchar.h>

#pragma comment(linker, "/INCLUDE:?Accept@MembershipMileage@@UEAAXPEAVLobbyMessage@@@Z")  // LIFT: keep until the caller is lifted (0x5bff0)
void MembershipMileage::Accept(LobbyMessage* message)
{
    if (message != nullptr)
        message->Dispatch(this);
}

#pragma comment(linker, "/INCLUDE:?Initialize@MembershipMileage@@UEAA_NAEBVMileageConfig@@_J@Z")  // LIFT: keep until the caller is lifted (0x5c040)
bool MembershipMileage::Initialize(MileageConfig const& config, long long scheduleTo)
{
    if (!Mileage::Initialize(config, scheduleTo))
        return false;

    char mileageType = config.policy.mileageType;
    if (mileageType != 2 || config.policyConditions == nullptr || config.policyConditionCount <= 0)
    {
        wchar_t const* format = L"== CRASH == [membership-mileage], initialize fail; invalid parameter, policy-id:%d, mileage-type:%d, policy-condition-count:%d";
        Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 37, format, config.policy.id, mileageType, config.policyConditionCount);
        AlertSender::Write(L"MembershipMileage.cpp", 37, format,
            config.policy.id, config.policy.mileageType, config.policyConditionCount);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }

    for (int i = 0; i < config.policyConditionCount; ++i)
    {
        MileagePolicyCondition const* condition = config.policyConditions[i];
        long key;
        int line;
        wchar_t const* format;
        switch (condition->type)
        {
        case 1:
            key = wcstol(condition->value, nullptr, 0);
            _mileageGameGradeKey = key;
            format = L"[membership-mileage], set mileage game-grade-key, mileage-id:%d, policy-id:%d, game-grade-key:%d";
            line = 56;
            break;
        case 2:
            key = wcstol(condition->value, nullptr, 0);
            _baseGameGradeKey = key;
            format = L"[membership-mileage], set base game-grade-key, mileage-id:%d, policy-id:%d, game-grade-key:%d";
            line = 50;
            break;
        case 3:
            key = wcstol(condition->value, nullptr, 0);
            _boostGameGradeKey = key;
            format = L"[membership-mileage], set boost game-grade-key, mileage-id:%d, policy-id:%d, game-grade-key:%d";
            line = 62;
            break;
        default:
            Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 66,
                L"[membership-mileage], initialize exception; unknown condition type, policy-id:%d, condition-type:%d",
                config.policy.id, condition->type);
            continue;
        }
        Log::Write(Log::LT_DEBUG, L"MembershipMileage.cpp", line, format, config.mileage.id, config.policy.id, key);
    }
    if (_mileageGameGradeKey <= 0)
    {
        Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 74,
            L"[membership-mileage], initialize fail; game-grade-key for mileage not exists, policy-id:%d", config.policy.id);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    if (_mileageGameGradeKey != _baseGameGradeKey && _mileageGameGradeKey != _boostGameGradeKey &&
        (_baseGameGradeKey == 0 || _baseGameGradeKey != _boostGameGradeKey))
    {
        Log::Write(Log::LT_DEBUG, L"MembershipMileage.cpp", 94,
            L"[membership-mileage], initialize ok, mileage-id:%d, policy-id:%d", config.mileage.id, config.policy.id);
        return true;
    }
    Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 87,
        L"[membership-mileage], initialize fail; game-grade-keys overlap, base:%d, mileage:%d, boost:%d, mileage-id:%d, policy-id:%d",
        _baseGameGradeKey, _mileageGameGradeKey, _boostGameGradeKey, config.mileage.id, config.policy.id);
    TLobbyError = LOBERR_INVALID_PARAMETER;
    return false;
}

// 0x5c300
bool MembershipMileage::Start(CliSession*, long long)
{
    LIFT_STUB(0x5c300);
}

// 0x5c6c0
bool MembershipMileage::Stop(CliSession*, long long, long long*)
{
    LIFT_STUB(0x5c6c0);
}

// 0x5ca20
bool MembershipMileage::GradeChanged(CliSession*, long long, int, GradeService::GradeChangedReasonType, Grade*)
{
    LIFT_STUB(0x5ca20);
}

#pragma comment(linker, "/INCLUDE:?start@MembershipMileageSession@@AEAAXW4SectionType@1@PEBVGrade@@_J_K@Z")  // LIFT: keep until the caller is lifted (0x5cca0)
void MembershipMileageSession::start(SectionType type, Grade const* grade, long long at, unsigned long long clikey)
{
    if (static_cast<unsigned int>(type) <= SECTIONTYPE_BOOST && grade != nullptr)
    {
        Section<long long> section;
        section.start = at;
        section.end = grade->_effectiveTo;
        _sections[type].push_back(section);
        Log::Write(Log::LT_DEBUG, L"MembershipMileage.cpp", 331,
            L"[membership-mileage], session started, mileage-id:%d, type:%d, at:%I64d, cli-key:0x%I64X",
            _owner->_config.mileage.id, type, at, clikey);
    }
    else
    {
        wchar_t const* format = L"== CRASH == [membership-mileage], start session fail; invalid parameter, mileage-id:%d, type:%d, grade:%p, at:%I64d, cli-key:0x%I64X";
        Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 319, format,
            _owner->_config.mileage.id, type, grade, at, clikey);
        AlertSender::Write(L"MembershipMileage.cpp", 319, format,
            _owner->_config.mileage.id, type, grade, at, clikey);
    }
}

#pragma comment(linker, "/INCLUDE:?update@MembershipMileageSession@@AEAAXW4SectionType@1@PEBVGrade@@_J_K@Z")  // LIFT: keep until the caller is lifted (0x5ce40)
void MembershipMileageSession::update(SectionType type, Grade const* grade, long long at, unsigned long long clikey)
{
    if (static_cast<unsigned int>(type) <= SECTIONTYPE_BOOST && grade != nullptr)
    {
        long long end = grade->_effectiveTo;
        if (!_sections[type].empty())
        {
            Section<long long>& section = _sections[type].back();
            section.end = end;
            Log::Write(Log::LT_DEBUG, L"MembershipMileage.cpp", 361,
                L"[membership-mileage], update session ok, mileage-id:%d, type:%d, grade:%p, at:%I64d, start:%I64d, end:%I64d, cli-key:0x%I64X",
                _owner->_config.mileage.id, type, grade, at, section.start, end, clikey);
            return;
        }
        wchar_t const* format = L"== CRASH == [membership-mileage], update session fail; section not exists, mileage-id:%d, type:%d, grade:%p, at:%I64d, cli-key:0x%I64X";
        Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 348, format, _owner->_config.mileage.id, type, grade, at, clikey);
        AlertSender::Write(L"MembershipMileage.cpp", 348, format, _owner->_config.mileage.id, type, grade, at, clikey);
        return;
    }
    wchar_t const* format = L"== CRASH == [membership-mileage], update session fail; invalid parameter, mileage-id:%d, type:%d, grade:%p, at:%I64d, cli-key:0x%I64X";
    Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 339, format, _owner->_config.mileage.id, type, grade, at, clikey);
    AlertSender::Write(L"MembershipMileage.cpp", 339, format, _owner->_config.mileage.id, type, grade, at, clikey);
}

#pragma comment(linker, "/INCLUDE:?stop@MembershipMileageSession@@AEAAXW4SectionType@1@_J_K@Z")  // LIFT: keep until the caller is lifted (0x5cfd0)
void MembershipMileageSession::stop(SectionType type, long long at, unsigned long long clikey)
{
    if (static_cast<unsigned int>(type) <= SECTIONTYPE_BOOST)
    {
        if (!_sections[type].empty())
        {
            long long end = _sections[type].back().end;
            if (end > at)
                end = at;
            _sections[type].back().end = end;
            Log::Write(Log::LT_DEBUG, L"MembershipMileage.cpp", 386,
                L"[membership-mileage], stop session ok, mileage-id:%d, type:%d, at:%I64d, cli-key:0x%I64X",
                _owner->_config.mileage.id, type, at, clikey);
        }
        return;
    }
    wchar_t const* format = L"== CRASH == [membership-mileage], stop session fail; invalid parameter, mileage-id:%d, type:%d, at:%I64d, cli-key:0x%I64X";
    Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 369, format, _owner->_config.mileage.id, type, at, clikey);
    AlertSender::Write(L"MembershipMileage.cpp", 369, format, _owner->_config.mileage.id, type, at, clikey);
}

#pragma comment(linker, "/INCLUDE:??$Intersect@_JVvector@std@@V?$StlAllocator@U?$Section@_J@@$01@@@?$Section@_J@@SAXAEBV?$vector@U?$Section@_J@@V?$StlAllocator@U?$Section@_J@@$01@@@std@@0AEAV12@@Z")  // LIFT: keep until the caller is lifted (0x5d240)
template<class T>
template<class U, template<class, class> class Container, class Allocator>
void Section<T>::Intersect(Container<Section<U>, Allocator> const& first,
    Container<Section<U>, Allocator> const& second, Container<Section<U>, Allocator>& out)
{
    typename Container<Section<U>, Allocator>::const_iterator a = first.begin();
    typename Container<Section<U>, Allocator>::const_iterator const firstEnd = first.end();
    typename Container<Section<U>, Allocator>::const_iterator b = second.begin();
    typename Container<Section<U>, Allocator>::const_iterator const secondEnd = second.end();
    for (; a != firstEnd; )
    {
        if (b == secondEnd)
            break;
        if (a->end > b->start && b->end > a->start)
        {
            Section<U> section;
            section.start = a->start > b->start ? a->start : b->start;
            section.end = a->end < b->end ? a->end : b->end;
            out.push_back(section);
        }
        if (a->end < b->end)
            ++a;
        else
            ++b;
    }
}

template void Section<long long>::Intersect<long long, std::vector, StlAllocator<Section<long long>, 2> >(
    std::vector<Section<long long>, StlAllocator<Section<long long>, 2> > const&,
    std::vector<Section<long long>, StlAllocator<Section<long long>, 2> > const&,
    std::vector<Section<long long>, StlAllocator<Section<long long>, 2> >&);
