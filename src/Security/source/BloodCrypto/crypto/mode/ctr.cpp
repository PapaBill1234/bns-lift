// ctr.obj (CacheGate PDB). CTR block cipher mode.
#include "ctr.h"
#include <string.h>
#include "Crypto.h"

// 0x35ca0 (??_G). The body resets the vptr to CryptoMode and destroys the cipher.
Ctr::~Ctr()
{
    if (_crypto != 0)
    {
        Crypto::Destroy(_crypto);
        _crypto = 0;
    }
}

// 0x368e0
bool Ctr::Setup(Crypto* crypto, int round, unsigned char const* key, int keySize,
                unsigned char const* iv, int ivSize)
{
    if (crypto == 0 || crypto->BlockSize() == 0)
        return false;
    if (_crypto != 0)
    {
        Crypto::Destroy(_crypto);
        _crypto = 0;
    }
    _crypto = crypto;
    _blockSize = crypto->BlockSize();
    _pos = 0;
    bool ok = _crypto->Setup(key, keySize, round);
    if (!ok)
        return ok;
    memset(_counter, 0, sizeof(_counter));
    memset(_keyStream, 0, sizeof(_keyStream));
    for (int i = 0; i < (ivSize > _blockSize ? _blockSize : ivSize); ++i)
        _counter[i] = iv[i];
    int s = 32;
    return _crypto->Encrypt(_counter, _blockSize, _keyStream, &s) != 0;
}

// 0x36a10
bool Ctr::Encrypt(unsigned char const* in, int size, unsigned char* out, int* /*encCount*/)
{
    // BUG: 0x36a10 does not set *encCount.
    if (size == 0)
        return true;
    for (int i = 0; i < size; ++i)
    {
        if (_pos == _blockSize)
        {
            for (int j = 0; j < _blockSize; ++j)
            {
                if (++_counter[j] != 0)
                    break;
            }
            int s = 32;
            if (!_crypto->Encrypt(_counter, _blockSize, _keyStream, &s))
                return false;
            _pos = 0;
        }
        out[i] = in[i] ^ _keyStream[_pos++];
    }
    return true;
}

// 0x36ad0
bool Ctr::Decrypt(unsigned char const* in, int size, unsigned char* out, int* encCount)
{
    return Encrypt(in, size, out, encCount);
}
