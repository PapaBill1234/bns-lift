// ContentsRuleConfigDefinition.obj (LobbyDaemon PDB, 2019 + PDB). Static data only.
// LIFT: LoadContentsRuleConfig (0x297d0) is not lifted. Config stays null until it is lifted.
#include "ContentsRuleConfigDefinition.h"

ContentsRuleConfig* ContentsRuleConfig::Config = nullptr;              // rva 0x209590
ContentsRuleConfigLoad* ContentsRuleConfig::ConfigNoReload = nullptr;  // rva 0x209598
ContentsRuleConfig* ContentsRuleConfig::ConfigOlds = nullptr;          // rva 0x2095a0
int ContentsRuleConfig::ConfigReloadCount = 0;                         // rva 0x2095a8
long long ContentsRuleConfig::ConfigLastReloadTime = 0;                // rva 0x2095b0
