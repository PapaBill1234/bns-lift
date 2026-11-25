// LobbyGateChannel.obj (LobbyDaemon PDB, 2019 + PDB). Lifted: ld-24 batches 1-2 and gap-02 (0xbf080 to 0xc11d0).
#include "PlacementNew.h"
#include <winsock2.h>
#include <windows.h>
#include <new>
#include <wchar.h>
#include "LobbyGateChannel.h"
#include "LobbyLobbyGatePacketHandler.h"
#include "AlertSender.h"
#include "CliSessionManager.h"
#include "Connection.h"
#include "Daemon.h"
#include "FragmentPacket.h"
#include "GradeService.h"
#include "CliSession.h"
#include "InfoGateChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyEvent.h"
#include "LobbyGoodsTypes.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "Session.h"
#include "StringUtil.h"
#include "WaitQueue.h"

namespace
{
// LIFT: No PDB symbol. The binary uses the literal as the file string of the log and reference count calls.
wchar_t const* const LOBBYGATE_FILE = L"LobbyGateChannel.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of SharedChannelList::Acquire/Remove errors (lines 200 and 234).
wchar_t const* const SHARED_CHANNEL_FILE = L"..\\Shared\\SharedChannel.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of the Session reference count calls (line 1059).
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";
}

#pragma comment(linker, "/INCLUDE:?SendInitSessionWithNPTokenOk@LobbyGateChannel@@QEAAX_K0Tid128@@1@Z")  // LIFT: keep until the caller is lifted (0xbbe90)
#pragma comment(linker, "/INCLUDE:?SendInitSessionWithNPTokenFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbbfb0)
#pragma comment(linker, "/INCLUDE:?SendInitSessionWithLobbyTokenOk@LobbyGateChannel@@QEAAX_K0@Z")  // LIFT: keep until the caller is lifted (0xbc080)
#pragma comment(linker, "/INCLUDE:?SendInitSessionWithLobbyTokenFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbc150)
#pragma comment(linker, "/INCLUDE:?SendStartSessionWithNPTokenOk@LobbyGateChannel@@QEAAX_KDAEBTid128@@KG_NAEBVGradeService@@2_JHAEBVGameAccountExpInfo@@@Z")  // LIFT: keep until the caller is lifted (0xbc220)
#pragma comment(linker, "/INCLUDE:?SendStartSessionWithNPTokenFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbc540)
#pragma comment(linker, "/INCLUDE:?SendStartSessionWithLobbyTokenOk@LobbyGateChannel@@QEAAX_K_NAEBVGradeService@@HAEBVGameAccountExpInfo@@@Z")  // LIFT: keep until the caller is lifted (0xbc610)
#pragma comment(linker, "/INCLUDE:?SendStartSessionWithLobbyTokenFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbc8f0)
#pragma comment(linker, "/INCLUDE:?SendCloseSessionNotify@LobbyGateChannel@@QEAAX_K@Z")  // LIFT: keep until the caller is lifted (0xbca80)
#pragma comment(linker, "/INCLUDE:?SendKickNotify@LobbyGateChannel@@QEAAX_KD@Z")  // LIFT: keep until the caller is lifted (0xbcb40)
#pragma comment(linker, "/INCLUDE:?SendGetCharacterInfoListFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbcc10)
#pragma comment(linker, "/INCLUDE:?SendGetCharacterInfoFail@LobbyGateChannel@@QEAAX_KAEBTid128@@F@Z")  // LIFT: keep until the caller is lifted (0xbcce0)
#pragma comment(linker, "/INCLUDE:?SendCreateCharacterOk@LobbyGateChannel@@QEAAX_K0AEBTid128@@FPEB_WPEADF_JD4H@Z")  // LIFT: keep until the caller is lifted (0xbcdd0)
#pragma comment(linker, "/INCLUDE:?SendCreateCharacterFail@LobbyGateChannel@@QEAAX_KAEBTid128@@F@Z")  // LIFT: keep until the caller is lifted (0xbcf40)
#pragma comment(linker, "/INCLUDE:?SendDeleteCharacterOk@LobbyGateChannel@@QEAAX_KAEBTid128@@DJ@Z")  // LIFT: keep until the caller is lifted (0xbd030)
#pragma comment(linker, "/INCLUDE:?SendDeleteCharacterFail@LobbyGateChannel@@QEAAX_KAEBTid128@@W4ClientState@Character@@F@Z")  // LIFT: keep until the caller is lifted (0xbd130)
#pragma comment(linker, "/INCLUDE:?SendCancelWaitCharacterDeletionOk@LobbyGateChannel@@QEAAX_KAEBTid128@@@Z")  // LIFT: keep until the caller is lifted (0xbd250)
#pragma comment(linker, "/INCLUDE:?SendCancelWaitCharacterDeletionFail@LobbyGateChannel@@QEAAX_KAEBTid128@@W4ClientState@Character@@F@Z")  // LIFT: keep until the caller is lifted (0xbd330)
#pragma comment(linker, "/INCLUDE:?SendEndWaitCharacterDeletionNotify@LobbyGateChannel@@QEAAX_KAEBTid128@@@Z")  // LIFT: keep until the caller is lifted (0xbd450)
#pragma comment(linker, "/INCLUDE:?SendGetEnterWorldTokenFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbd530)
#pragma comment(linker, "/INCLUDE:?SendGetEnterWorldTokenOk@LobbyGateChannel@@QEAAX_K0F@Z")  // LIFT: keep until the caller is lifted (0xbd600)
#pragma comment(linker, "/INCLUDE:?SendStartWaitNotify@LobbyGateChannel@@QEAAX_KAEBUWaitInfo@@@Z")  // LIFT: keep until the caller is lifted (0xbd6e0)
#pragma comment(linker, "/INCLUDE:?SendGetWaitInfoOk@LobbyGateChannel@@QEAAX_KAEBUWaitInfo@@@Z")  // LIFT: keep until the caller is lifted (0xbd9c0)
#pragma comment(linker, "/INCLUDE:?SendGetWaitInfoFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbdca0)
#pragma comment(linker, "/INCLUDE:?SendGiveupWaitOk@LobbyGateChannel@@QEAAX_K@Z")  // LIFT: keep until the caller is lifted (0xbdd70)
#pragma comment(linker, "/INCLUDE:?SendGiveupWaitFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbde30)
#pragma comment(linker, "/INCLUDE:?SendEndWaitNotify@LobbyGateChannel@@QEAAX_K0@Z")  // LIFT: keep until the caller is lifted (0xbdf00)
#pragma comment(linker, "/INCLUDE:?SendGetChargeInfoOk@LobbyGateChannel@@QEAAX_KDDJFDIDDD@Z")  // LIFT: keep until the caller is lifted (0xbdfd0)
#pragma comment(linker, "/INCLUDE:?SendGetChargeInfoFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbe120)
#pragma comment(linker, "/INCLUDE:?SendRecoverCharacterOk@LobbyGateChannel@@QEAAX_KAEBTid128@@@Z")  // LIFT: keep until the caller is lifted (0xbe1f0)
#pragma comment(linker, "/INCLUDE:?SendRecoverCharacterFail@LobbyGateChannel@@QEAAX_KAEBTid128@@W4ClientState@Character@@F@Z")  // LIFT: keep until the caller is lifted (0xbe2d0)
#pragma comment(linker, "/INCLUDE:?SendBindCharacterSlotFail@LobbyGateChannel@@QEAAX_KAEBTid128@@0F@Z")  // LIFT: keep until the caller is lifted (0xbe3f0)
#pragma comment(linker, "/INCLUDE:?SendAccountInventoryNotify@LobbyGateChannel@@QEAAX_KD0@Z")  // LIFT: keep until the caller is lifted (0xbe4f0)
#pragma comment(linker, "/INCLUDE:?SendGetGoodsCountOk@LobbyGateChannel@@QEAAX_KH@Z")  // LIFT: keep until the caller is lifted (0xbe5d0)
#pragma comment(linker, "/INCLUDE:?SendGetGoodsCountFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbe6a0)
#pragma comment(linker, "/INCLUDE:?SendListGoodsOk@LobbyGateChannel@@QEAAX_KPEAUGoods@@H@Z")  // LIFT: keep until the caller is lifted (0xbe770)
#pragma comment(linker, "/INCLUDE:?SendListGoodsFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbe980)
#pragma comment(linker, "/INCLUDE:?SendTakeGoodsOk@LobbyGateChannel@@QEAAX_K0PEAULobbyServiceItem@@H@Z")  // LIFT: keep until the caller is lifted (0xbea50)
#pragma comment(linker, "/INCLUDE:?SendTakeGoodsFail@LobbyGateChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0xbed00)
#pragma comment(linker, "/INCLUDE:?SendListLobbyServiceItemInfoOk@LobbyGateChannel@@QEAAX_KDHPEAULobbyServiceItem@@H@Z")  // LIFT: keep until the caller is lifted (0xbedd0)

// 0xbbe90
void LobbyGateChannel::SendInitSessionWithNPTokenOk(unsigned long long gatekey, unsigned long long clikey, id128 nptoken, id128 portalAccountId)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqoo", 7, gatekey, clikey, nptoken, portalAccountId))
        Send(&p);
}

// 0xbbfb0
void LobbyGateChannel::SendInitSessionWithNPTokenFail(unsigned long long gatekey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 8, gatekey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbc080
void LobbyGateChannel::SendInitSessionWithLobbyTokenOk(unsigned long long gatekey, unsigned long long clikey)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqq", 13, gatekey, clikey))
        Send(&p);
}

// 0xbc150
void LobbyGateChannel::SendInitSessionWithLobbyTokenFail(unsigned long long gatekey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 14, gatekey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbc220
void LobbyGateChannel::SendStartSessionWithNPTokenOk(unsigned long long clikey, char createInitialUserName,
                                                    id128 const& infoGateToken, unsigned long infoGatePubAddr,
                                                    unsigned short infoGatePubPort, bool enableGrade,
                                                    GradeService const& gradeService, bool teen,
                                                    long long closestEndTime, int remainJumpingCharacterCreationQuota,
                                                    GameAccountExpInfo const& accExpInfo)
{
    FragmentPacket fp(10, "hiqQoihCiiiii;CiiQiqq;Qqiqiq");
    fp.packet.Allocate(&fp.composer);
    if (fp.Compose(5, clikey, static_cast<unsigned int>(createInitialUserName), infoGateToken, infoGatePubAddr,
                   infoGatePubPort) == 0)
        return;
    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 2u)
        fp.packet.Allocate(&fp.composer);
    fp.composer.PushRepeatCount(&fp.packet);
    if (enableGrade)
    {
        if (!gradeService.FetchGradeLevel(&fp))
            return;
        RepeatPacketComposer& composer = fp.composer;
        int start = composer.start[composer.top] + 1;
        if (composer.subTop < 0)
            composer.index = start;
        else
            composer.sub[composer.subTop].index = start;
        ++*composer.counts[composer.top];
    }
    fp.composer.PopRepeatCount();
    if (enableGrade)
    {
        if (!gradeService.FetchGameGradeList(&fp))
            return;
    }
    else
    {
        if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 2u)
            fp.packet.Allocate(&fp.composer);
        fp.composer.PushRepeatCount(&fp.packet);
        fp.composer.PopRepeatCount();
    }
    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 0xDu)
        fp.packet.Allocate(&fp.composer);
    if (fp.Compose(3, teen, closestEndTime, remainJumpingCharacterCreationQuota) != 0)
    {
        if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 0x14u)
            fp.packet.Allocate(&fp.composer);
        if (fp.Compose(3, accExpInfo._info.exp, static_cast<unsigned int>(accExpInfo._info.expQuotaPerDay),
                       accExpInfo._info.lastUpdateTime) == 0)
            return;
        if (fp.packet.Splitter != nullptr)
            fp.packet.Splitter->Finalize(fp.packet.CurHeader);
        Send(&fp.packet);
    }
}

// 0xbc540
void LobbyGateChannel::SendStartSessionWithNPTokenFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 11, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbc610
void LobbyGateChannel::SendStartSessionWithLobbyTokenOk(unsigned long long clikey, bool enableGrade,
                                                        GradeService const& gradeService,
                                                        int remainJumpingCharacterCreationQuota,
                                                        GameAccountExpInfo const& accExpInfo)
{
    FragmentPacket fp(16, "hiqCiiiii;CiiQiqq;iqiq");
    fp.packet.Allocate(&fp.composer);
    if (fp.Compose(1, clikey) == 0)
        return;
    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 2u)
        fp.packet.Allocate(&fp.composer);
    fp.composer.PushRepeatCount(&fp.packet);
    if (enableGrade)
    {
        if (!gradeService.FetchGradeLevel(&fp))
            return;
        RepeatPacketComposer& composer = fp.composer;
        int start = composer.start[composer.top] + 1;
        if (composer.subTop < 0)
            composer.index = start;
        else
            composer.sub[composer.subTop].index = start;
        ++*composer.counts[composer.top];
    }
    fp.composer.PopRepeatCount();
    if (enableGrade)
    {
        if (!gradeService.FetchGameGradeList(&fp))
            return;
    }
    else
    {
        if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 2u)
            fp.packet.Allocate(&fp.composer);
        fp.composer.PushRepeatCount(&fp.packet);
        fp.composer.PopRepeatCount();
    }
    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 4u)
        fp.packet.Allocate(&fp.composer);
    if (fp.Compose(1, remainJumpingCharacterCreationQuota) != 0)
    {
        if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 0x14u)
            fp.packet.Allocate(&fp.composer);
        if (fp.Compose(3, accExpInfo._info.exp, static_cast<unsigned int>(accExpInfo._info.expQuotaPerDay),
                       accExpInfo._info.lastUpdateTime) == 0)
            return;
        if (fp.packet.Splitter != nullptr)
            fp.packet.Splitter->Finalize(fp.packet.CurHeader);
        Send(&fp.packet);
    }
}

// 0xbc8f0
void LobbyGateChannel::SendStartSessionWithLobbyTokenFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 17, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbc9c0
void LobbyGateChannel::SendCloseAnonymousSessionNotify(unsigned long long gatekey)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hq", 20, gatekey))
        Send(&p);
}

// 0xbca80
void LobbyGateChannel::SendCloseSessionNotify(unsigned long long clikey)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hq", 21, clikey))
        Send(&p);
}

// 0xbcb40
void LobbyGateChannel::SendKickNotify(unsigned long long clikey, char reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqQ", 22, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbcc10
void LobbyGateChannel::SendGetCharacterInfoListFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 37, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbcce0
void LobbyGateChannel::SendGetCharacterInfoFail(unsigned long long clikey, id128 const& slotid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqoE", 40, clikey, &slot, static_cast<int>(reason)))
        Send(&p);
}

// 0xbcdd0
void LobbyGateChannel::SendCreateCharacterOk(unsigned long long clikey, unsigned long long pcId, id128 const& slotid, short wid, wchar_t const* characterName, char* showcaseData, short showcaseDataSize, long long lastPlayEndDate, char jumpingCharacterState, long long deleteRemainTime, int)  // LIFT: the last int is unused in the binary
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqqohsbqQQii", 45, clikey, pcId, &slot, static_cast<int>(wid), characterName, showcaseData, static_cast<int>(showcaseDataSize), lastPlayEndDate, 1, static_cast<int>(jumpingCharacterState), 0, static_cast<int>(deleteRemainTime)))
        Send(&p);
}

// 0xbcf40
void LobbyGateChannel::SendCreateCharacterFail(unsigned long long clikey, id128 const& slotid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqoE", 46, clikey, &slot, static_cast<int>(reason)))
        Send(&p);
}

// 0xbd030
void LobbyGateChannel::SendDeleteCharacterOk(unsigned long long clikey, id128 const& slotid, char deleteActionType, long deleteRemainTime)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqoQi", 48, clikey, &slot, static_cast<int>(deleteActionType), static_cast<int>(deleteRemainTime)))
        Send(&p);
}

// 0xbd130
void LobbyGateChannel::SendDeleteCharacterFail(unsigned long long clikey, id128 const& slotid, Character::ClientState state, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    char stateCode = 0;
    if (state == Character::CLIENTSTATE_IN_USUAL)
        stateCode = 1;
    else if (state == Character::CLIENTSTATE_IN_WAIT_DELETION)
        stateCode = 2;
    else if (state == Character::CLIENTSTATE_IN_STUCK)
        stateCode = 3;
    if (0 != p.Compose("hqoQE", 49, clikey, &slot, static_cast<int>(stateCode), static_cast<int>(reason)))
        Send(&p);
}

// 0xbd250
void LobbyGateChannel::SendCancelWaitCharacterDeletionOk(unsigned long long clikey, id128 const& slotid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqo", 52, clikey, &slot))
        Send(&p);
}

// 0xbd330
void LobbyGateChannel::SendCancelWaitCharacterDeletionFail(unsigned long long clikey, id128 const& slotid, Character::ClientState state, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    char stateCode = 0;
    if (state == Character::CLIENTSTATE_IN_USUAL)
        stateCode = 1;
    else if (state == Character::CLIENTSTATE_IN_WAIT_DELETION)
        stateCode = 2;
    else if (state == Character::CLIENTSTATE_IN_STUCK)
        stateCode = 3;
    if (0 != p.Compose("hqoQE", 53, clikey, &slot, static_cast<int>(stateCode), static_cast<int>(reason)))
        Send(&p);
}

// 0xbd450
void LobbyGateChannel::SendEndWaitCharacterDeletionNotify(unsigned long long clikey, id128 const& slotid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqo", 50, clikey, &slot))
        Send(&p);
}

// 0xbd530
void LobbyGateChannel::SendGetEnterWorldTokenFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 26, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbd600
void LobbyGateChannel::SendGetEnterWorldTokenOk(unsigned long long clikey, unsigned long long token, short worldId)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqh", 25, clikey, token, static_cast<int>(worldId)))
        Send(&p);
}

// 0xbd6e0
void LobbyGateChannel::SendStartWaitNotify(unsigned long long clikey, WaitInfo const& waitinfo)
{
    RepeatPacketComposer rpc;  // LIFT: inlined constructor
    rpc.format = nullptr;
    rpc.len = 0;
    rpc.index = 0;
    rpc.SetFormat("hqiiCch;", 0);
    rpc.top = -1;
    rpc.subTop = -1;
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (p.Compose(&rpc, 1, 27) == 0)
        return;
    if (p.Compose(&rpc, 3, clikey, waitinfo.turn, static_cast<int>(waitinfo.avg)) == 0)
        return;
    rpc.PushRepeatCount(&p);
    for (int i = 0; i < waitinfo.waitQueueInfoCount; ++i)
    {
        WaitQueueInfo const& info = waitinfo.waitQueueInfo[i];
        if (p.Compose(&rpc, 2, static_cast<unsigned int>(static_cast<signed char>(info.queueType)), static_cast<int>(info.waitingPlayerCount)) == 0)
            return;
        rpc.IncRepeatCount();
    }
    rpc.PopRepeatCount();
    if (p.Splitter != nullptr)
        p.Splitter->Finalize(p.CurHeader);
    Send(&p);
}

// 0xbd9c0
void LobbyGateChannel::SendGetWaitInfoOk(unsigned long long clikey, WaitInfo const& waitinfo)
{
    RepeatPacketComposer rpc;  // LIFT: inlined constructor
    rpc.format = nullptr;
    rpc.len = 0;
    rpc.index = 0;
    rpc.SetFormat("hqiiCch;", 0);
    rpc.top = -1;
    rpc.subTop = -1;
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (p.Compose(&rpc, 1, 29) == 0)
        return;
    if (p.Compose(&rpc, 3, clikey, waitinfo.turn, static_cast<int>(waitinfo.avg)) == 0)
        return;
    rpc.PushRepeatCount(&p);
    for (int i = 0; i < waitinfo.waitQueueInfoCount; ++i)
    {
        WaitQueueInfo const& info = waitinfo.waitQueueInfo[i];
        if (p.Compose(&rpc, 2, static_cast<unsigned int>(static_cast<signed char>(info.queueType)), static_cast<int>(info.waitingPlayerCount)) == 0)
            return;
        rpc.IncRepeatCount();
    }
    rpc.PopRepeatCount();
    if (p.Splitter != nullptr)
        p.Splitter->Finalize(p.CurHeader);
    Send(&p);
}

// 0xbdca0
void LobbyGateChannel::SendGetWaitInfoFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 30, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbdd70
void LobbyGateChannel::SendGiveupWaitOk(unsigned long long clikey)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hq", 32, clikey))
        Send(&p);
}

// 0xbde30
void LobbyGateChannel::SendGiveupWaitFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 33, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbdf00
void LobbyGateChannel::SendEndWaitNotify(unsigned long long clikey, unsigned long long token)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqq", 34, clikey, token))
        Send(&p);
}

// 0xbdfd0
void LobbyGateChannel::SendGetChargeInfoOk(unsigned long long clikey, char chargeBaseType, char personalInfo, long remainPlayTime, short reservations, char valueType, unsigned int itemId, char computationBasis, char pcCafeInfo, char ipKind)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqQQihQiQQQ", 61, clikey, static_cast<int>(chargeBaseType), static_cast<int>(personalInfo), static_cast<int>(remainPlayTime), static_cast<int>(reservations), static_cast<int>(valueType), itemId, static_cast<int>(computationBasis), static_cast<int>(pcCafeInfo), static_cast<int>(ipKind)))
        Send(&p);
}

// 0xbe120
void LobbyGateChannel::SendGetChargeInfoFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 62, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbe1f0
void LobbyGateChannel::SendRecoverCharacterOk(unsigned long long clikey, id128 const& slotid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqo", 55, clikey, &slot))
        Send(&p);
}

// 0xbe2d0
void LobbyGateChannel::SendRecoverCharacterFail(unsigned long long clikey, id128 const& slotid, Character::ClientState state, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    char stateCode = 0;
    if (state == Character::CLIENTSTATE_IN_USUAL)
        stateCode = 1;
    else if (state == Character::CLIENTSTATE_IN_WAIT_DELETION)
        stateCode = 2;
    else if (state == Character::CLIENTSTATE_IN_STUCK)
        stateCode = 3;
    if (0 != p.Compose("hqoQE", 56, clikey, &slot, static_cast<int>(stateCode), static_cast<int>(reason)))
        Send(&p);
}

// 0xbe3f0
void LobbyGateChannel::SendBindCharacterSlotFail(unsigned long long clikey, id128 const& slotid, unsigned long long pcId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqoqE", 59, clikey, &slot, pcId, static_cast<int>(reason)))
        Send(&p);
}

// 0xbe4f0
void LobbyGateChannel::SendAccountInventoryNotify(unsigned long long clikey, char notificationType, unsigned long long goodsItemInsIdMin)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqQq", 63, clikey, static_cast<int>(notificationType), goodsItemInsIdMin))
        Send(&p);
}

// 0xbe5d0
void LobbyGateChannel::SendGetGoodsCountOk(unsigned long long clikey, int count)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqi", 65, clikey, count))
        Send(&p);
}

// 0xbe6a0
void LobbyGateChannel::SendGetGoodsCountFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 66, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbe770
void LobbyGateChannel::SendListGoodsOk(unsigned long long clikey, Goods* goodsList, int goodsCount)
{
    FragmentPacket fp(68, "hiqCqiQQqqssissbbCiiibb;;");
    fp.packet.Allocate(&fp.composer);
    fp.Compose(1, clikey);
    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 2u)
        fp.packet.Allocate(&fp.composer);
    fp.composer.PushRepeatCount(&fp.packet);
    if (goodsList != nullptr && goodsCount > 0)
    {
        for (int i = 0; i < goodsCount; ++i)
        {
            if (!goodsList[i].Fetch(&fp))
            {
                Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 516,
                           L"[lobby-gate], send list-goods-count ok fail; compose packet fail, cli-key:0x%I64X",
                           clikey);
                return;
            }
            RepeatPacketComposer& composer = fp.composer;
            int start = composer.start[composer.top] + 1;
            if (composer.subTop < 0)
                composer.index = start;
            else
                composer.sub[composer.subTop].index = start;
            ++*composer.counts[composer.top];
        }
    }
    fp.composer.PopRepeatCount();
    if (fp.packet.Splitter != nullptr)
        fp.packet.Splitter->Finalize(fp.packet.CurHeader);
    Send(&fp.packet);
}

// 0xbe980
void LobbyGateChannel::SendListGoodsFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 69, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbea50
void LobbyGateChannel::SendTakeGoodsOk(unsigned long long clikey, unsigned long long goodsId, LobbyServiceItem* items,
                                       int itemCount)
{
    FragmentPacket fp(71, "hiqqCqqqiQ;");
    fp.packet.Allocate(&fp.composer);
    if (fp.Compose(2, clikey, goodsId) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 547,
                   L"[lobby-gate], send take-goods-ok fail; compose cli-key & goods-id fail, cli-key:0x%I64X, "
                   L"goods-id:0x%I64X",
                   clikey, goodsId);
        return;
    }
    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 2u)
        fp.packet.Allocate(&fp.composer);
    fp.composer.PushRepeatCount(&fp.packet);
    if (items != nullptr && itemCount > 0)
    {
        for (int i = 0; i < itemCount; ++i)
        {
            if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 0x1Du)
                fp.packet.Allocate(&fp.composer);
            if (fp.Compose(5, items[i].ownerPcId, items[i].instanceId, items[i].labelId,
                           static_cast<int>(items[i].dataId), static_cast<int>(items[i].state)) == 0)
            {
                Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 561,
                           L"[lobby-gate], send take-goods-ok fail; compose #%d item fail, item-instance-id:0x%I64X, "
                           L"cli-key:0x%I64X",
                           i, items[i].instanceId, clikey);
                return;
            }
            RepeatPacketComposer& composer = fp.composer;
            int start = composer.start[composer.top] + 1;
            if (composer.subTop < 0)
                composer.index = start;
            else
                composer.sub[composer.subTop].index = start;
            ++*composer.counts[composer.top];
        }
    }
    fp.composer.PopRepeatCount();
    if (fp.packet.Splitter != nullptr)
        fp.packet.Splitter->Finalize(fp.packet.CurHeader);
    Send(&fp.packet);
}

// 0xbed00
void LobbyGateChannel::SendTakeGoodsFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 72, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbedd0
void LobbyGateChannel::SendListLobbyServiceItemInfoOk(unsigned long long clikey, char searchType, int searchCount,
                                                      LobbyServiceItem* items, int itemCount)
{
    FragmentPacket fp(74, "hiqQiCqqqiQ;");
    fp.packet.Allocate(&fp.composer);
    fp.Compose(3, clikey, static_cast<unsigned int>(searchType), searchCount);
    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 2u)
        fp.packet.Allocate(&fp.composer);
    fp.composer.PushRepeatCount(&fp.packet);
    if (items != nullptr && itemCount > 0)
    {
        for (int i = 0; i < itemCount; ++i)
        {
            if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 0x1Du)
                fp.packet.Allocate(&fp.composer);
            if (fp.Compose(5, items[i].ownerPcId, items[i].instanceId, items[i].labelId,
                           static_cast<int>(items[i].dataId), static_cast<int>(items[i].state)) == 0)
            {
                Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 604,
                           L"[lobby-gate], send list lobby service item ok fail; compose #%d item fail, pcid:0x%I64X, "
                           L"label-id:0x%I64X, item-instance-id:0x%I64X, cli-key:0x%I64X",
                           i, items[i].ownerPcId, items[i].labelId, items[i].instanceId, clikey);
                return;
            }
            RepeatPacketComposer& composer = fp.composer;
            int start = composer.start[composer.top] + 1;
            if (composer.subTop < 0)
                composer.index = start;
            else
                composer.sub[composer.subTop].index = start;
            ++*composer.counts[composer.top];
        }
    }
    fp.composer.PopRepeatCount();
    if (fp.packet.Splitter != nullptr)
        fp.packet.Splitter->Finalize(fp.packet.CurHeader);
    Send(&fp.packet);
}

// 0xbf080
void LobbyGateChannel::SendListLobbyServiceItemInfoFail(unsigned long long clikey, char searchType, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqQE", 75, clikey, static_cast<int>(searchType), static_cast<int>(reason)))
        Send(&p);
}

// 0xbf160
void LobbyGateChannel::SendGetLobbyServiceItemInfoOk(unsigned long long clikey, LobbyServiceItem const& item)
{
    PacketComposer pcr;  // LIFT: inlined constructor
    pcr.format = nullptr;
    pcr.len = 0;
    pcr.index = 0;
    pcr.SetFormat("hqqqqiQ", 0);
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose(&pcr, 2, 77, clikey) &&
        0 != p.Compose(&pcr, 5, item.ownerPcId, item.instanceId, item.labelId, item.dataId, static_cast<int>(item.state)))
        Send(&p);
}

// 0xbf2e0
void LobbyGateChannel::SendGetLobbyServiceItemInfoFail(unsigned long long clikey, unsigned long long itemInstanceId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqE", 78, clikey, itemInstanceId, static_cast<int>(reason)))
        Send(&p);
}

// 0xbf3c0
void LobbyGateChannel::SendGetServiceEntryListFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 81, clikey, static_cast<int>(reason)))
        Send(&p);
}

// 0xbf490
void LobbyGateChannel::SendChangeCharacterAppearanceWithAccountInventoryItemOk(unsigned long long clikey, id128 const& slotid, char* newShowcaseData, short newShowcaseDataSize, unsigned long long labelId, unsigned long long itemInstanceId)
{
    if (newShowcaseData == nullptr || newShowcaseDataSize < 0)
        return;
    Packet packet;  // LIFT: inlined constructor
    packet.CurHeader = nullptr;
    packet.Splitter = nullptr;
    packet.ListHead = nullptr;
    packet.ListTail = nullptr;
    packet.IsFragmentPacket = false;
    packet.FragmentPacketCmd = 0;
    packet.Allocate();
    id128 slot = slotid;
    if (0 != packet.Compose("hqobqq", 83, clikey, &slot, newShowcaseData, static_cast<int>(newShowcaseDataSize), labelId, itemInstanceId))
        Send(&packet);
}

// 0xbf5a0
void LobbyGateChannel::SendChangeCharacterAppearanceWithAccountInventoryItemFail(unsigned long long clikey, id128 const& slotid, unsigned long long labelId, unsigned long long itemInstanceId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqoqqE", 84, clikey, &slot, labelId, itemInstanceId, static_cast<int>(reason)))
        Send(&p);
}

// 0xbf6b0
void LobbyGateChannel::SendChangeCharacterSexWithAccountInventoryItemOk(unsigned long long clikey, id128 const& slotid, char* newShowcaseData, short newShowcaseDataSize, unsigned long long labelId, unsigned long long itemInstanceId)
{
    if (newShowcaseData == nullptr || newShowcaseDataSize < 0)
        return;
    Packet packet;  // LIFT: inlined constructor
    packet.CurHeader = nullptr;
    packet.Splitter = nullptr;
    packet.ListHead = nullptr;
    packet.ListTail = nullptr;
    packet.IsFragmentPacket = false;
    packet.FragmentPacketCmd = 0;
    packet.Allocate();
    id128 slot = slotid;
    if (0 != packet.Compose("hqobqq", 86, clikey, &slot, newShowcaseData, static_cast<int>(newShowcaseDataSize), labelId, itemInstanceId))
        Send(&packet);
}

// 0xbf7c0
void LobbyGateChannel::SendChangeCharacterSexWithAccountInventoryItemFail(unsigned long long clikey, id128 const& slotid, unsigned long long labelId, unsigned long long itemInstanceId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqoqqE", 87, clikey, &slot, labelId, itemInstanceId, static_cast<int>(reason)))
        Send(&p);
}

// 0xbf8d0
void LobbyGateChannel::SendChangeCharacterRaceWithAccountInventoryItemOk(unsigned long long clikey, id128 const& slotid, char* newShowcaseData, short newShowcaseDataSize, unsigned long long labelId, unsigned long long itemInstanceId)
{
    if (newShowcaseData == nullptr || newShowcaseDataSize < 0)
        return;
    Packet packet;  // LIFT: inlined constructor
    packet.CurHeader = nullptr;
    packet.Splitter = nullptr;
    packet.ListHead = nullptr;
    packet.ListTail = nullptr;
    packet.IsFragmentPacket = false;
    packet.FragmentPacketCmd = 0;
    packet.Allocate();
    id128 slot = slotid;
    if (0 != packet.Compose("hqobqq", 89, clikey, &slot, newShowcaseData, static_cast<int>(newShowcaseDataSize), labelId, itemInstanceId))
        Send(&packet);
}

// 0xbf9e0
void LobbyGateChannel::SendChangeCharacterRaceWithAccountInventoryItemFail(unsigned long long clikey, id128 const& slotid, unsigned long long labelId, unsigned long long itemInstanceId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqoqqE", 90, clikey, &slot, labelId, itemInstanceId, static_cast<int>(reason)))
        Send(&p);
}

// 0xbfaf0
void LobbyGateChannel::SendRenameCharacterWithAccountInventoryItemOk(unsigned long long clikey, id128 const& slotid, wchar_t const* newName, unsigned long long labelId, unsigned long long itemInstanceId)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqosqq", 92, clikey, &slot, newName, labelId, itemInstanceId))
        Send(&p);
}

// 0xbfc00
void LobbyGateChannel::SendRenameCharacterWithAccountInventoryItemFail(unsigned long long clikey, id128 const& slotid, unsigned long long labelId, unsigned long long itemInstanceId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqoqqE", 93, clikey, &slot, labelId, itemInstanceId, static_cast<int>(reason)))
        Send(&p);
}

// 0xbfd10
void LobbyGateChannel::SendAddSlotWithAccountInventoryItemOk(unsigned long long clikey, unsigned long long labelId, unsigned long long itemInstanceId, id128 const& slotid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    id128 slot = slotid;
    if (0 != p.Compose("hqqqo", 95, clikey, labelId, itemInstanceId, &slot))
        Send(&p);
}

// 0xbfe10
void LobbyGateChannel::SendAddSlotWithAccountInventoryItemFail(unsigned long long clikey, unsigned long long labelId, unsigned long long itemInstanceId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqqE", 96, clikey, labelId, itemInstanceId, static_cast<int>(reason)))
        Send(&p);
}

// 0xbff00
void LobbyGateChannel::SendChangeUserNameWithAccountInventoryItemOk(unsigned long long clikey, wchar_t const* newUserName, unsigned long long labelId, unsigned long long itemInstanceId, unsigned int itemDataId)
{
    if (newUserName == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 802,
                   L"[lobby-gate], send change-user-name-with-account-inventory-item-ok fail; null new-user-name, cli-key:0x%I64X", clikey);
        return;
    }
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqsqqi", 98, clikey, newUserName, labelId, itemInstanceId, itemDataId))
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 812,
                   L"[lobby-gate], send change-user-name-with-account-inventory-item-ok fail; compose fail, cli-key:0x%I64X", clikey);
    else
        Send(&p);
}

// 0xc0050
void LobbyGateChannel::SendChangeUserNameWithAccountInventoryItemFail(unsigned long long clikey, unsigned long long labelId, unsigned long long itemInstanceId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqqE", 99, clikey, labelId, itemInstanceId, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 827,
                   L"[lobby-gate], send change-user-name-with-account-inventory-item-fail fail; compose fail, cli-key:0x%I64X", clikey);
    else
        Send(&p);
}

// 0xc0160
void LobbyGateChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(unsigned long long clikey, unsigned long long labelId, unsigned long long itemInstanceId, int remainQuota)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqqi", 101, clikey, labelId, itemInstanceId, remainQuota))
        Send(&p);
}

// 0xc0250
void LobbyGateChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(unsigned long long clikey, unsigned long long labelId, unsigned long long itemInstanceId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqqE", 102, clikey, labelId, itemInstanceId, static_cast<int>(reason)))
        Send(&p);
}

// 0xc0340
void LobbyGateChannel::SendCreateInitialUserNameOk(unsigned long long clikey, wchar_t const* newUserName)
{
    if (newUserName == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 862,
                   L"[lobby-gate], send create-initial-user-name-ok fail; null new-user-name, cli-key:0x%I64X", clikey);
        return;
    }
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqs", 104, clikey, newUserName))
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 874,
                   L"[lobby-gate], send create-initial-user-name-ok fail; compose fail, cli-key:0x%I64X, new-user-name:%s", clikey, newUserName);
    else
        Send(&p);
}

// 0xc0460
void LobbyGateChannel::SendCreateInitialUserNameFail(unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    // LIFT: the original log text says "ok" in the fail function (0xc0460, line 891). Kept as is.
    if (0 == p.Compose("hqE", 105, clikey, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 891,
                   L"[lobby-gate], send create-initial-user-name-ok fail; compose fail, cli-key:0x%I64X", clikey);
    else
        Send(&p);
}

// 0xc0550
void LobbyGateChannel::SendActivateGradeOk(unsigned long long clikey, int gameGradeKey, int gradeId, long long effectiveFrom, long long effectiveTo)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqiiqq", 107, clikey, gameGradeKey, gradeId, effectiveFrom, effectiveTo))
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 904,
                   L"[lobby-gate], send activate-grade-ok fail; compose fail, cli-key:0x%I64X, game-grade-key:%d, grade-id:%d",
                   clikey, gameGradeKey, gradeId);
    else
        Send(&p);
}

// 0xc0670
void LobbyGateChannel::SendActivateGradeFail(unsigned long long clikey, int keyType, int key, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqQiE", 108, clikey, keyType, key, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 917,
                   L"[lobby-gate], send activate-grade-fail fail; compose fail, cli-key:0x%I64X, key-type:%d, key:%d, reason:%d",
                   clikey, keyType, key, static_cast<int>(reason));
    else
        Send(&p);
}

// 0xc0790
void LobbyGateChannel::SendChangedGradeNotify(unsigned long long clikey, int gameGradeKey, int gradeId, bool activation, int gradeCount, long long totalEffectiveFrom, long long totalEffectiveTo, wchar_t const* reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    // LIFT: The binary compares the reason text with the five known names. Other text (and null or empty text) gives 0.
    char reasonCode = 0;
    if (reason != nullptr && reason[0] != L'\0')
    {
        if (wcscmp(reason, L"Activated") == 0)
            reasonCode = 1;
        else if (wcscmp(reason, L"ActivatedWithAdding") == 0)
            reasonCode = 2;
        else if (wcscmp(reason, L"Added") == 0)
            reasonCode = 3;
        else if (wcscmp(reason, L"Deleted") == 0)
            reasonCode = 4;
        else if (wcscmp(reason, L"DeletedAndExhausted") == 0)
            reasonCode = 5;
    }

    if (0 != p.Compose("hqiiQiqqQ", 109, clikey, gameGradeKey, gradeId, static_cast<int>(activation), gradeCount, totalEffectiveFrom, totalEffectiveTo, static_cast<int>(reasonCode)))
        Send(&p);
}

// 0xc0970
void LobbyGateChannel::SendChangedGradeLevelNotify(unsigned long long clikey, int levelId, int accumulateGradeScore, int minimumLevelScore, int maximumLevelScore, int maximumGradeScore)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqiiiii", 110, clikey, levelId, accumulateGradeScore, minimumLevelScore, maximumLevelScore, maximumGradeScore))
        Send(&p);
}

// 0xc0aa0
LobbyGateChannelManager::~LobbyGateChannelManager()
{
    // LIFT: 0xc0aa0 loop at LobbyGateChannel.cpp:985 releases each channel. The explicit list destructor call is
    // inlined (SharedChannel.cpp:190). The member destructors run it a second time (original sequence).
    SharedChannel** channels = _channels._channels;
    for (SharedChannel** i = channels + _channels._idsize; channels != i; ++channels)
    {
        if (*channels != nullptr)
            (*channels)->removeReferenceCount(LOBBYGATE_FILE, 985);
    }
    _channels.~SharedChannelList();
}

// 0xc0b80
bool LobbyGateChannelManager::Add(LobbyGateChannel* channel)
{
    if (channel != nullptr && channel->_rawChannel != nullptr &&
        static_cast<unsigned short>(channel->_rawChannel->GetId()) != 0)
    {
        bool result = false;
        _lock.Enter();
        if (_channels.Set(channel))
        {
            channel->addReferenceCount(LOBBYGATE_FILE, 1008);
            result = true;
        }
        _lock.Leave();
        return result;
    }
    Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1002, L"[lobby-gate], add fail; invalid parameter");
    return false;
}

// 0xc0c40
void LobbyGateChannelManager::Remove(short wid)
{
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1018, L"[lobby-gate], remove fail; invalid wid");
        return;
    }
    _lock.Enter();
    long long id = wid;
    int index = wid - static_cast<int>(_channels._idmin);
    if (index < 0 || index >= _channels._idsize)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 200,
                   L"[shared-channel-list], acquire fail; id out of range, id:%I64d", id);
    }
    else
    {
        SharedChannel* channel = _channels._channels[index];
        if (channel != nullptr)
        {
            int removeIndex = static_cast<int>(id) - static_cast<int>(_channels._idmin);
            if (removeIndex < 0 || removeIndex >= _channels._idsize)
            {
                Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 234,
                           L"[shared-channel-list], remove fail; id out of range, id:%I64d", id);
            }
            else if (_channels._channels[removeIndex] != nullptr)
            {
                _channels._channels[removeIndex] = nullptr;
                --_channels._size;
            }
            channel->removeReferenceCount(LOBBYGATE_FILE, 1026);
        }
    }
    _lock.Leave();
}

// 0xc0d50
LobbyGateChannel* LobbyGateChannelManager::Acquire(short wid)
{
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1034, L"[lobby-gate], acquire fail; invalid wid");
        return nullptr;
    }
    _lock.Enter();
    SharedChannel* channel;
    int index = wid - static_cast<int>(_channels._idmin);
    if (index < 0 || index >= _channels._idsize)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 200,
                   L"[shared-channel-list], acquire fail; id out of range, id:%I64d", static_cast<long long>(wid));
        channel = nullptr;
    }
    else
    {
        channel = _channels._channels[index];
        if (channel != nullptr)
            channel->addReferenceCount(LOBBYGATE_FILE, 1041);
    }
    _lock.Leave();
    return static_cast<LobbyGateChannel*>(channel);
}

// 0xc0e20
void LobbyGateChannelManager::BroadcastAnnounceNotify(wchar_t const* message)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hs", 5, message))
    {
        Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1074,
                   L"[lobby-gate], broadcast announce notify fail; compose fail, message:%s", message);
        return;
    }
    // LIFT: the original calls 0x2ef40 with this. InfoGateChannelManager::Broadcast and the LobbyGateChannelManager
    // body are the same (folded). Both classes have the same layout (0x48). Precedent: LobbyDaemon.cpp:188.
    if (!reinterpret_cast<InfoGateChannelManager*>(this)->Broadcast(&p))
    {
        Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1080,
                   L"[lobby-gate], broadcast announce notify fail; broadcast fail, message:%s", message);
        return;
    }
}

// 0xc0f20
bool LobbyGateChannelManager::OnAccept(Session const* session) const
{
    unsigned long long id = session != nullptr ? session->_id : 0;
    // BUG: 0xc0f20 checks session for nullptr only for the id. It reads session->_connection without a check.
    Connection* connection = session->_connection;
    int portNumber = connection->_portNumber;
    Log::Write(Log::LT_DEBUG, LOBBYGATE_FILE, 1118,
               L"[lobby-gate], accept session, session-id:0x%I64X, ip-address:%s, port:%d", id,
               Network::GetAddressStringW(connection->_ip), portNumber);
    return true;
}

// 0xc0f80
bool LobbyGateChannelManager::OnConnect(Session const* session, bool) const
{
    unsigned long long id = session != nullptr ? session->_id : 0;
    // BUG: 0xc0f80 checks session for nullptr only for the id. It reads session->_connection without a check.
    Connection* connection = session->_connection;
    int portNumber = connection->_portNumber;
    Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1124,
               L"== CRASH == [lobby-gate], connect session forbidden, session-id:0x%I64X, ip-address:%s, port:%d", id,
               Network::GetAddressStringW(connection->_ip), portNumber);
    connection = session->_connection;
    portNumber = connection->_portNumber;
    AlertSender::Write(LOBBYGATE_FILE, 1124,
                       L"== CRASH == [lobby-gate], connect session forbidden, session-id:0x%I64X, ip-address:%s, port:%d",
                       session->_id, Network::GetAddressStringW(connection->_ip), portNumber);
    return false;
}

// 0xc1030
void LobbyGateChannelManager::OnClose(Session const* session, bool) const
{
    Channel* channel = session->GetChannel();
    if (channel != nullptr)
    {
        SharedChannel* shared = static_cast<SharedChannel::RawChannel*>(channel)->_owner;
        short closedWid = 0;
        if (shared != nullptr)
        {
            short wid = 0;
            Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1138, L"[lobby-gate], lobby-gate channel closed, gate-wid:%d",
                       shared->_rawChannel != nullptr ? static_cast<int>(static_cast<short>(shared->_rawChannel->GetId())) : 0);
            if (shared->_rawChannel != nullptr)
                closedWid = static_cast<short>(shared->_rawChannel->GetId());
            if (shared->_rawChannel != nullptr)
                wid = static_cast<short>(shared->_rawChannel->GetId());
            const_cast<LobbyGateChannelManager*>(this)->Remove(wid);
        }
        else
        {
            Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1143,
                       L"== CRASH == [lobby-gate], lobby-gate channel closed exception; raw-channel has no shared-channel, channel-id:%I64d",
                       channel->GetId());
            AlertSender::Write(LOBBYGATE_FILE, 1143,
                               L"== CRASH == [lobby-gate], lobby-gate channel closed exception; raw-channel has no shared-channel, channel-id:%I64d",
                               channel->GetId());
        }
        LobbyDaemon::_instance->_clisessionMgr->OnCloseLobbyGateChannel(closedWid);
        channel->removeReferenceCount(SESSION_FILE, 1059);
    }
    Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1150, L"[lobby-gate], session closed, session-id:0x%I64X", session->_id);
}

// 0xc11d0
bool LobbyGateChannelManager::PacketHandler(Session const* session, Packet const* packet) const
{
    if (session == nullptr || packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1159,
                   L"== CRASH == [lobby-gate], handle packet failed; invalid parameter");
        AlertSender::Write(LOBBYGATE_FILE, 1159,
                           L"== CRASH == [lobby-gate], handle packet failed; invalid parameter");
        return false;
    }

    Packet::Header const* header = packet->CurHeader;
    unsigned short bodySize = static_cast<unsigned short>(header->size - 2);
    if (bodySize < 2u)
    {
        Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1165,
                   L"[lobby-gate], handle packet failed; invalid packet size, size:%d, session-id:0x%I64X",
                   static_cast<int>(bodySize), session->_id);
        return false;
    }

    short cmd = header[1].size;
    if (static_cast<unsigned short>(cmd - 1) > 109u)
    {
        Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1173,
                   L"[lobby-gate], handle packet failed; invalid packet command, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        return false;
    }

    LobbyLobbyGatePacketHandlerDef const* def = &LobbyLobbyGatePacketLobbySideHandlerList[cmd];
    if (def->handler == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1180,
                   L"[lobby-gate], handle packet failed; handler not exists, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        return false;
    }

    bool result = false;
    Channel* channel = session->GetChannel();
    void* iocp = nullptr;
    SharedChannel* shared = channel != nullptr ? static_cast<SharedChannel::RawChannel*>(channel)->_owner : nullptr;
    if (cmd == 1)
    {
        Log::Write(Log::LT_DEBUG, LOBBYGATE_FILE, 1191, L"[lobby-gate], handle begin, cmd:%d, session-id:0x%I64X", 1,
                   session->_id);
        result = reinterpret_cast<Daemon::PacketHandler>(def->handler)(session, packet);
        Log::Write(Log::LT_DEBUG, LOBBYGATE_FILE, 1193, L"[lobby-gate], handle end, cmd:%d, session-id:0x%I64X", 1,
                   session->_id);
    }
    else if (shared != nullptr && def->auth)
    {
        if (def->fragment)
        {
            bool completed = false;
            ConcatenatePacket(session, packet, completed);
            if (completed)
            {
                FragmentPacketConcatenater* concatenater = static_cast<FragmentPacketConcatenater*>(session->_concatenater);
                void* mem = Memory::_Manager[2]->Alloc(sizeof(FragmentPacketConcatenater), LOBBYGATE_FILE, 1204);
                FragmentPacketConcatenater* fpc = mem != nullptr ? ::new (mem) FragmentPacketConcatenater : nullptr;
                // BUG: 0xc11d0 fpc is not checked for nullptr before Copy when the alloc fails.
                if (fpc->Copy(concatenater))
                {
                    void* eventMem = Memory::_Manager[2]->Alloc(sizeof(SharedChannelFragmentPacketHandleEvent), LOBBYGATE_FILE, 1206);
                    SharedChannelFragmentPacketHandleEvent* event =
                        eventMem != nullptr
                            ? ::new (eventMem) SharedChannelFragmentPacketHandleEvent(
                                  shared, fpc, reinterpret_cast<bool (*)(SharedChannel*, FragmentPacketConcatenater*)>(def->handler))
                            : nullptr;
                    iocp = Network::iocpHandle();
                    PostQueuedCompletionStatus(iocp, 0, reinterpret_cast<ULONG_PTR>(event), nullptr);
                }
                else
                {
                    if (shared->_rawChannel != nullptr)
                        iocp = reinterpret_cast<void*>(shared->_rawChannel->GetId());
                    Log::Write(Log::LT_ERROR, LOBBYGATE_FILE, 1210,
                               L"[lobby-gate], handle packet fail; copy fragment packet concatenater fail, cmd:%d, channel-id:%I64d",
                               static_cast<int>(cmd), iocp);
                    if (fpc != nullptr)
                        fpc->~FragmentPacketConcatenater();  // LIFT: vtable slot 4 with flag 1 runs the destructor only.
                    Memory::_Manager[2]->Free(fpc, LOBBYGATE_FILE, 1211);
                }
                concatenater->Clear();
            }
        }
        else
        {
            void* mem = Memory::_Manager[2]->Alloc(sizeof(Packet), LOBBYGATE_FILE, 1218);
            Packet* copy = nullptr;
            if (mem != nullptr)
            {
                copy = static_cast<Packet*>(mem);
                copy->CurHeader = nullptr;
                copy->Splitter = nullptr;
                copy->ListHead = nullptr;
                copy->ListTail = nullptr;
                copy->IsFragmentPacket = false;
                copy->FragmentPacketCmd = 0;
            }
            // BUG: 0xc11d0 copy is not checked for nullptr before Allocate/Add when the alloc fails.
            copy->Allocate();
            copy->Add(&packet->CurHeader[1], static_cast<short>(packet->CurHeader->size - 2));
            void* eventMem = Memory::_Manager[2]->Alloc(sizeof(SharedChannelPacketHandleEvent), LOBBYGATE_FILE, 1221);
            SharedChannelPacketHandleEvent* event =
                eventMem != nullptr
                    ? ::new (eventMem) SharedChannelPacketHandleEvent(
                          shared, copy, reinterpret_cast<bool (*)(SharedChannel*, Packet const*)>(def->handler))
                    : nullptr;
            iocp = Network::iocpHandle();
            PostQueuedCompletionStatus(iocp, 0, reinterpret_cast<ULONG_PTR>(event), nullptr);
        }
        result = true;
    }

    if (channel != nullptr)
        channel->removeReferenceCount(SESSION_FILE, 1059);
    return result;
}
