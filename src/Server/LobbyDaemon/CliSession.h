// CliSession.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Character;
class CliSession;
class CliSessionTable;
class FragmentPacket;
class GameTimeScheduleNode;
class GamedChannel;
struct GoodsInventoryChangedNotifyParam;
class LobbyGateChannel;
class LobbyService;
class Packet;
class PacketComposer;
class PcCafe;
class Presence;
class RenameUserService;
class RepeatPacketComposer;
class RepeatPacketDecomposer;
class ServiceLocation;
class StopPlayTimerEvent;
class TimeBasedPlayInfoList;
struct UserPromotionReward;
union id128;

class AnonymousLobbyGatePresence
{
public:
    AnonymousLobbyGatePresence(LobbyGateChannel*, unsigned long long);  // 0x3a3f0
    virtual bool IsEqual(Presence const*) const;  // 0x3a4a0
    virtual bool OnSet(CliSessionTable*, CliSession*);  // 0x3a530
    virtual void OnUnset(CliSessionTable*, CliSession*);  // 0x3a600
    virtual void Close(CliSession*);  // 0x3a650
    virtual void Kick(CliSession*, int);  // 0x3a670
};

class CliSession
{
public:
    CliSession(unsigned long long, CliSessionTable*);  // 0x33490
    virtual ~CliSession();  // 0x336b0
    void finalize();  // 0x33cc0
    bool npLogin(id128 const&);  // 0x33d60
    bool login(id128 const&, wchar_t const*, char, wchar_t const*);  // 0x33f00
    bool logout();  // 0x34750
    bool loadDB();  // 0x349a0
    bool setPresence(Presence*);  // 0x35730
    void closePresence();  // 0x35810
    void kickPresence(int);  // 0x358e0
    bool enter(ServiceLocation*);  // 0x359c0
    void leave();  // 0x35c10
    Character* getCharacter(unsigned long long);  // 0x35cf0
    void removeCharacter(unsigned long long);  // 0x35d30
    Character* getPlayingCharacter();  // 0x35d90
    void setChargeKey(wchar_t const*);  // 0x35e20
    void completeRequestChargeStop(bool);  // 0x35eb0
    void cleanupCharge();  // 0x35fc0
    void HandleGameGetGradeList(GamedChannel*, unsigned long long, char, unsigned long long, int) const;  // 0x36240
    bool fetchContentBans(FragmentPacket*);  // 0x36df0
    bool fetchAccountContentQuotaList(FragmentPacket*);  // 0x36fa0
    bool fetchAccountRecycleTimeList(FragmentPacket*);  // 0x371b0
    bool addLobbyService(LobbyService*);  // 0x373a0
    void removeLobbyService(unsigned long long);  // 0x37530
    LobbyService* getLobbyServiceByType(unsigned long long, int);  // 0x37670
    LobbyService* queryLobbyService(Character*);  // 0x376b0
    bool addRenameUserService(RenameUserService*);  // 0x37790
    void setScheduledEndTime(GameTimeScheduleNode*);  // 0x37890
    void releaseScheduledEndTime();  // 0x37950
    bool FetchCharacterInfo(id128 const&, Packet*, PacketComposer*) const;  // 0x37af0
    bool FetchServiceEntryList(FragmentPacket*) const;  // 0x37c70
    bool UpdateBotScore(unsigned long long, int);  // 0x37de0
    bool BindCharacterSlot(unsigned long long, id128 const&);  // 0x37eb0
    bool UpdateCharacterData(unsigned long long, short, char*, short);  // 0x381c0
    bool UpdateCharacterLevel(unsigned long long, short);  // 0x38380
    bool UpdateAccountData(unsigned long long, int, TimeBasedPlayInfoList&);  // 0x38500
    bool UpdateTimeBasedPlayReward(unsigned long long, int, char, short, UserPromotionReward&, long long);  // 0x38670
    bool NotifyGoodsInventoryChangedAlongPresence(GoodsInventoryChangedNotifyParam&);  // 0x392c0
    bool ReserveStopPlay(bool, int, int);  // 0x39820
    bool TimeoutStopPlay(StopPlayTimerEvent*);  // 0x39a70
    bool OnChargeStopRequested(unsigned int);  // 0x39be0
    bool ApplyNewChargeItem(wchar_t const*, long, unsigned int, short);  // 0x39cc0
    bool NotifyChargeRemainTime(long, short, unsigned int);  // 0x39e50
    bool setRole(unsigned int const* const, int);  // 0x39f70
    bool setPcCafeCode(wchar_t const*);  // 0x3a000
    void setPcCafe(PcCafe*);  // 0x3a100
    void onPcCafeChargeStart();  // 0x3a190
    void onPcCafeChargeStop();  // 0x3a2c0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x329f0
    CliSession();  // 0x32a40
};

class GameAccount
{
public:
    GameAccount();  // 0x33360
    ~GameAccount();  // 0x33450
};

class GameServiceLocation
{
public:
    virtual ~GameServiceLocation();  // 0x3b360
    virtual void OnEnter(CliSession*);  // 0x3b3d0
    virtual void OnLeave(CliSession*);  // 0x3b540
    virtual bool Enter(CliSession*);  // 0x3b6f0
    virtual bool Leave(CliSession*);  // 0x3b9a0
    virtual bool ReserveStopPlay(CliSession*, StopPlayTimerEvent*);  // 0x3bb60
    virtual bool TimeoutStopPlay(CliSession*, StopPlayTimerEvent*);  // 0x3bc80
    virtual void NotifyStopPlay(CliSession*, int);  // 0x3bda0
};

class GameWorldPresence
{
public:
    virtual bool IsEqual(Presence const*) const;  // 0x3adf0
    virtual bool OnSet(CliSessionTable*, CliSession*);  // 0x3ae90
    virtual void OnUnset(CliSessionTable*, CliSession*);  // 0x3aff0
    virtual void Close(CliSession*);  // 0x3b0c0
    virtual void Kick(CliSession*, int);  // 0x3b120
};

class LobbyGatePresence
{
public:
    virtual bool IsEqual(Presence const*) const;  // 0x3a760
    virtual bool OnSet(CliSessionTable*, CliSession*);  // 0x3a7d0
    virtual void OnUnset(CliSessionTable*, CliSession*);  // 0x3aa30
    virtual void Close(CliSession*);  // 0x3abc0
    virtual void Kick(CliSession*, int);  // 0x3ac20
};

class ServiceLocation
{
public:
    virtual ~ServiceLocation();  // 0x329d0
};

class TimeBasedPlayInfoList
{
public:
    ~TimeBasedPlayInfoList();  // 0x32bb0
    void ValidateDurations();  // 0x32be0
    void SetPlayInfoFromGame(TimeBasedPlayInfoList const&);  // 0x32e20
    bool Compose(FragmentPacket&) const;  // 0x32ed0
    bool Compose(RepeatPacketComposer&, Packet&) const;  // 0x33070
    bool Decompose(RepeatPacketDecomposer&, Packet const*);  // 0x331e0
};
