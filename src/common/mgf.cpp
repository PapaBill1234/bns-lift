// mgf.obj (LobbyGate PDB).
#include "mgf.h"
#include <string.h>

// 0x5EB40
bool MaskGenerator::generate(unsigned char const* seed, int seedSize, unsigned char* out, int outSize)
{
    int counter = 0;
    if (_hash == 0 || seed == 0 || seedSize <= 0 || out == 0 || outSize <= 0)
        return false;
    if (seedSize >= 1024)
        seedSize = 1024;
    unsigned char input[1028];
    memcpy(input, seed, seedSize);
    do
    {
        // The counter is in host byte order (not big-endian as in PKCS #1).
        *reinterpret_cast<int*>(input + seedSize) = counter++;
        int hashSize = _size;
        _hash->Digest(input, seedSize + 4, _digest, &hashSize);
        for (int i = 0; outSize > 0 && i < hashSize; ++i)
        {
            *out++ = _digest[i];
            --outSize;
        }
    } while (outSize > 0);
    memset(_digest, 0, _size);
    return true;
}
