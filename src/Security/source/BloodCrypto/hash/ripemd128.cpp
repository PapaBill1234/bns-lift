// ripemd128.obj (LobbyGate PDB). RIPEMD-128 (reference code by A. Bosselaers).
#include "ripemd128.h"
#include <string.h>

#define ROL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define F(x, y, z) ((x) ^ (y) ^ (z))
#define G(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define H(x, y, z) (((x) | ~(y)) ^ (z))
#define I(x, y, z) (((x) & (z)) | ((y) & ~(z)))

#define STEP(f, a, b, c, d, x, s, k) \
    { (a) += f((b), (c), (d)) + (x) + (k); (a) = ROL((a), (s)); }

#define FF(a, b, c, d, x, s)  STEP(F, a, b, c, d, x, s, 0u)
#define GG(a, b, c, d, x, s)  STEP(G, a, b, c, d, x, s, 0x5a827999u)
#define HH(a, b, c, d, x, s)  STEP(H, a, b, c, d, x, s, 0x6ed9eba1u)
#define II(a, b, c, d, x, s)  STEP(I, a, b, c, d, x, s, 0x8f1bbcdcu)
#define FFF(a, b, c, d, x, s) STEP(F, a, b, c, d, x, s, 0u)
#define GGG(a, b, c, d, x, s) STEP(G, a, b, c, d, x, s, 0x6d703ef3u)
#define HHH(a, b, c, d, x, s) STEP(H, a, b, c, d, x, s, 0x5c4dd124u)
#define III(a, b, c, d, x, s) STEP(I, a, b, c, d, x, s, 0x50a28be6u)

// 0x5DA80 (file-static, no PDB type). Compression function.
static void hash(unsigned int* X, unsigned int* MDbuf)
{
    unsigned int aa = MDbuf[0], bb = MDbuf[1], cc = MDbuf[2], dd = MDbuf[3];
    unsigned int aaa = MDbuf[0], bbb = MDbuf[1], ccc = MDbuf[2], ddd = MDbuf[3];

    // left round 1
    FF(aa, bb, cc, dd, X[ 0], 11); FF(dd, aa, bb, cc, X[ 1], 14);
    FF(cc, dd, aa, bb, X[ 2], 15); FF(bb, cc, dd, aa, X[ 3], 12);
    FF(aa, bb, cc, dd, X[ 4],  5); FF(dd, aa, bb, cc, X[ 5],  8);
    FF(cc, dd, aa, bb, X[ 6],  7); FF(bb, cc, dd, aa, X[ 7],  9);
    FF(aa, bb, cc, dd, X[ 8], 11); FF(dd, aa, bb, cc, X[ 9], 13);
    FF(cc, dd, aa, bb, X[10], 14); FF(bb, cc, dd, aa, X[11], 15);
    FF(aa, bb, cc, dd, X[12],  6); FF(dd, aa, bb, cc, X[13],  7);
    FF(cc, dd, aa, bb, X[14],  9); FF(bb, cc, dd, aa, X[15],  8);
    // left round 2
    GG(aa, bb, cc, dd, X[ 7],  7); GG(dd, aa, bb, cc, X[ 4],  6);
    GG(cc, dd, aa, bb, X[13],  8); GG(bb, cc, dd, aa, X[ 1], 13);
    GG(aa, bb, cc, dd, X[10], 11); GG(dd, aa, bb, cc, X[ 6],  9);
    GG(cc, dd, aa, bb, X[15],  7); GG(bb, cc, dd, aa, X[ 3], 15);
    GG(aa, bb, cc, dd, X[12],  7); GG(dd, aa, bb, cc, X[ 0], 12);
    GG(cc, dd, aa, bb, X[ 9], 15); GG(bb, cc, dd, aa, X[ 5],  9);
    GG(aa, bb, cc, dd, X[ 2], 11); GG(dd, aa, bb, cc, X[14],  7);
    GG(cc, dd, aa, bb, X[11], 13); GG(bb, cc, dd, aa, X[ 8], 12);
    // left round 3
    HH(aa, bb, cc, dd, X[ 3], 11); HH(dd, aa, bb, cc, X[10], 13);
    HH(cc, dd, aa, bb, X[14],  6); HH(bb, cc, dd, aa, X[ 4],  7);
    HH(aa, bb, cc, dd, X[ 9], 14); HH(dd, aa, bb, cc, X[15],  9);
    HH(cc, dd, aa, bb, X[ 8], 13); HH(bb, cc, dd, aa, X[ 1], 15);
    HH(aa, bb, cc, dd, X[ 2], 14); HH(dd, aa, bb, cc, X[ 7],  8);
    HH(cc, dd, aa, bb, X[ 0], 13); HH(bb, cc, dd, aa, X[ 6],  6);
    HH(aa, bb, cc, dd, X[13],  5); HH(dd, aa, bb, cc, X[11], 12);
    HH(cc, dd, aa, bb, X[ 5],  7); HH(bb, cc, dd, aa, X[12],  5);
    // left round 4
    II(aa, bb, cc, dd, X[ 1], 11); II(dd, aa, bb, cc, X[ 9], 12);
    II(cc, dd, aa, bb, X[11], 14); II(bb, cc, dd, aa, X[10], 15);
    II(aa, bb, cc, dd, X[ 0], 14); II(dd, aa, bb, cc, X[ 8], 15);
    II(cc, dd, aa, bb, X[12],  9); II(bb, cc, dd, aa, X[ 4],  8);
    II(aa, bb, cc, dd, X[13],  9); II(dd, aa, bb, cc, X[ 3], 14);
    II(cc, dd, aa, bb, X[ 7],  5); II(bb, cc, dd, aa, X[15],  6);
    II(aa, bb, cc, dd, X[14],  8); II(dd, aa, bb, cc, X[ 5],  6);
    II(cc, dd, aa, bb, X[ 6],  5); II(bb, cc, dd, aa, X[ 2], 12);
    // parallel round 1
    III(aaa, bbb, ccc, ddd, X[ 5],  8); III(ddd, aaa, bbb, ccc, X[14],  9);
    III(ccc, ddd, aaa, bbb, X[ 7],  9); III(bbb, ccc, ddd, aaa, X[ 0], 11);
    III(aaa, bbb, ccc, ddd, X[ 9], 13); III(ddd, aaa, bbb, ccc, X[ 2], 15);
    III(ccc, ddd, aaa, bbb, X[11], 15); III(bbb, ccc, ddd, aaa, X[ 4],  5);
    III(aaa, bbb, ccc, ddd, X[13],  7); III(ddd, aaa, bbb, ccc, X[ 6],  7);
    III(ccc, ddd, aaa, bbb, X[15],  8); III(bbb, ccc, ddd, aaa, X[ 8], 11);
    III(aaa, bbb, ccc, ddd, X[ 1], 14); III(ddd, aaa, bbb, ccc, X[10], 14);
    III(ccc, ddd, aaa, bbb, X[ 3], 12); III(bbb, ccc, ddd, aaa, X[12],  6);
    // parallel round 2
    HHH(aaa, bbb, ccc, ddd, X[ 6],  9); HHH(ddd, aaa, bbb, ccc, X[11], 13);
    HHH(ccc, ddd, aaa, bbb, X[ 3], 15); HHH(bbb, ccc, ddd, aaa, X[ 7],  7);
    HHH(aaa, bbb, ccc, ddd, X[ 0], 12); HHH(ddd, aaa, bbb, ccc, X[13],  8);
    HHH(ccc, ddd, aaa, bbb, X[ 5],  9); HHH(bbb, ccc, ddd, aaa, X[10], 11);
    HHH(aaa, bbb, ccc, ddd, X[14],  7); HHH(ddd, aaa, bbb, ccc, X[15],  7);
    HHH(ccc, ddd, aaa, bbb, X[ 8], 12); HHH(bbb, ccc, ddd, aaa, X[12],  7);
    HHH(aaa, bbb, ccc, ddd, X[ 4],  6); HHH(ddd, aaa, bbb, ccc, X[ 9], 15);
    HHH(ccc, ddd, aaa, bbb, X[ 1], 13); HHH(bbb, ccc, ddd, aaa, X[ 2], 11);
    // parallel round 3
    GGG(aaa, bbb, ccc, ddd, X[15],  9); GGG(ddd, aaa, bbb, ccc, X[ 5],  7);
    GGG(ccc, ddd, aaa, bbb, X[ 1], 15); GGG(bbb, ccc, ddd, aaa, X[ 3], 11);
    GGG(aaa, bbb, ccc, ddd, X[ 7],  8); GGG(ddd, aaa, bbb, ccc, X[14],  6);
    GGG(ccc, ddd, aaa, bbb, X[ 6],  6); GGG(bbb, ccc, ddd, aaa, X[ 9], 14);
    GGG(aaa, bbb, ccc, ddd, X[11], 12); GGG(ddd, aaa, bbb, ccc, X[ 8], 13);
    GGG(ccc, ddd, aaa, bbb, X[12],  5); GGG(bbb, ccc, ddd, aaa, X[ 2], 14);
    GGG(aaa, bbb, ccc, ddd, X[10], 13); GGG(ddd, aaa, bbb, ccc, X[ 0], 13);
    GGG(ccc, ddd, aaa, bbb, X[ 4],  7); GGG(bbb, ccc, ddd, aaa, X[13],  5);
    // parallel round 4
    FFF(aaa, bbb, ccc, ddd, X[ 8], 15); FFF(ddd, aaa, bbb, ccc, X[ 6],  5);
    FFF(ccc, ddd, aaa, bbb, X[ 4],  8); FFF(bbb, ccc, ddd, aaa, X[ 1], 11);
    FFF(aaa, bbb, ccc, ddd, X[ 3], 14); FFF(ddd, aaa, bbb, ccc, X[11], 14);
    FFF(ccc, ddd, aaa, bbb, X[15],  6); FFF(bbb, ccc, ddd, aaa, X[ 0], 14);
    FFF(aaa, bbb, ccc, ddd, X[ 5],  6); FFF(ddd, aaa, bbb, ccc, X[12],  9);
    FFF(ccc, ddd, aaa, bbb, X[ 2], 12); FFF(bbb, ccc, ddd, aaa, X[13],  9);
    FFF(aaa, bbb, ccc, ddd, X[ 9], 12); FFF(ddd, aaa, bbb, ccc, X[ 7],  5);
    FFF(ccc, ddd, aaa, bbb, X[10], 15); FFF(bbb, ccc, ddd, aaa, X[14],  8);

    // combine results
    ddd += cc + MDbuf[1];
    MDbuf[1] = MDbuf[2] + dd + aaa;
    MDbuf[2] = MDbuf[3] + aa + bbb;
    MDbuf[3] = MDbuf[0] + bb + ccc;
    MDbuf[0] = ddd;
}

// 0x27FC0 (folded with Rsa::KeySize). LIFT: No Ripemd128::GetType symbol.
int Ripemd128::GetType() const
{
    return 0;
}

// 0x54FB0
int Ripemd128::Size() const
{
    return 16;
}

// 0x5E890
bool Ripemd128::Digest(unsigned char const* in, int size, unsigned char* digest, int* digestSize) const
{
    if (in == 0 || digest == 0 || digestSize == 0 || *digestSize < 16)
        return false;

    unsigned int X[16];
    unsigned int MDbuf[4];
    memset(X, 0, sizeof(X));
    MDbuf[0] = 0x67452301u;
    MDbuf[1] = 0xefcdab89u;
    MDbuf[2] = 0x98badcfeu;
    MDbuf[3] = 0x10325476u;

    unsigned char const* p = in;
    for (int n = size; n > 63; n -= 64)
    {
        for (int i = 0; i < 16; ++i, p += 4)
            X[i] = p[0] | (p[1] << 8) | (p[2] << 16) | (static_cast<unsigned int>(p[3]) << 24);
        hash(X, MDbuf);
    }

    memset(X, 0, sizeof(X));
    for (int i = 0; i < (size & 63); ++i)
    {
        // BUG: 0x5E890 uses '=' and not '^='. Only the last byte of each word stays.
        X[i >> 2] = static_cast<unsigned int>(*p++) << (8 * (i & 3));
    }
    X[(static_cast<unsigned int>(size) >> 2) & 15] ^= 1u << (8 * (size & 3) + 7);
    if ((size & 63) >= 56)
    {
        hash(X, MDbuf);
        memset(X, 0, sizeof(X));
    }
    X[14] = static_cast<unsigned int>(size << 3);
    X[15] = static_cast<unsigned int>(size >> 29);
    hash(X, MDbuf);

    *digestSize = 16;
    for (int i = 0; i < 16; i += 4)
        memcpy(digest + i, &MDbuf[i >> 2], 4);
    return true;
}
