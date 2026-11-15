// aes128NI.obj (CacheGate PDB). AES-128 with the AES-NI instructions.
#pragma once

class Aes128;

bool Aes128NI_Setup(Aes128* aes, unsigned char const* key, int keycnt, int round);
bool Aes128NI_Encrypt(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount);
bool Aes128NI_Decrypt(Aes128 const* aes, unsigned char const* in, int size, unsigned char* out, int* encCount);
