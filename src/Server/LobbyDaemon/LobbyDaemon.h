// LobbyDaemon.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct EventContext;
class EventObject;
class GameWorldReporter;
class Packet;
class RepeatPacketComposer;
class Session;

class BannedWordFilterMemoryAllocator
{
public:
    virtual void* Alloc(unsigned long long, wchar_t const*, int);  // 0x99380
    virtual void* Realloc(void*, unsigned long long, wchar_t const*, int);  // 0x99390
    virtual void Free(void*, wchar_t const*, int);  // 0x993b0
};

class CoolDown
{
public:
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x995c0
    bool Start(long, long);  // 0x99880
};

class LobbyDaemon
{
public:
    virtual wchar_t const* ShortName();  // 0x99220
    virtual wchar_t const* Name();  // 0x99230
    virtual wchar_t const* ServiceName();  // 0x99240
    virtual wchar_t const* Descriptions();  // 0x99250
    LobbyDaemon();  // 0x9a230
    virtual ~LobbyDaemon();  // 0x9a3c0
    virtual void PrintDependency();  // 0x9ae30
    virtual long GetTimerInterval();  // 0x9af60
    virtual long GetTimerMaxTime();  // 0x9af70
    bool SetTimeZoneBias();  // 0x9af80
    static void FailedEventObjectHandler(EventObject*);  // 0x9b0c0
    static wchar_t const* GetAddressStringWForLogs(unsigned long);  // 0x9f3c0
protected:
    virtual bool initLog();  // 0x9b1b0
    virtual bool initialize();  // 0x9b300
    virtual bool initNetwork();  // 0x9d520
    virtual bool onStart();  // 0x9dca0
    virtual void shutdown();  // 0x9e2f0
    virtual bool reload(wchar_t**, int);  // 0x9e5b0
    virtual bool cooldown();  // 0x9ef40
private:
    bool startNPChannel();  // 0x9f010
    bool setupNpScheduleInfo();  // 0x9f130
};

class LobbyObjPoolMemAllocator
{
public:
    virtual void* Alloc(unsigned long long, wchar_t const*, int);  // 0x99260
};

class LobbydReloadInvalidRestoreTimer
{
public:
    virtual unsigned int EventId() const;  // 0x99990
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x999a0
private:
    void restoreInvalid();  // 0x999b0
};

class TimeBasedPlaySeasonSchedule
{
public:
    TimeBasedPlaySeasonSchedule();  // 0x99df0
    bool Compose(RepeatPacketComposer&, Packet&) const;  // 0x99ef0
};

unsigned long long GenerateClikey();  // 0x993c0
unsigned long long GenerateJobid();  // 0x99410
unsigned long long GenerateLobbyTokenkey();  // 0x99460
void GameWorldReporterListener(GameWorldReporter*);  // 0x994b0
bool ConcatenatePacket(Session const*, Packet const*, bool&);  // 0x9f3f0
