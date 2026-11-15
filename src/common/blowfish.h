// blowfish.obj (CacheGate PDB). The PDB has no type records for this class.
// The layout comes from the code. ❓ member names.
#pragma once
#include <stddef.h>
#include "Crypto.h"

class Blowfish : public Crypto
{
public:
    Blowfish() {}
    ~Blowfish() { Cleanup(); }

    virtual bool Setup(unsigned char const* key, int keySize, int round);
    virtual void Cleanup();
    virtual Type GetType() const;
    virtual int BlockSize() const;
    virtual int KeySize() const;
    virtual int EncSize(int size) const;
    virtual bool Encrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const;
    virtual bool Decrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const;

    int _round;               // ❓ +16, -1 after Cleanup
    unsigned int _pbox[18];   // ❓ +20
    unsigned int _sbox[1024]; // ❓ +92, 4 x 256
};
static_assert(sizeof(Blowfish) == 4192, "sizeof Blowfish");
static_assert(offsetof(Blowfish, _pbox) == 20, "Blowfish::_pbox");
static_assert(offsetof(Blowfish, _sbox) == 92, "Blowfish::_sbox");
