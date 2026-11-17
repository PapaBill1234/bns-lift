// IdleWatcher.obj (LobbyGate PDB).
#include "IdleWatcher.h"
#include <windows.h>
#include <string.h>
#include "MemoryManager.h"
#include <new>
#include "Daemon.h"
#include "Log.h"
#include "LogBuffer.h"
#include "Network.h"
#include "Port.h"

static wchar_t const IDLEWATCHER_FILE[] = L"source\\IdleWatcher.cpp";

// 0x6D55C
unsigned char const IdleStateTable::STATE_MASK[4] = {0xC0, 0x30, 0x0C, 0x03};

// 0x30B50. PDB: IdleWatcher::`scalar deleting destructor' (vftable 0x845C8 slot 0).
// The code is folded with Thread's. It only sets the vftable. It does not free memory.
IdleWatcher::~IdleWatcher() {}

// 0x24CC0
wchar_t const* IdleWatcher::Name()
{
    return L"IdleWatcher";
}

// 0x24CD0
IdleStateTable* IdleStateTable::Create(Port* port, int size, long maxIdleTime, bool disconnect)
{
    int allocSize = (size >> 2) + static_cast<int>(sizeof(IdleStateTable));
    if (allocSize > 0x100000)
    {
        Log::Write(Log::LT_ERROR, IDLEWATCHER_FILE, 56, L"[idlewatcher], size is too big. size:%d", size);
        return nullptr;
    }
    void* memory = BaseMemoryManager::_Instance.Alloc(allocSize, IDLEWATCHER_FILE, 60);
    IdleStateTable* table = memory != nullptr ? new (memory) IdleStateTable() : nullptr;
    // BUG: 0x24CD0 no null check after Alloc. The code writes to a null table.
    table->_port = port;
    table->_size = size;
    table->_maxIdleTime = 1000 * maxIdleTime;
    table->_disconnect = disconnect;
    table->_table = reinterpret_cast<unsigned char*>(table + 1);
    memset(table->_table, 0, allocSize - sizeof(IdleStateTable));
    Log::Write(Log::LT_DEBUG, IDLEWATCHER_FILE, 70,
               L"[idlewatcher], idle state table created, port: %d, max count: %d, max idle time: %d",
               port->_id, size, maxIdleTime);
    return table;
}

// 0x24DF0
void IdleStateTable::scan()
{
    unsigned int portId = _port->_id;
    int count = _size >> 2;
    long long now = static_cast<long long>(GetTickCount64()) - Daemon::Instance->StartSystemTick64;
    for (int i = 0; i < count; ++i)
    {
        for (short j = 0; j < 4; ++j)
        {
            int shift = 2 * (3 - j);
            unsigned char state = static_cast<unsigned char>((STATE_MASK[j] & _table[i]) >> shift);
            if (state == 0)
                continue;
            unsigned long long sessionId = (static_cast<unsigned long long>(portId) << 32) | static_cast<unsigned int>(j + 4 * i);
            switch (state)
            {
            case 1:
                _table[i] &= ~STATE_MASK[j];
                _table[i] |= 2 << shift;
                break;
            case 2:
                if (_maxIdleTime + _port->GetSessionLastRecvTime(sessionId) < now)
                {
                    _table[i] &= ~STATE_MASK[j];
                    _table[i] |= 3 << shift;
                }
                break;
            case 3:
            {
                long long lastRecv = _port->GetSessionLastRecvTime(sessionId);
                if (lastRecv + _maxIdleTime < now)
                {
                    _table[i] &= ~STATE_MASK[j];
                    _table[i] |= 0 << shift;
                    if (_disconnect)
                    {
                        Log::Write(Log::LT_ERROR, IDLEWATCHER_FILE, 181,
                                   L"[idlewatcher], close idle session, id: 0x%I64X, last recv: %I64d, current: %I64d",
                                   sessionId, lastRecv, now);
                        Network::CloseSession(sessionId, true);
                    }
                    else
                    {
                        Log::Write(Log::LT_ERROR, IDLEWATCHER_FILE, 186,
                                   L"[idlewatcher], idle session; don't close, id: 0x%I64X, last recv: %I64d, current: %I64d",
                                   sessionId, lastRecv, now);
                    }
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

// 0x24FF0
void IdleWatcher::run()
{
    LogBufferAllocator::Initialize();
    Log::Write(Log::LT_DEBUG, IDLEWATCHER_FILE, 226, L"[idlewatcher], idle watcher start");  // 0x25038, 4 arguments
    HANDLE event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    while (_run)
    {
        if (event != nullptr)
            WaitForSingleObject(event, 5000);
        _lastExecuted = _threadManager->_now;
        if (!_run)
            break;
        for (int i = 0; i < 24; ++i)
        {
            if (_table[i] != nullptr)
                _table[i]->scan();
        }
    }
    if (event != nullptr)
        CloseHandle(event);
}
