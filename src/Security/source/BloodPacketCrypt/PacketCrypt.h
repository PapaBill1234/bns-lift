// BloodPacketCrypt64.lib (closed library). The LobbyGate PDB has no S_GPROC32 and no type records for these classes.
// LIFT: Class names come from the PDB public symbols (0x4cc60 - 0x4da60, LobbyGate). Member names and the
// layout come from the code. LIFT: Member names. The PDB has no field list.
#pragma once
#include <stddef.h>
#include <string.h>
#include "PacketBuffer.h"
#include "rsa.h"
#include "CryptoKey.h"

class Crypto;

// Vtable 0x86BA8 (LobbyGate).
class NoPacketCrypt : public PacketCrypt
{
public:
    NoPacketCrypt() {}
    virtual int GetType();                                                                          // 0x4CED0
    virtual ErrCode SetEncryptParam(Param param);                                                   // 0x4CF60 (folded)
    virtual ErrCode SetKey(unsigned char const* key, int keySize);                                  // 0x4CF60 (folded)
    virtual ErrCode GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2);  // 0x4CF60 (folded)
    virtual ErrCode Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty);   // 0x4CEF0
    virtual ErrCode Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty);     // 0x4CF30
    virtual ErrCode SetExternalCompressFunc(ExternalCompressFunc func, unsigned char const* data, int size);  // 0x4D620 (folded)
    virtual ~NoPacketCrypt() {}                                                                     // 0x4CEE0
};
static_assert(sizeof(NoPacketCrypt) == 8, "sizeof NoPacketCrypt");

// Vtable 0x86BF8 (LobbyGate).
class HandshakePacketCrypt : public PacketCrypt
{
public:
    HandshakePacketCrypt();   // 0x4CF70
    virtual int GetType();    // 0x4CF60 (folded)
    virtual ErrCode SetEncryptParam(Param param);                                                   // 0x4D1D0
    virtual ErrCode SetKey(unsigned char const* key, int keySize);                                  // 0x4D1F0
    virtual ErrCode GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2);  // 0x4D310
    virtual ErrCode Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty);   // 0x4D440
    virtual ErrCode Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty);     // 0x4D570
    virtual ErrCode SetExternalCompressFunc(ExternalCompressFunc func, unsigned char const* data, int size);  // 0x4D620
    virtual ~HandshakePacketCrypt();  // 0x4D080

private:
    // LIFT: Inline code. The ctor, the dtor and GenerateKey clear the key with the same stores (0x4cf70, 0x4d080, 0x4d310).
    void clearKey()
    {
        _keySize = 0;
        memset(_key, 0, sizeof(_key));
    }

public:
    Param _param;               // LIFT: +8. SetEncryptParam writes it (0x4d1d0)
    RsaPublic _rsaPublic;       // LIFT: +16. vtable 0x86DC8, SetKey sets it up from the peer key (0x4d1f0)
    RsaPrivate _rsaPrivate;     // LIFT: +1448. vtable 0x86E18, the ctor sets it up from the server key (0x4cf70)
    bool _keyExchanged;         // LIFT: +3400. SetKey sets it (0x4d1f0)
    Dh _dh;                     // LIFT: +3408
    int _keySize;               // LIFT: +5512
    unsigned char _key[32];     // LIFT: +5516
};
static_assert(offsetof(HandshakePacketCrypt, _rsaPublic) == 16, "HandshakePacketCrypt::_rsaPublic");
static_assert(offsetof(HandshakePacketCrypt, _rsaPrivate) == 1448, "HandshakePacketCrypt::_rsaPrivate");
static_assert(offsetof(HandshakePacketCrypt, _keyExchanged) == 3400, "HandshakePacketCrypt::_keyExchanged");
static_assert(offsetof(HandshakePacketCrypt, _dh) == 3408, "HandshakePacketCrypt::_dh");
static_assert(offsetof(HandshakePacketCrypt, _keySize) == 5512, "HandshakePacketCrypt::_keySize");
static_assert(offsetof(HandshakePacketCrypt, _key) == 5516, "HandshakePacketCrypt::_key");
static_assert(sizeof(HandshakePacketCrypt) == 0x15B0, "sizeof HandshakePacketCrypt");

// Vtable 0x86C48 (LobbyGate). The two Crypto objects are in the same buffer, after the object (+48).
class SessionPacketCrypt : public PacketCrypt
{
public:
    explicit SessionPacketCrypt(Crypto* const* crypto) : _keyChanged(false), _encIndex(-1), _decIndex(-1)
    {
        _crypto[0] = crypto[0];
        _crypto[1] = crypto[1];
    }
    virtual int GetType();                                                                          // 0x4D610
    virtual ErrCode SetEncryptParam(Param param);                                                   // 0x4CF60 (folded)
    virtual ErrCode SetKey(unsigned char const* key, int keySize);                                  // 0x4D770
    virtual ErrCode GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2);  // 0x4D7D0
    virtual ErrCode Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty);   // 0x4D940
    virtual ErrCode Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty);     // 0x4DA60
    virtual ErrCode SetExternalCompressFunc(ExternalCompressFunc func, unsigned char const* data, int size);  // 0x4D620 (folded)
    virtual ~SessionPacketCrypt();  // 0x4D650

    bool _keyChanged;     // LIFT: +8. GenerateKey sets it, Encrypt moves _encIndex (0x4d7d0, 0x4d940)
    int _encIndex;        // LIFT: +12. -1 = no key
    int _decIndex;        // LIFT: +16. -1 = no key
    Crypto* _crypto[2];   // LIFT: +24
};
static_assert(offsetof(SessionPacketCrypt, _encIndex) == 12, "SessionPacketCrypt::_encIndex");
static_assert(offsetof(SessionPacketCrypt, _crypto) == 24, "SessionPacketCrypt::_crypto");
static_assert(sizeof(SessionPacketCrypt) == 40, "sizeof SessionPacketCrypt");
