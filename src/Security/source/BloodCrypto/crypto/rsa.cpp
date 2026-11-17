// rsa.obj (LobbyGate PDB).
#include "rsa.h"
#include <string.h>

// 0x27FC0 (identical COMDAT folding: the code returns 0)
int Rsa::BlockSize() const
{
    return 0;
}

// 0x27FC0 (identical COMDAT folding: the code returns 0)
int Rsa::KeySize() const
{
    return 0;
}

// 0x4BF50
int Rsa::EncSize(int size) const
{
    return _encoder._blockSize * ((_encoder._maxSize + size - 1) / _encoder._maxSize);
}

// 0x52A60
bool Rsa::encrypt(BigInteger const* key, unsigned char const* in, int size, unsigned char* out, int* outSize) const
{
    if (*outSize < EncSize(size))
    {
        _error = 4;
        return false;
    }
    unsigned char const* end = in + size;
    unsigned char* o = out;
    BigInteger m;
    BigInteger r;
    while (in < end)
    {
        int len = static_cast<int>(end - in);
        unsigned char const* src;
        unsigned char tmp[128];
        if (len >= _encoder._maxSize)
        {
            len = _encoder._maxSize;
            src = in;
        }
        else
        {
            memset(tmp, 0, sizeof(tmp));
            memcpy(tmp, in, len);
            src = tmp;
        }
        unsigned char buf[128];
        int count = 128;
        // The result of Encode is not examined.
        _encoder.Encode(src, len, buf, &count, 0, 0);
        m.Set(buf, count);
        if (((_n.bits + 31) & ~31) <= 2048)
            r.ExpMod(&m, key, &_n);
        int c = (r.bits + 7) >> 3;
        if (o != 0 && _encoder._blockSize >= c)
            memcpy(o, r.digits, c);
        else
            c = 0;
        for (; c < _encoder._blockSize; ++c)
            o[c] = 0;
        o += c;
        in += len;
    }
    *outSize = static_cast<int>(o - out);
    _error = 0;
    return true;
}

// 0x52DE0
bool Rsa::decrypt(BigInteger const* key, unsigned char const* in, int size, unsigned char* out, int* outSize) const
{
    int k = _encoder._blockSize;
    if (size % k != 0 || *outSize < size / k * _encoder._maxSize)
    {
        _error = 4;
        return false;
    }
    unsigned char const* end = in + size;
    unsigned char* outEnd = out + *outSize;
    unsigned char* o = out;
    BigInteger m;
    BigInteger r;
    *outSize = 0;
    while (in < end)
    {
        m.Set(in, _encoder._blockSize);
        if (((_n.bits + 31) & ~31) <= 2048)
            r.ExpMod(&m, key, &_n);
        unsigned char buf[128];
        int c = (r.bits + 7) >> 3;
        if (c > 128)
            c = 0;
        else
            memcpy(buf, r.digits, c);
        for (; c < _encoder._blockSize; ++c)
            buf[c] = 0;
        int rem = static_cast<int>(outEnd - o);
        if (!_encoder.Decode(buf, c, o, &rem))
        {
            _error = 17;
            return false;
        }
        *outSize += rem;
        o += rem;
        in += _encoder._blockSize;
    }
    _error = 0;
    return true;
}

// 0x531F0. The compiler adds the destructor calls of the members (_n, _e, _encoder).
RsaPublic::~RsaPublic()
{
}

// 0x532A0
bool RsaPublic::Setup(unsigned char const* key, int keySize, int round)
{
    int bits = round;
    // BUG: 0x532A0 sets the default 512, but bits == 0 fails the range check first.
    int v = bits != 0 ? bits : 512;
    if (static_cast<unsigned int>(bits - 64) > 0x3C0 || (bits & 63) != 0 || key == 0 ||
        ((v + 7) >> 3) + 4 > keySize)
    {
        _error = 3;
        return false;
    }
    if (!_encoder.Setup(bits))
    {
        _error = 6;
        return false;
    }
    if (!_n.Set(key + 4, *reinterpret_cast<int const*>(key)))
    {
        _error = 5;
        return false;
    }
    _error = 0;
    return true;
}

// 0x126F0 (identical COMDAT folding: empty)
void RsaPublic::Cleanup()
{
}

// 0x52A40
Crypto::Type RsaPublic::GetType() const
{
    return RSA_PUBLIC;
}

// 0x53370
bool RsaPublic::Encrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const
{
    if (_encoder._blockSize <= 0)
    {
        _error = 8;
        return false;
    }
    if (in == 0 || out == 0 || outSize == 0)
    {
        _error = 3;
        return false;
    }
    return encrypt(&_e, in, size, out, outSize);
}

// 0x533D0
bool RsaPublic::Decrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const
{
    if (_encoder._blockSize <= 0)
    {
        _error = 8;
        return false;
    }
    if (in == 0 || out == 0 || outSize == 0)
    {
        _error = 3;
        return false;
    }
    return decrypt(&_e, in, size, out, outSize);
}

// 0x53560
bool RsaPrivate::Setup(unsigned char const* key, int keySize, int round)
{
    int bits = round;
    // BUG: 0x53560 sets the default 512, but bits == 0 fails the range check first.
    int v = bits != 0 ? bits : 512;
    if (static_cast<unsigned int>(bits - 64) > 0x3C0 || (bits & 63) != 0 || key == 0 ||
        2 * ((v + 7) >> 3) + 8 > keySize)
    {
        _error = 3;
        return false;
    }
    if (!_encoder.Setup(bits))
    {
        _error = 6;
        return false;
    }
    int len = *reinterpret_cast<int const*>(key);
    unsigned char const* nx = key + 4 + len;
    if (!_n.Set(key + 4, len) || !_d.Set(nx + 4, *reinterpret_cast<int const*>(nx)))
    {
        _error = 5;
        return false;
    }
    _error = 0;
    return true;
}

// 0x126F0 (identical COMDAT folding: empty)
void RsaPrivate::Cleanup()
{
}

// 0x52A50
Crypto::Type RsaPrivate::GetType() const
{
    return RSA_PRIVATE;
}

// 0x53660
bool RsaPrivate::Encrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const
{
    if (_encoder._blockSize <= 0)
    {
        _error = 8;
        return false;
    }
    if (in == 0 || out == 0 || outSize == 0)
    {
        _error = 3;
        return false;
    }
    return encrypt(&_d, in, size, out, outSize);
}

// 0x536C0
bool RsaPrivate::Decrypt(unsigned char const* in, int size, unsigned char* out, int* outSize) const
{
    if (_encoder._blockSize <= 0)
    {
        _error = 8;
        return false;
    }
    if (in == 0 || out == 0 || outSize == 0)
    {
        _error = 3;
        return false;
    }
    return decrypt(&_d, in, size, out, outSize);
}
