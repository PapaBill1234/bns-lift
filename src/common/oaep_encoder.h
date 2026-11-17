// oaep_encoder.obj (LobbyGate PDB). OAEP encoder for RSA.
// The PDB has no type records for these classes. The layout comes from the code.
// LIFT: Member names. The PDB has no field list.
#pragma once
#include <stddef.h>
#include <string.h>
#include "ripemd128.h"
#include "mgf.h"

// Vtable 0x86F68: dtor, Setup, Encode, Decode.
class CryptoEncoder
{
public:
    CryptoEncoder() : _maxSize(0), _blockSize(0) {}
    // 0x5A8F0
    virtual ~CryptoEncoder()
    {
        _maxSize = 0;
        _blockSize = 0;
    }
    virtual bool Setup(int bits) = 0;
    virtual bool Encode(unsigned char const* in, int size, unsigned char* out, int* outSize,
                        void* label, int labelSize) const = 0;
    virtual bool Decode(unsigned char const* in, int size, unsigned char* out, int* outSize) const = 0;

    int _maxSize;   // ❓ +8, largest plain text of one block
    int _blockSize; // ❓ +12, size of one encoded block (k)
};
static_assert(sizeof(CryptoEncoder) == 16, "sizeof CryptoEncoder");

// Vtable 0x86F90.
class OaepEncoder : public CryptoEncoder
{
public:
    OaepEncoder() : _dbSize(0) { memset(_buffer, 0, sizeof(_buffer)); }
    // 0x5AB30 (scalar deleting destructor)
    virtual ~OaepEncoder()
    {
        memset(_buffer, 0, sizeof(_buffer));
        _dbSize = 0;
    }
    virtual bool Setup(int bits);
    virtual bool Encode(unsigned char const* in, int size, unsigned char* out, int* outSize,
                        void* label, int labelSize) const;
    virtual bool Decode(unsigned char const* in, int size, unsigned char* out, int* outSize) const;

private:
    bool encode(unsigned char const* in, int size, unsigned char* out, int* outSize, void* label, int labelSize);
    bool decode(unsigned char const* in, int size, unsigned char* out, int* outSize);

public:
    Ripemd128 _hash;             // ❓ +16
    MaskGenerator _mgf;          // ❓ +32
    unsigned char _buffer[256];  // ❓ +112
    int _dbSize;                 // ❓ +368
};
static_assert(sizeof(OaepEncoder) == 376, "sizeof OaepEncoder");
static_assert(offsetof(OaepEncoder, _hash) == 16, "OaepEncoder::_hash");
static_assert(offsetof(OaepEncoder, _mgf) == 32, "OaepEncoder::_mgf");
static_assert(offsetof(OaepEncoder, _buffer) == 112, "OaepEncoder::_buffer");
static_assert(offsetof(OaepEncoder, _dbSize) == 368, "OaepEncoder::_dbSize");

// Byte strings to and from little-endian digit arrays (oaep_encoder.obj).
void i2os(unsigned char const* in, int inSize, unsigned char* out, int outSize);
void os2i(unsigned char const* in, int inSize, unsigned char* out, int outSize);
