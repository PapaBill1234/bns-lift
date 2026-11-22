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

// LIFT: The grade checks are inlined at the three start sites in 0x5c300.
static __forceinline bool isActiveGrade(Grade const* grade, long long at)
{
    return grade != nullptr && grade->_gameGradeKey > 0 && grade->_gradeId > 0 &&
        grade->_gradeCount > 0 && grade->_activation && grade->_effectiveTo >= at;
}

#pragma comment(linker, "/INCLUDE:?Start@MembershipMileage@@UEAA_NPEAVCliSession@@_J@Z")  // LIFT: keep until the caller is lifted (0x5c300)
bool MembershipMileage::Start(CliSession* cs, long long at)
{
    if (cs == nullptr)
    {
        wchar_t const* format = L"== CRASH == [membership-mileage], start fail; invalid parameter, mileage-id:%d, cli-key:0x%I64X, cli-state:%d.%d";
        Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 103, format, _config.mileage.id, 0ULL, 0, 0);
        AlertSender::Write(L"MembershipMileage.cpp", 103, format, _config.mileage.id, 0ULL, 0, 0);
        return false;
    }
    MileageSlot* slot = cs->_mileageSlot;
    if (slot == nullptr)
    {
        wchar_t const* format = L"== CRASH == [membership-mileage], start fail; slot not exists, mileage-id:%d, cli-key:0x%I64X, cli-state:%d.%d";
        Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 110, format,
            _config.mileage.id, cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
        AlertSender::Write(L"MembershipMileage.cpp", 110, format,
            _config.mileage.id, cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
        return false;
    }
    // BUG: The original starts a session with no valid slot, which leaks it. Reject the slot before allocation (0x5c300).
    if (_slotId < 0 || _slotId >= slot->_size || slot->_sessions == nullptr)
        return false;
    MileageSession* existing = slot->_sessions[_slotId];
    if (existing != nullptr)
    {
        wchar_t const* format = L"== CRASH == [membership-mileage], start fail; session already exists, mileage-id:%d, session:%p, cli-key:0x%I64X, cli-state:%d.%d";
        Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 119, format,
            _config.mileage.id, existing, cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
        AlertSender::Write(L"MembershipMileage.cpp", 119, format,
            _config.mileage.id, existing, cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
        return false;
    }

    void* memory = Memory::_Manager[Memory::DYNAMIC]->Alloc(sizeof(MembershipMileageSession), L"MembershipMileage.cpp", 124);
    // BUG: The original can call start on a null session. Stop when allocation fails (0x5c300).
    if (memory == nullptr)
        return false;
    MembershipMileageSession* session = ::new (memory) MembershipMileageSession(this, at);
    if (_baseGameGradeKey > 0)
    {
        Grade const* grade = cs->_gradeService.GetGrade(_baseGameGradeKey);
        if (isActiveGrade(grade, at))
            session->start(MembershipMileageSession::SECTIONTYPE_BASE, grade, at, cs->_clikey);
    }
    Grade const* grade = cs->_gradeService.GetGrade(_mileageGameGradeKey);
    if (isActiveGrade(grade, at))
        session->start(MembershipMileageSession::SECTIONTYPE_MILEAGE, grade, at, cs->_clikey);
    if (_boostGameGradeKey > 0)
    {
        grade = cs->_gradeService.GetGrade(_boostGameGradeKey);
        if (isActiveGrade(grade, at))
            session->start(MembershipMileageSession::SECTIONTYPE_BOOST, grade, at, cs->_clikey);
    }
    slot->_sessions[_slotId] = session;
    Log::Write(Log::LT_DEBUG, L"MembershipMileage.cpp", 148,
        L"[membership-mileage], start ok, mileage-id:%d, cli-key:0x%I64X, cli-state:%d.%d",
        _config.mileage.id, cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
    return true;
}

// 0x5c6c0
bool MembershipMileage::Stop(CliSession*, long long, long long*)
{
    LIFT_STUB(0x5c6c0);
}

#pragma comment(linker, "/INCLUDE:?GradeChanged@MembershipMileage@@QEAA_NPEAVCliSession@@_JHW4GradeChangedReasonType@GradeService@@PEAVGrade@@@Z")  // LIFT: keep until the caller is lifted (0x5ca20)
bool MembershipMileage::GradeChanged(CliSession* cs, long long at, int gameGradeKey,
    GradeService::GradeChangedReasonType reason, Grade* changedGrade)
{
    if (cs == nullptr || gameGradeKey <= 0 ||
        static_cast<unsigned int>(reason) - 1 > GradeService::GRADECHANGEDREASONTYPE_DELETED)
    {
        wchar_t const* format = L"== CRASH == [membership-mileage], change grade fail, mileage-id:%d, game-grade-key:%d, reason:%d, cli-key:0x%I64X, cli-state:%d.%d";
        int state = cs != nullptr ? cs->_state : 0;
        Log::Write(Log::LT_ERROR, L"MembershipMileage.cpp", 247, format, _config.mileage.id,
            gameGradeKey, reason, cs != nullptr ? cs->_clikey : 0ULL, HIWORD(state), LOWORD(state));
        state = cs != nullptr ? cs->_state : 0;
        AlertSender::Write(L"MembershipMileage.cpp", 247, format, _config.mileage.id,
            gameGradeKey, reason, cs != nullptr ? cs->_clikey : 0ULL, HIWORD(state), LOWORD(state));
        return false;
    }
    MileageSlot* slot = cs->_mileageSlot;
    if (slot == nullptr || _slotId < 0 || _slotId >= slot->_size)
        return false;
    // BUG: AllocZero can leave the session array null. Check it before use (0x5ca20).
    if (slot->_sessions == nullptr)
        return false;
    MembershipMileageSession* session = static_cast<MembershipMileageSession*>(slot->_sessions[_slotId]);
    if (session == nullptr)
        return false;

    MembershipMileageSession::SectionType type = MembershipMileageSession::SECTIONTYPE_BASE;
    if (gameGradeKey == _mileageGameGradeKey)
        type = MembershipMileageSession::SECTIONTYPE_MILEAGE;
    else if (gameGradeKey != _baseGameGradeKey)
    {
        if (gameGradeKey != _boostGameGradeKey)
            return false;
        type = MembershipMileageSession::SECTIONTYPE_BOOST;
    }
    if (reason == GradeService::GRADECHANGEDREASONTYPE_DELETED_AND_EXAUSTED)
    {
        session->stop(type, at, cs->_clikey);
    }
    else if (reason > GradeService::GRADECHANGEDREASONTYPE_ACTIVATED_WITH_ADDING)
    {
        if (changedGrade != nullptr && changedGrade->_activation)
            session->update(type, changedGrade, at, cs->_clikey);
    }
    else if (changedGrade != nullptr)
    {
        session->start(type, changedGrade, at, cs->_clikey);
    }
    Log::Write(Log::LT_DEBUG, L"MembershipMileage.cpp", 295,
        L"[membership-mileage], change grade ok, mileage-id:%d, game-grade-key:%d, reason:%d, cli-key:0x%I64X, cli-state:%d.%d",
        _config.mileage.id, gameGradeKey, reason, cs->_clikey, HIWORD(cs->_state), LOWORD(cs->_state));
    return true;
}

// 0x5cca0
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

// 0x5ce40
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

// 0x5cfd0
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
