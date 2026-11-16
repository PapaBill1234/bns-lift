// LobbyDPacketHandler.obj (LobbyGate PDB). Handlers for the packets from LobbyD to LobbyGate.
#include "Network.h"
#include "LobbyDPacketHandler.h"
#include "Session.h"
#include "Connection.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "PacketUtil.h"
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "Daemon.h"
#include "StringUtil.h"
#include "Client.h"
#include "FragmentPacket.h"
#include "LobbyGate.h"
#include "LobbyGatePredefine.h"
#include "LobbyDChannel.h"
#include "ContentsRuleConfigDefinition.h"
#include "WorldListManager.h"
#include "PcCafeMileageFeverTimeScheduleList.h"

// ❓ The PDB gives no module for these structs. Layout from include/pdb/LobbyGate/types.h.
struct GradeInfo
{
    int gameGradeKey;
    int gradeId;
    char activation;
    int gradeCount;
    long long totalEffectiveFrom;
    long long totalEffectiveTo;
};
static_assert(sizeof(GradeInfo) == 0x20, "sizeof GradeInfo");

struct GradeLevelInfo
{
    int level;
    int score;
    int minLevelScore;
    int maxLevelScore;
    int maxGradeScore;
};
static_assert(sizeof(GradeLevelInfo) == 0x14, "sizeof GradeLevelInfo");

static wchar_t const* const HANDLER_FILE = L"LobbyDPacketHandler.cpp";
static wchar_t const* const SESSION_FILE = L"source\\Session.cpp";
static wchar_t const* const CHANNEL_H_FILE =
    L"E:\\DailyBuild02\\LobbyGate-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";

#define ID128_ARGS(x)                                                                                        \
    *reinterpret_cast<unsigned int const*>(&(x).guid[0]),                                                    \
        static_cast<unsigned int>(*reinterpret_cast<unsigned short const*>(&(x).guid[4])),                   \
        static_cast<unsigned int>(*reinterpret_cast<unsigned short const*>(&(x).guid[6])), (x).guid[8],      \
        (x).guid[9], (x).guid[10], (x).guid[11], (x).guid[12], (x).guid[13], (x).guid[14], (x).guid[15]

// All log texts start with this prefix. Arguments: session id, channel id (❓).
#define LDPFX L"[lobbyd], 0x%.16I64X, %I64d, "
#define LD_ERR(line, fmt, ...) \
    Log::Write(Log::LT_ERROR, HANDLER_FILE, line, LDPFX fmt, session->_id, chId, ##__VA_ARGS__)
#define LD_DBG(line, fmt, ...) \
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, line, LDPFX fmt, session->_id, chId, ##__VA_ARGS__)
#define LD_ALLOC(size, line) Memory::_Manager[2]->Alloc((size), HANDLER_FILE, (line))
#define LD_ALLOCZERO(size, line) Memory::_Manager[2]->AllocZero((size), HANDLER_FILE, (line))
#define LD_FREE(ptr, line) Memory::_Manager[2]->Free((ptr), HANDLER_FILE, (line))

// The inlined prologue of each handler: Session::GetChannel and the crash log. ❓ helper name, message text.
static Channel* LobbyDHandlerChannel(Session const* session, int line)
{
    Channel* ch = session->GetChannel();
    if (ch == nullptr)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, line, L"[lobbyd], 0x%.16I64X, CRASH, channel is null", session->_id);  // ❓
        AlertSender::Write(HANDLER_FILE, line, L"[lobbyd], 0x%.16I64X, CRASH, channel is null", session->_id);       // ❓
    }
    return ch;
}

static void LobbyDHandlerRelease(Channel* ch)
{
    ch->removeReferenceCount(SESSION_FILE, 1059);
}

static void LobbyDRepeatNext(PacketConcatenateBuffer* pcb)
{
    pcb->decomposer.index = pcb->decomposer.start[pcb->decomposer.top] + 1;
    --pcb->decomposer.counts[pcb->decomposer.top];
}

static void LobbyDFpReserve(FragmentPacket& fp, int need)
{
    if (4000 - fp.packet.CurHeader->size < need)
        fp.packet.Allocate(&fp.composer);
}

static void LobbyDBroadcastReload(Session const* clientSession)
{
    long long const* extraData = static_cast<long long const*>(clientSession->_extraData);
    if (extraData != nullptr && *extraData > 0 && *extraData < ContentsRuleConfig::ConfigLastReloadTime)
        clientSession->Send("hi", 109, ContentsRuleConfig::ConfigReloadCount);
}

// 0xaf20
bool HandleLobbyLobbyGate_HelloOk(Session const* session, Packet* packet)
{
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(packet);
    Channel* ch = LobbyDHandlerChannel(session, 32);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());  // ❓

    LobbyGate* gate = LobbyGate::_instance;
    gate->_lobbyD->_state = 1;
    LD_DBG(37, L"enable service");
    if (gate->_lobbyD->_helloEvent.Event != nullptr)
        SetEvent(gate->_lobbyD->_helloEvent.Event);

    int worldCount = 0;
    WorldInfo* worldList = nullptr;
    char enablePcCafeMileage = 0;
    char enablePcCafeMileageDeposit = 0;
    long long pcCafeMileageSeasonExpireTime = 0;
    int scheduleCount = 0;
    PcCafeMileageFeverTimeScheduleInfo* scheduleList = nullptr;

    pcb->decomposer.SetFormat("hiChhsQQiihhiQQQQQQQ;QQqCqqiQiic;", 2);
    worldCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    worldList = static_cast<WorldInfo*>(LD_ALLOCZERO(68 * worldCount, 89));
    for (int i = 0; i < worldCount; ++i)
    {
        WorldInfo& w = worldList[i];
        if (!pcb->Decompose(17, &w.worldId, &w.worldClusterId, w.worldName, 17, &w.worldType, &w.playType,
                            &w.publicAddress, &w.internalAddress, &w.publicPort, &w.mobilePort, &w.worldScore,
                            &w.worldLive, &w.entrance, &w.characterCreation, &w.characterCreationLimitedOnNewAccount,
                            &w.recommend, &w.brandnew, &w.crowdness))
        {
            // BUG: 0xaf20 the suffix text is passed as an argument, not appended to the format.
            LD_ERR(113, L"world-info decompose fail, ",
                   L"HelloOk, worldCount:%d, enablePcCafeMileage:%s, enablePcCafeMileageDeposit:%s, "
                   L"pcCafeMileageFeverTimeScheduleCount:%d");
            goto fail;
        }
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();

    if (!pcb->Decompose(3, &enablePcCafeMileage, &enablePcCafeMileageDeposit, &pcCafeMileageSeasonExpireTime))
    {
        LD_ERR(124, L"current-pc-cafe-mileage-season-expire-time decompose fail, ");
        goto fail;
    }

    scheduleCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    scheduleList = static_cast<PcCafeMileageFeverTimeScheduleInfo*>(
        LD_ALLOCZERO(sizeof(PcCafeMileageFeverTimeScheduleInfo) * scheduleCount, 130));
    for (int i = 0; i < scheduleCount; ++i)
    {
        PcCafeMileageFeverTimeScheduleInfo& s = scheduleList[i];
        if (!pcb->Decompose(7, &s.startTime, &s.endTime, &s.feverPoints, &s.repeatType, &s.repeatStartTime,
                            &s.repeatDuration, &s.daysOfWeek))
        {
            LD_ERR(143, L"pc-cafe-mileage-fever-time-schedule-info decompose fail, ");
            goto fail;
        }
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();

    LD_DBG(152,
           L"recv ok, HelloOk, worldCount:%d, enablePcCafeMileage:%s, enablePcCafeMileageDeposit:%s, "
           L"pcCafeMileageFeverTimeScheduleCount:%d",
           worldCount, enablePcCafeMileage ? L"true" : L"false", enablePcCafeMileageDeposit ? L"true" : L"false",
           scheduleCount);  // ❓ yes/no texts

    if (!gate->_worldListManger->SetWorldList(worldList, worldCount))
    {
        LD_ERR(158, L"setworldlist fail, ");
        LD_FREE(worldList, 160);
    }
    if (!gate->_pcCafeMileageFeverTimeScheduleListManager->SetPcCafeMileageFeverTimeScheduleList(
            enablePcCafeMileage != 0, enablePcCafeMileageDeposit != 0, pcCafeMileageSeasonExpireTime, scheduleList,
            scheduleCount))
    {
        LD_ERR(170, L"set pc-cafe-mileage-fever-time-schedule-list fail, ");
        LD_FREE(scheduleList, 172);
    }
    pcb->Clear();
    LobbyDHandlerRelease(ch);
    return true;

fail:
    // BUG: 0xaf20 scheduleList is not freed on this path.
    if (worldList != nullptr)
        LD_FREE(worldList, 182);
    pcb->Clear();
    LobbyDHandlerRelease(ch);
    return false;
}

// 0xb750
bool HandleLobbyLobbyGate_HelloFail(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 196);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    short reason = 0;
    packet->Decompose("hh", &cmd, &reason);
    LD_ERR(203, L"hello fail, reason:%d", reason);
    LobbyDHandlerRelease(ch);
    return true;
}

// 0xb890
bool HandleLobbyLobbyGate_UpdateWorldInfoListNotify(Session const* session, Packet* packet)
{
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(packet);
    Channel* ch = LobbyDHandlerChannel(session, 217);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());

    pcb->decomposer.SetFormat("hiChhsQQiihhiQQQQQQQ;", 2);
    int worldCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    WorldInfo* worldList = static_cast<WorldInfo*>(LD_ALLOCZERO(68 * worldCount, 265));  // ❓ line
    for (int i = 0; i < worldCount; ++i)
    {
        WorldInfo& w = worldList[i];
        if (!pcb->Decompose(17, &w.worldId, &w.worldClusterId, w.worldName, 17, &w.worldType, &w.playType,
                            &w.publicAddress, &w.internalAddress, &w.publicPort, &w.mobilePort, &w.worldScore,
                            &w.worldLive, &w.entrance, &w.characterCreation, &w.characterCreationLimitedOnNewAccount,
                            &w.recommend, &w.brandnew, &w.crowdness))
        {
            // BUG: 0xb890 the suffix text is passed as an argument, not appended to the format.
            LD_ERR(284, L"world-info decompose fail, ", L"UpdateWorldInfoListNotify, worldCount:%d", worldCount);
            LD_FREE(worldList, 286);  // ❓ line
            pcb->Clear();
            LobbyDHandlerRelease(ch);
            return true;
        }
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();
    LD_DBG(293, L"recv ok, UpdateWorldInfoListNotify, worldCount:%d", worldCount);
    if (!LobbyGate::_instance->_worldListManger->SetWorldList(worldList, worldCount))
    {
        // BUG: 0xb890 the suffix text is passed as an argument, not appended to the format.
        LD_ERR(299, L"setworldlist fail, ", L"UpdateWorldInfoListNotify, worldCount:%d", worldCount);
        LD_FREE(worldList, 301);  // ❓ line
    }
    pcb->Clear();
    LobbyDHandlerRelease(ch);
    return true;
}

// 0xbce0
bool HandleLobbyLobbyGate_AnnounceNotify(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 326);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    wchar_t message[1025];
    message[0] = L'\0';
    if (!packet->Decompose("hs", &cmd, message, 1025))
    {
        LD_ERR(340, L"decompose fail,AnnounceNotify, message:%s", message);
    }
    else
    {
        LD_DBG(345, L"recv ok, AnnounceNotify, message:%s", message);
        LobbyGate::_instance->_clientManager->BroadcastAnnounceNotify(message);  // ❓
    }
    LobbyDHandlerRelease(ch);
    return true;
}

#define INITNP_SUFFIX                                                                                       \
    L"InitSessionWithNPTokenOk, gateKey:0x%I64X, cliKey:0x%I64X, "                                           \
    L"npToken:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "                                            \
    L"portalAccountid:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"
#define INITNP_ARGS gateKey, cliKey, ID128_ARGS(npGameToken), ID128_ARGS(portalAccountId)

// 0xbe90
bool HandleLobbyLobbyGate_InitSessionWithNPTokenOk(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 357);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long gateKey = 0;
    long long cliKey = 0;
    id128 npGameToken = {};
    id128 portalAccountId = {};
    if (!packet->Decompose("hqqoo", &cmd, &gateKey, &cliKey, &npGameToken, &portalAccountId))
    {
        LD_ERR(375, L"decompose fail," INITNP_SUFFIX, INITNP_ARGS);
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(380, L"recv ok, " INITNP_SUFFIX, INITNP_ARGS);

    LobbyGate* gate = LobbyGate::_instance;
    GateKeyEntry* e = gate->_gatekeyManager->GetGKEntry(gateKey);
    if (e == nullptr)
    {
        LD_ERR(386, L"failed to find gatekey" INITNP_SUFFIX, INITNP_ARGS);
    }
    else if (e->_session == nullptr)
    {
        LD_ERR(395, L"failed to get client session" INITNP_SUFFIX, INITNP_ARGS);
    }
    else if (!gate->_clientManager->AddClient(e->_session, gateKey, cliKey))
    {
        LD_ERR(404, L"failed to add clien in climgr" INITNP_SUFFIX, INITNP_ARGS);
        e->_session->Send("hh", 5);  // BUG: 0xbe90 the format has two fields, but the reason is missing.
    }
    else
    {
        e->_cliKey = cliKey;
        if (!gate->_lobbyD->SendStartSessionWithNPTokenReq(cliKey, &npGameToken, &portalAccountId,
                                                           e->_session->_connection->_ip))
        {
            LD_ERR(414, L"failed to SendStartSessionWithNPTokenReq" INITNP_SUFFIX, INITNP_ARGS);
            e->_session->Send("hh", 5);  // BUG: 0xbe90 the format has two fields, but the reason is missing.
        }
    }
    LobbyDHandlerRelease(ch);
    return true;
}

// 0xca10
bool HandleLobbyLobbyGate_InitSessionWithNPTokenFail(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 427);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long gateKey = 0;
    int failReason = 0;  // ❓ type of 'E'
    if (!packet->Decompose("hqE", &cmd, &gateKey, &failReason))
    {
        LD_ERR(442, L"decompose fail,InitSessionWithNPTokenFail, gateKey:0x%I64X, failReason:%d", gateKey, failReason);
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(447, L"recv ok, InitSessionWithNPTokenFail, gateKey:0x%I64X, failReason:%d", gateKey, failReason);
    GateKeyEntry* e = LobbyGate::_instance->_gatekeyManager->RemoveGateKey(gateKey);
    if (e != nullptr && e->_session != nullptr)
    {
        // BUG: 0xca10 the suffix text is passed as an argument, not appended to the format.
        LD_ERR(457, L"SendLoginWitNPTokenFail, ", L"InitSessionWithNPTokenFail, gateKey:0x%I64X, failReason:%d",
               gateKey, failReason);
        e->_session->Send("hh", 5, failReason);
    }
    else
    {
        // BUG: 0xca10 the suffix text is passed as an argument, not appended to the format.
        LD_ERR(462, L"fail to SendLoginWitNPTokenFail, ",
               L"InitSessionWithNPTokenFail, gateKey:0x%I64X, failReason:%d", gateKey, failReason);
    }
    if (e != nullptr)
    {
        e->~GateKeyEntry();
        LD_FREE(e, 464);
    }
    LobbyDHandlerRelease(ch);
    return true;
}

// 0xcd00
bool HandleLobbyLobbyGate_StartSessionWithNPTokenOk(Session const* session, Packet* packet)
{
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(packet);
    Channel* ch = LobbyDHandlerChannel(session, 478);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());

    long long cliKey = 0;
    char createInitialUserName[1] = {0};  // ❓ type
    id128 infoGateToken = {};
    int infoGatePubAddr = 0;
    short infoGatePubPort[1] = {0};
    int gradeLevelCount = 0;
    GradeLevelInfo* gradeLevelList = nullptr;
    int gradeCount = 0;
    GradeInfo* gradeList = nullptr;
    char teen = 0;
    long long closestEndTime = 0;
    int remainJumpingCharacterCreationQuota = 0;
    long long accountExp = 0;          // ❓ name
    int accountLevel = 0;              // ❓ name
    long long accountExpUpdateTime = 0;  // ❓ name
    Client* client = nullptr;
    Session const* clientSession = nullptr;

    pcb->decomposer.SetFormat("hiqQoihCiiiii;CiiQiqq;Qqiqiq", 2);
    if (!pcb->Decompose(5, &cliKey, createInitialUserName, &infoGateToken, &infoGatePubAddr, infoGatePubPort))
    {
        LD_ERR(549, L"decompose fail,StartSessionWithNPTokenOk, cliKey:0x%I64X, create-initial-user-name:%s", cliKey,
               createInitialUserName[0] ? L"yes" : L"no");
        pcb->Clear();
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(555,
           L"recv ok, StartSessionWithNPTokenOk, cliKey:0x%I64X, create-initial-user-name:%s, "
           L"info-gate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",  // ❓ tail of the text
           cliKey, createInitialUserName[0] ? L"yes" : L"no", ID128_ARGS(infoGateToken));

    gradeLevelCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    gradeLevelList = static_cast<GradeLevelInfo*>(LD_ALLOC(sizeof(GradeLevelInfo) * gradeLevelCount, 561));
    for (int i = 0; i < gradeLevelCount; ++i)
    {
        GradeLevelInfo& g = gradeLevelList[i];
        if (!pcb->Decompose(5, &g.level, &g.score, &g.minLevelScore, &g.maxLevelScore, &g.maxGradeScore))
        {
            LD_ERR(569, L"vipLevelInfo decompose fail,StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
            goto cleanup;
        }
        LD_DBG(579, L"gradeLevelInfo recv ok, level:%d, score:%d, minLevelScore:%d, maxLevelScore:%d, maxGradeScore:%d",
               g.level, g.score, g.minLevelScore, g.maxLevelScore, g.maxGradeScore);  // ❓ text
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();

    gradeCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    gradeList = static_cast<GradeInfo*>(LD_ALLOC(sizeof(GradeInfo) * gradeCount, 590));
    for (int i = 0; i < gradeCount; ++i)
    {
        GradeInfo& g = gradeList[i];
        if (!pcb->Decompose(6, &g.gameGradeKey, &g.gradeId, &g.activation, &g.gradeCount, &g.totalEffectiveFrom,
                            &g.totalEffectiveTo))
        {
            LD_ERR(598, L"gradeInfo decompose fail,StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
            goto cleanup;
        }
        LD_DBG(609, L"gradeInfo recv ok, gameGradeKey:%d, gradeId:%d, activation:%s, gradeCount:%d", g.gameGradeKey,
               g.gradeId, g.activation ? L"yes" : L"no", g.gradeCount);  // ❓ text
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();

    if (!pcb->Decompose(3, &teen, &closestEndTime, &remainJumpingCharacterCreationQuota))
    {
        LD_ERR(617, L"teen and closest-end-time and remain-jumping-character-creation-quota decompose fail, "
                    L"StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
        goto cleanup;
    }
    if (!pcb->Decompose(3, &accountExp, &accountLevel, &accountExpUpdateTime))
    {
        LD_ERR(622, L"accountExpInfo decompose fail, StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
        goto cleanup;
    }

    client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
    if (client == nullptr)
        goto cleanup;
    client->_state = 1;
    clientSession = client->GetSession();
    if (clientSession != nullptr)
    {
        LD_DBG(633, L"sendLoginWithNPTokenOk, StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);  // ❓ suffix
        FragmentPacket fp(4, "hiqQoihCiiiii;CiiQiqq;QqiqiqK");  // ❓ command
        bool ok = false;
        if (!fp.Compose(5, cliKey, createInitialUserName[0], &infoGateToken, infoGatePubAddr, infoGatePubPort[0]))
        {
            LD_ERR(644, L"client packet compose fail, StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
        }
        else
        {
            ok = true;
            fp.composer.PushRepeatCount(&fp.packet);
            for (int i = 0; ok && i < gradeLevelCount; ++i)
            {
                GradeLevelInfo& g = gradeLevelList[i];
                LobbyDFpReserve(fp, 0x14);
                if (!fp.Compose(5, g.level, g.score, g.minLevelScore, g.maxLevelScore, g.maxGradeScore))
                {
                    LD_ERR(666, L"gradelevelinfo compose fail, StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                fp.composer.PopRepeatCount();
                fp.composer.PushRepeatCount(&fp.packet);
            }
            for (int i = 0; ok && i < gradeCount; ++i)
            {
                GradeInfo& g = gradeList[i];
                LobbyDFpReserve(fp, 0x1D);
                if (!fp.Compose(6, g.gameGradeKey, g.gradeId, g.activation, g.gradeCount, g.totalEffectiveFrom,
                                g.totalEffectiveTo))
                {
                    LD_ERR(698, L"gradeinfo compose fail, StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                fp.composer.PopRepeatCount();
                LobbyDFpReserve(fp, 0xD);
                if (!fp.Compose(3, teen, closestEndTime, remainJumpingCharacterCreationQuota))
                {
                    LD_ERR(711, L"teen and closest-end-time and remain-jumping-character-creation-quota compose fail, "
                                L"StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                LobbyDFpReserve(fp, 0x14);
                if (!fp.Compose(3, accountExp, accountLevel, accountExpUpdateTime))
                {
                    LD_ERR(722, L"accountExpInfo compose fail, StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                LobbyGate* gate = LobbyGate::_instance;
                if (!fp.Compose(1, gate->_broadcastCrypt.key, gate->_broadcastCrypt.size))
                {
                    LD_ERR(732, L"broadcastkey compose fail, StartSessionWithNPTokenOk, cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                fp.packet.Splitter->Finalize(fp.packet.CurHeader);
                clientSession->Send(&fp.packet);
                client->_broadcast = true;
                LobbyDBroadcastReload(clientSession);
            }
        }
        fp.packet.Clear();
    }
    client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line

cleanup:
    pcb->Clear();
    if (gradeLevelList != nullptr)
        LD_FREE(gradeLevelList, 760);  // ❓ line
    if (gradeList != nullptr)
        LD_FREE(gradeList, 763);  // ❓ line
    LobbyDHandlerRelease(ch);
    return true;
}

// 0xe810
bool HandleLobbyLobbyGate_StartSessionWithNPTokenFail(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 778);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long cliKey = 0;
    int failReason = 0;
    if (!packet->Decompose("hqE", &cmd, &cliKey, &failReason))
    {
        LD_ERR(793, L"decompose fail,StartSessionWithNPTokenFail, cliKey:0x%I64X, failReason:%d", cliKey, failReason);
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(798, L"recv ok, StartSessionWithNPTokenFail, cliKey:0x%I64X, failReason:%d", cliKey, failReason);

    LobbyGate* gate = LobbyGate::_instance;
    long long gateKey = 0;
    Client* client = gate->_clientManager->AcquireClient(cliKey);
    if (client != nullptr)
    {
        gateKey = client->_gateKey;
        gate->_clientManager->RemoveClient(cliKey);
        client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
    }
    else
    {
        LD_ERR(808, L"failed to find cliKey, StartSessionWithNPTokenFail, cliKey:0x%I64X, failReason:%d", cliKey,
               failReason);  // ❓
    }
    GateKeyEntry* e = gate->_gatekeyManager->RemoveGateKey(gateKey);
    if (e != nullptr && e->_session != nullptr)
    {
        // BUG: 0xe810 the suffix text is passed as an argument, not appended to the format.
        LD_ERR(819, L"SendLoginWitNPTokenFail, ", L"StartSessionWithNPTokenFail, cliKey:0x%I64X, failReason:%d",
               cliKey, failReason);
        int reason = failReason;
        switch (failReason)
        {
        case 15: reason = 10; break;
        case 16: reason = 11; break;
        case 17: reason = 12; break;
        case 18: reason = 13; break;
        default: break;  // ❓
        }
        e->_session->Send("hh", 5, reason);
    }
    else
    {
        LD_ERR(841, L"fail to SendLoginWitNPTokenFail, StartSessionWithNPTokenFail, cliKey:0x%I64X, failReason:%d",
               cliKey, failReason);  // ❓
    }
    if (e != nullptr)
    {
        e->~GateKeyEntry();
        LD_FREE(e, 846);  // ❓ line
    }
    LobbyDHandlerRelease(ch);
    return true;
}

#define INITLT_SUFFIX L"InitSessionWithLobbyTokenOk, gateKey:0x%I64X, cliKey:0x%I64X"

// 0xeb30
bool HandleLobbyLobbyGate_InitSessionWithLobbyTokenOk(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 856);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long gateKey = 0;
    long long cliKey = 0;
    if (!packet->Decompose("hqq", &cmd, &gateKey, &cliKey))
    {
        LD_ERR(872, L"decompose fail," INITLT_SUFFIX, gateKey, cliKey);
        LobbyDHandlerRelease(ch);
        return false;
    }
    if (gateKey == 0 || cliKey == 0)
    {
        LD_ERR(879, L"invalid parameter, " INITLT_SUFFIX, gateKey, cliKey);
    }
    else
    {
        LD_DBG(884, L"recv ok, " INITLT_SUFFIX, gateKey, cliKey);
        LobbyGate* gate = LobbyGate::_instance;
        GateKeyEntry* e = gate->_gatekeyManager->GetGKEntry(gateKey);
        if (e == nullptr)
        {
            LD_ERR(890, L"failed to find gatekey" INITLT_SUFFIX, gateKey, cliKey);
        }
        else if (e->_session == nullptr)
        {
            LD_ERR(899, L"failed to get client session" INITLT_SUFFIX, gateKey, cliKey);
        }
        else if (!gate->_clientManager->AddClient(e->_session, gateKey, cliKey))
        {
            LD_ERR(907, L"failed to AddClient" INITLT_SUFFIX, gateKey, cliKey);
            e->_session->Send("hh", 8);  // BUG: 0xeb30 the format has two fields, but the reason is missing.
        }
        else
        {
            e->_cliKey = cliKey;  // ❓
            if (!gate->_lobbyD->SendStartSessionWithLobbyTokenReq(cliKey))
            {
                LD_ERR(916, L"failed to SendStartSessionWithLobbyTokenReq" INITLT_SUFFIX, gateKey, cliKey);
                e->_session->Send("hh", 8);  // BUG: 0xeb30 the format has two fields, but the reason is missing.
            }
        }
    }
    LobbyDHandlerRelease(ch);
    return true;
}

// 0xef10
bool HandleLobbyLobbyGate_InitSessionWithLobbyTokenFail(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 930);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long gateKey = 0;
    int failReason = 0;
    if (!packet->Decompose("hqE", &cmd, &gateKey, &failReason))
    {
        LD_ERR(945, L"decompose fail,InitSessionWithLobbyTokenFail, gateKey:0x%I64X, failReason:%d", gateKey,
               failReason);
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(950, L"recv ok, InitSessionWithLobbyTokenFail, gateKey:0x%I64X, failReason:%d", gateKey, failReason);
    GateKeyEntry* e = LobbyGate::_instance->_gatekeyManager->RemoveGateKey(gateKey);
    if (e != nullptr && e->_session != nullptr)
    {
        // BUG: 0xef10 the suffix text is passed as an argument, not appended to the format.
        LD_ERR(960, L"SendLoginWitLobbyTokenFail, ", L"InitSessionWithLobbyTokenFail, gateKey:0x%I64X, failReason:%d",
               gateKey, failReason);
        int reason = failReason;
        switch (failReason)
        {
        case 19: reason = 14; break;
        case 20: reason = 15; break;
        case 21: reason = 16; break;
        default: break;  // ❓
        }
        e->_session->Send("hh", 8, reason);
    }
    else
    {
        // BUG: 0xef10 the suffix text is passed as an argument, not appended to the format.
        LD_ERR(981, L"fail to SendLoginWitLobbyTokenFail, ",
               L"InitSessionWithLobbyTokenFail, gateKey:0x%I64X, failReason:%d", gateKey, failReason);
    }
    if (e != nullptr)
    {
        e->~GateKeyEntry();
        LD_FREE(e, 983);  // ❓ line
    }
    LobbyDHandlerRelease(ch);
    return true;
}

// 0xf230
bool HandleLobbyLobbyGate_StartSessionWithLobbyTokenOk(Session const* session, Packet* packet)
{
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(packet);
    Channel* ch = LobbyDHandlerChannel(session, 998);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());

    long long cliKey = 0;
    int gradeLevelCount = 0;
    GradeLevelInfo* gradeLevelList = nullptr;
    int gradeCount = 0;
    GradeInfo* gradeList = nullptr;
    int remainJumpingCharacterCreationQuota = 0;
    long long accountExp = 0;            // ❓ name
    int accountLevel = 0;                // ❓ name
    long long accountExpUpdateTime = 0;  // ❓ name
    Client* client = nullptr;
    Session const* clientSession = nullptr;

    pcb->decomposer.SetFormat("hiqCiiiii;CiiQiqq;iqiq", 2);
    if (!pcb->Decompose(1, &cliKey))
    {
        LD_ERR(1064,
               L"decompose fail,StartSessionWithLobbyTokenOk, cliKey:0x%I64X, remainJumpingCharacterCreationQuota:%d",
               cliKey, remainJumpingCharacterCreationQuota);
        pcb->Clear();
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(1070, L"recv ok, StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);  // ❓ text

    gradeLevelCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    gradeLevelList = static_cast<GradeLevelInfo*>(LD_ALLOC(sizeof(GradeLevelInfo) * gradeLevelCount, 1076));
    for (int i = 0; i < gradeLevelCount; ++i)
    {
        GradeLevelInfo& g = gradeLevelList[i];
        if (!pcb->Decompose(5, &g.level, &g.score, &g.minLevelScore, &g.maxLevelScore, &g.maxGradeScore))
        {
            LD_ERR(1084, L"gradeLevelInfo decompose fail,StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);
            goto cleanup;
        }
        LD_DBG(1094,
               L"gradeLevelInfo recv ok, level:%d, score:%d, minLevelScore:%d, maxLevelScore:%d, maxGradeScore:%d",
               g.level, g.score, g.minLevelScore, g.maxLevelScore, g.maxGradeScore);  // ❓ text
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();

    gradeCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    gradeList = static_cast<GradeInfo*>(LD_ALLOC(sizeof(GradeInfo) * gradeCount, 1105));
    for (int i = 0; i < gradeCount; ++i)
    {
        GradeInfo& g = gradeList[i];
        if (!pcb->Decompose(6, &g.gameGradeKey, &g.gradeId, &g.activation, &g.gradeCount, &g.totalEffectiveFrom,
                            &g.totalEffectiveTo))
        {
            LD_ERR(1113, L"vipLevelInfo decompose fail,StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);
            goto cleanup;
        }
        LD_DBG(1124, L"gradeInfo recv ok, gameGradeKey:%d, gradeId:%d, activation:%s, gradeCount:%d", g.gameGradeKey,
               g.gradeId, g.activation ? L"yes" : L"no", g.gradeCount);  // ❓ text
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();

    if (!pcb->Decompose(1, &remainJumpingCharacterCreationQuota))
    {
        LD_ERR(1133, L"remainJumpingCharacterCreationQuota decompose fail, StartSessionWithLobbyTokenOk, cliKey:0x%I64X",
               cliKey);
        goto cleanup;
    }
    if (!pcb->Decompose(3, &accountExp, &accountLevel, &accountExpUpdateTime))
    {
        LD_ERR(1138, L"accountExpInfo decompose fail, StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);
        goto cleanup;
    }

    client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
    if (client == nullptr)
        goto cleanup;
    client->_state = 1;
    clientSession = client->GetSession();
    if (clientSession != nullptr)
    {
        LD_DBG(1149, L"sendLoginWithLobbyTokenOk, StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);  // ❓ suffix
        FragmentPacket fp(7, "hiqCiiiii;CiiQiqq;iqiqK");
        bool ok = false;
        if (!fp.Compose(1, cliKey))
        {
            LD_ERR(1156, L"client packet compose fail, StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);
        }
        else
        {
            ok = true;
            fp.composer.PushRepeatCount(&fp.packet);
            for (int i = 0; ok && i < gradeLevelCount; ++i)
            {
                GradeLevelInfo& g = gradeLevelList[i];
                LobbyDFpReserve(fp, 0x14);
                if (!fp.Compose(5, g.level, g.score, g.minLevelScore, g.maxLevelScore, g.maxGradeScore))
                {
                    LD_ERR(1178, L"gradelevelinfo compose fail, StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                fp.composer.PopRepeatCount();
                fp.composer.PushRepeatCount(&fp.packet);
            }
            for (int i = 0; ok && i < gradeCount; ++i)
            {
                GradeInfo& g = gradeList[i];
                LobbyDFpReserve(fp, 0x1D);
                if (!fp.Compose(6, g.gameGradeKey, g.gradeId, g.activation, g.gradeCount, g.totalEffectiveFrom,
                                g.totalEffectiveTo))
                {
                    LD_ERR(1209, L"gradeinfo compose fail, StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                fp.composer.PopRepeatCount();
                LobbyDFpReserve(fp, 4);
                if (!fp.Compose(1, remainJumpingCharacterCreationQuota))
                {
                    LD_ERR(1222, L"remainJumpingCharacterCreationQuota compose fail, StartSessionWithLobbyTokenOk, "
                                 L"cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                LobbyDFpReserve(fp, 0x14);
                if (!fp.Compose(3, accountExp, accountLevel, accountExpUpdateTime))
                {
                    LD_ERR(1233, L"accountExpInfo compose fail, StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                LobbyGate* gate = LobbyGate::_instance;
                if (!fp.Compose(1, gate->_broadcastCrypt.key, gate->_broadcastCrypt.size))
                {
                    LD_ERR(1243, L"broadcastkey compose fail, StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);
                    ok = false;
                }
            }
            if (ok)
            {
                fp.packet.Splitter->Finalize(fp.packet.CurHeader);
                clientSession->Send(&fp.packet);
                client->_broadcast = true;
                LobbyDBroadcastReload(clientSession);
                LD_DBG(1262, L"send ok, StartSessionWithLobbyTokenOk, cliKey:0x%I64X", cliKey);  // ❓ text
            }
        }
        fp.packet.Clear();
    }
    client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line

cleanup:
    pcb->Clear();
    if (gradeLevelList != nullptr)
        LD_FREE(gradeLevelList, 1270);
    if (gradeList != nullptr)
        LD_FREE(gradeList, 1273);
    LobbyDHandlerRelease(ch);
    return true;
}

// 0xffc0
bool HandleLobbyLobbyGate_StartSessionWithLobbyTokenFail(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 1289);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long cliKey = 0;
    int failReason = 0;
    if (!packet->Decompose("hqE", &cmd, &cliKey, &failReason))
    {
        LD_ERR(1304, L"decompose fail,StartSessionWithLobbyTokenFail, cliKey:0x%I64X, failReason:%d", cliKey,
               failReason);
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(1309, L"recv ok, StartSessionWithLobbyTokenFail, cliKey:0x%I64X, failReason:%d", cliKey, failReason);

    LobbyGate* gate = LobbyGate::_instance;
    long long gateKey = 0;
    Client* client = gate->_clientManager->AcquireClient(cliKey);
    if (client != nullptr)
    {
        gateKey = client->_gateKey;
        gate->_clientManager->RemoveClient(cliKey);
        client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
    }
    else
    {
        LD_ERR(1319, L"failed to find cliKey, StartSessionWithLobbyTokenFail, cliKey:0x%I64X, failReason:%d", cliKey,
               failReason);  // ❓
    }
    GateKeyEntry* e = gate->_gatekeyManager->RemoveGateKey(gateKey);
    if (e != nullptr && e->_session != nullptr)
    {
        // BUG: 0xffc0 the suffix text is passed as an argument, not appended to the format.
        LD_ERR(1330, L"SendLoginWitLobbyTokenFail, ", L"StartSessionWithLobbyTokenFail, cliKey:0x%I64X, failReason:%d",
               cliKey, failReason);
        e->_session->Send("hh", 8, failReason);
    }
    if (e != nullptr)
    {
        e->~GateKeyEntry();
        LD_FREE(e, 1333);
    }
    LobbyDHandlerRelease(ch);
    return true;
}

// 0x102b0
bool HandleLobbyLobbyGate_CloseAnonymousSessionNotify(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 1351);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long gateKey = 0;
    if (!packet->Decompose("hq", &cmd, &gateKey))
    {
        LD_ERR(1365, L"decompose fail,CloseAnonymousSessionNotify, gateKey:0x%I64X", gateKey);
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(1370, L"recv ok, CloseAnonymousSessionNotify, gateKey:0x%I64X", gateKey);
    LobbyDHandlerRelease(ch);
    return true;
}

// 0x10440
bool HandleLobbyLobbyGate_CloseSessionNotify(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 1383);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long cliKey = 0;
    if (!packet->Decompose("hq", &cmd, &cliKey))
    {
        LD_ERR(1397, L"decompose fail,CloseSessionNotify, cliKey:0x%I64X", cliKey);
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(1402, L"recv ok, CloseSessionNotify, cliKey:0x%I64X", cliKey);
    Client* client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
    if (client != nullptr)
    {
        LobbyGate::_instance->AddJobTimer(client->_gateKey, 3);
        client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
    }
    else
    {
        LD_ERR(1407, L"failed to find cliKey, CloseSessionNotify, cliKey:0x%I64X", cliKey);
    }
    LobbyDHandlerRelease(ch);
    return true;
}

// 0x10660
bool HandleLobbyLobbyGate_KickNotify(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 1428);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long cliKey = 0;
    char reason = 0;
    if (!packet->Decompose("hqQ", &cmd, &cliKey, &reason))
    {
        LD_ERR(1443, L"decompose fail,KickNotify, cliKey:0x%I64X, reason:%d", cliKey, reason);
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(1448, L"recv ok, KickNotify, cliKey:0x%I64X, reason:%d", cliKey, reason);
    Client* client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
    if (client == nullptr)
    {
        LD_ERR(1453, L"failed to find cliKey, KickNotify, cliKey:0x%I64X, reason:%d", cliKey, reason);
    }
    else
    {
        Session const* clientSession = client->GetSession();
        if (clientSession == nullptr)
        {
            LD_ERR(1461, L"failed to get client session, KickNotify, cliKey:0x%I64X, reason:%d", cliKey, reason);
        }
        else
        {
            Packet p;
            p.Allocate();
            if (!p.Compose("hQ", 10, reason))
            {
                LD_ERR(1473, L"failed to compose packet cmd, KickNotify, cliKey:0x%I64X, reason:%d", cliKey, reason);
            }
            else
            {
                clientSession->Send(&p);
                LD_DBG(1482, L"send ok, kicknotify, sessionId:0x%I64X, reason:%d", clientSession->_id, reason);
                LobbyGate::_instance->AddJobTimer(client->_gateKey, 1);
            }
            p.Clear();
        }
        client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
    }
    LobbyDHandlerRelease(ch);
    return true;
}

// 0x10ab0
bool HandleLobbyLobbyGate_GetCharacterInfoListOk(Session const* session, Packet* packet)
{
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(packet);
    Channel* ch = LobbyDHandlerChannel(session, 1503);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());

    long long cliKey = 0;
    long long now = 0;
    short timeZoneBias = 0;
    int characterCount = 0;
    CharacterInfo* characterList = nullptr;
    bool result = true;

    pcb->decomposer.SetFormat("hiqqhCqohsbqQQi;", 2);
    if (!pcb->Decompose(3, &cliKey, &now, &timeZoneBias))
    {
        LD_ERR(1552, L"decompose packet fail, GetCharacterInfoListOk, cliKey:0x%I64X, characterCount:%d", cliKey,
               characterCount);
        pcb->Clear();
        LobbyDHandlerRelease(ch);
        return false;
    }
    characterCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    characterList = static_cast<CharacterInfo*>(LD_ALLOCZERO(sizeof(CharacterInfo) * characterCount, 1561));
    for (int i = 0; i < characterCount; ++i)
    {
        CharacterInfo& c = characterList[i];
        c.characterData = static_cast<char*>(LD_ALLOC(1024, 1566));
        if (!pcb->Decompose(9, &c.pcId, &c.slotId, &c.worldId, c.characterName, 33, c.characterData,
                            &c.characterDataSize, &c.lastPlayEndDate, &c.state, &c.jumpingCharacterState,
                            &c.deleteRemainTime))  // ❓ 'b' arguments
        {
            LD_ERR(1580, L"character-info decompose fail, GetCharacterInfoListOk, cliKey:0x%I64X, characterCount:%d",
                   cliKey, characterCount);
            result = false;  // ❓
            goto cleanup;
        }
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();
    LD_DBG(1589, L"recv ok, GetCharacterInfoListOk, cliKey:0x%I64X, characterCount:%d", cliKey, characterCount);
    {
        Client* client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
        if (client == nullptr)
        {
            LD_ERR(1595, L"failed to acquire client, GetCharacterInfoListOk, cliKey:0x%I64X, characterCount:%d", cliKey,
                   characterCount);
            result = false;
        }
        else
        {
            if (!client->SendGetCharacterInfoListOk(now, timeZoneBias, characterList, characterCount))
                LD_ERR(1601, L"failed to SendGetCharacterInfoListOk, GetCharacterInfoListOk, cliKey:0x%I64X, "
                             L"characterCount:%d", cliKey, characterCount);
            client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
        }
    }

cleanup:
    for (int i = 0; i < characterCount; ++i)
    {
        if (characterList[i].characterData != nullptr)
            LD_FREE(characterList[i].characterData, 1612);
    }
    LD_FREE(characterList, 1614);
    pcb->Clear();
    LobbyDHandlerRelease(ch);
    return result;
}

// 0x11060
bool HandleLobbyLobbyGate_ListGoodsOk(Session const* session, Packet* packet)
{
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(packet);
    Channel* ch = LobbyDHandlerChannel(session, 1645);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());

    long long cliKey = 0;
    int goodsCount = 0;
    Goods* goodsList = nullptr;

    pcb->decomposer.SetFormat("hiqCqiQQqqssissbbCiiibb;;", 2);
    if (!pcb->Decompose(1, &cliKey))
    {
        LD_ERR(1693, L"decompose packet fail, ListGoodsOk, cliKey:0x%I64X, goodsCount:%d", cliKey, goodsCount);
        pcb->Clear();
        LobbyDHandlerRelease(ch);
        return true;
    }
    goodsCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    goodsList = static_cast<Goods*>(LD_ALLOCZERO(sizeof(Goods) * goodsCount, 1702));
    for (int i = 0; i < goodsCount; ++i)
    {
        if (!goodsList[i].Setup(static_cast<FragmentPacketConcatenater*>(pcb)))
        {
            LD_ERR(1709, L"decompose goods-info fail, ListGoodsOk, cliKey:0x%I64X, goodsCount:%d", cliKey, goodsCount);
            goto cleanup;
        }
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();
    LD_DBG(1718, L"recv ok, ListGoodsOk, cliKey:0x%I64X, goodsCount:%d", cliKey, goodsCount);
    {
        Client* client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
        if (client != nullptr)
        {
            if (!client->SendListGoodsOk(goodsList, goodsCount))
                LD_ERR(1723, L"ack fail, ListGoodsOk, cliKey:0x%I64X, goodsCount:%d", cliKey, goodsCount);
            client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
        }
        else
        {
            LD_ERR(1729, L"failed to acquire client, ListGoodsOk, cliKey:0x%I64X, goodsCount:%d", cliKey, goodsCount);
        }
    }

cleanup:
    for (int i = 0; i < goodsCount; ++i)
        goodsList[i].Cleanup();
    if (goodsList != nullptr)
        LD_FREE(goodsList, 1746);
    pcb->Clear();
    LobbyDHandlerRelease(ch);
    return true;
}

// 0x113e0
bool HandleLobbyLobbyGate_TakeGoodsOk(Session const* session, Packet* packet)
{
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(packet);
    Channel* ch = LobbyDHandlerChannel(session, 1756);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());

    long long cliKey = 0;
    unsigned long long goodsId = 0;
    int itemCount = 0;
    LobbyServiceItem* itemList = nullptr;

    pcb->decomposer.SetFormat("hiqqCqqqiQ;", 2);
    if (!pcb->Decompose(2, &cliKey, &goodsId))
    {
        LD_ERR(1804, L"decompose packet fail, TakeGoodsOk, cliKey:0x%I64X, goodsId:0x%I64X, itemCount:%d", cliKey,
               goodsId, itemCount);
        pcb->Clear();
        LobbyDHandlerRelease(ch);
        return true;  // ❓
    }
    itemCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    itemList = static_cast<LobbyServiceItem*>(LD_ALLOC(sizeof(LobbyServiceItem) * itemCount, 1811));
    for (int i = 0; i < itemCount; ++i)
    {
        LobbyServiceItem& it = itemList[i];
        if (!pcb->Decompose(5, &it.ownerPcId, &it.instanceId, &it.labelId, &it.dataId, &it.state))
        {
            LD_ERR(1818, L"decompose item-info fail, TakeGoodsOk, cliKey:0x%I64X, goodsId:0x%I64X, itemCount:%d",
                   cliKey, goodsId, itemCount);
            goto cleanup;
        }
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();
    LD_DBG(1827, L"recv ok, TakeGoodsOk, cliKey:0x%I64X, goodsId:0x%I64X, itemCount:%d", cliKey, goodsId, itemCount);
    {
        Client* client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
        if (client != nullptr)
        {
            if (!client->SendTakeGoodsOk(goodsId, itemList, itemCount))
                LD_ERR(1832, L"ack fail, TakeGoodsOk, cliKey:0x%I64X, goodsId:0x%I64X, itemCount:%d", cliKey, goodsId,
                       itemCount);
            client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
        }
        else
        {
            LD_ERR(1838, L"failed to acquire client, TakeGoodsOk, cliKey:0x%I64X, goodsId:0x%I64X, itemCount:%d",
                   cliKey, goodsId, itemCount);
        }
    }

cleanup:
    if (itemList != nullptr)
        LD_FREE(itemList, 1855);
    pcb->Clear();
    LobbyDHandlerRelease(ch);
    return true;
}

#define LSII_SUFFIX L"ListAccountInventoryItemInfoOk, cliKey:0x%I64X, searchType:%d, searchCount:%d, itemCount:%d"

// 0x117a0
bool HandleLobbyLobbyGate_ListLobbyServiceItemInfoOk(Session const* session, Packet* packet)
{
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(packet);
    Channel* ch = LobbyDHandlerChannel(session, 1865);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());

    long long cliKey = 0;
    char searchType = 0;
    unsigned int searchCount = 0;
    int itemCount = 0;
    LobbyServiceItem* itemList = nullptr;

    pcb->decomposer.SetFormat("hiqQiCqqqiQ;", 2);
    if (!pcb->Decompose(3, &cliKey, &searchType, &searchCount))
    {
        LD_ERR(1914, L"decompose packet fail, " LSII_SUFFIX, cliKey, searchType, searchCount, itemCount);
        pcb->Clear();
        LobbyDHandlerRelease(ch);
        return true;  // ❓
    }
    itemCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    itemList = static_cast<LobbyServiceItem*>(LD_ALLOC(sizeof(LobbyServiceItem) * itemCount, 1921));
    for (int i = 0; i < itemCount; ++i)
    {
        LobbyServiceItem& it = itemList[i];
        if (!pcb->Decompose(5, &it.ownerPcId, &it.instanceId, &it.labelId, &it.dataId, &it.state))
        {
            LD_ERR(1928, L"decompose item-info fail, " LSII_SUFFIX, cliKey, searchType, searchCount, itemCount);
            goto cleanup;
        }
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();
    LD_DBG(1937, L"recv ok, " LSII_SUFFIX, cliKey, searchType, searchCount, itemCount);
    {
        Client* client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
        if (client != nullptr)
        {
            if (!client->SendListLobbyServiceItemInfoOk(searchType, searchCount, itemList, itemCount))
                LD_ERR(1942, L"ack fail, " LSII_SUFFIX, cliKey, searchType, searchCount, itemCount);
            client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
        }
        else
        {
            LD_ERR(1948, L"failed to acquire client, " LSII_SUFFIX, cliKey, searchType, searchCount, itemCount);
        }
    }

cleanup:
    if (itemList != nullptr)
        LD_FREE(itemList, 1965);
    pcb->Clear();
    LobbyDHandlerRelease(ch);
    return true;
}

#define GSEL_SUFFIX L"GetServiceEntryListOk, cliKey:0x%I64X, serviceEntryCount:%d"

// 0x11b60
bool HandleLobbyLobbyGate_GetServiceEntryListOk(Session const* session, Packet* packet)
{
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(packet);
    Channel* ch = LobbyDHandlerChannel(session, 1975);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());

    long long cliKey = 0;
    int serviceEntryCount = 0;
    ServiceEntry* serviceEntryList = nullptr;

    pcb->decomposer.SetFormat("hiqCqQqohq;", 2);
    if (!pcb->Decompose(1, &cliKey))
    {
        LD_ERR(2022, L"decompose packet fail, " GSEL_SUFFIX, cliKey, serviceEntryCount);
        pcb->Clear();
        LobbyDHandlerRelease(ch);
        return true;  // ❓
    }
    serviceEntryCount = pcb->decomposer.PushRepeatCount(pcb->buffer, pcb->size);
    serviceEntryList = static_cast<ServiceEntry*>(LD_ALLOCZERO(sizeof(ServiceEntry) * serviceEntryCount, 2029));
    for (int i = 0; i < serviceEntryCount; ++i)
    {
        ServiceEntry& e = serviceEntryList[i];
        if (!pcb->Decompose(6, &e.serviceId, &e.serviceKind, &e.itemInstanceId, &e.targetSlotId, &e.targetWorldId,
                            &e.hint1))
        {
            LD_ERR(2036, L"decompose service-entry fail, " GSEL_SUFFIX, cliKey, serviceEntryCount);  // ❓ text
            goto cleanup;
        }
        LobbyDRepeatNext(pcb);
    }
    pcb->decomposer.PopRepeatCount();
    LD_DBG(2045, L"recv ok, " GSEL_SUFFIX, cliKey, serviceEntryCount);
    {
        Client* client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
        if (client != nullptr)
        {
            if (!client->SendGetServiceEntryListOk(reinterpret_cast<PacketBuffer*>(serviceEntryList), serviceEntryCount))
                LD_ERR(2050, L"ack fail, " GSEL_SUFFIX, cliKey, serviceEntryCount);
            client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
        }
        else
        {
            LD_ERR(2056, L"failed to acquire client, " GSEL_SUFFIX, cliKey, serviceEntryCount);
        }
    }

cleanup:
    if (serviceEntryList != nullptr)
        LD_FREE(serviceEntryList, 2073);
    pcb->Clear();
    LobbyDHandlerRelease(ch);
    return true;
}

#define GEWT_SUFFIX L"GetEnterWorldTokenOk, cliKey:0x%I64X, lobbyToken:0x%I64x, worldId:%d"

// 0x11ee0
bool HandleLobbyLobbyGate_GetEnterWorldTokenOk(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 2083);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long cliKey = 0;
    long long lobbyToken = 0;
    short worldId = 0;
    if (!packet->Decompose("hqqh", &cmd, &cliKey, &lobbyToken, &worldId))
    {
        LD_ERR(2100, L"decompose fail, " GEWT_SUFFIX, cliKey, lobbyToken, worldId);
        LobbyDHandlerRelease(ch);
        return true;
    }
    LD_DBG(2105, L"recv ok, " GEWT_SUFFIX, cliKey, lobbyToken, worldId);
    Client* client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
    if (client == nullptr)
    {
        LD_ERR(2109, L"failed to find cliKey, " GEWT_SUFFIX, cliKey, lobbyToken, worldId);
    }
    else
    {
        client->Send("hq", 14, lobbyToken);
        LD_DBG(2115, L"send to client ok, " GEWT_SUFFIX, cliKey, lobbyToken, worldId);
        client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
    }
    LobbyDHandlerRelease(ch);
    return true;
}

// 0x121d0
bool HandleLobbyLobbyGate_BypassPacket(Session const* session, Packet* packet)
{
    Channel* ch = LobbyDHandlerChannel(session, 2144);
    if (ch == nullptr)
        return false;
    long long chId = static_cast<long long>(ch->GetId());
    short cmd = 0;
    long long cliKey = 0;
    if (!packet->Decompose("hq", &cmd, &cliKey))
    {
        LD_ERR(2158, L"decompose fail, cmd:%d, cliKey:0x%I64X", cmd, cliKey);
        LobbyDHandlerRelease(ch);
        return false;
    }
    LD_DBG(2163, L"recv ok, cmd:%d, cliKey:0x%I64X", cmd, cliKey);
    Client* client = LobbyGate::_instance->_clientManager->AcquireClient(cliKey);
    if (client == nullptr)
    {
        LD_ERR(2168, L"failed to find cliKey, cmd:%d, cliKey:0x%I64X", cmd, cliKey);
    }
    else
    {
        Session const* clientSession = client->GetSession();
        if (clientSession == nullptr)
        {
            // BUG: 0x121d0 an extra 0 argument is passed before the format arguments.
            LD_ERR(2176, L"failed to get client session, cmd:%d, cliKey:0x%I64X", 0, cmd, cliKey);
        }
        else
        {
            Packet::Header* hdr = packet->CurHeader;
            Packet p;
            p.Allocate();
            short clientCmd =
                LobbyDSessionHandler::SwitchCmdLobbyDaemonToLobbyGate(static_cast<char>(hdr[1].size));
            if (!p.Compose("h", clientCmd))
            {
                LD_ERR(2189, L"failed to compose packet cmd, cmd:%d, cliKey:0x%I64X", cmd, cliKey);
            }
            else
            {
                if (hdr->size > 10)
                {
                    short bodySize = static_cast<short>(hdr->size - 12);
                    if (4000 - p.CurHeader->size < bodySize)
                        p.Allocate();
                    p.Add(reinterpret_cast<char const*>(hdr) + 12, bodySize);
                }
                clientSession->Send(&p);
                LD_DBG(2209, L"send to client ok, sessionId:0x%I64X, cmd:%d", clientSession->_id, clientCmd);
            }
            p.Clear();
        }
        client->removeReferenceCount(CHANNEL_H_FILE, 52);  // ❓ line
    }
    LobbyDHandlerRelease(ch);
    return true;
}

// 0x12650. The linker folded many `return true;` handlers to this body.
bool HandleLobbyLobbyGate_ChangedGradeLevelNotify(Session const* session, Packet* packet)
{
    (void)session;
    (void)packet;
    return true;
}

// Handler tables. ❓ The array sizes come from the highest command index (110).
#define LD_H(f) reinterpret_cast<void*>(&(f))
#define LD_NOP LD_H(HandleLobbyLobbyGate_ChangedGradeLevelNotify)

void* LobbyLobbyGatePacketLobbyGateSideHandlerList[111] = {
    /*   0 */ nullptr, nullptr, LD_H(HandleLobbyLobbyGate_HelloOk), LD_H(HandleLobbyLobbyGate_HelloFail),
    /*   4 */ LD_H(HandleLobbyLobbyGate_UpdateWorldInfoListNotify), LD_H(HandleLobbyLobbyGate_AnnounceNotify), nullptr,
    /*   7 */ LD_H(HandleLobbyLobbyGate_InitSessionWithNPTokenOk), LD_H(HandleLobbyLobbyGate_InitSessionWithNPTokenFail),
    /*   9 */ nullptr, LD_H(HandleLobbyLobbyGate_StartSessionWithNPTokenOk),
    /*  11 */ LD_H(HandleLobbyLobbyGate_StartSessionWithNPTokenFail), nullptr,
    /*  13 */ LD_H(HandleLobbyLobbyGate_InitSessionWithLobbyTokenOk),
    /*  14 */ LD_H(HandleLobbyLobbyGate_InitSessionWithLobbyTokenFail), nullptr,
    /*  16 */ LD_H(HandleLobbyLobbyGate_StartSessionWithLobbyTokenOk),
    /*  17 */ LD_H(HandleLobbyLobbyGate_StartSessionWithLobbyTokenFail), nullptr, nullptr,
    /*  20 */ LD_H(HandleLobbyLobbyGate_CloseAnonymousSessionNotify), LD_H(HandleLobbyLobbyGate_CloseSessionNotify),
    /*  22 */ LD_H(HandleLobbyLobbyGate_KickNotify), nullptr, nullptr,
    /*  25 */ LD_H(HandleLobbyLobbyGate_GetEnterWorldTokenOk), LD_NOP, LD_NOP, nullptr, LD_NOP,
    /*  30 */ LD_NOP, nullptr, LD_NOP, LD_NOP, LD_NOP, nullptr,
    /*  36 */ LD_H(HandleLobbyLobbyGate_GetCharacterInfoListOk), LD_NOP, nullptr, LD_NOP,
    /*  40 */ LD_NOP, nullptr, LD_NOP, LD_NOP, nullptr, LD_NOP, LD_NOP, nullptr, LD_NOP, LD_NOP,
    /*  50 */ LD_NOP, nullptr, LD_NOP, LD_NOP, nullptr, LD_NOP, LD_NOP, nullptr, LD_NOP, LD_NOP,
    /*  60 */ nullptr, LD_NOP, LD_NOP, LD_NOP, nullptr, LD_NOP, LD_NOP, nullptr,
    /*  68 */ LD_H(HandleLobbyLobbyGate_ListGoodsOk), LD_NOP, nullptr, LD_H(HandleLobbyLobbyGate_TakeGoodsOk),
    /*  72 */ LD_NOP, nullptr, LD_H(HandleLobbyLobbyGate_ListLobbyServiceItemInfoOk), LD_NOP, nullptr, LD_NOP,
    /*  78 */ LD_NOP, nullptr, LD_H(HandleLobbyLobbyGate_GetServiceEntryListOk), LD_NOP, nullptr, LD_NOP,
    /*  84 */ LD_NOP, nullptr, LD_NOP, LD_NOP, nullptr, LD_NOP,
    /*  90 */ LD_NOP, nullptr, LD_NOP, LD_NOP, nullptr, LD_NOP, LD_NOP, nullptr, LD_NOP, LD_NOP,
    /* 100 */ nullptr, LD_NOP, LD_NOP, nullptr, LD_NOP, LD_NOP, nullptr, LD_NOP, LD_NOP, LD_NOP,
    /* 110 */ LD_NOP,
};

// ❓ The fragment list has the fragment handlers only.
void* LobbyLobbyGatePacketLobbyGateSideFragmentHandlerList[111] = {
    /*   0 */ nullptr, nullptr, LD_H(HandleLobbyLobbyGate_HelloOk), nullptr,
    /*   4 */ LD_H(HandleLobbyLobbyGate_UpdateWorldInfoListNotify), nullptr, nullptr, nullptr, nullptr, nullptr,
    /*  10 */ LD_H(HandleLobbyLobbyGate_StartSessionWithNPTokenOk), nullptr, nullptr, nullptr, nullptr, nullptr,
    /*  16 */ LD_H(HandleLobbyLobbyGate_StartSessionWithLobbyTokenOk), nullptr, nullptr, nullptr,
    /*  20 */ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    /*  30 */ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    /*  36 */ LD_H(HandleLobbyLobbyGate_GetCharacterInfoListOk), nullptr, nullptr, nullptr,
    /*  40 */ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    /*  50 */ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    /*  60 */ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    /*  68 */ LD_H(HandleLobbyLobbyGate_ListGoodsOk), nullptr, nullptr, LD_H(HandleLobbyLobbyGate_TakeGoodsOk),
    /*  72 */ nullptr, nullptr, LD_H(HandleLobbyLobbyGate_ListLobbyServiceItemInfoOk), nullptr, nullptr, nullptr,
    /*  78 */ nullptr, nullptr, LD_H(HandleLobbyLobbyGate_GetServiceEntryListOk),
};

TFPP_PacketHandler bypassHandler[2] = {nullptr, reinterpret_cast<TFPP_PacketHandler>(&HandleLobbyLobbyGate_BypassPacket)};
TFPP_PacketHandler bypassHandlerFF[2] = {nullptr, nullptr};  // ❓ values
