// gametran_h.cpp: gametran.h (GameDaemon PDB, 2019 + PDB).
#include "gametran.h"
#include "user.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1GameTran@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?run@GameTran@@MEAA_NHPEAX@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1UserTran@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1SessionTran@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

#define GAMETRAN_H_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\GameTran.h"

namespace
{
// LIFT: PDB User has base Channel and Session has base EventObject. Both have RefCntObject at +0.
// The skeleton User and Session classes have no bases yet, so this view gives the RefCntObject.
inline RefCntObject * AsRefCntObject(void * object)
{
    return static_cast<RefCntObject *>(object);
}
}

// 0x27e10
__cdecl GameTran::~GameTran(void)
{
}

// 0x27e50
bool __cdecl GameTran::run(int op, void * param)
{
    return work(op, param);
}

// 0x27e60
__cdecl UserTran::UserTran(::User *)
{
    LIFT_STUB(0x27e60);
}

// 0x27ef0
__cdecl UserTran::~UserTran(void)
{
    if (_user != nullptr)
        AsRefCntObject(_user)->removeReferenceCount(GAMETRAN_H_FILE, 199);
}

// 0x1105e0
__cdecl SessionTran::SessionTran(::Session *)
{
    LIFT_STUB(0x1105e0);
}

// 0x110670
__cdecl SessionTran::~SessionTran(void)
{
    if (_session != nullptr)
        AsRefCntObject(_session)->removeReferenceCount(GAMETRAN_H_FILE, 169);
}
