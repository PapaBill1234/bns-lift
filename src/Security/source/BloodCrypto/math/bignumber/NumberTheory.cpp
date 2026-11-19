// NumberTheory.obj (BloodCrypto). The code follows libtommath
// (mp_exptmod_fast, mp_invmod_slow, fast_mp_invmod).
// The compiler put Add, Sub and RightShift inline in invMod and InvMod. The lift calls them.
#include "BigInteger.h"
#include <string.h>

namespace
{
// LIFT: Inline helper. No PDB symbol.
inline bool isOdd(BigInteger const& x)
{
    return x.bits != 0 && (x.digits[0] & 1) != 0;
}

// LIFT: Inline helper. No PDB symbol. A value is "even" for the loops when bits != 0 and bit 0 is clear.
inline bool isEvenNonZero(BigInteger const& x)
{
    return x.bits != 0 && (x.digits[0] & 1) == 0;
}

// LIFT: Inline helper. No PDB symbol. Same test as the code: sign, bits, then the digits.
inline bool isEqual(BigInteger const& x, BigInteger const& y, int (*absCompare)(BigInteger const*, BigInteger const*))
{
    return x.sign == y.sign && x.bits == y.bits && absCompare(&x, &y) == 0;
}
} // namespace

// 0x4ae30
void BigInteger::expMod(BigInteger const* a, BigInteger const* e, BigInteger const* n)
{
    BigInteger M[64];
    BigInteger res;

    int winsize;
    int ebits = e->bits;
    if (ebits <= 21)
        winsize = 1;
    else if (ebits <= 36)
        winsize = 3;
    else if (ebits <= 140)
        winsize = 4;
    else
        winsize = ebits > 450 ? 6 : 5;

    // The modulus must be odd (mp_exptmod_fast).
    bool oddModulus = (n->digits[0] & 1) != 0;
    if (oddModulus)
    {
        // mp_montgomery_setup
        unsigned int b = n->digits[0];
        unsigned int x = (((b + 2) & 4) << 1) + b;
        x *= 2 - b * x;
        x *= 2 - b * x;
        x *= 2 - b * x;
        unsigned int rho = 0u - x;

        res.montgomeryNormalize(n);

        BigInteger& M1 = M[1];
        if (absCompare(n, a) > 0)
        {
            if (a != &M1)
            {
                M1.sign = a->sign;
                M1.bits = a->bits;
                memcpy(M1.digits, a->digits, sizeof(M1.digits));
            }
        }
        else
        {
            Divide(a, n, 0, &M1);
        }

        BigInteger tmp;
        tmp.Mul(&M1, &res);
        Divide(&tmp, n, 0, &M1);

        int half = 1 << (winsize - 1);
        BigInteger* top = &M[half];
        if (&M1 != top)
        {
            top->sign = M1.sign;
            top->bits = M1.bits;
            for (int i = 0; i < MAX_DIGITS; ++i)
                top->digits[i] = M1.digits[i];
        }
        for (int i = 0; i < winsize - 1; ++i)
        {
            top->Sqr(top);
            top->montgomeryReduce(n, rho);
        }
        for (int i = half + 1; i < (1 << winsize); ++i)
        {
            M[i].Mul(&M[i - 1], &M1);
            M[i].montgomeryReduce(n, rho);
        }

        int mode = 0;
        int bitcnt = 1;
        int bitcpy = 0;
        int bitbuf = 0;
        int digidx = e->digitCount() - 1;
        unsigned int buf = 0;
        for (;;)
        {
            if (--bitcnt == 0)
            {
                if (digidx == -1)
                    break;
                buf = e->digits[digidx--];
                bitcnt = 32;
            }
            int y = static_cast<int>(buf >> 31);
            buf <<= 1;
            if (mode == 0 && y == 0)
                continue;
            if (mode == 1 && y == 0)
            {
                res.Sqr(&res);
                res.montgomeryReduce(n, rho);
                continue;
            }
            bitbuf |= y << (winsize - ++bitcpy);
            mode = 2;
            if (bitcpy == winsize)
            {
                for (int i = 0; i < winsize; ++i)
                {
                    res.Sqr(&res);
                    res.montgomeryReduce(n, rho);
                }
                res.Mul(&res, &M[bitbuf]);
                res.montgomeryReduce(n, rho);
                bitcpy = 0;
                bitbuf = 0;
                mode = 1;
            }
        }

        if (mode == 2 && bitcpy > 0)
        {
            for (int i = 0; i < bitcpy; ++i)
            {
                res.Sqr(&res);
                res.montgomeryReduce(n, rho);
                bitbuf <<= 1;
                if ((bitbuf & (1 << winsize)) != 0)
                {
                    res.Mul(&res, &M1);
                    res.montgomeryReduce(n, rho);
                }
            }
        }

        res.montgomeryReduce(n, rho);
        if (&res != this)
        {
            sign = res.sign;
            bits = res.bits;
            memcpy(digits, res.digits, sizeof(digits));
        }
        // LIFT: 0x58670 (LobbyGate) each path has its own destructor of res. This return keeps the two paths apart.
        return;
    }
}

// 0x49db0
bool BigInteger::invMod(BigInteger const* a, BigInteger const* b)
{
    // b must be positive and not zero.
    if (b->bits != 0 && b->sign == -1)
        return false;
    if (b->sign == 1 && b->bits == 1 && b->digits[0] == 0)
        return false;

    BigInteger x;
    BigInteger y;
    BigInteger u;
    BigInteger v;
    BigInteger A;
    BigInteger B;
    BigInteger C;
    BigInteger D;
    BigInteger one;
    one.Set(1LL);
    BigInteger zero;

    Divide(a, b, 0, &x);
    y.Set(b, 1);
    if (isEvenNonZero(x) && isEvenNonZero(y))
        return false;

    u.Set(&x, 1);
    v.Set(&y, 1);
    A.Set(1LL);
    D.Set(1LL);

    do
    {
        while (isEvenNonZero(u))
        {
            u.RightShift(&u, 1);
            if (isOdd(A) || isOdd(B))
            {
                A.Add(&A, &y);
                B.Sub(&B, &x);
            }
            A.RightShift(&A, 1);
            B.RightShift(&B, 1);
        }
        while (isEvenNonZero(v))
        {
            v.RightShift(&v, 1);
            if (isOdd(C) || isOdd(D))
            {
                C.Add(&C, &y);
                D.Sub(&D, &x);
            }
            C.RightShift(&C, 1);
            D.RightShift(&D, 1);
        }
        int c = u.sign;
        if (u.sign < v.sign)
            c = -1;
        else if (u.bits != 0)
            c = absCompare(&u, &v);
        if (c < 0)
        {
            v.Sub(&v, &u);
            C.Sub(&C, &A);
            D.Sub(&D, &B);
        }
        else
        {
            u.Sub(&u, &v);
            A.Sub(&A, &C);
            B.Sub(&B, &D);
        }
    } while (!(u.sign == 1 && u.bits == 1 && u.digits[0] == 0));

    if (!isEqual(v, one, absCompare))
        return false;

    while (C.sign <= zero.sign && (C.sign < zero.sign || (C.bits != 0 && absCompare(&C, &zero) < 0)))
        C.Add(&C, b);
    while (absCompare(&C, b) >= 0)
        C.Sub(&C, b);

    if (&C != this)
    {
        sign = C.sign;
        bits = C.bits;
        memcpy(digits, C.digits, sizeof(digits));
    }
    return true;
}

// 0x48f10
bool BigInteger::InvMod(BigInteger const* a, BigInteger const* b)
{
    if (b->bits != 0 && (b->digits[0] & 1) == 0)
        return invMod(a, b);

    BigInteger x;
    BigInteger y;
    BigInteger u;
    BigInteger v;
    BigInteger B;
    BigInteger D;
    BigInteger one;
    one.Set(1LL);

    x.Set(b, 1);
    y.Set(a, 1);
    y.sign = 1;
    u.Set(&x, 1);
    v.Set(&y, 1);
    D.Set(1LL);

    do
    {
        while (isEvenNonZero(u))
        {
            u.RightShift(&u, 1);
            if (isOdd(B))
                B.Sub(&B, &x);
            B.RightShift(&B, 1);
        }
        while (isEvenNonZero(v))
        {
            v.RightShift(&v, 1);
            if (isOdd(D))
                D.Sub(&D, &x);
            D.RightShift(&D, 1);
        }
        int c = u.sign;
        if (u.sign < v.sign)
            c = -1;
        else if (u.bits != 0)
            c = absCompare(&u, &v);
        if (c < 0)
        {
            v.Sub(&v, &u);
            D.Sub(&D, &B);
        }
        else
        {
            u.Sub(&u, &v);
            B.Sub(&B, &D);
        }
    } while (!(u.sign == 1 && u.bits == 1 && u.digits[0] == 0));

    if (!isEqual(v, one, absCompare))
        return false;

    while (D.bits != 0 && D.sign == -1)
        D.Add(&D, b);

    if (&D != this)
    {
        sign = a->sign * D.sign;
        bits = D.bits;
        memcpy(digits, D.digits, sizeof(digits));
    }
    return true;
}

// NumberTheory.obj (LobbyGate PDB). The functions below are in LobbyGate only.

// 0x692A0. Trial division table: the first 256 primes.
static unsigned int const primes[256] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
    59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
    617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719,
    727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827,
    829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
    947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049,
    1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163,
    1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283,
    1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423,
    1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
    1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619,
};

// 0x696A0. Number of low zero bits in a 4-bit value (libtommath lnz).
static int const lnz[16] = { 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0 };

// 0x570d0
void BigInteger::ExpMod(BigInteger const* a, BigInteger const* e, BigInteger const* n)
{
    if (e->bits != 0 && e->sign == -1)
    {
        // BUG: 0x570F4 computes the inverse in t, but expMod uses a and not t.
        BigInteger t;
        t.InvMod(a, n);
        BigInteger* me = const_cast<BigInteger*>(e);
        me->sign = -me->sign;
        expMod(a, e, n);
        if (e != this)
            me->sign = -me->sign;
    }
    else
    {
        expMod(a, e, n);
    }
}

// 0x57190
bool BigInteger::isPrimeMR(BigInteger const* n, unsigned long long b)
{
    if (b <= 1)
        return false;

    BigInteger a;
    a.Set(static_cast<long long>(b));
    BigInteger one;
    one.Set(1LL);

    BigInteger n1;
    BigInteger r;
    BigInteger y;
    n1.Sub(n, &one);

    int s = 0;
    if (n1.isZero())
    {
        r.setZero();
    }
    else
    {
        int count = n1.digitCount();
        while (s < count && n1.digits[s] == 0)
            ++s;
        unsigned int digit = n1.digits[s];
        s *= 32;
        if ((digit & 1) == 0)
        {
            unsigned int low;
            do
            {
                low = digit & 0xF;
                s += lnz[low];
                digit >>= 4;
            } while (low == 0);
        }
        r.RightShift(&n1, s);
    }

    // The compiler put ExpMod inline here, with the 2048-bit limit.
    if (((n->bits + 31) & ~31) <= 2048)
        y.ExpMod(&a, &r, n);

    if (isEqual(y, one, absCompare))
        return true;
    if (isEqual(y, n1, absCompare))
        return true;

    for (int j = 1; j <= s - 1; ++j)
    {
        if (isEqual(y, n1, absCompare))
            break;
        BigInteger t;
        t.Sqr(&y);
        Divide(&t, n, 0, &y);
        if (isEqual(y, one, absCompare))
            return false;
    }
    return isEqual(y, n1, absCompare);
}

// 0x561a0. LIFT: noinline only in LG: the LG original keeps a call.
#if defined(LIFT_EXE_LG)
__declspec(noinline)
#endif
bool BigInteger::IsPrime() const
{
    unsigned int r;
    for (int i = 0; i < 256; ++i)
    {
        Divide(this, primes[i], 0, &r);
        if (r == 0)
            return false;
    }
    for (unsigned int const* p = primes; p < primes + 8; ++p)
    {
        if (!isPrimeMR(this, *p))
            return false;
    }
    return true;
}
