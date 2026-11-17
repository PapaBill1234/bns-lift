// Security.obj (LobbyGate PDB).
#pragma once
#include "PacketBuffer.h"

class Crypto;

// BroadcastPacketCrypt: the PDB has no type record for this class. The layout comes from the
// inlined constructor in BroadcastCrypt::Initialize (0x23000). LIFT: Member names. The PDB has no field list.
// The methods (0x4CF60, 0x4DBA0 - 0x4DF40, LobbyGate) are in no LobbyGate card. Declarations only.
class BroadcastPacketCrypt : public PacketCrypt
{
public:
    explicit BroadcastPacketCrypt(Crypto* crypto)
        : _crypto(crypto), _param(PARAM_NONE), _keySet(false), _compressType(1), _compressFunc(nullptr), _dict(nullptr),
          _dictSize(0)
    {
    }

    virtual int GetType();                                                                  // 0x4DBA0
    virtual ErrCode SetEncryptParam(Param param);                                              // 0x4DC00
    virtual ErrCode SetKey(unsigned char const* key, int keySize);                              // 0x4CF60
    virtual ErrCode GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2);  // 0x4DC20
    virtual ErrCode Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty);  // 0x4DD70
    virtual ErrCode Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty);    // 0x4DF30
    virtual ErrCode SetExternalCompressFunc(ExternalCompressFunc func, unsigned char const* data, int size);      // 0x4DF40
    virtual ~BroadcastPacketCrypt();                                                        // 0x4DBB0

    Crypto* _crypto;               // ❓ +0x8
    Param _param;                       // ❓ +0x10
    bool _keySet;                       // ❓ +0x14
    char _compressType;                 // ❓ +0x15, 1 = compress2, 2 = _compressFunc
    unsigned char _buffer[0x2818 - 0x16];  // ❓ +0x16, compress output
    int _bufferSize;                    // ❓ +0x2818
    ExternalCompressFunc _compressFunc;  // ❓ +0x2820
    unsigned char* _dict;               // ❓ +0x2828
    int _dictSize;                      // ❓ +0x2830
};
static_assert(sizeof(BroadcastPacketCrypt) == 0x2838, "sizeof BroadcastPacketCrypt");
static_assert(offsetof(BroadcastPacketCrypt, _bufferSize) == 0x2818, "BroadcastPacketCrypt::_bufferSize");
static_assert(offsetof(BroadcastPacketCrypt, _compressFunc) == 0x2820, "BroadcastPacketCrypt::_compressFunc");
static_assert(offsetof(BroadcastPacketCrypt, _dictSize) == 0x2830, "BroadcastPacketCrypt::_dictSize");

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
    friend class LobbyGate;  // ❓ access for LobbyGate::~LobbyGate (0x129c0, LobbyGate)
};
static_assert(sizeof(BroadcastCrypt) == 0x18, "sizeof BroadcastCrypt");

// 0x22F50
int zstdPacketCompress(unsigned char* dest, int* destLen, unsigned char const* src, int srcLen,
                       unsigned char const* args);
