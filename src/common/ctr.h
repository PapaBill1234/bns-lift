// ctr.obj (CacheGate PDB). The PDB has no type records for these classes.
// The layout comes from the code. LIFT: Member names. The PDB has no field list.
#pragma once
#include <stddef.h>

class Crypto;

// Vtable 0x52D38: dtor, Setup, Encrypt, Decrypt.
class CryptoMode
{
public:
    virtual ~CryptoMode() {}
    virtual bool Setup(Crypto* crypto, int round, unsigned char const* key, int keySize,
                       unsigned char const* iv, int ivSize) = 0;
    virtual bool Encrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) = 0;
    virtual bool Decrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) = 0;
};

// Vtable 0x52D60.
class Ctr : public CryptoMode
{
public:
    Ctr() : _crypto(0), _blockSize(-1), _pos(-1) {}
    virtual ~Ctr();
    virtual bool Setup(Crypto* crypto, int round, unsigned char const* key, int keySize,
                       unsigned char const* iv, int ivSize);
    virtual bool Encrypt(unsigned char const* in, int size, unsigned char* out, int* encCount);
    virtual bool Decrypt(unsigned char const* in, int size, unsigned char* out, int* encCount);

    Crypto* _crypto;              // ❓ +8
    int _blockSize;               // ❓ +16
    int _pos;                     // ❓ +20
    unsigned char _counter[32];   // ❓ +24
    unsigned char _keyStream[32]; // ❓ +56
};
static_assert(sizeof(Ctr) == 88, "sizeof Ctr");
static_assert(offsetof(Ctr, _counter) == 24, "Ctr::_counter");
static_assert(offsetof(Ctr, _keyStream) == 56, "Ctr::_keyStream");
