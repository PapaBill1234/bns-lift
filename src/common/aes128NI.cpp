// aes128NI.obj (CacheGate PDB). AES-128 with the AES-NI instructions.
#include "aes128NI.h"
#include <string.h>
#include <wmmintrin.h>
#include "aes128.h"

// _mm_aeskeygenassist_si128 needs an immediate. The original code uses a switch.
static __m128i keyGenAssist(__m128i key, int i)  // ❓ lift helper name, not in any PDB
{
    switch (i)
    {
    case 0: return _mm_aeskeygenassist_si128(key, 0x01);
    case 1: return _mm_aeskeygenassist_si128(key, 0x02);
    case 2: return _mm_aeskeygenassist_si128(key, 0x04);
    case 3: return _mm_aeskeygenassist_si128(key, 0x08);
    case 4: return _mm_aeskeygenassist_si128(key, 0x10);
    case 5: return _mm_aeskeygenassist_si128(key, 0x20);
    case 6: return _mm_aeskeygenassist_si128(key, 0x40);
    case 7: return _mm_aeskeygenassist_si128(key, 0x80);
    case 8: return _mm_aeskeygenassist_si128(key, 0x1B);
    default: return _mm_aeskeygenassist_si128(key, 0x36);
    }
}

// 0x394c0
bool Aes128NI_Setup(Aes128* aes, unsigned char const* key, int keycnt, int /*round*/)
{
    if (keycnt < 16)
    {
        aes->_error = 5;
        return false;
    }
    __m128i* ek = reinterpret_cast<__m128i*>(aes->_encKey);
    __m128i* dk = reinterpret_cast<__m128i*>(aes->_decKey);
    __m128i k = _mm_loadu_si128(reinterpret_cast<__m128i const*>(key));
    _mm_storeu_si128(&ek[0], k);
    for (int i = 0; i < 10; ++i)
    {
        __m128i a = keyGenAssist(k, i);
        k = _mm_xor_si128(k, _mm_slli_si128(k, 4));
        k = _mm_xor_si128(k, _mm_slli_si128(k, 4));
        k = _mm_xor_si128(k, _mm_slli_si128(k, 4));
        k = _mm_xor_si128(k, _mm_shuffle_epi32(a, 0xFF));
        _mm_storeu_si128(&ek[i + 1], k);
    }
    _mm_storeu_si128(&dk[0], _mm_loadu_si128(&ek[0]));
    for (int i = 1; i < 10; ++i)
        _mm_storeu_si128(&dk[i], _mm_aesimc_si128(_mm_loadu_si128(&ek[i])));
    _mm_storeu_si128(&dk[10], _mm_loadu_si128(&ek[10]));
    return true;
}

// 0x39610
bool Aes128NI_Encrypt(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount)
{
    if (in == 0 || out == 0 || encCount == 0 || *encCount < size)
    {
        aes->_error = 3;
        return false;
    }
    // BUG: 0x39610 checks *encCount < size, but it writes size rounded up to 16 bytes.
    __m128i const* ek = reinterpret_cast<__m128i const*>(aes->_encKey);
    unsigned char const* end = in + size;
    unsigned char* dst = out;
    for (unsigned char const* src = in; src < end;)
    {
        __m128i x;
        long long step = end - src;
        if (static_cast<unsigned long long>(step) >= 16)
        {
            step = 16;
            x = _mm_loadu_si128(reinterpret_cast<__m128i const*>(src));
        }
        else
        {
            unsigned long long pad[2];
            pad[0] = 0;
            pad[1] = 0;
            memcpy(pad, src, end - src);
            x = _mm_loadu_si128(reinterpret_cast<__m128i const*>(pad));
        }
        x = _mm_xor_si128(x, _mm_loadu_si128(&ek[0]));
        for (int r = 1; r < 10; ++r)
            x = _mm_aesenc_si128(x, _mm_loadu_si128(&ek[r]));
        x = _mm_aesenclast_si128(x, _mm_loadu_si128(&ek[10]));
        _mm_storeu_si128(reinterpret_cast<__m128i*>(dst), x);
        src += step;
        dst += 16;
    }
    *encCount = static_cast<int>(dst - out);
    aes->_error = 0;
    return true;
}

// 0x39750
bool Aes128NI_Decrypt(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount)
{
    if (in == 0 || out == 0 || encCount == 0 || *encCount < size)
    {
        aes->_error = 3;
        return false;
    }
    // BUG: 0x39750 reads a full 16-byte block when size is not a multiple of 16.
    __m128i const* dk = reinterpret_cast<__m128i const*>(aes->_decKey);
    unsigned char const* end = in + size;
    unsigned char* dst = out;
    for (unsigned char const* src = in; src < end; src += 16, dst += 16)
    {
        __m128i x = _mm_loadu_si128(reinterpret_cast<__m128i const*>(src));
        x = _mm_xor_si128(x, _mm_loadu_si128(&dk[10]));
        for (int r = 9; r > 0; --r)
            x = _mm_aesdec_si128(x, _mm_loadu_si128(&dk[r]));
        x = _mm_aesdeclast_si128(x, _mm_loadu_si128(&dk[0]));
        _mm_storeu_si128(reinterpret_cast<__m128i*>(dst), x);
    }
    *encCount = static_cast<int>(dst - out);
    aes->_error = 0;
    return true;
}
