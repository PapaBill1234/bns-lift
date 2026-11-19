// oaep_encoder.obj (LobbyGate PDB).
#include "oaep_encoder.h"
#include <string.h>
#include "prng.h"

// PDB: S_LDATA32 nullparam, oaep_encoder.obj (Mod 0076), 0003:12064 = 0x93F20. Default OAEP label.
static unsigned char const nullparam[16] = {0};

// 0x5AA00
void i2os(unsigned char const* in, int inSize, unsigned char* out, int outSize)
{
    for (int pos = 0; pos < outSize; pos += 4)
    {
        unsigned int word = *reinterpret_cast<unsigned int const*>(in + pos);
        for (int j = 0, shift = 24; j < 4 && pos + j < inSize; ++j, shift -= 8)
            out[pos + j] = static_cast<unsigned char>(word >> shift);
    }
    int lo = 0;
    int hi = outSize - 4;
    if (hi > 0)
    {
        unsigned int* p = reinterpret_cast<unsigned int*>(out);
        unsigned int* q = reinterpret_cast<unsigned int*>(out + hi);
        do
        {
            unsigned int t = *p;
            *p = *q;
            *q = t;
            lo += 4;
            hi -= 4;
            ++p;
            --q;
        } while (lo < hi);
    }
}

// 0x5A910
void os2i(unsigned char const* in, int inSize, unsigned char* out, int outSize)
{
    if (inSize < outSize)
        memset(out + inSize, 0, outSize - inSize);
    for (int pos = 0; pos < inSize; pos += 4)
    {
        unsigned int word = 0;
        for (int j = 0, shift = 24; j < 4 && pos + j < inSize; ++j, shift -= 8)
            word |= static_cast<unsigned int>(in[pos + j]) << shift;
        *reinterpret_cast<unsigned int*>(out + pos) = word;
    }
    int lo = 0;
    int hi = outSize - 4;
    if (hi > 0)
    {
        unsigned int* p = reinterpret_cast<unsigned int*>(out);
        unsigned int* q = reinterpret_cast<unsigned int*>(out + hi);
        do
        {
            unsigned int t = *p;
            *p = *q;
            *q = t;
            lo += 4;
            hi -= 4;
            ++p;
            --q;
        } while (lo < hi);
    }
}

// 0x5AAE0
bool OaepEncoder::Encode(unsigned char const* in, int size, unsigned char* out, int* outSize,
                         void* label, int labelSize) const
{
    return const_cast<OaepEncoder*>(this)->encode(in, size, out, outSize, label, labelSize);
}

// 0x5AB10
bool OaepEncoder::Decode(unsigned char const* in, int size, unsigned char* out, int* outSize) const
{
    return const_cast<OaepEncoder*>(this)->decode(in, size, out, outSize);
}

// 0x5ABA0
bool OaepEncoder::Setup(int bits)
{
    int k = ((((bits + 7) >> 3) + 3) & ~3);
    // The original calls _hash.Size() again at each use (LobbyGate 0x5aba0).
    int twoH = 2 * _hash.Size();
    if (k < twoH + 2)
        return false;
    _blockSize = k;
    _maxSize = k - twoH - 2;
    _dbSize = k - _hash.Size() - 1;
    CryptoHash* hash = &_hash;
    // LIFT: 0x5aba0 (LobbyGate) the original tests the hash pointer of the mask generator for null.
    if (static_cast<unsigned int>(_dbSize) > 0x100 || hash == 0)
        return false;
    _mgf._hash = hash;
    _mgf._size = hash->Size();
    return static_cast<unsigned int>(_mgf._size) <= 0x40;
}

// 0x5AC40
bool OaepEncoder::encode(unsigned char const* in, int size, unsigned char* out, int* outSize,
                         void* label, int labelSize)
{
    if (in == 0 || size > _maxSize || out == 0 || outSize == 0 || *outSize < _blockSize)
        return false;

    // The original calls _hash.Size() again at each use (LobbyGate 0x5ac40).
    int psSize = _blockSize - (2 * _hash.Size() + 2) - size;
    unsigned char* db = out + _hash.Size() + 1;
    unsigned char* ps = _buffer + _hash.Size();
    unsigned char* one = ps + psSize;
    int hashSize = _hash.Size();
    if (label != 0)
        _hash.Digest(static_cast<unsigned char const*>(label), labelSize, _buffer, &hashSize);
    else
        _hash.Digest(nullparam, 16, _buffer, &hashSize);

    memset(ps, 0, one - ps);
    *one = 1;
    memcpy(one + 1, in, size);

    unsigned char seed[16];
    Prng::Generate(seed, 16);
    _mgf.generate(seed, 16, db, _dbSize);
    for (int i = 0; i < _dbSize; ++i)
    {
        db[i] ^= _buffer[i];
        _buffer[i] = 0;
    }

    _mgf.generate(db, _dbSize, out + 1, _hash.Size());
    for (int i = 0; i < _hash.Size(); ++i)
    {
        out[1 + i] ^= seed[i];
        seed[i] = 0;
    }

    out[0] = 0;
    *outSize = _blockSize;
    os2i(out, _blockSize, out, _blockSize);
    return true;
}

// 0x5AEB0
bool OaepEncoder::decode(unsigned char const* in, int size, unsigned char* out, int* outSize)
{
    if (in == 0 || size != _blockSize || out == 0 || outSize == 0 || *outSize < _maxSize)
        return false;

    // The input buffer is changed in place.
    unsigned char* data = const_cast<unsigned char*>(in);
    i2os(data, size, data, size);
    // The original calls _hash.Size() again at each use (LobbyGate 0x5aeb0).
    unsigned char* db = data + 1 + _hash.Size();

    unsigned char seed[16];
    _mgf.generate(db, _dbSize, seed, 16);
    for (int i = 0; i < 16; ++i)
        seed[i] ^= data[1 + i];

    _mgf.generate(seed, 16, _buffer, _dbSize);
    for (int i = 0; i < _dbSize; ++i)
        _buffer[i] ^= db[i];

    unsigned char* p = _buffer + _hash.Size();
    int n = 0;
    while (*p == 0)
    {
        if (n >= _dbSize - _hash.Size())
            break;
        ++p;
        ++n;
    }
    if (*p != 1 || n >= _dbSize - _hash.Size())
        return false;

    // BUG: 0x5AEB0 does not compare lHash with the label hash. The seed is not cleared.
    int len = _blockSize - (2 * _hash.Size() + 2) - n;
    *outSize = len;
    memcpy(out, p + 1, len);
    memset(_buffer, 0, _dbSize);
    return true;
}
