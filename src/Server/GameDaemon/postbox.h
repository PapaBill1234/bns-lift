// postbox.h: postbox.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ArchivePostTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Pc *, char, unsigned __int64);  // 0x195f90
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x196020
    virtual void __cdecl start(void);  // 0x196060
};

class PostBox
{
public:
    struct PostBody {};
    struct PostBriefBody {};
    struct PostHeader {};
public:
    __cdecl ~PostBox(void);  // 0x1922c0
    bool __cdecl AddPost(char, __int64, ::PostBox::PostHeader *, ::PostBox::PostBriefBody *);  // 0x192330
    bool __cdecl RemovePost(char, __int64);  // 0x192460
    bool __cdecl AddPostBody(char, __int64, ::PostBox::PostBody *);  // 0x192570
    short __cdecl TryDetachPostAttachment(__int64, char, __int64, __int64);  // 0x1926d0
    void __cdecl FinishDetachPostAttachment(__int64, char, __int64, __int64, __int64, short);  // 0x193a60
    void __cdecl RollbackDetachPostAttachment(__int64, char, __int64, __int64, short);  // 0x194140
    bool __cdecl ReadPost(char, __int64);  // 0x194480
    void __cdecl SendPostBody(char, __int64);  // 0x194a80
};

class ReadPostTask
{
private:
    virtual void __cdecl start(void);  // 0x195f50
};

class RetreivePostBriefListTask
{
public:
    __cdecl RetreivePostBriefListTask(void);  // 0x195210
    virtual __cdecl ~RetreivePostBriefListTask(void);  // 0x1952c0
    bool __cdecl Initialize(::Zone *, ::Pc *);  // 0x1953c0
    void __cdecl AddPostCapacity(int);  // 0x195430
    bool __cdecl AddPost(char, unsigned __int64, ::PostBox::PostHeader *, ::PostBox::PostBriefBody *);  // 0x195620
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x1956f0
private:
    virtual void __cdecl start(void);  // 0x195730
};

class RetreivePostTask
{
private:
    virtual void __cdecl start(void);  // 0x195f10
};

