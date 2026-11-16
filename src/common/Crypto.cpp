// Crypto.obj (CacheGate PDB).
#include "Crypto.h"
#include <stdlib.h>
#include <string.h>
#include <intrin.h>
#include "aes128.h"
#include "aes128NI.h"
#include "aes128Table.h"
#include "blowfish.h"
#include "rsa.h"
#include <new>

// 0x35b30
void Crypto::Initialize()
{
    if (Aes128::_Delegator.setup == 0)
    {
        int cpuInfo[4];
        __cpuid(cpuInfo, 1);
        if (cpuInfo[2] & 0x2000000) // ECX bit 25: AES-NI
        {
            Aes128::_Delegator.setup = Aes128NI_Setup;
            Aes128::_Delegator.encrypt = Aes128NI_Encrypt;
            Aes128::_Delegator.decrypt = Aes128NI_Decrypt;
        }
        else
        {
            Aes128::_Delegator.setup = Aes128Table_Setup;
            Aes128::_Delegator.encrypt = Aes128Table_Encrypt;
            Aes128::_Delegator.decrypt = Aes128Table_Decrypt;
        }
    }
}

// 0x35be0
void Crypto::Destroy(Crypto* crypto)
{
    if (crypto == 0)
        return;
    bool alloc = crypto->_alloc;
    switch (static_cast<int>(crypto->GetType()))
    {
    case AES128:
        static_cast<Aes128*>(crypto)->~Aes128();
        break;
    case BLOWFISH:
        static_cast<Blowfish*>(crypto)->~Blowfish();
        break;
    case RSA_PUBLIC:
        static_cast<RsaPublic*>(crypto)->~RsaPublic();
        break;
    case RSA_PRIVATE:
        static_cast<RsaPrivate*>(crypto)->~RsaPrivate();
        break;
    default:
        return;
    }
    if (alloc)
        free(crypto);
}

// 0x55150 (LobbyGate)
int Crypto::InstanceSize(Type type)
{
    switch (static_cast<int>(type))
    {
    case 2:
        return sizeof(Aes128);
    case 3:
        return sizeof(Blowfish);
    case 64:
        return sizeof(RsaPublic);
    case 80:
        return sizeof(RsaPrivate);
    default:
        return -1;
    }
}

// 0x55200 (LobbyGate)
Crypto* Crypto::Create(void* buffer, int size, Type type)
{
    unsigned int need;
    switch (static_cast<int>(type))
    {
    case 2:
        need = sizeof(Aes128);
        break;
    case 3:
        need = sizeof(Blowfish);
        break;
    case 64:
        need = sizeof(RsaPublic);
        break;
    case 80:
        need = sizeof(RsaPrivate);
        break;
    default:
        return 0;
    }
    void* mem;
    if (buffer != 0)
    {
        if (static_cast<unsigned int>(size) < need)
            return 0;
        mem = buffer;
    }
    else
    {
        mem = malloc(need);
    }
    if (mem == 0)
        return 0;
    Crypto* crypto;
    switch (static_cast<int>(type))
    {
    case 2:
        crypto = new (mem) Aes128();
        break;
    case 3:
    {
        Blowfish* blowfish = new (mem) Blowfish();
        blowfish->_round = -1;
        crypto = blowfish;
        break;
    }
    case 64:
        crypto = new (mem) RsaPublic();
        break;
    default:
        crypto = new (mem) RsaPrivate();
        break;
    }
    crypto->_error = 0;
    crypto->_alloc = (buffer == 0);
    return crypto;
}
