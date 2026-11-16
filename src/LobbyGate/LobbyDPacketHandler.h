// LobbyDPacketHandler.obj (LobbyGate PDB).
#pragma once

class Session;
class Packet;

bool HandleLobbyLobbyGate_HelloOk(Session const* session, Packet* packet);                         // 0xaf20
bool HandleLobbyLobbyGate_HelloFail(Session const* session, Packet* packet);                       // 0xb750
bool HandleLobbyLobbyGate_UpdateWorldInfoListNotify(Session const* session, Packet* packet);       // 0xb890
bool HandleLobbyLobbyGate_AnnounceNotify(Session const* session, Packet* packet);                  // 0xbce0
bool HandleLobbyLobbyGate_InitSessionWithNPTokenOk(Session const* session, Packet* packet);        // 0xbe90
bool HandleLobbyLobbyGate_InitSessionWithNPTokenFail(Session const* session, Packet* packet);      // 0xca10
bool HandleLobbyLobbyGate_StartSessionWithNPTokenOk(Session const* session, Packet* packet);       // 0xcd00
bool HandleLobbyLobbyGate_StartSessionWithNPTokenFail(Session const* session, Packet* packet);     // 0xe810
bool HandleLobbyLobbyGate_InitSessionWithLobbyTokenOk(Session const* session, Packet* packet);     // 0xeb30
bool HandleLobbyLobbyGate_InitSessionWithLobbyTokenFail(Session const* session, Packet* packet);   // 0xef10
bool HandleLobbyLobbyGate_StartSessionWithLobbyTokenOk(Session const* session, Packet* packet);    // 0xf230
bool HandleLobbyLobbyGate_StartSessionWithLobbyTokenFail(Session const* session, Packet* packet);  // 0xffc0
bool HandleLobbyLobbyGate_CloseAnonymousSessionNotify(Session const* session, Packet* packet);     // 0x102b0
bool HandleLobbyLobbyGate_CloseSessionNotify(Session const* session, Packet* packet);              // 0x10440
bool HandleLobbyLobbyGate_KickNotify(Session const* session, Packet* packet);                      // 0x10660
bool HandleLobbyLobbyGate_GetCharacterInfoListOk(Session const* session, Packet* packet);          // 0x10ab0
bool HandleLobbyLobbyGate_ListGoodsOk(Session const* session, Packet* packet);                     // 0x11060
bool HandleLobbyLobbyGate_TakeGoodsOk(Session const* session, Packet* packet);                     // 0x113e0
bool HandleLobbyLobbyGate_ListLobbyServiceItemInfoOk(Session const* session, Packet* packet);      // 0x117a0
bool HandleLobbyLobbyGate_GetServiceEntryListOk(Session const* session, Packet* packet);           // 0x11b60
bool HandleLobbyLobbyGate_GetEnterWorldTokenOk(Session const* session, Packet* packet);            // 0x11ee0
bool HandleLobbyLobbyGate_BypassPacket(Session const* session, Packet* packet);                    // 0x121d0
// 0x12650. The linker folded many `return true;` handlers to this one body (IDA name
// HandleLobbyLobbyGate_GetGoodsCountFail). The handler lists use this address for all of them.
bool HandleLobbyLobbyGate_ChangedGradeLevelNotify(Session const* session, Packet* packet);
