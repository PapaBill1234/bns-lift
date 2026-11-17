// aes128Table.obj (CacheGate PDB). Table (T-box) AES-128.
#pragma once

class Aes128;

void aes128TableSetupEncKey(unsigned int* rk, unsigned char const* key, int keycnt);
void aes128TableSetupDecKey(unsigned int* rk, unsigned int const* encKey);
void aes128TableEncrypt(unsigned int* out, unsigned int const* in, unsigned int const* rk);
void aes128TableDecrypt(unsigned int* out, unsigned int const* in, unsigned int const* rk);

bool Aes128Table_Setup(Aes128* aes, unsigned char const* key, int keycnt, int round);
bool Aes128Table_Encrypt(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount);
bool Aes128Table_Decrypt(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount);
