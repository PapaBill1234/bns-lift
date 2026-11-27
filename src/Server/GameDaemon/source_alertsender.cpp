// source_alertsender.cpp: alertsender.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameDaemonFwd.h"
#include "LiftStub.h"

// 0x686920
// LIFT: file-local function (no public name). A /INCLUDE pragma cannot keep it. It pairs when a lifted
// caller in this file (AlertSender::fini, AlertSender::run) calls it.
static void destroy(AlertBufferList& list)
{
    AlertBuffer* head = list._head;
    while (head != nullptr)
    {
        AlertBuffer* buffer = head;
        head = head->_next;
        Memory::_Manager[2]->Free(buffer, L"source\\AlertSender.cpp", 95);
    }
    list._head = nullptr;
    list._tail = nullptr;
    list._count = 0;
}
