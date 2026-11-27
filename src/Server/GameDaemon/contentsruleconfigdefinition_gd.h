// contentsruleconfigdefinition_gd.h: contentsruleconfigdefinition.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ContentsRuleConfig
{
public:
    __cdecl ContentsRuleConfig(void);  // 0x891b0
    static bool __cdecl LoadContentsRuleConfig(void);  // 0x893a0
    static bool __cdecl ReloadContentsRuleConfig(bool &, bool &);  // 0x895c0
    static void __cdecl DestroyContentsRuleConfig(void);  // 0x89920
    static void __cdecl Dump(void);  // 0x89a50
private:
    static ::FragmentPacket * __cdecl MakeListPacket(::ContentsRuleConfig *);  // 0x89c50
    bool __cdecl ConvPacketElement(char *, char *, wchar_t const *const, wchar_t const *const, int);  // 0x8a100
    static bool __cdecl CheckMinMaxBoundary(void const *const, ::XmlCfgDefLocal const *, ::XmlCfgDef const *, int);  // 0x8a310
    bool __cdecl UpdateAllVariable(::ContentsRuleConfigLoad const *const);  // 0x8a480
    bool __cdecl Copy(::ContentsRuleConfig const *const);  // 0x8a620
    bool __cdecl UpdateReloadedVariable(::ContentsRuleConfigReload const *const, bool &);  // 0x8ac60
    bool __cdecl CompareMatch(::ContentsRuleConfigReload const *) const;  // 0x8aeb0
};

class ContentsRuleConfigLoad
{
public:
    static ::ContentsRuleConfigLoad * __cdecl Load(void);  // 0x89070
};

class ContentsRuleConfigReload
{
public:
    static ::ContentsRuleConfigReload * __cdecl Load(void);  // 0x89110
};

