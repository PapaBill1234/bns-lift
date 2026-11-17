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
    // ❓ InstanceSize and Create use the value GetType() - 1 (2, 3, 64, 80).
    static int InstanceSize(Type type);
    // ❓ The PDB name gives (Type, void*, int). The code uses rcx=buffer, edx=size, r8d=type.
    static Crypto* Create(void* buffer, int size, Type type);

    mutable int _error; // ❓ +8, the const Encrypt and Decrypt write it
    bool _alloc; // ❓ +12, true when the object came from malloc

protected:
    Crypto() : _error(0), _alloc(false) {}
};
static_assert(sizeof(Crypto) == 16, "sizeof Crypto");
