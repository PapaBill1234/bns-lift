// aes128Table.obj (CacheGate PDB). Table (T-box) AES-128.
// Each table entry is 8 bytes. The code reads only the low 32 bits.
#include "aes128Table.h"
#include <string.h>
#include "aes128.h"

#include "aes128TableData.inc"

#define TE(t, x) ((unsigned int)(t)[(x)])
#define B0(x) ((x) & 0xFF)
#define B1(x) (((x) >> 8) & 0xFF)
#define B2(x) (((x) >> 16) & 0xFF)
#define B3(x) ((x) >> 24)

// 0x38370
void aes128TableSetupEncKey(unsigned int* rk, unsigned char const* key, int keycnt)
{
    // BUG: 0x38370 copies keycnt bytes. A key longer than 176 bytes writes past rk.
    memcpy(rk, key, keycnt);
    for (int i = 0; i < 10; ++i, rk += 4)
    {
        unsigned int temp = rk[3];
        rk[4] = rk[0] ^ (unsigned int)Rcon[i]
              ^ (TE(E_precalc_sbox4, B1(temp)) & 0x000000FF)
              ^ (TE(E_precalc_sbox4, B2(temp)) & 0x0000FF00)
              ^ (TE(E_precalc_sbox4, B3(temp)) & 0x00FF0000)
              ^ (TE(E_precalc_sbox4, B0(temp)) & 0xFF000000);
        rk[5] = rk[1] ^ rk[4];
        rk[6] = rk[2] ^ rk[5];
        rk[7] = rk[3] ^ rk[6];
    }
}

// 0x385c0
void aes128TableSetupDecKey(unsigned int* rk, unsigned int const* encKey)
{
    // LIFT: 0x385c0 copies the round keys in reverse order and reads the key bytes from memory.
    for (int i = 0, j = 40; i <= 40; i += 4, j -= 4)
    {
        rk[i + 0] = encKey[j + 0];
        rk[i + 1] = encKey[j + 1];
        rk[i + 2] = encKey[j + 2];
        rk[i + 3] = encKey[j + 3];
    }
    for (int r = 1; r < 10; ++r)
    {
        rk += 4;
        for (int j = 0; j < 4; ++j)
        {
            unsigned char const* w = reinterpret_cast<unsigned char const*>(&rk[j]);
            rk[j] = TE(D_precalc_sbox0, (unsigned char)TE(E_precalc_sbox4, w[0]))
                  ^ TE(D_precalc_sbox1, (unsigned char)TE(E_precalc_sbox4, w[1]))
                  ^ TE(D_precalc_sbox2, (unsigned char)TE(E_precalc_sbox4, w[2]))
                  ^ TE(D_precalc_sbox3, (unsigned char)TE(E_precalc_sbox4, w[3]));
        }
    }
}

// 0x38790
void aes128TableEncrypt(unsigned int* out, unsigned int const* in, unsigned int const* rk)
{
    unsigned int s0 = in[0] ^ rk[0];
    unsigned int s1 = in[1] ^ rk[1];
    unsigned int s2 = in[2] ^ rk[2];
    unsigned int s3 = in[3] ^ rk[3];
    unsigned int t0, t1, t2, t3;
    for (int r = 1; r <= 9; ++r)
    {
        rk += 4;
        t0 = rk[0] ^ TE(E_precalc_sbox0, B0(s0)) ^ TE(E_precalc_sbox1, B1(s1)) ^ TE(E_precalc_sbox2, B2(s2)) ^ TE(E_precalc_sbox3, B3(s3));
        t1 = rk[1] ^ TE(E_precalc_sbox0, B0(s1)) ^ TE(E_precalc_sbox1, B1(s2)) ^ TE(E_precalc_sbox2, B2(s3)) ^ TE(E_precalc_sbox3, B3(s0));
        t2 = rk[2] ^ TE(E_precalc_sbox0, B0(s2)) ^ TE(E_precalc_sbox1, B1(s3)) ^ TE(E_precalc_sbox2, B2(s0)) ^ TE(E_precalc_sbox3, B3(s1));
        t3 = rk[3] ^ TE(E_precalc_sbox0, B0(s3)) ^ TE(E_precalc_sbox1, B1(s0)) ^ TE(E_precalc_sbox2, B2(s1)) ^ TE(E_precalc_sbox3, B3(s2));
        s0 = t0; s1 = t1; s2 = t2; s3 = t3;
    }
    rk += 4;
    out[0] = rk[0] ^ (TE(E_precalc_sbox4, B0(s0)) & 0x000000FF) ^ (TE(E_precalc_sbox4, B1(s1)) & 0x0000FF00)
                   ^ (TE(E_precalc_sbox4, B2(s2)) & 0x00FF0000) ^ (TE(E_precalc_sbox4, B3(s3)) & 0xFF000000);
    out[1] = rk[1] ^ (TE(E_precalc_sbox4, B0(s1)) & 0x000000FF) ^ (TE(E_precalc_sbox4, B1(s2)) & 0x0000FF00)
                   ^ (TE(E_precalc_sbox4, B2(s3)) & 0x00FF0000) ^ (TE(E_precalc_sbox4, B3(s0)) & 0xFF000000);
    out[2] = rk[2] ^ (TE(E_precalc_sbox4, B0(s2)) & 0x000000FF) ^ (TE(E_precalc_sbox4, B1(s3)) & 0x0000FF00)
                   ^ (TE(E_precalc_sbox4, B2(s0)) & 0x00FF0000) ^ (TE(E_precalc_sbox4, B3(s1)) & 0xFF000000);
    out[3] = rk[3] ^ (TE(E_precalc_sbox4, B0(s3)) & 0x000000FF) ^ (TE(E_precalc_sbox4, B1(s0)) & 0x0000FF00)
                   ^ (TE(E_precalc_sbox4, B2(s1)) & 0x00FF0000) ^ (TE(E_precalc_sbox4, B3(s2)) & 0xFF000000);
}

// 0x38d10
void aes128TableDecrypt(unsigned int* out, unsigned int const* in, unsigned int const* rk)
{
    unsigned int s0 = in[0] ^ rk[0];
    unsigned int s1 = in[1] ^ rk[1];
    unsigned int s2 = in[2] ^ rk[2];
    unsigned int s3 = in[3] ^ rk[3];
    unsigned int t0, t1, t2, t3;
    for (int r = 1; r <= 9; ++r)
    {
        rk += 4;
        t0 = rk[0] ^ TE(D_precalc_sbox0, B0(s0)) ^ TE(D_precalc_sbox1, B1(s3)) ^ TE(D_precalc_sbox2, B2(s2)) ^ TE(D_precalc_sbox3, B3(s1));
        t1 = rk[1] ^ TE(D_precalc_sbox0, B0(s1)) ^ TE(D_precalc_sbox1, B1(s0)) ^ TE(D_precalc_sbox2, B2(s3)) ^ TE(D_precalc_sbox3, B3(s2));
        t2 = rk[2] ^ TE(D_precalc_sbox0, B0(s2)) ^ TE(D_precalc_sbox1, B1(s1)) ^ TE(D_precalc_sbox2, B2(s0)) ^ TE(D_precalc_sbox3, B3(s3));
        t3 = rk[3] ^ TE(D_precalc_sbox0, B0(s3)) ^ TE(D_precalc_sbox1, B1(s2)) ^ TE(D_precalc_sbox2, B2(s1)) ^ TE(D_precalc_sbox3, B3(s0));
        s0 = t0; s1 = t1; s2 = t2; s3 = t3;
    }
    rk += 4;
    out[0] = rk[0] ^ (TE(D_precalc_sbox4, B0(s0)) & 0x000000FF) ^ (TE(D_precalc_sbox4, B1(s3)) & 0x0000FF00)
                   ^ (TE(D_precalc_sbox4, B2(s2)) & 0x00FF0000) ^ (TE(D_precalc_sbox4, B3(s1)) & 0xFF000000);
    out[1] = rk[1] ^ (TE(D_precalc_sbox4, B0(s1)) & 0x000000FF) ^ (TE(D_precalc_sbox4, B1(s0)) & 0x0000FF00)
                   ^ (TE(D_precalc_sbox4, B2(s3)) & 0x00FF0000) ^ (TE(D_precalc_sbox4, B3(s2)) & 0xFF000000);
    out[2] = rk[2] ^ (TE(D_precalc_sbox4, B0(s2)) & 0x000000FF) ^ (TE(D_precalc_sbox4, B1(s1)) & 0x0000FF00)
                   ^ (TE(D_precalc_sbox4, B2(s0)) & 0x00FF0000) ^ (TE(D_precalc_sbox4, B3(s3)) & 0xFF000000);
    out[3] = rk[3] ^ (TE(D_precalc_sbox4, B0(s3)) & 0x000000FF) ^ (TE(D_precalc_sbox4, B1(s2)) & 0x0000FF00)
                   ^ (TE(D_precalc_sbox4, B2(s1)) & 0x00FF0000) ^ (TE(D_precalc_sbox4, B3(s0)) & 0xFF000000);
}

// 0x39290
bool Aes128Table_Setup(Aes128* aes, unsigned char const* key, int keycnt, int /*round*/)
{
    if (keycnt < 16)
    {
        aes->_error = 5;
        return false;
    }
    aes128TableSetupEncKey(aes->_encKey, key, keycnt);
    aes128TableSetupDecKey(aes->_decKey, aes->_encKey);
    return true;
}

// 0x392e0
bool Aes128Table_Encrypt(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount)
{
    if (in == 0 || out == 0 || encCount == 0 || *encCount < size)
    {
        aes->_error = 3;
        return false;
    }
    // BUG: 0x392e0 checks *encCount < size, but it writes size rounded up to 16 bytes.
    unsigned char const* end = in + size;
    unsigned int* dst = reinterpret_cast<unsigned int*>(out);
    for (unsigned char const* src = in; src < end;)
    {
        unsigned int const* block = reinterpret_cast<unsigned int const*>(src);
        long long step = end - src;
        unsigned long long pad[2];
        if (static_cast<unsigned long long>(step) >= 16)
        {
            step = 16;
        }
        else
        {
            pad[0] = 0;
            pad[1] = 0;
            memcpy(pad, src, end - src);
            block = reinterpret_cast<unsigned int const*>(pad);
        }
        aes128TableEncrypt(dst, block, aes->_encKey);
        src += step;
        dst += 4;
    }
    *encCount = static_cast<int>(reinterpret_cast<unsigned char*>(dst) - out);
    aes->_error = 0;
    return true;
}

// 0x39400
bool Aes128Table_Decrypt(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount)
{
    if (in == 0 || out == 0 || encCount == 0 || *encCount < size)
    {
        aes->_error = 3;
        return false;
    }
    // BUG: 0x39400 reads a full 16-byte block when size is not a multiple of 16.
    unsigned char const* end = in + size;
    unsigned int const* src = reinterpret_cast<unsigned int const*>(in);
    unsigned int* dst = reinterpret_cast<unsigned int*>(out);
    while (src < reinterpret_cast<unsigned int const*>(end))
    {
        aes128TableDecrypt(dst, src, aes->_decKey);
        src += 4;
        dst += 4;
    }
    *encCount = static_cast<int>(reinterpret_cast<unsigned char*>(dst) - out);
    aes->_error = 0;
    return true;
}
