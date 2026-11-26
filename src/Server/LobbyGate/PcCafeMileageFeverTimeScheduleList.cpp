// PcCafeMileageFeverTimeScheduleList.obj (LobbyGate PDB).
// DynamicRefCntObj::~DynamicRefCntObj (0x15df0) and its scalar deleting destructor (0x15e00) are COMDAT copies.
// The body is in src/common/RefCntObject.cpp.
#include "PcCafeMileageFeverTimeScheduleList.h"
#include <new>
#include "LobbyGate.h"
#include "Log.h"
#include "Memory.h"

#define SCHEDULE_FILE L"PcCafeMileageFeverTimeScheduleList.cpp"

// 0x15e30 (scalar deleting destructor). The FragmentPacket member clears its packet.
PcCafeMileageFeverTimeScheduleList::~PcCafeMileageFeverTimeScheduleList()
{
}

// 0x15e80
bool PcCafeMileageFeverTimeScheduleList::Set(bool enablePcCafeMileage, bool enablePcCafeMileageDeposit,
                                             long long seasonExpireTime,
                                             PcCafeMileageFeverTimeScheduleInfo const* infos, int count)
{
    if (count < 0)
    {
        Log::Write(Log::LT_ERROR, SCHEDULE_FILE, 29, L"[schedule-list], set fail; invalid parameter");
        return false;
    }
    _fp.packet.Allocate(&_fp.composer);
    if (_fp.Compose(3, static_cast<int>(enablePcCafeMileage), static_cast<int>(enablePcCafeMileageDeposit),
                    seasonExpireTime) == 0)
        return false;

    Packet::Header* header = _fp.packet.CurHeader;
    if (header == nullptr || static_cast<unsigned short>(4000 - header->size) < 2)
        _fp.packet.Allocate(&_fp.composer);
    _fp.composer.PushRepeatCount(&_fp.packet);

    for (long long i = 0; i < count; ++i)
    {
        header = _fp.packet.CurHeader;
        if (header == nullptr || static_cast<unsigned short>(4000 - header->size) < 0x1E)
            _fp.packet.Allocate(&_fp.composer);
        PcCafeMileageFeverTimeScheduleInfo const* info = &infos[i];
        if (_fp.Compose(7, info->startTime, info->endTime, info->feverPoints, static_cast<int>(info->repeatType),
                        info->repeatStartTime, info->repeatDuration, static_cast<int>(info->daysOfWeek)) == 0)
            return false;
        // Inlined FragmentPacket::IncRepeatCount (0x3840).
        long long subTop = _fp.composer.subTop;  // 0x15fe2: subTop is read before start[top].
        int next = _fp.composer.start[_fp.composer.top] + 1;
        if (subTop >= 0)  // 0x15ff2: the sub[] store is the fall-through block.
            _fp.composer.sub[subTop].index = next;
        else
            _fp.composer.index = next;
        ++*_fp.composer.counts[_fp.composer.top];
    }
    _fp.composer.PopRepeatCount();
    _fp.packet.Finalize(LobbyGate::_instance->_broadcastCrypt.crypt);
    return true;
}

// 0x16080
bool PcCafeMileageFeverTimeScheduleListManager::SetPcCafeMileageFeverTimeScheduleList(
    bool enablePcCafeMileage, bool enablePcCafeMileageDeposit, long long seasonExpireTime,
    PcCafeMileageFeverTimeScheduleInfo const* scheduleList, int scheduleCount)
{
    if (scheduleCount < 0)
    {
        Log::Write(Log::LT_ERROR, SCHEDULE_FILE, 111,
                   L"[PcCafeMileageFeverTimeScheduleListManger], SetPcCafeMileageFeverTimeScheduleList fail; invalid "
                   L"parameter, schedule-count:%d",
                   scheduleCount);
        return false;
    }
    void* mem = Memory::_Manager[2]->Alloc(sizeof(PcCafeMileageFeverTimeScheduleList), SCHEDULE_FILE, 116);
    PcCafeMileageFeverTimeScheduleList* list = mem != nullptr ? new (mem) PcCafeMileageFeverTimeScheduleList() : nullptr;
    // BUG: 0x16080 calls Set on a null list when Alloc fails.
    if (!list->Set(enablePcCafeMileage, enablePcCafeMileageDeposit, seasonExpireTime, scheduleList, scheduleCount))
    {
        Log::Write(Log::LT_ERROR, SCHEDULE_FILE, 118,
                   L"[scheduleListManager], SetPcCafeMileageFeverTimeScheduleList fail; set schedule infos fail");
        list->removeReferenceCount(SCHEDULE_FILE, 119);
        return false;
    }
    AcquireSRWLockExclusive(&_srwLock);
    PcCafeMileageFeverTimeScheduleList* old = _scheduleList;
    _scheduleList = list;
    ReleaseSRWLockExclusive(&_srwLock);
    if (old != nullptr)
        old->removeReferenceCount(SCHEDULE_FILE, 129);
    return true;
}
