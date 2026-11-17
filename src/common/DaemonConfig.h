// DaemonConfig.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
// The XmlReader DLL types are here because only the config code uses them.
#pragma once
#include <stddef.h>
#include "XmlReader.h"

struct XmlCfgDef
{
    enum  // PDB type 0x2433
    {
        CFG_NONE = 0,
        CFG_INT = 1,
        CFG_INT64 = 2,
        CFG_FLOAT = 3,
        CFG_BOOL = 4,
        CFG_IP = 5,
        CFG_STR = 6,
        CFG_DIR = 7,
        CFG_ANSI = 8,
        CFG_GROUP = 9,
        CFG_TYPE_MAX = 10,
    };
    enum  // PDB type 0x2435
    {
        CFG_OPTIONAL = 0,
        CFG_REQUIRED = 1,
        CFG_DERIVED = 2,
        CFG_DEV = 3,
    };

    unsigned long long offset;
    wchar_t const* name;
    int type;
    int reqOption;
    void const* defaultValue;
    wchar_t const* desc;
};
static_assert(sizeof(XmlCfgDef) == 0x28, "sizeof XmlCfgDef");
static_assert(offsetof(XmlCfgDef, desc) == 0x20, "XmlCfgDef::desc");

struct XmlCfgDefLocal
{
    enum CFG_DEF_TYPE  // PDB type 0x239A
    {
        CFG_DEF_TYPE_INT = 0,
        CFG_DEF_TYPE_INT64 = 1,
        CFG_DEF_TYPE_FLOAT = 2,
        CFG_DEF_TYPE_BOOL = 3,
        CFG_DEF_TYPE_STRING = 4,
        CFG_DEF_TYPE_ANSI_STRING = 5,
        CFG_DEF_TYPE_IP = 6,
        CFG_DEF_TYPE_DIRECTORY = 7,
        CFG_DEF_TYPE_GUID = 8,
    };

    unsigned long long offset;
    wchar_t const* name;
    int type;
    CFG_DEF_TYPE defType;
    void const* minValue;
    void const* maxValue;
    bool reload;
    void const* defaultValue;
    unsigned long long refOffset;
};
static_assert(sizeof(XmlCfgDefLocal) == 0x40, "sizeof XmlCfgDefLocal");
static_assert(offsetof(XmlCfgDefLocal, refOffset) == 0x38, "XmlCfgDefLocal::refOffset");


struct XmlCfgDef2;

class XmlConfigReader
{
public:
    // The MSVC ABI puts overloads of a virtual function in the vtable in reverse order. Declare slot 1 first.
    virtual bool Initialize(XmlCfgDef const* def, int count, void* (*alloc)(unsigned long long), unsigned long long size) const = 0;   // slot 1
    virtual bool Initialize(XmlCfgDef2 const* def, int count, void* (*alloc)(unsigned long long), unsigned long long size) const = 0;  // slot 0
    virtual void Cleanup() const = 0;                                                                                                 // slot 2
    virtual void* Read(wchar_t const* fileName, wchar_t const* configName, bool const readOnly) const = 0;                           // slot 5
    virtual void* Read(unsigned long long&, wchar_t const*, wchar_t const*, bool const, int const, int const, bool const,
                       bool const) const = 0;                                                                                         // slot 4, not used
    virtual void* Read(unsigned long long&, unsigned char*, unsigned int, wchar_t const*, wchar_t const*, bool const, int const,
                       int const, bool const, bool const) const = 0;                                                                  // slot 3, not used
    virtual wchar_t const* GetLastErrorString() const = 0;                                                                            // slot 6
};

class DaemonConfig
{
public:
    static void* Load(XmlCfgDef const* def, int count, unsigned long long size, wchar_t const* fileName,
                      wchar_t const* configName, bool readOnly);                                    // 0xc600
    static void* AllocConfig(unsigned long long size);                                             // 0xc9f0
    static void Dump(wchar_t const* name, void const* config, XmlCfgDef const* defs, int count);  // 0xca10
    static void FreeConfig(void* config);  // LIFT: inline, source line 115
};
