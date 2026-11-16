// Security.obj (LobbyGate PDB).
#pragma once
#include "PacketBuffer.h"

class Crypto;

// BroadcastPacketCrypt: the PDB has no type record for this class. The layout comes from the
// inlined constructor in BroadcastCrypt::Initialize (0x23000). ❓ member names.
// The methods (0x4CF60, 0x4DBA0 - 0x4DF40, LobbyGate) are in no LobbyGate card. Declarations only.
class BroadcastPacketCrypt : public PacketCrypt
{
public:
    explicit BroadcastPacketCrypt(Crypto* crypto)
        : _crypto(crypto), _unknown10(0), _unknown14(0x100), _unknown2820(0), _unknown2828(0), _unknown2830(0)
    {
    }

    virtual int GetType();                                                                  // 0x4DBA0
    virtual int SetEncryptParam(int param);                                                 // 0x4DC00
    virtual int SetKey(unsigned char const* key, int keySize);                              // 0x4CF60
    virtual int GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2);  // 0x4DC20
    virtual int Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty);  // 0x4DD70
    virtual int Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty);    // 0x4DF30
    virtual int SetExternalCompressFunc(void* func, unsigned char const* data, int size);      // 0x4DF40
    virtual ~BroadcastPacketCrypt();                                                        // 0x4DBB0

    Crypto* _crypto;               // ❓ +0x8
    int _unknown10;                // ❓ +0x10
    unsigned short _unknown14;     // ❓ +0x14
    char _buffer[0x2820 - 0x16];   // ❓ +0x16, the constructor does not set it
    unsigned long long _unknown2820;  // ❓ +0x2820
    unsigned long long _unknown2828;  // ❓ +0x2828
    int _unknown2830;              // ❓ +0x2830
};
static_assert(sizeof(BroadcastPacketCrypt) == 0x2838, "sizeof BroadcastPacketCrypt");

class BroadcastCrypt
{
public:
    enum Type
    {
        BROADCAST_DAEMON = 0,
        BROADCAST_LOCAL = 1,
    };

    ~BroadcastCrypt();  // 0x22FF0
    bool Initialize(Type type, PacketCrypt::Algorithm algorithm, int broadcastCompressType);  // 0x23000

    PacketCrypt* crypt;
    char* key;
    int size;

private:
    void clear();  // 0x232F0
};
static_assert(sizeof(BroadcastCrypt) == 0x18, "sizeof BroadcastCrypt");

// 0x22F50
int zstdPacketCompress(unsigned char* dest, int* destLen, unsigned char const* src, int srcLen,
                       unsigned char const* args);
