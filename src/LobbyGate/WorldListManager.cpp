// WorldListManager.obj (LobbyGate PDB).
#include "WorldListManager.h"
#include <new>
#include "LobbyGate.h"
#include "Log.h"
#include "Memory.h"

#define WORLDLIST_FILE L"WorldListManager.cpp"

// 0x16200 (scalar deleting destructor)
WorldList::~WorldList()
{
    if (_worldInfos != nullptr)
    {
        Memory::_Manager[2]->Free(const_cast<WorldInfo*>(_worldInfos), WORLDLIST_FILE, 30);
        _worldInfos = nullptr;
        _worldCount = 0;
    }
    // The FragmentPacket member clears its packet.
}

// 0x16280
bool WorldList::Set(WorldInfo const* infos, int count)
{
    if (count < 0)
    {
        Log::Write(Log::LT_ERROR, WORLDLIST_FILE, 41, L"[world-list], set fail; invalid parameter");
        return false;
    }
    _worldInfos = infos;
    _worldCount = count;
    _fp.packet.Allocate(&_fp.composer);
    Packet::Header* header = _fp.packet.CurHeader;
    if (header == nullptr || static_cast<unsigned short>(4000 - header->size) < 2)
        _fp.packet.Allocate(&_fp.composer);
    _fp.composer.PushRepeatCount(&_fp.packet);

    for (int i = 0; i < _worldCount; ++i)
    {
        header = _fp.packet.CurHeader;
        if (header == nullptr || static_cast<unsigned short>(4000 - header->size) < 0x3D)
            _fp.packet.Allocate(&_fp.composer);
        WorldInfo const* info = &_worldInfos[i];
        if (_fp.Compose(15, static_cast<int>(info->worldId), static_cast<int>(info->worldClusterId), info->worldName,
                        static_cast<int>(info->worldType), static_cast<int>(info->playType), info->publicAddress,
                        static_cast<int>(info->publicPort), info->worldScore, static_cast<int>(info->worldLive),
                        static_cast<int>(info->entrance), static_cast<int>(info->characterCreation),
                        static_cast<int>(info->characterCreationLimitedOnNewAccount),
                        static_cast<int>(info->recommend), static_cast<int>(info->brandnew),
                        static_cast<int>(info->crowdness)) == 0)
            return false;
        // Inlined FragmentPacket::IncRepeatCount (0x3840).
        int next = _fp.composer.start[_fp.composer.top] + 1;
        if (_fp.composer.subTop < 0)
            _fp.composer.index = next;
        else
            _fp.composer.sub[_fp.composer.subTop].index = next;
        ++*_fp.composer.counts[_fp.composer.top];
    }
    _fp.composer.PopRepeatCount();
    _fp.packet.Finalize(LobbyGate::_instance->_broadcastCrypt.crypt);
    return true;
}

// 0x16530
bool WorldListManager::SetWorldList(WorldInfo const* worldList, int worldCount)
{
    if (worldCount < 0)
    {
        Log::Write(Log::LT_ERROR, WORLDLIST_FILE, 204,
                   L"[WorldListManger], SetWorldList fail; invalid parameter, world-count:%d", worldCount);
        return false;
    }
    // ❓ The Alloc call has no line argument in the pseudocode.
    void* mem = Memory::_Manager[2]->Alloc(sizeof(WorldList), WORLDLIST_FILE, 0);
    WorldList* list = mem != nullptr ? new (mem) WorldList() : nullptr;
    // BUG: 0x16530 calls Set on a null list when Alloc fails.
    if (!list->Set(worldList, worldCount))
    {
        Log::Write(Log::LT_ERROR, WORLDLIST_FILE, 211, L"[worldListManager], SetWorldList fail; set world infos fail");
        list->removeReferenceCount(WORLDLIST_FILE, 212);
        return false;
    }
    AcquireSRWLockExclusive(&_srwLock);
    WorldList* old = _worldList;
    _worldList = list;
    ReleaseSRWLockExclusive(&_srwLock);
    if (old != nullptr)
        old->removeReferenceCount(WORLDLIST_FILE, 222);
    return true;
}
