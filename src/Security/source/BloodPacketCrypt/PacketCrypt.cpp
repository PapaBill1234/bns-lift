// BloodPacketCrypt64.lib (closed library). LIFT: file. The LobbyGate PDB has no module record for this code.
// The code comes from the LobbyGate disassembly (0x4cc60 - 0x4da60).
#include "PacketCrypt.h"
#include <string.h>
#include <stdlib.h>
#include <new>
#include "Crypto.h"
#include "Security.h"

// LIFT: The server RSA private key (LobbyGate 0x6C370, 264 bytes). keyhere. The lift has no key data. ❓ name
static unsigned char const s_handshakePrivateKey[264] = {0};

// LIFT: Crypto type 2 = AES128 (the Create table index, GetType() - 1). See Crypto.h.
static Crypto::Type const SESSION_CRYPTO_TYPE = static_cast<Crypto::Type>(2);

// LIFT: Inline code. SessionPacketCrypt::GenerateKey and BroadcastPacketCrypt::GenerateKey have the same random key
// loop (0x4d7d0, 0x4dc20). ❓ name
static inline bool generateRandomKey(unsigned char* key, int* size, int bits)
{
    if (*size < 0 || 8 * *size < bits)
        return false;
    unsigned char* p = key;
    for (long long i = bits / 8; i != 0; --i)
        *p++ = static_cast<unsigned char>(rand());
    *size = bits / 8;
    return true;
}

// 0x4cc60
int PacketCrypt::InstanceSize(Type type, Algorithm algorithm)
{
    (void)algorithm;
    switch (type)
    {
    case NO_CRYPT:
        return sizeof(NoPacketCrypt);
    case HANDSHAKE_CRYPT:
        return sizeof(HandshakePacketCrypt);
    case SESSION_CRYPT:
        return 2 * ((Crypto::InstanceSize(SESSION_CRYPTO_TYPE) + 15) / 16 * 16) + 48;
    case BROADCAST_CRYPT:
        return 16 * ((Crypto::InstanceSize(SESSION_CRYPTO_TYPE) + 15) / 16 + 644);
    default:
        return -1;
    }
}

// 0x4cce0
PacketCrypt* PacketCrypt::Create(Type type, Algorithm algorithm, unsigned char* buffer, int size)
{
    (void)algorithm;
    if (buffer == nullptr || size <= 0)
        return nullptr;
    switch (type)
    {
    case NO_CRYPT:
        if (static_cast<unsigned int>(size) < sizeof(NoPacketCrypt))
            return nullptr;
        return new (buffer) NoPacketCrypt();
    case HANDSHAKE_CRYPT:
        if (static_cast<unsigned int>(size) < sizeof(HandshakePacketCrypt))
            return nullptr;
        return new (buffer) HandshakePacketCrypt();
    case SESSION_CRYPT:
    {
        Crypto* crypto[2] = {nullptr, nullptr};
        int cryptoSize = (Crypto::InstanceSize(SESSION_CRYPTO_TYPE) + 15) / 16 * 16;
        if (size < 2 * cryptoSize + 48)
            return nullptr;
        unsigned char* p = buffer + 48;
        int left = size - 48;
        for (int i = 0; i < 2; ++i)
        {
            crypto[i] = Crypto::Create(p, left, SESSION_CRYPTO_TYPE);
            left -= cryptoSize;
            p += cryptoSize;
        }
        return new (buffer) SessionPacketCrypt(crypto);
    }
    case BROADCAST_CRYPT:
    {
        int cryptoSize = (Crypto::InstanceSize(SESSION_CRYPTO_TYPE) + 15) / 16 * 16;
        if (size < (cryptoSize + static_cast<int>(sizeof(BroadcastPacketCrypt)) + 15) / 16 * 16)
            return nullptr;
        int objectSize = (sizeof(BroadcastPacketCrypt) + 15) / 16 * 16;
        Crypto* crypto = Crypto::Create(buffer + objectSize, size - objectSize, SESSION_CRYPTO_TYPE);
        return new (buffer) BroadcastPacketCrypt(crypto);
    }
    default:
        return nullptr;
    }
}

// 0x4ced0
int NoPacketCrypt::GetType()
{
    return NO_CRYPT;
}

// 0x4cf60 (folded)
PacketCrypt::ErrCode NoPacketCrypt::SetEncryptParam(Param param)
{
    (void)param;
    return NO_RESULT;
}

// 0x4cf60 (folded)
PacketCrypt::ErrCode NoPacketCrypt::SetKey(unsigned char const* key, int keySize)
{
    (void)key;
    (void)keySize;
    return NO_RESULT;
}

// 0x4cf60 (folded)
PacketCrypt::ErrCode NoPacketCrypt::GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2)
{
    (void)key1;
    (void)size1;
    (void)key2;
    (void)size2;
    return NO_RESULT;
}

// 0x4cef0
PacketCrypt::ErrCode NoPacketCrypt::Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty)
{
    (void)with3rdParty;
    if (_MaxSize < *bufferSize)  // BUG: 0x4cef0 compares the buffer size, not the packet size, with _MaxSize.
        return FAILED_TOO_LARGE_PACKET;
    if (size + 2 > *bufferSize)
        return FAILED_INSUFFIENT_BUFFER;
    *reinterpret_cast<unsigned short*>(buffer) = static_cast<unsigned short>(size & 0x3FFF);
    *bufferSize = size + 2;
    return SPCE_NO_ERROR;
}

// 0x4cf30
PacketCrypt::ErrCode NoPacketCrypt::Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty)
{
    (void)size;
    (void)with3rdParty;
    unsigned short header = *reinterpret_cast<unsigned short*>(buffer);
    if ((header & 0xC000) != 0)
        return FAILED_INVALID_CODE;
    if (outSize != nullptr)
        *outSize = (header & 0x3FFF) + 2;
    return SPCE_NO_ERROR;
}

// 0x4d620 (folded)
PacketCrypt::ErrCode NoPacketCrypt::SetExternalCompressFunc(ExternalCompressFunc func, unsigned char const* data, int size)
{
    (void)func;
    (void)data;
    (void)size;
    return FAILED_SET_EXT_COMP_FUNC;
}

// 0x4cf70
HandshakePacketCrypt::HandshakePacketCrypt() : _param(PARAM_NONE), _keyExchanged(false)
{
    clearKey();
    // LIFT: The orig calls Setup through the vtable (0x4cf70).
    Crypto* crypto = &_rsaPrivate;
    crypto->Setup(s_handshakePrivateKey, sizeof(s_handshakePrivateKey), 1024);
}

// 0x4d080
HandshakePacketCrypt::~HandshakePacketCrypt()
{
    _param = PARAM_NONE;
    _keyExchanged = false;
    clearKey();
    // LIFT: The orig calls Cleanup through the vtables (0x4d080).
    Crypto* crypto = &_rsaPublic;
    crypto->Cleanup();
    crypto = &_rsaPrivate;
    crypto->Cleanup();
    CryptoKey* key = &_dh;
    key->Cleanup();
}

// 0x4cf60 (folded)
int HandshakePacketCrypt::GetType()
{
    return HANDSHAKE_CRYPT;
}

// 0x4d1d0
PacketCrypt::ErrCode HandshakePacketCrypt::SetEncryptParam(Param param)
{
    if (static_cast<unsigned int>(param) >= 2)
        return INVALID_PARAM;
    _param = param;
    return SPCE_NO_ERROR;
}

// 0x4d1f0
PacketCrypt::ErrCode HandshakePacketCrypt::SetKey(unsigned char const* key, int keySize)
{
    if (key == nullptr)
        return INVALID_PARAM;
    if (_keySize > 0)
        return ALREADY_INITIALIZED;
    if (static_cast<unsigned int>(keySize) < sizeof(int))
        return INVALID_PARAM;
    int rsaSize = *reinterpret_cast<int const*>(key) + 4;
    if (keySize < rsaSize)
        return INVALID_PARAM;
    CryptoKey* dh = &_dh;
    Crypto* rsa = &_rsaPublic;
    if (!dh->Setup(128) || !rsa->Setup(key, rsaSize, 512))
        return FAILED_SETUP_CRYPTO;
    _keyExchanged = true;
    unsigned char* out = _key;
    _keySize = sizeof(_key);
    if (!dh->Process(key + rsaSize, keySize - rsaSize, out, &_keySize) || out == nullptr)
        return FAILED_KEYGEN;
    return SPCE_NO_ERROR;
}

// 0x4d310
PacketCrypt::ErrCode HandshakePacketCrypt::GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2)
{
    if (key1 == nullptr || size1 == nullptr || *size1 < 16)
        return INVALID_PARAM;
    if (key2 == nullptr || size2 == nullptr || *size2 < 32)
        return INVALID_PARAM;
    if (_keySize <= 0)
        return NOT_INITIALIZED;
    CryptoKey* dh = &_dh;
    if (!dh->GetKey(key1, size1))
        return FAILED_KEYGEN;
    memcpy(key2, _key, _keySize);
    *size2 = _keySize;
    clearKey();
    dh->Cleanup();
    return SPCE_NO_ERROR;
}

// 0x4d440
PacketCrypt::ErrCode HandshakePacketCrypt::Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty)
{
    (void)with3rdParty;
    Param param = _param;
    if (param != PARAM_HANDSHAKE_FAIL && !_keyExchanged)
        return NOT_INITIALIZED;
    int outSize = 0;
    Crypto* crypto;
    if (param == PARAM_NONE)
        crypto = &_rsaPublic;
    else if (param == PARAM_HANDSHAKE_FAIL)
        crypto = &_rsaPrivate;
    else
        return INVALID_PARAM;
    int encSize = crypto->EncSize(size);
    if (_MaxSize < encSize)
        return FAILED_TOO_LARGE_PACKET;
    if (encSize + 2 > *bufferSize)
        return FAILED_INSUFFIENT_BUFFER;
    unsigned short code;
    if (_param == PARAM_NONE)
    {
        code = CLI_HANDSHAKE_KEY;
        crypto = &_rsaPublic;
    }
    else if (_param == PARAM_HANDSHAKE_FAIL)
    {
        code = INITIAL_KEY;
        crypto = &_rsaPrivate;
    }
    else
    {
        return FAILED_ENCRYPT;
    }
    outSize = *bufferSize - 2;
    if (!crypto->Encrypt(buffer + 2, size, buffer + 2, &outSize))
        return FAILED_ENCRYPT;
    *reinterpret_cast<unsigned short*>(buffer) = static_cast<unsigned short>((code << 12) | ((outSize >> 2) & 0xFFF));
    *bufferSize = outSize + 2;
    return SPCE_NO_ERROR;
}

// 0x4d570
PacketCrypt::ErrCode HandshakePacketCrypt::Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty)
{
    (void)with3rdParty;
    if (_keySize > 0)
        return ALREADY_INITIALIZED;
    unsigned short header = *reinterpret_cast<unsigned short*>(buffer);
    int encSize = 4 * (header & 0xFFF);
    int decSize = size - 2;
    if (outSize != nullptr)
        *outSize = encSize + 2;
    if (*outSize > size)  // BUG: 0x4d570 reads *outSize after the null test.
        return FAILED_NOT_COMPLETE_PACKET;
    if ((header & 0xF000) != (INITIAL_KEY << 12))
        return FAILED_INVALID_CODE;
    Crypto* crypto = &_rsaPrivate;
    if (!crypto->Decrypt(buffer + 2, encSize, buffer + 2, &decSize))
        return FAILED_DECRYPT;
    return SPCE_NO_ERROR;
}

// 0x4d620
PacketCrypt::ErrCode HandshakePacketCrypt::SetExternalCompressFunc(ExternalCompressFunc func, unsigned char const* data,
                                                                   int size)
{
    (void)func;
    (void)data;
    (void)size;
    return FAILED_SET_EXT_COMP_FUNC;
}

// 0x4d610
int SessionPacketCrypt::GetType()
{
    return SESSION_CRYPT;
}

// 0x4cf60 (folded)
PacketCrypt::ErrCode SessionPacketCrypt::SetEncryptParam(Param param)
{
    (void)param;
    return NO_RESULT;
}

// 0x4d620 (folded)
PacketCrypt::ErrCode SessionPacketCrypt::SetExternalCompressFunc(ExternalCompressFunc func, unsigned char const* data,
                                                                 int size)
{
    (void)func;
    (void)data;
    (void)size;
    return FAILED_SET_EXT_COMP_FUNC;
}

// 0x4d650
SessionPacketCrypt::~SessionPacketCrypt()
{
    _keyChanged = false;
    _encIndex = -1;
    _decIndex = -1;
    for (int i = 0; i < 2; ++i)
    {
        Crypto::Destroy(_crypto[i]);
        _crypto[i] = nullptr;
    }
}

// 0x4d770
PacketCrypt::ErrCode SessionPacketCrypt::SetKey(unsigned char const* key, int keySize)
{
    if (key == nullptr)
        return INVALID_PARAM;
    if (_encIndex != -1 && _decIndex != -1)
        return ALREADY_INITIALIZED;
    if (!_crypto[0]->Setup(key, keySize, 0))
        return FAILED_SETUP_CRYPTO;
    _encIndex = 0;
    _decIndex = 0;
    return SPCE_NO_ERROR;
}

// 0x4d7d0
PacketCrypt::ErrCode SessionPacketCrypt::GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2)
{
    (void)key2;
    (void)size2;
    if (key1 == nullptr || size1 == nullptr || *size1 < 16)
        return INVALID_PARAM;
    if (_encIndex == -1 || _decIndex == -1)
        return NOT_INITIALIZED;
    if (_keyChanged == true || _encIndex != _decIndex)
        return ALREADY_CHANGE_KEY;
    int next = (_encIndex + 1) % 2;
    if (!generateRandomKey(key1, size1, 128))
        return FAILED_KEYGEN;
    if (_crypto[next]->Setup(key1, 16, 0))
    {
        _keyChanged = true;
        return SPCE_NO_ERROR;
    }
    memset(key1, 0, *size1);
    return FAILED_SETUP_CRYPTO;
}

// 0x4d940
PacketCrypt::ErrCode SessionPacketCrypt::Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty)
{
    if (_encIndex == -1)
        return NOT_INITIALIZED;
    int outSize = 0;
    int encSize = _crypto[_encIndex]->EncSize(size);
    if (_MaxSize < encSize)
        return FAILED_TOO_LARGE_PACKET;
    if (encSize + 2 > *bufferSize)
        return FAILED_INSUFFIENT_BUFFER;
    outSize = *bufferSize - 2;
    if (!_crypto[_encIndex]->Encrypt(buffer + 2, size, buffer + 2, &outSize))
        return FAILED_ENCRYPT;
    unsigned short code = static_cast<unsigned short>(_encIndex != 0);
    if (with3rdParty)
        code += SESSION_KEY_1_AND_3RD_PARTY;
    else
        code += SESSION_KEY_1;
    *reinterpret_cast<unsigned short*>(buffer) = static_cast<unsigned short>((code << 12) | ((outSize >> 2) & 0xFFF));
    *bufferSize = outSize + 2;
    if (_keyChanged)
    {
        _keyChanged = false;
        _encIndex = (_encIndex + 1) % 2;
    }
    return SPCE_NO_ERROR;
}

// 0x4da60
PacketCrypt::ErrCode SessionPacketCrypt::Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty)
{
    if (_decIndex == -1)
        return NOT_INITIALIZED;
    unsigned short header = *reinterpret_cast<unsigned short*>(buffer);
    int encSize = 4 * (header & 0xFFF);
    int expected = (_decIndex != 0) + SESSION_KEY_1;
    int decSize = size - 2;
    if (outSize != nullptr)
        *outSize = encSize + 2;
    if (*outSize > size)  // BUG: 0x4da60 reads *outSize after the null test.
        return FAILED_NOT_COMPLETE_PACKET;
    int code = header >> 12;
    // BUG: 0x4da60 writes *with3rdParty before the null test.
    *with3rdParty = (code == SESSION_KEY_1_AND_3RD_PARTY || code == SESSION_KEY_2_AND_3RD_PARTY) && with3rdParty != nullptr;
    if (code == SESSION_KEY_1_AND_3RD_PARTY)
        code = SESSION_KEY_1;
    else if (code == SESSION_KEY_2_AND_3RD_PARTY)
        code = SESSION_KEY_2;
    if (_encIndex == _decIndex)
    {
        if (expected != code)
            return FAILED_INVALID_CODE;
    }
    else if (expected != code)
    {
        _crypto[_decIndex]->Cleanup();
        _decIndex = _encIndex;
    }
    if (!_crypto[_decIndex]->Decrypt(buffer + 2, encSize, buffer + 2, &decSize))
        return FAILED_DECRYPT;
    return SPCE_NO_ERROR;
}
