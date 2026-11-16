// rsa.obj (LobbyGate PDB). RSA with OAEP (RIPEMD-128) padding.
// The PDB has no type records for these classes. The layout comes from the code.
// ❓ member names.
#pragma once
#include <stddef.h>
#include "Crypto.h"
#include "BigInteger.h"
#include "oaep_encoder.h"

// Vtable 0x86D78.
class Rsa : public Crypto
{
public:
    Rsa() { _e.Set(65537LL); }
    virtual ~Rsa() {}

    virtual bool Setup(unsigned char const* key, int keySize, int round) = 0;
    virtual void Cleanup() = 0;
    virtual Type GetType() const = 0;
    virtual int BlockSize() const; // 0x27FC0 (folded), returns 0
    virtual int KeySize() const;   // 0x27FC0 (folded), returns 0
    virtual int EncSize(int size) const;
    virtual bool Encrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const = 0;
    virtual bool Decrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const = 0;

protected:
    bool encrypt(BigInteger const* key, unsigned char const* in, int size, unsigned char* out, int* outSize) const;
    bool decrypt(BigInteger const* key, unsigned char const* in, int size, unsigned char* out, int* outSize) const;

public:
    OaepEncoder _encoder; // ❓ +16
    BigInteger _e;        // ❓ +392, public exponent
    BigInteger _n;        // ❓ +912, modulus
};
static_assert(sizeof(Rsa) == 1432, "sizeof Rsa");
static_assert(offsetof(Rsa, _encoder) == 16, "Rsa::_encoder");
static_assert(offsetof(Rsa, _e) == 392, "Rsa::_e");
static_assert(offsetof(Rsa, _n) == 912, "Rsa::_n");

// Vtable 0x86DC8.
class RsaPublic : public Rsa
{
public:
    RsaPublic() {}
    // 0x531F0
    virtual ~RsaPublic() {}

    virtual bool Setup(unsigned char const* key, int keySize, int round);
    virtual void Cleanup(); // 0x126F0 (folded), empty
    virtual Type GetType() const;
    virtual bool Encrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const;
    virtual bool Decrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const;
};
static_assert(sizeof(RsaPublic) == 1432, "sizeof RsaPublic");

// Vtable 0x86E18.
class RsaPrivate : public Rsa
{
public:
    RsaPrivate() {}
    // 0x534A0
    virtual ~RsaPrivate() {}

    virtual bool Setup(unsigned char const* key, int keySize, int round);
    virtual void Cleanup(); // 0x126F0 (folded), empty
    virtual Type GetType() const;
    virtual bool Encrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const;
    virtual bool Decrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const;

    BigInteger _d; // ❓ +1432, private exponent
};
static_assert(sizeof(RsaPrivate) == 1952, "sizeof RsaPrivate");
static_assert(offsetof(RsaPrivate, _d) == 1432, "RsaPrivate::_d");
