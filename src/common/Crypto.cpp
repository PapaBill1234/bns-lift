// Crypto.obj (CacheGate PDB).
#include "Crypto.h"
#include <stdlib.h>
#include <string.h>
#include <intrin.h>
#include "aes128.h"
#include "aes128NI.h"
#include "aes128Table.h"
#include "blowfish.h"

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
    case 65: // ❓ type 65 and 81 are not Crypto types (CryptoMode types?)
    case 81:
    {
        // BUG: 0x35c1b calls vtable slot 8 (+0x40) with arg 0. Crypto has only 8 slots.
        typedef void (*Slot8)(Crypto* self, int flags);
        Slot8 fn = (*reinterpret_cast<Slot8**>(crypto))[8];
        fn(crypto, 0);
        break;
    }
    default:
        return;
    }
    if (alloc)
        free(crypto);
}
