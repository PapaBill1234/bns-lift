// blowfish.obj (CacheGate PDB).
#include "blowfish.h"
#include <string.h>

#include "blowfishData.inc"

// The S-box offset is a pointer offset (64-bit), so the compiler puts it in the address (orig disp 0x400, 0x800, 0xc00).
#define BF_F(s, x) (((((s))[(x) >> 24] + ((s) + 256)[((x) >> 16) & 0xFF]) ^ ((s) + 512)[((x) >> 8) & 0xFF]) + ((s) + 768)[(x) & 0xFF])

// 0x35fa0 (file-static, no PDB type)
static void encrypt(int round, unsigned int const* pbox, unsigned int const* sbox, unsigned int* xl, unsigned int* xr)
{
    unsigned int l = *xl;
    unsigned int r = *xr;
    for (long long k = 0; k < round;)
    {
        unsigned int t = pbox[k] ^ l;
        k += 2;
        r ^= pbox[k - 1] ^ BF_F(sbox, t);
        l = BF_F(sbox, r) ^ t;
    }
    *xr = l ^ pbox[16];
    *xl = r ^ pbox[17];
}

// 0x360a0 (file-static, no PDB type)
static void decrypt(int round, unsigned int const* pbox, unsigned int const* sbox, unsigned int* xl, unsigned int* xr)
{
    unsigned int l = *xr ^ pbox[16];
    unsigned int r = *xl ^ pbox[17];
    for (long long i = round - 1; i > 0; i -= 2)
    {
        unsigned int t = BF_F(sbox, r) ^ l;
        l = pbox[i - 1] ^ t;
        r = BF_F(sbox, t) ^ pbox[i] ^ r;
    }
    *xl = l;
    *xr = r;
}

// 0x35f70
Crypto::Type Blowfish::GetType() const
{
    return BLOWFISH;
}

// 0x35f80
int Blowfish::BlockSize() const
{
    return 8;
}

// 0x35ec0. PDB: same address as Aes128::KeySize (ICF). mov eax,16; ret.
int Blowfish::KeySize() const
{
    return 16;
}

// 0x35f90
int Blowfish::EncSize(int size) const
{
    return (size + 7) & ~7;
}

// 0x36190
void Blowfish::Cleanup()
{
    _round = -1;
    memset(_pbox, 0, sizeof(_pbox));
    memset(_sbox, 0, sizeof(_sbox));
}

// 0x361d0
bool Blowfish::Setup(unsigned char const* key, int keySize, int round)
{
    if (round != 0 && round != 8 && round != 16)
    {
        _error = 3;
        return false;
    }
    // The original puts the error 5 path after the body (ja to the end of the function).
    if (static_cast<unsigned int>(keySize - 4) <= 0x34)
    {
        if (round == 0)
            round = 16;
        _round = round;
        memcpy(_pbox, P, sizeof(_pbox));
        memcpy(_sbox, S, sizeof(_sbox));

        int j = 0;
        for (int i = 0; i < 18; ++i)
        {
            _pbox[i] ^= (static_cast<unsigned int>(key[j]) << 24)
                      | (static_cast<unsigned int>(key[(j + 1) % keySize]) << 16)
                      | (static_cast<unsigned int>(key[(j + 2) % keySize]) << 8)
                      | static_cast<unsigned int>(key[(j + 3) % keySize]);
            j = (j + 4) % keySize;
        }

        unsigned int l = 0;
        unsigned int r = 0;
        for (int i = 0; i < 18; i += 2)
        {
            encrypt(_round, _pbox, _sbox, &l, &r);
            _pbox[i] = l;
            _pbox[i + 1] = r;
        }
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 256; j += 2)
            {
                encrypt(_round, _pbox, _sbox, &l, &r);
                _sbox[256 * i + j] = l;
                _sbox[256 * i + j + 1] = r;
            }
        }
        _error = 0;
        return true;
    }
    _error = 5;
    return false;
}

// 0x366a0
bool Blowfish::Encrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const
{
    if (_round < 0)
    {
        _error = 8;
        return false;
    }
    if (in == 0 || out == 0 || encCount == 0 || *encCount < size)
    {
        _error = 3;
        return false;
    }
    // BUG: 0x366a0 checks *encCount < size, but it writes size rounded up to 8 bytes.
    unsigned char const* end = in + size;
    unsigned int* dst = reinterpret_cast<unsigned int*>(out);
    for (unsigned char const* src = in; src < end;)
    {
        long long step = end - src;
        unsigned int const* block;
        unsigned long long pad;
        if (static_cast<unsigned long long>(step) >= 8)
        {
            step = 8;
            block = reinterpret_cast<unsigned int const*>(src);
        }
        else
        {
            pad = 0;
            memcpy(&pad, src, end - src);
            block = reinterpret_cast<unsigned int const*>(&pad);
        }
        dst[0] = block[0];
        dst[1] = block[1];
        encrypt(_round, _pbox, _sbox, &dst[0], &dst[1]);
        src += step;
        dst += 2;
    }
    *encCount = static_cast<int>(reinterpret_cast<unsigned char*>(dst) - out);
    _error = 0;
    return true;
}

// 0x367e0
bool Blowfish::Decrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const
{
    if (_round < 0)
    {
        _error = 8;
        return false;
    }
    if (in == 0 || out == 0 || encCount == 0 || *encCount < size)
    {
        _error = 3;
        return false;
    }
    // BUG: 0x367e0 reads a full 8-byte block when size is not a multiple of 8.
    unsigned char const* end = in + size;
    unsigned char const* src = in;
    unsigned int* dst = reinterpret_cast<unsigned int*>(out);
    while (src < end)
    {
        dst[0] = reinterpret_cast<unsigned int const*>(src)[0];
        dst[1] = reinterpret_cast<unsigned int const*>(src)[1];
        decrypt(_round, _pbox, _sbox, &dst[0], &dst[1]);
        src += 8;
        dst += 2;
    }
    *encCount = static_cast<int>(reinterpret_cast<unsigned char*>(dst) - out);
    _error = 0;
    return true;
}
