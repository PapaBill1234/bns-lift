// DaemonConfig.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
// The XmlReader DLL types are here because only the config code uses them.
#pragma once
#include <stddef.h>

struct XmlCfgDef
{
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
    unsigned long long offset;
    wchar_t const* name;
    int type;
    int defType;
    void const* minValue;
    void const* maxValue;
    bool reload;
    void const* defaultValue;
    unsigned long long refOffset;
};
static_assert(sizeof(XmlCfgDefLocal) == 0x40, "sizeof XmlCfgDefLocal");
static_assert(offsetof(XmlCfgDefLocal, refOffset) == 0x38, "XmlCfgDefLocal::refOffset");

// ❓ The value names are not in the PDB. Values from the Dump switch (0xca10, 0x1880).
enum XML_CFG_TYPE  // ❓ name
{
    XML_CFG_TYPE_INT = 1,       // ❓
    XML_CFG_TYPE_INT64 = 2,     // ❓
    XML_CFG_TYPE_FLOAT = 3,     // ❓
    XML_CFG_TYPE_BOOL = 4,      // ❓
    XML_CFG_TYPE_ADDRESS = 5,   // ❓
    XML_CFG_TYPE_WSTRING = 6,   // ❓
    XML_CFG_TYPE_WSTRING2 = 7,  // ❓
    XML_CFG_TYPE_STRING = 8,    // ❓
};
enum { CFG_DEF_TYPE_GUID = 8 };  // defType value

struct XmlCfgDef2;
class XmlReaderIO;
class XmlReaderLog;

// Interface of XmlReader_sv64.dll. Only the vtable layout is used.
class XmlReader
{
public:
    virtual bool Initialize(XmlReaderIO* io, XmlReaderLog const* log, bool flag) const = 0;  // slot 0
};

class XmlConfigReader
{
public:
    virtual bool Initialize(XmlCfgDef2 const* def, int count, void* (*alloc)(unsigned long long), unsigned long long size) const = 0;  // slot 0
    virtual bool Initialize(XmlCfgDef const* def, int count, void* (*alloc)(unsigned long long), unsigned long long size) const = 0;   // slot 1
    virtual void Cleanup() = 0;                                                                                                       // slot 2
    virtual void* Read3() const = 0;  // ❓ slot 3, Read overload, not used
    virtual void* Read4() const = 0;  // ❓ slot 4, Read overload, not used
    virtual void* Read(wchar_t const* fileName, wchar_t const* configName, bool const readOnly) const = 0;                           // slot 5
    virtual wchar_t const* GetLastErrorString() const = 0;                                                                            // slot 6
};

class DaemonConfig
{
public:
    static void* Load(XmlCfgDef const* def, int count, unsigned long long size, wchar_t const* fileName,
                      wchar_t const* configName, bool readOnly);                                    // 0xc600
    static void* AllocConfig(unsigned long long size);                                             // 0xc9f0
    static void Dump(wchar_t const* name, void const* config, XmlCfgDef const* defs, int count);  // 0xca10
    static void FreeConfig(void* config);  // ❓ inline, source line 115
};
