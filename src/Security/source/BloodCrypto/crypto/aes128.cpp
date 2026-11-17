// aes128.obj (CacheGate PDB).
#include "aes128.h"
#include <string.h>

// 0x5a388. Crypto::Initialize fills it.
Aes128::Delegator Aes128::_Delegator = { 0, 0, 0 };

// 0xded0. PDB: Aes128::GetType and Session::EventId have the same address (ICF). mov eax,3; ret.
Crypto::Type Aes128::GetType() const
{
    return AES128;
}

// 0x35ec0. PDB: Aes128::BlockSize, Aes128::KeySize and Blowfish::KeySize have the same address (ICF). mov eax,16; ret.
int Aes128::BlockSize() const
{
    return 16;
}

// 0x35ec0
int Aes128::KeySize() const
{
    return 16;
}

// 0x35ed0
int Aes128::EncSize(int size) const
{
    return (size + 15) & ~15;
}

// 0x35ee0
void Aes128::Cleanup()
{
    memset(_encKey, 0, sizeof(_encKey));
    memset(_decKey, 0, sizeof(_decKey));
}

// 0x35f20
bool Aes128::Setup(unsigned char const* key, int keySize, int round)
{
    return _Delegator.setup(this, key, keySize, round);
}

// 0x35f30
bool Aes128::Encrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const
{
    return _Delegator.encrypt(this, in, size, out, encCount);
}

// 0x35f50
bool Aes128::Decrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const
{
    return _Delegator.decrypt(this, in, size, out, encCount);
}
