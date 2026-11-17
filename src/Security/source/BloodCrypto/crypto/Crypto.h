// Crypto.obj (CacheGate PDB). The PDB has no type records for this class.
// The layout and the member names come from the code. LIFT: Member names. The PDB has no field list.
#pragma once

class Crypto
{
public:
    enum Type
    {
        AES128 = 3,   // LIFT: No PDB type record.
        BLOWFISH = 4, // LIFT: No PDB type record.
        RSA_PUBLIC = 65,  // LIFT: No PDB type record.
        RSA_PRIVATE = 81, // LIFT: No PDB type record.
    };

    virtual bool Setup(unsigned char const* key, int keySize, int round) = 0;
    virtual void Cleanup() = 0;
    virtual Type GetType() const = 0;
    virtual int BlockSize() const = 0;
    virtual int KeySize() const = 0;
    virtual int EncSize(int size) const = 0;
    virtual bool Encrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const = 0;
    virtual bool Decrypt(unsigned char const* in, int size, unsigned char* out, int* encCount) const = 0;

    static void Initialize();
    static void Destroy(Crypto* crypto);
    // LIFT: LobbyGate table 0x551a4 maps 2, 3, 64, 80. GetType gives 4 (0x5c570), 0x41 (0x52a40), 0x51 (0x52a50). The callers give GetType() - 1.
    static int InstanceSize(Type type);
    // LIFT: LobbyGate Create 0x55200 reads r8d as type (0x5520a), rcx as buffer (0x5520d), edx as size (0x55242).
    static Crypto* Create(void* buffer, int size, Type type);

    mutable int _error; // +8 (LobbyGate 0x55279), the const Encrypt and Decrypt write it
    bool _alloc; // +12 (LobbyGate 0x55281), true when the object came from malloc

protected:
    Crypto() : _error(0), _alloc(false) {}
};
static_assert(sizeof(Crypto) == 16, "sizeof Crypto");
