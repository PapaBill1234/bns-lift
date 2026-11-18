// BloodCert64.lib (closed library). LIFT: file. The PDB has only the public symbols of this code.
// The code comes from the LobbyGate disassembly (0x4bf70 - 0x4cc5f).
#pragma once

class BloodCert
{
public:
    // LIFT: Enum values. The PDB has only the enum name. The values come from IsValid (0x4c100). ❓ names
    enum ErrCode
    {
        ERR_OK = 0,           // ❓
        ERR_UNKNOWN = 1,      // ❓
        ERR_NO_CERT = 2,      // ❓
        ERR_CERT_SIZE = 3,    // ❓
        ERR_CERT_FORMAT = 4,  // ❓
        ERR_CERT_VERSION = 5, // ❓
        ERR_NO_DATA = 6,      // ❓
        ERR_NO_DIGEST = 7,    // ❓
        ERR_NIC = 9,          // ❓
        ERR_EXPIRED = 10,     // ❓
    };
    // LIFT: Enum values. The PDB has only the enum name. ❓ values
    enum Module
    {
        MODULE_NONE = 0, // ❓
    };

    // 0x4c100
    static ErrCode IsValid(unsigned long long now, Module module, unsigned char const* cert, int certSize, char* text,
                           int* textSize, unsigned char* grade);
};

class SSN
{
public:
    // 0x4c390
    static int Generate(BloodCert::Module module, unsigned long ip, unsigned char const* const mac, unsigned char* out,
                        int outSize);
};

class CertDec
{
public:
    // 0x4c5d0
    static int Decrypt(unsigned char const* cert, int certSize, int* type, unsigned long long* expire,
                       unsigned char* digest, int* digestSize, unsigned char* grade, char* text, int* textSize,
                       unsigned char* data, int* dataSize, int* reserved);
};

// LIFT: Layout from NIC::Initialize (0x4c940) and getNicInfomationIpHelper (0x4ca10). The PDB has no field list.
// Vtable 0x86B10.
class NIC
{
public:
    // LIFT: One entry is 12 bytes (0x4ca10). ❓ names
    struct Info
    {
        unsigned char mac[6]; // +0 ❓
        unsigned long ip;     // +8 ❓
    };

    NIC() : _count(0), _index(-1), _list(0) {}
    // 0x4c9d0 (??_E)
    virtual ~NIC();

    // 0x4c940
    static bool Initialize();

private:
    // 0x4ca10
    int getNicInfomationIpHelper();

public:
    int _count;  // +8 ❓
    int _index;  // +12 ❓ (set to -1, no reader)
    Info* _list; // +16 ❓

    static NIC* _instance;
};
