// PcCafeMileageFeverTimeScheduleList.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>
#include <windows.h>
#include "RefCntObject.h"
#include "FragmentPacket.h"

struct PcCafeMileageFeverTimeScheduleInfo
{
    long long startTime;
    long long endTime;
    int feverPoints;
    char repeatType;
    int repeatStartTime;
    int repeatDuration;
    char daysOfWeek;
};
static_assert(sizeof(PcCafeMileageFeverTimeScheduleInfo) == 0x28, "sizeof PcCafeMileageFeverTimeScheduleInfo");

class PcCafeMileageFeverTimeScheduleList : public DynamicRefCntObj
{
public:
    // ❓ The constructor is inlined in SetPcCafeMileageFeverTimeScheduleList (0x16080).
    PcCafeMileageFeverTimeScheduleList() : _fp(104, "hiQQqCqqiQiic;") {}
    virtual ~PcCafeMileageFeverTimeScheduleList();  // 0x15e30

    bool Set(bool enablePcCafeMileage, bool enablePcCafeMileageDeposit, long long seasonExpireTime,
             PcCafeMileageFeverTimeScheduleInfo const* infos, int count);  // 0x15e80

    FragmentPacket _fp;
};
static_assert(sizeof(PcCafeMileageFeverTimeScheduleList) == 272, "sizeof PcCafeMileageFeverTimeScheduleList");

class PcCafeMileageFeverTimeScheduleListManager
{
public:
    bool SetPcCafeMileageFeverTimeScheduleList(bool enablePcCafeMileage, bool enablePcCafeMileageDeposit,
                                               long long seasonExpireTime,
                                               PcCafeMileageFeverTimeScheduleInfo const* scheduleList,
                                               int scheduleCount);  // 0x16080

    SRWLOCK _srwLock;
    long long _mileageExpireTime;
    PcCafeMileageFeverTimeScheduleList* _scheduleList;
};
static_assert(sizeof(PcCafeMileageFeverTimeScheduleListManager) == 0x18, "sizeof PcCafeMileageFeverTimeScheduleListManager");
