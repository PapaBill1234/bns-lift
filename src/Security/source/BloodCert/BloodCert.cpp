// BloodCert64.lib (closed library). LIFT: file. The PDB has only the public symbols of this code.
// The code comes from the LobbyGate disassembly (0x4bf70 - 0x4cc5f).
#include "BloodCert.h"
#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>
#include "Crypto.h"
#include "aes128.h"
#include "rsa.h"
#include "ripemd160.h"

// LIFT: The original has no caller of BloodCert::IsValid. The closed library object is kept as a whole.
// The lift keeps it with /INCLUDE in LobbyGate, SmartCouponDaemon and PostOfficeDaemon. CacheGate has no BloodCert.
#if defined(LIFT_EXE_LG) || defined(LIFT_EXE_SCD) || defined(LIFT_EXE_POD)
#pragma comment(linker, "/INCLUDE:?IsValid@BloodCert@@SA?AW4ErrCode@1@_KW4Module@1@PEBEHPEADPEAHPEAE@Z")
#endif

// LIFT: The certificate RSA public modulus (LobbyGate 0x6C504, 128 bytes). keyhere. The lift has no key data. ❓ name
static unsigned char const s_certPublicKey[128] = {0};

// LIFT: The expire value that means "no expire date" (0x4c22e). ❓ name
static unsigned long long const CERT_NO_EXPIRE = 2524575599ULL;

// LIFT: Layout of the decrypted certificate body (896 bytes, CertDec::Decrypt 0x4c5d0 stack). ❓ names
struct CertBody
{
    int dataSize;              // +0
    int digestSize;            // +4
    int textSize;              // +8
    int reserved;              // +12
    unsigned char digest[32];  // +16, RIPEMD-160 of the 600 bytes at +48
    unsigned long long expire; // +48
    int type;                  // +56
    unsigned char body[836];   // +60
};

NIC* NIC::_instance = 0;

// LIFT: Inline code. Delete of NIC::_instance (0x4c0b9, 0x4c9a4). The object comes from malloc. ❓ name
static inline void destroyNic()
{
    NIC::_instance->~NIC();
    free(NIC::_instance);
    NIC::_instance = 0;
}

// 0x4c9d0
NIC::~NIC()
{
    if (_list != 0)
    {
        free(_list);
        _list = 0;
    }
}

// 0x4c940
__declspec(noinline) bool NIC::Initialize()
{
    if (_instance != 0)
        return false;
    _instance = new (malloc(sizeof(NIC))) NIC();
    if (_instance->getNicInfomationIpHelper() > 0)
        return true;
    destroyNic();
    return false;
}

// 0x4ca10
__declspec(noinline) int NIC::getNicInfomationIpHelper()
{
    // LIFT: The original reads _instance, not this (0x4ca1c).
    NIC* nic = _instance;
    ULONG size = sizeof(IP_ADAPTER_INFO);
    IP_ADAPTER_INFO* adapters = static_cast<IP_ADAPTER_INFO*>(malloc(size));
    if (GetAdaptersInfo(adapters, &size) == ERROR_BUFFER_OVERFLOW)
        adapters = static_cast<IP_ADAPTER_INFO*>(realloc(adapters, size));
    if (GetAdaptersInfo(adapters, &size) == NO_ERROR)
    {
        for (IP_ADAPTER_INFO* adapter = adapters; adapter != 0; adapter = adapter->Next)
        {
            // BUG: 0x4ca7a loses the old list when realloc fails.
            Info* list = nic->_list != 0 ? static_cast<Info*>(realloc(nic->_list, sizeof(Info) * (nic->_count + 1)))
                                         : static_cast<Info*>(malloc(sizeof(Info) * (nic->_count + 1)));
            nic->_list = list;
            if (list == 0)
                goto fail;
            memset(&list[nic->_count], 0, sizeof(Info));
            if (adapter->AddressLength != 6)
                goto fail;
            for (int i = 0; i < 6; ++i)
                nic->_list[nic->_count].mac[i] = adapter->Address[i];

            char const* p = adapter->IpAddressList.IpAddress.String;
            unsigned long ip = 0;
            int part = 0;
            long value;
            char c = *p;
            if (c != 0)
            {
                int shift = 24;
                while (shift >= 0)
                {
                    if (c == '.')
                    {
                        ip |= static_cast<unsigned char>(part) << shift;
                        shift -= 8;
                        part = 0;
                    }
                    else
                    {
                        if (!isdigit(c))
                        {
                            value = -1;
                            goto store;
                        }
                        part = *p + 10 * part - '0';
                    }
                    c = *++p;
                    if (c == 0)
                        break;
                }
            }
            value = static_cast<long>(ip | part);
        store:
            nic->_list[nic->_count++].ip = static_cast<unsigned long>(value);
        }
        free(adapters);
        return nic->_count;
    }
fail:
    free(adapters);
    return -1;
}

// 0x4c390
__declspec(noinline) int SSN::Generate(BloodCert::Module module, unsigned long ip, unsigned char const* const mac,
                                       unsigned char* out, int outSize)
{
    (void)module;
    (void)outSize;
    if (out == 0)
        return 1;
    Ripemd160 hash;
    // LIFT: "LBBG" is constant in LobbyGate (0x4c3f1). ❓ It can come from BloodCert::MODULE_CODE_STRING.
    char text[37] = "LBBG";
    sprintf_s(&text[4], 16, "%03d.%03d.%03d.%03d", (ip >> 24) & 0xff, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff);
    sprintf_s(&text[19], 18, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    unsigned char key[24];
    int keySize = 20;
    if (!hash.Digest(reinterpret_cast<unsigned char const*>(text), 36, key, &keySize))
        return 2;
    Aes128 aes;
    unsigned char enc[48];
    int encSize = 48;
    Crypto::Initialize();
    if (!aes.Setup(key, keySize, 0))
        return 2;
    if (!aes.Encrypt(reinterpret_cast<unsigned char const*>(text), 36, enc, &encSize))
        return 2;
    keySize = 32;
    if (hash.Digest(enc, encSize, out, &keySize))
        return 0;
    return 2;
}

// 0x4c5d0
__declspec(noinline) int CertDec::Decrypt(unsigned char const* cert, int certSize, int* type, unsigned long long* expire,
                                          unsigned char* digest, int* digestSize, unsigned char* grade, char* text,
                                          int* textSize, unsigned char* data, int* dataSize, int* reserved)
{
    (void)reserved;
    if (certSize != 1000 || (data != 0 && (dataSize == 0 || *dataSize < 256)) ||
        (digest != 0 && (digestSize == 0 || *digestSize < 32)) || (text != 0 && (textSize == 0 || *textSize < 300)))
        return 1;
    Ripemd160 hash;
    unsigned char const* encrypted = cert + 104;
    if (*reinterpret_cast<unsigned short const*>(cert) != 0xCEB1)
        return 2;
    if (*reinterpret_cast<unsigned short const*>(cert + 2) != 6)
        return 3;
    *grade = cert[36];
    unsigned char md[32];
    int size = 32;
    if (!hash.Digest(encrypted, 896, md, &size))
        return 4;
    if (memcmp(cert + 4, md, size) != 0)
        return 4;
    size = 896;
    RsaPublic rsa;
    // LIFT: The original sets the modulus without RsaPublic::Setup (0x4c6f6 - 0x4c72c). ❓ form
    if (!rsa._encoder.Setup(1024))
        return 6;
    if (!rsa._n.Set(1, s_certPublicKey, 128))
        return 6;
    rsa._error = 0;
    CertBody plain;
    if (!rsa.Decrypt(encrypted, 896, reinterpret_cast<unsigned char*>(&plain), &size))
        return 6;
    size_t const dataLen = static_cast<unsigned int>(plain.dataSize);
    size_t const digestLen = static_cast<unsigned int>(plain.digestSize);
    size_t const textLen = static_cast<unsigned int>(plain.textSize);
    if (plain.dataSize == 0)
        return 7;
    if (plain.digestSize == 0)
        return 8;
    size = 32;
    if (!hash.Digest(reinterpret_cast<unsigned char const*>(&plain.expire), 600, md, &size) ||
        memcmp(plain.digest, md, size) != 0)
        return 6;
    *expire = plain.expire;
    *type = plain.type;
    // BUG: 0x4c86d - 0x4c8f0 copy the sizes from the certificate without a check against the buffer sizes.
    if (data != 0)
    {
        memcpy(data, plain.body, dataLen);
        *dataSize = static_cast<int>(dataLen);
    }
    if (digest != 0)
    {
        memcpy(digest, &plain.body[dataLen], digestLen);
        *digestSize = static_cast<int>(digestLen);
    }
    if (text != 0)
    {
        memset(text, 0, *textSize);
        if (static_cast<int>(textLen) != 0)
        {
            memcpy(text, &plain.body[dataLen + digestLen], textLen);
            *textSize = static_cast<int>(textLen);
        }
    }
    return 0;
}

// 0x4bf70 LIFT: The PDB has no public name for this function. ❓ name
static __declspec(noinline) bool isValidNic(unsigned char const* digest, int digestSize)
{
    if (digestSize <= 0)
        return false;
    NIC* nic = NIC::_instance;
    int count;
    if (nic != 0 || (NIC::Initialize() && (nic = NIC::_instance) != 0))
        count = nic->_count;
    else
    {
        nic = NIC::_instance;
        count = 0;
    }
    int i = 0;
    for (; i < count; ++i)
    {
        if (nic == 0)
        {
            if (!NIC::Initialize())
            {
                nic = NIC::_instance;
                continue;
            }
            nic = NIC::_instance;
            if (nic == 0)
                continue;
        }
        if (i >= nic->_count)
            continue;
        unsigned char md[32];
        NIC::Info const& info = nic->_list[i];
        if (SSN::Generate(BloodCert::MODULE_NONE, info.ip, info.mac, md, 32) == 0 && memcmp(md, digest, digestSize) == 0)
        {
            nic = NIC::_instance;
            break;
        }
        nic = NIC::_instance;
    }
    if (nic != 0)
        destroyNic();
    return i < count;
}

// 0x4c100
BloodCert::ErrCode BloodCert::IsValid(unsigned long long now, Module module, unsigned char const* cert, int certSize,
                                      char* text, int* textSize, unsigned char* grade)
{
    (void)module;
    ErrCode result = ERR_OK;
    int digestSize = 32;
    int dataSize = 512;
    int const textCapacity = textSize != 0 ? *textSize : 0;
    if (cert == 0)
        return ERR_NO_CERT;
    if (certSize < 1000)
        return ERR_CERT_SIZE;
    int type;
    unsigned long long expire;
    unsigned char digest[40];
    unsigned char data[512];
    int rc = CertDec::Decrypt(cert, certSize, &type, &expire, digest, &digestSize, grade, text, textSize, data, &dataSize,
                              0);
    // LIFT: 0x4c1e9 maps a type that is not 16 to the code 5. ❓ form
    if (rc == 0 && type != 16)
        rc = 5;
    switch (rc)
    {
    case 0:
        if (expire != CERT_NO_EXPIRE && now >= expire)
        {
            if (text != 0)
                memset(text, 0, textCapacity);
            return ERR_EXPIRED;
        }
        if (!isValidNic(digest, digestSize))
        {
            if (text != 0)
                memset(text, 0, textCapacity);
            return ERR_NIC;
        }
        if (type != 17 && text != 0)
            memset(text, 0, *textSize);
        return result;
    case 2:
    case 5:
    case 6:
    case 7:
        if (text != 0)
            memset(text, 0, textCapacity);
        return ERR_CERT_FORMAT;
    case 3:
        if (text != 0)
            memset(text, 0, textCapacity);
        return ERR_CERT_VERSION;
    case 8:
        if (text != 0)
            memset(text, 0, textCapacity);
        return ERR_NO_DATA;
    case 9:
        if (text != 0)
            memset(text, 0, textCapacity);
        return ERR_NO_DIGEST;
    default:
        if (text != 0)
            memset(text, 0, textCapacity);
        return ERR_UNKNOWN;
    }
}
