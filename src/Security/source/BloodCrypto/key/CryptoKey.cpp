// CryptoKey.obj (BloodCrypto, LobbyGate PDB).
#include "CryptoKey.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <intrin.h>
#include "Crypto.h"
#include "prng.h"

// 0x94108
long s_initializedCount = 0;

// 0x526e0. LIFT: noinline only in LG/SCD/POD: these originals keep a call. CacheGate inlines it.
#if defined(LIFT_EXE_LG) || defined(LIFT_EXE_SCD) || defined(LIFT_EXE_POD)
__declspec(noinline)
#endif
bool CryptoKey::Initialize()
{
    if (_InterlockedIncrement(&s_initializedCount) > 1)
        return true;
    srand((unsigned int)_time64(0));
    Crypto::Initialize();
    return Prng::Initialize() && Prng::Initialize() && Prng::instance()->setSeed();
}

// 0x52750
// LIFT: Both Dh callers call this function in LobbyGate (0x52750).
__declspec(noinline) bool CryptoKey::generateBigNumber(int bits, unsigned char* out, int* size)
{
    if ((unsigned int)(bits - 8) > 0xFF8)
        return false;
    int bytes = (bits + 7) >> 3;
    if (bytes > *size)
        return false;
    unsigned char mask = (unsigned char)(255 >> (8 - (bits & 7)));
    unsigned char top = (unsigned char)(1 << ((bits - 1) & 7));
    if (mask == 0)
        mask = 0xFF;
    if (!Prng::Generate(out, bytes))
        return false;
    out[bytes - 1] = top | (mask & out[bytes - 1]);
    out[0] |= 1;
    *size = bytes;
    return true;
}

// 0x52820
bool CryptoKey::generatePrimeNumber(int bits, unsigned char* out, int* size)
{
    if ((unsigned int)(bits - 64) > 0x3C0)
        return false;
    if ((bits + 7) >> 3 > *size)
        return false;
    BigInteger p;
    if (!Prng::GeneratePrime(bits, &p))
        return false;
    int count = (p.bits + 7) >> 3;
    if (out && *size >= count)
        memcpy(out, p.digits, count);
    else
        count = 0;
    *size = count;
    return true;
}

// 0x55580 area. The ctor is inline in the scalar deleting dtor area.
Dh::Dh()
{
    clear();
}

// 0x27fc0 (folded: returns 0)
int Dh::GetType() const
{
    return 0;
}

// 0x55610
bool Dh::Setup(int bits)
{
    if ((unsigned int)(bits - 32) > 0x1E0)
        return false;
    _state = 0;
    _bits = bits;
    return true;
}

// 0x55630
void Dh::Cleanup()
{
    clear();
}

// 0x555a0
Dh::~Dh()
{
    clear();
}

// 0x55640
void Dh::clear()
{
    _state = 0;
    _bits = 0;
    _g.setZero();
    _p.setZero();
    _x.setZero();
    _y.setZero();
}

// 0x556f0
bool Dh::Start(unsigned char const* in, int inSize, unsigned char* out, int* outSize)
{
    int bits = _bits;
    if (bits == 0 || out == 0 || outSize == 0)
        return false;
    int avail = *outSize;
    int primeBits = 2 * bits;
    int* len1 = (int*)out;

    if (in && inSize)
    {
        if (avail <= inSize)
            return false;
        memcpy(out, in, inSize);
        bool ok = _g.Set(1, out + 4, *len1);
        unsigned char* q = out + *len1 + 4;
        if (!ok || !_p.Set(1, q + 4, *(int*)q))
        {
            memset(out, 0, *outSize);
            return false;
        }
    }
    else
    {
        *len1 = avail;
        if (avail < 0 || bits > 8 * avail || !generateBigNumber(bits, out + 4, len1))
            return false;
        unsigned char* q = out + 4 + *len1;
        avail += -4 - *len1;
        *(int*)q = avail;
        if (avail < 0 || primeBits > 8 * avail || !generatePrimeNumber(primeBits, q + 4, (int*)q))
        {
            memset(out, 0, *outSize);
            return false;
        }
        if (!_g.Set(1, out + 4, *len1) || !_p.Set(1, q + 4, *(int*)q))
        {
            memset(out, 0, *outSize);
            return false;
        }
        if (pNotAboveG())
        {
            _p.setZero();
            _g.setZero();
            memset(out, 0, *outSize);
            return false;
        }
    }

    int len2 = *(int*)(out + *len1 + 4);
    unsigned char* r = out + *len1 + 8 + len2;
    *(int*)r = avail - len2 - *len1 - 8;
    if (!getValue(r + 4, (int*)r))
    {
        _p.setZero();
        _g.setZero();
        memset(out, 0, *outSize);
        return false;
    }
    *outSize = *len1 + len2 + *(int*)r + 12;
    _state = 1;
    return true;
}

// 0x55980
bool Dh::Process(unsigned char const* in, int inSize, unsigned char* out, int* outSize)
{
    // LIFT: switch on _state (LobbyGate 0x5598d: test, dec chain).
    switch (_state)
    {
    case 0:
        if (!setupFactors(in, inSize) || !getValue(out, outSize))
            return false;
        break;
    case 1:
        if (in == 0 || inSize <= 0 || !_y.Set(1, in, inSize))
            return false;
        break;
    default:
        return false;
    }
    _state = -1;
    return true;
}

// 0x55a00
bool Dh::GetKey(unsigned char* out, int* size) const
{
    if (out == 0 || size == 0 || *size <= 0 || (_bits + 7) >> 3 > *size || _y.isZero() || _x.isZero())
        return false;
    BigInteger r;
    if (((_p.bits + 31) & ~31) <= 2048)
        r.ExpMod(&_y, &_x, &_p);
    int count = (r.bits + 7) >> 3;
    unsigned char buffer[128];
    if (count > 128)
        count = 0;
    else
        memcpy(buffer, r.digits, count);
    *size = (_bits + 7) >> 3;
    int i = 0;
    for (; i < count && i < *size; ++i)
        out[i] = buffer[i];
    for (; i < *size; ++i)
        out[i] = buffer[i % count]; // BUG: 0x55a00 count can be 0 here (divide by zero).
    return true;
}

// 0x55bb0
bool Dh::setupFactors(unsigned char const* data, int size)
{
    int bits = _bits;
    if (bits == 0 || data == 0 || size <= 4)
        return false;
    unsigned char const* end = data + size;
    int len1 = *(int const*)data;
    if (end < data + len1 + 8 || len1 <= 0)
        return false;
    unsigned char const* pStart = data + len1 + 4;
    int len2 = *(int const*)pStart;
    if (end < pStart + len2 + 4 || len2 <= 0 || (2 * bits + 7) >> 3 < len2)
        return false;
    unsigned char const* yStart = pStart + len2 + 4;
    int len3 = *(int const*)yStart;
    if (end < yStart + len3 + 4 || len3 <= 0 || size < len1 + len2 + len3 + 12)
        return false;
    if (!_g.Set(1, data + 4, len1) || !_p.Set(1, pStart + 4, len2) || !_y.Set(1, yStart + 4, len3))
        return false;
    if (pNotAboveG())
    {
        _p.setZero();
        _g.setZero();
        return false;
    }
    return true;
}

// 0x55d80
bool Dh::getValue(unsigned char* out, int* size)
{
    int half = _bits >> 1;
    if (half < 64)
        half = 64;
    if (out == 0 || size == 0 || *size <= 0 || (2 * _bits + 7) >> 3 > *size)
        return false;
    unsigned char buffer[128];
    int count = 128;
    if (half > 1024 || !CryptoKey::generateBigNumber(half, buffer, &count))
        return false;
    _x.Set(1, buffer, count);
    memset(buffer, 0, sizeof(buffer));
    BigInteger value;
    if (((_p.bits + 31) & ~31) <= 2048)
        value.ExpMod(&_g, &_x, &_p);
    int length = (value.bits + 7) >> 3;
    if (*size < length)
        length = 0;
    else
        memcpy(out, value.digits, length);
    *size = length;
    return true;
}
