// MembershipMileage.obj (LobbyDaemon PDB, 2019 + PDB).
#pragma once

#include "Mileage.h"
#include "GradeService.h"

class MembershipMileage : public Mileage
{
public:
    // LIFT: inline in MileageManager::Initialize (0x5f5a0).
    explicit MembershipMileage(int slotId)
        : Mileage(slotId), _mileageGameGradeKey(0), _baseGameGradeKey(0), _boostGameGradeKey(0) {}
    virtual void Accept(LobbyMessage*);  // 0x5bff0
    virtual bool Initialize(MileageConfig const&, long long);  // 0x5c040
    virtual bool Start(CliSession*, long long);  // 0x5c300
    virtual bool Stop(CliSession*, long long, long long*);  // 0x5c6c0
    bool GradeChanged(CliSession*, long long, int, GradeService::GradeChangedReasonType, Grade*);  // 0x5ca20

private:
    int _mileageGameGradeKey;
    int _baseGameGradeKey;
    int _boostGameGradeKey;
};
static_assert(sizeof(MembershipMileage) == 0x1378, "sizeof MembershipMileage");

class MembershipMileageSession : public MileageSession
{
public:
    enum SectionType
    {
        SECTIONTYPE_INVALID = -1,
        SECTIONTYPE_BASE = 0,
        SECTIONTYPE_MILEAGE = 1,
        SECTIONTYPE_BOOST = 2,
        SECTIONTYPE_MAX = 3,
    };

    // LIFT: Inlined in MembershipMileage::Start at 0x5c300.
    MembershipMileageSession(Mileage* owner, long long at) : MileageSession(owner, at) {}

private:
    // LIFT: Start and GradeChanged call the private members at 0x5c300 and 0x5ca20.
    friend class MembershipMileage;
    void start(SectionType, Grade const*, long long, unsigned long long);  // 0x5cca0
    void update(SectionType, Grade const*, long long, unsigned long long);  // 0x5ce40
    void stop(SectionType, long long, unsigned long long);  // 0x5cfd0

    std::vector<Section<long long>, StlAllocator<Section<long long>, 2> > _sections[SECTIONTYPE_MAX];
};
static_assert(sizeof(MembershipMileageSession) == 0x88, "sizeof MembershipMileageSession");
