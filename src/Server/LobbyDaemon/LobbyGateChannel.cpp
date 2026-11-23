// LobbyGateChannel.obj (LobbyDaemon PDB, 2019 + PDB). Part 1 lifted (ld-24 batches 1-2); the other functions are stubs. A stub is not a lift.
#include "LobbyGateChannel.h"
#include "FragmentPacket.h"
#include "GradeService.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyGoodsTypes.h"
#include "Log.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "StringUtil.h"
#include "WaitQueue.h"

#pragma comment(linker, "/INCLUDE:?SendInitSessionWithNPTokenOk@LobbyGateChannel@@QEAAX_K0AEBTid128@@1@Z")  // LIFT: keep until the caller is lifted (0xbbe90)
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
void LobbyGateChannel::SendInitSessionWithNPTokenOk(unsigned long long gatekey, unsigned long long clikey, id128 const& nptoken, id128 const& portalAccountId)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqoo", 7, gatekey, clikey, nptoken, portalAccountId))
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
void LobbyGateChannel::SendListLobbyServiceItemInfoFail(unsigned long long, char, short)
{
    LIFT_STUB(0xbf080);
}

// 0xbf160
void LobbyGateChannel::SendGetLobbyServiceItemInfoOk(unsigned long long, LobbyServiceItem const&)
{
    LIFT_STUB(0xbf160);
}

// 0xbf2e0
void LobbyGateChannel::SendGetLobbyServiceItemInfoFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbf2e0);
}

// 0xbf3c0
void LobbyGateChannel::SendGetServiceEntryListFail(unsigned long long, short)
{
    LIFT_STUB(0xbf3c0);
}

// 0xbf490
void LobbyGateChannel::SendChangeCharacterAppearanceWithAccountInventoryItemOk(unsigned long long, id128 const&, char*, short, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbf490);
}

// 0xbf5a0
void LobbyGateChannel::SendChangeCharacterAppearanceWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbf5a0);
}

// 0xbf6b0
void LobbyGateChannel::SendChangeCharacterSexWithAccountInventoryItemOk(unsigned long long, id128 const&, char*, short, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbf6b0);
}

// 0xbf7c0
void LobbyGateChannel::SendChangeCharacterSexWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbf7c0);
}

// 0xbf8d0
void LobbyGateChannel::SendChangeCharacterRaceWithAccountInventoryItemOk(unsigned long long, id128 const&, char*, short, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbf8d0);
}

// 0xbf9e0
void LobbyGateChannel::SendChangeCharacterRaceWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbf9e0);
}

// 0xbfaf0
void LobbyGateChannel::SendRenameCharacterWithAccountInventoryItemOk(unsigned long long, id128 const&, wchar_t const*, unsigned long long, unsigned long long)
{
    LIFT_STUB(0xbfaf0);
}

// 0xbfc00
void LobbyGateChannel::SendRenameCharacterWithAccountInventoryItemFail(unsigned long long, id128 const&, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbfc00);
}

// 0xbfd10
void LobbyGateChannel::SendAddSlotWithAccountInventoryItemOk(unsigned long long, unsigned long long, unsigned long long, id128 const&)
{
    LIFT_STUB(0xbfd10);
}

// 0xbfe10
void LobbyGateChannel::SendAddSlotWithAccountInventoryItemFail(unsigned long long, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xbfe10);
}

// 0xbff00
void LobbyGateChannel::SendChangeUserNameWithAccountInventoryItemOk(unsigned long long, wchar_t const*, unsigned long long, unsigned long long, unsigned int)
{
    LIFT_STUB(0xbff00);
}

// 0xc0050
void LobbyGateChannel::SendChangeUserNameWithAccountInventoryItemFail(unsigned long long, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xc0050);
}

// 0xc0160
void LobbyGateChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(unsigned long long, unsigned long long, unsigned long long, int)
{
    LIFT_STUB(0xc0160);
}

// 0xc0250
void LobbyGateChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(unsigned long long, unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0xc0250);
}

// 0xc0340
void LobbyGateChannel::SendCreateInitialUserNameOk(unsigned long long, wchar_t const*)
{
    LIFT_STUB(0xc0340);
}

// 0xc0460
void LobbyGateChannel::SendCreateInitialUserNameFail(unsigned long long, short)
{
    LIFT_STUB(0xc0460);
}

// 0xc0550
void LobbyGateChannel::SendActivateGradeOk(unsigned long long, int, int, long long, long long)
{
    LIFT_STUB(0xc0550);
}

// 0xc0670
void LobbyGateChannel::SendActivateGradeFail(unsigned long long, int, int, short)
{
    LIFT_STUB(0xc0670);
}

// 0xc0790
void LobbyGateChannel::SendChangedGradeNotify(unsigned long long, int, int, bool, int, long long, long long, wchar_t const*)
{
    LIFT_STUB(0xc0790);
}

// 0xc0970
void LobbyGateChannel::SendChangedGradeLevelNotify(unsigned long long, int, int, int, int, int)
{
    LIFT_STUB(0xc0970);
}

// 0xc0aa0
LobbyGateChannelManager::~LobbyGateChannelManager()
{
    LIFT_STUB(0xc0aa0);
}

// 0xc0b80
bool LobbyGateChannelManager::Add(LobbyGateChannel*)
{
    LIFT_STUB(0xc0b80);
}

// 0xc0c40
void LobbyGateChannelManager::Remove(short)
{
    LIFT_STUB(0xc0c40);
}

// 0xc0d50
LobbyGateChannel* LobbyGateChannelManager::Acquire(short)
{
    LIFT_STUB(0xc0d50);
}

// 0xc0e20
void LobbyGateChannelManager::BroadcastAnnounceNotify(wchar_t const*)
{
    LIFT_STUB(0xc0e20);
}

// 0xc0f20
bool LobbyGateChannelManager::OnAccept(Session const*) const
{
    LIFT_STUB(0xc0f20);
}

// 0xc0f80
bool LobbyGateChannelManager::OnConnect(Session const*, bool) const
{
    LIFT_STUB(0xc0f80);
}

// 0xc1030
void LobbyGateChannelManager::OnClose(Session const*, bool) const
{
    LIFT_STUB(0xc1030);
}

// 0xc11d0
bool LobbyGateChannelManager::PacketHandler(Session const*, Packet const*) const
{
    LIFT_STUB(0xc11d0);
}
