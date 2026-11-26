// LobbyConfig.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyConfig.h"
#include "LiftStub.h"
#include "ContentsRuleConfigDefinition.h"
#include "LobbyPredefine.h"
#include "Log.h"
#include "Memory.h"
#include "StringUtil.h"
#include <wchar.h>

// 0x98980
// LIFT: the PDB gives a const this, but the function writes the parsed lists. The const_cast keeps the PDB signature.
bool LobbyConfig::Check() const
{
    LobbyConfig* config = const_cast<LobbyConfig*>(this);

    if (_reservedMinLobbyGateWidRange <= 0 || _reservedMinLobbyGateWidRange > 0x7FFF)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 510,
                   L"[lobby], lobby-gate world id reservation is out of range[1 ~ %d], min:%d, max:%d", 0x7FFF,
                   _reservedMinLobbyGateWidRange, _reservedMaxLobbyGateWidRange);
        return false;
    }
    if (_reservedMinGameWorldWidRange <= 0 || _reservedMinGameWorldWidRange > 0x7FFF)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 515,
                   L"[lobby], game-world world id reservation is out of range[1 ~ %d], min:%d, max:%d", 0x7FFF,
                   _reservedMinGameWorldWidRange, _reservedMaxGameWorldWidRange);
        return false;
    }
    if (_reservedMinInfoGateWidRange <= 0 || _reservedMinInfoGateWidRange > 0x7FFF)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 520,
                   L"[lobby], info-gate world id reservation is out of range[1 ~ %d], min:%d, max:%d", 0x7FFF,
                   _reservedMinInfoGateWidRange, _reservedMaxInfoGateWidRange);
        return false;
    }
    if (_reservedMinLobbyGateWidRange > _reservedMaxLobbyGateWidRange)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 525,
                   L"[lobby], invalid lobby-gate world id range reservation, min:%d, max:%d",
                   _reservedMinLobbyGateWidRange, _reservedMaxLobbyGateWidRange);
        return false;
    }
    if (_reservedMinGameWorldWidRange > _reservedMaxGameWorldWidRange)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 530,
                   L"[lobby], invalid game-world world id range reservation, min:%d, max:%d",
                   _reservedMinGameWorldWidRange, _reservedMaxGameWorldWidRange);
        return false;
    }
    if (_reservedMinInfoGateWidRange > _reservedMaxInfoGateWidRange)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 535,
                   L"[lobby], invalid info-gate world id range reservation, min:%d, max:%d",
                   _reservedMinInfoGateWidRange, _reservedMaxInfoGateWidRange);
        return false;
    }
    if (_allowedCharacterNameLenMin <= 0 || _allowedCharacterNameLenMax > 32 ||
        _allowedCharacterNameLenMax - _allowedCharacterNameLenMin < 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 543,
                   L"[lobby], invalid character name length range, min:%d, max:%d", _allowedCharacterNameLenMin,
                   _allowedCharacterNameLenMax);
        return false;
    }
    if (_allowedGuildNameLenMin <= 0 || _allowedGuildNameLenMax > 32 ||
        _allowedGuildNameLenMax - _allowedGuildNameLenMin < 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 551,
                   L"[lobby], invalid guild name length range, min:%d, max:%d", _allowedGuildNameLenMin,
                   _allowedGuildNameLenMax);
        return false;
    }

    config->_friendMessageRecipientAppIdList = nullptr;
    config->_friendMessageRecipientAppIdCount = 0;
    if (_friendMessageRecipientAppIdListString == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 562,
                   L"[lobby], check config fail; invalid friend message recipient app-id list string");
        return false;
    }
    size_t len = wcslen(_friendMessageRecipientAppIdListString);
    if (len != 0)
    {
        wchar_t* buffer = static_cast<wchar_t*>(
            Memory::_Manager[Memory::DYNAMIC]->AllocZero(sizeof(wchar_t) * (len + 1), L"LobbyConfig.cpp", 569));
        wchar_t seps[] = L";";
        wchar_t* next = nullptr;
        wcscpy_s(buffer, len + 1, _friendMessageRecipientAppIdListString);
        for (wchar_t* token = wcstok_s(buffer, seps, &next); token != nullptr; token = wcstok_s(nullptr, seps, &next))
            ++config->_friendMessageRecipientAppIdCount;

        config->_friendMessageRecipientAppIdList = static_cast<id128*>(Memory::_Manager[Memory::DYNAMIC]->AllocZero(
            sizeof(id128) * _friendMessageRecipientAppIdCount, L"LobbyConfig.cpp", 583));
        next = nullptr;
        wcscpy_s(buffer, len + 1, _friendMessageRecipientAppIdListString);
        int index = 0;
        for (wchar_t* token = wcstok_s(buffer, seps, &next); token != nullptr; token = wcstok_s(nullptr, seps, &next))
        {
            if (!GetId128FromGuidString(token, &_friendMessageRecipientAppIdList[index]))
            {
                Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 595,
                           L"[lobby], check config fail; invalid friend message recipient app-id, index:%d, app-id-string:%s",
                           index, token);
                Memory::_Manager[Memory::DYNAMIC]->Free(buffer, L"LobbyConfig.cpp", 596);
                Memory::_Manager[Memory::DYNAMIC]->Free(_friendMessageRecipientAppIdList, L"LobbyConfig.cpp", 597);
                config->_friendMessageRecipientAppIdList = nullptr;
                return false;
            }
            ++index;
        }
        Memory::_Manager[Memory::DYNAMIC]->Free(buffer, L"LobbyConfig.cpp", 604);
    }

    if (static_cast<unsigned int>(_freePlayType) > FREEPLAYTYPE_F2P)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 612, L"[lobby], check config fail; invalid free-play-type");
        return false;
    }
    if (!_useGrade && _useGradePriorityQueue)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 622,
                   L"[lobby], check config exception; cannot use grade priority queue when not using grade; force to disable");
        config->_useGradePriorityQueue = false;
    }
    if (_useGradeLevel)
    {
        if (!_useGrade)
        {
            Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 630,
                       L"[lobby], check config fail; use-grade-level can be set only when using grade");
            return false;
        }
        if (!(_gradeLevelGroupId > 0 && _gameGradeKeyForGetLevel == 0) &&
            !(_gameGradeKeyForGetLevel > 0 && _gradeLevelGroupId == 0))
        {
            Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 636,
                       L"[lobby], check config fail; either grade-level-group-id or game-grade-key-for-get-level must be properly defined when using grade level");
            return false;
        }
    }
    if (_useGradePriorityQueue && _gradePriorityQueueGameGradeKey <= 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 641,
                   L"[lobby], check config fail; proper grade-priority-queue-game-grade-key must be defined when grade-priority-queue is enabled");
        return false;
    }
    if (_enableGameMileage &&
        (_gameMileageVirtualCurrencyId <= 0 || _gameMileageDepositRequestCode <= 0 ||
         _gameMileageDepositReasonCode <= 0 || _gameMileageEffectiveDurationInDays < 0))
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 654,
                   L"[lobby], check config fail; invalid configuration for game-mileage");
        return false;
    }

    config->_initialUserNamePrefixList = nullptr;
    config->_initialUserNamePrefixCount = 0;
    if (_initialUserNamePrefixString == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 668,
                   L"[lobby], check config fail; initial user-name prefix not configured");
        return false;
    }
    len = wcslen(_initialUserNamePrefixString);
    if (len != 0)
    {
        wchar_t* buffer = static_cast<wchar_t*>(
            Memory::_Manager[Memory::DYNAMIC]->AllocZero(sizeof(wchar_t) * (len + 1), L"LobbyConfig.cpp", 675));
        wchar_t seps[] = L";";
        wchar_t* next = nullptr;
        wcscpy_s(buffer, len + 1, _initialUserNamePrefixString);
        for (wchar_t* token = wcstok_s(buffer, seps, &next); token != nullptr; token = wcstok_s(nullptr, seps, &next))
            ++config->_initialUserNamePrefixCount;

        config->_initialUserNamePrefixList =
            static_cast<InitialUserNamePrefix*>(Memory::_Manager[Memory::DYNAMIC]->AllocZero(
                sizeof(InitialUserNamePrefix) * _initialUserNamePrefixCount, L"LobbyConfig.cpp", 689));
        next = nullptr;
        wcscpy_s(buffer, len + 1, _initialUserNamePrefixString);
        long long index = 0;
        for (wchar_t* token = wcstok_s(buffer, seps, &next); token != nullptr; token = wcstok_s(nullptr, seps, &next))
        {
            _initialUserNamePrefixList[index].len = static_cast<int>(wcslen(token));
            _initialUserNamePrefixList[index].prefix = static_cast<wchar_t*>(Memory::_Manager[Memory::DYNAMIC]->AllocZero(
                sizeof(wchar_t) * (_initialUserNamePrefixList[index].len + 1), L"LobbyConfig.cpp", 700));
            wcscpy_s(_initialUserNamePrefixList[index].prefix, _initialUserNamePrefixList[index].len + 1, token);
            ++index;
        }
        Memory::_Manager[Memory::DYNAMIC]->Free(buffer, L"LobbyConfig.cpp", 709);
    }

    if (_enableRMSInquiry && !_enableContentBan)
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 719,
                   L"[lobby], check config fail; to use RMS Inquiry ContentBan must be enabled");
        return false;
    }
    if (_useGradePriorityQueue && ContentsRuleConfig::GetContentsRuleConfig()->GetUseBotPriorityQueue())
    {
        Log::Write(Log::LT_ERROR, L"LobbyConfig.cpp", 728,
                   L"[lobby], check config fail; cannot use both VIP(Grade) Priority Queue and BOT Priority Queue");
        return false;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyConfig.cpp", 732, L"[lobby], check config ok");
    return true;
}

// 0x990f0
void LobbyConfig::Reload()
{
    LIFT_STUB(0x990f0);
}
