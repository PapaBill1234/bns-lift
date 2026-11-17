// aes128.obj (CacheGate PDB). The PDB has no type records for this class.
// The layout comes from the code. LIFT: Member names. The PDB has no field list.
#pragma once
#include <stddef.h>
#include "Crypto.h"

class Aes128 : public Crypto
{
public:
    // PDB public symbol ?_Delegator@Aes128@@0UDelegator@1@A gives the struct name.
    // LIFT: The member names are not in the PDB. The PDB has no field list for this struct.
    struct Delegator
    {
        bool (*setup)(Aes128* aes, unsigned char const* key, int keySize, int round);
        bool (*encrypt)(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount);
        bool (*decrypt)(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount);
    };

    Aes128() {}
    ~Aes128() { Cleanup(); }

    virtual bool Setup(unsigned char const* key, int keySize, int round);
    virtual void Cleanup();
    virtual Type GetType() const;
    virtual int BlockSize() const;
    virtual int KeySize() const;
    virtual int EncSize(int size) const;
    virtual bool Encrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const;
    virtual bool Decrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const;

    unsigned int _encKey[44]; // ❓ +16
    unsigned int _decKey[44]; // ❓ +192

    static Delegator _Delegator; // 0x5A388
};
static_assert(sizeof(Aes128) == 368, "sizeof Aes128");
static_assert(offsetof(Aes128, _encKey) == 16, "Aes128::_encKey");
static_assert(offsetof(Aes128, _decKey) == 192, "Aes128::_decKey");
