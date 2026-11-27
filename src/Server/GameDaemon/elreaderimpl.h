// elreaderimpl.h: elreaderimpl.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DrElReaderImpl
{
public:
    __cdecl ~DrElReaderImpl(void);  // 0x6ed6d0
    static int __cdecl GetElAllocedSize(::DrEl const *, ::DrTableDef const &);  // 0x6ed6e0
    virtual void __cdecl DeleteElementExtra(::DrEl *, ::DrTableDef const &) const;  // 0x6ed9b0
    virtual bool __cdecl RelocateAddress(::DrEl *, ::DrTableDef const &, __int64, bool) const;  // 0x6edcb0
private:
    bool __cdecl __readBool(bool &, wchar_t const *, ::dr_log_info const *) const;  // 0x6edef0
    void __cdecl shinkBlank(wchar_t *, int, wchar_t const *) const;  // 0x6edfe0
    bool __cdecl isMultiKey(wchar_t const *) const;  // 0x6ee0e0
public:
    static wchar_t const * __cdecl tokenize(wchar_t const *, wchar_t, wchar_t *, short);  // 0x6ee160
private:
    short __cdecl findSubtype(wchar_t const *, ::DrElDef const &) const;  // 0x6ee200
    char __cdecl findEltype(wchar_t const *, ::DrTableDef const &) const;  // 0x6ee280
    short __cdecl findTableType(wchar_t const *) const;  // 0x6ee2f0
    char __cdecl findSeqstr(wchar_t const *, wchar_t const **, char) const;  // 0x6ee370
    bool __cdecl readSeq(char *, wchar_t const *, ::DrAttrDef const &, char *, ::dr_log_info const *) const;  // 0x6ee3d0
    bool __cdecl readSeq16(char *, wchar_t const *, ::DrAttrDef const &, short *, ::dr_log_info const *) const;  // 0x6ee470
    bool __cdecl readPropField(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6ee520
    bool __cdecl readSub(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6ee5c0
    bool __cdecl readVersion(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6ee630
public:
    __cdecl DrElReaderImpl(void);  // 0x6ee840
    virtual int __cdecl AllocedSize(::DrEl const *, ::DrTableDef const &) const;  // 0x6ee860
    static bool __cdecl RelocateElMemory(::DrEl const *, ::DrTableDef const &, char *, int &, bool, bool);  // 0x6ee870
    virtual void __cdecl DeleteElementExtraNativePointer(::DrEl *, ::DrTableDef const &) const;  // 0x6eedf0
private:
    bool __cdecl __readStr(wchar_t *&, wchar_t const *, int, bool, ::dr_log_info const *) const;  // 0x6ef1b0
    bool __cdecl __readRef(unsigned __int64 &, wchar_t const *, short, char, ::DrAliasMap *, ::dr_log_info const *) const;  // 0x6ef280
    bool __cdecl __readDateTime(::tm &, wchar_t const *, wchar_t const *, ::dr_log_info const *) const;  // 0x6ef5b0
    bool __cdecl readInt8(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6ef7c0
    bool __cdecl readInt16(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6ef870
    bool __cdecl readInt32(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6ef920
    bool __cdecl readInt64(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6ef9d0
    bool __cdecl readFloat32(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6efa80
    bool __cdecl readVector16(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6efb40
    bool __cdecl readVector32(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6efcb0
    bool __cdecl readIColor(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6efe20
    bool __cdecl readFColor(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6eff90
    bool __cdecl readBox(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6f0140
    bool __cdecl readMsec(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6f0340
    bool __cdecl readAngle(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6f0400
    bool __cdecl readStr(char *, wchar_t const *, ::DrAttrDef const &, bool, ::dr_log_info const *) const;  // 0x6f04a0
    bool __cdecl readTRef(char *, wchar_t const *, ::DrAttrDef const &, ::DrAliasMap *, ::dr_log_info const *) const;  // 0x6f0500
    bool __cdecl readScriptObj(char *, wchar_t const *, ::DrAttrDef const &, ::DrAliasMap *, ::dr_log_info const *) const;  // 0x6f06e0
    bool __cdecl readIcon(char *, wchar_t const *, ::DrAttrDef const &, ::DrAliasMap *, ::dr_log_info const *) const;  // 0x6f0ab0
    bool __cdecl readDateTime32(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6f0c30
    bool __cdecl readDateTime64(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6f0cf0
public:
    virtual bool __cdecl RelocateMemory(::DrEl const *, ::DrTableDef const &, char *, int &, bool) const;  // 0x6f0dc0
private:
    bool __cdecl readNative(char *, wchar_t const *, ::DrAttrDef const &, ::dr_log_info const *) const;  // 0x6f1a50
    bool __cdecl __readAttr(char *, wchar_t const *, ::DrAttrDef const &, ::DrAliasMap *, bool, ::dr_log_info const *) const;  // 0x6f1b70
    bool __cdecl readAttr(::XmlElement const *, ::DrAttrDef const &, void *, ::DrAliasMap *, bool) const;  // 0x6f1ee0
    bool __cdecl readSetupedAttr(::XmlElement const *, ::DrAttrDef const &, void *, ::DrAliasMap *, bool) const;  // 0x6f2090
    bool __cdecl readDefaultAttr(::DrAttrDef const &, void *, ::DrAliasMap *, ::dr_log_info const *, bool) const;  // 0x6f2250
    bool __cdecl setupDefaultEl(void);  // 0x6f2370
public:
    virtual bool __cdecl Setup(::DrTableDef const **, short, ::DrScriptObjDef const *, bool);  // 0x6f2760
private:
    bool __cdecl readAlias(::XmlElement const *, ::DrTableDef const &, ::DrElDef const &, ::DrAliasMap &, unsigned __int64 const *) const;  // 0x6f2790
    bool __cdecl initEl(::XmlElement const *, ::DrElDef const &, ::DrEl *) const;  // 0x6f29e0
    bool __cdecl initDefaultEl(::XmlElement const *, ::DrElDef const &, ::DrEl *) const;  // 0x6f2b10
    bool __cdecl readEl(::XmlElement const *, ::DrTableDef const &, ::DrElDef const &, char *, ::DrAliasMap &, unsigned __int64 const *) const;  // 0x6f2c10
    bool __cdecl readSetupedEl(::XmlElement const *, ::DrTableDef const &, ::DrElDef const &, char *, ::DrAliasMap &, unsigned __int64 const *) const;  // 0x6f2d70
public:
    virtual char __cdecl ReadAlias(::XmlElement const *, ::DrTableDef const &, ::DrAliasMap &, unsigned __int64 const *) const;  // 0x6f2ed0
    virtual char __cdecl ReadHeader(::XmlElement const *, ::DrTableDef const &, ::DrEl *) const;  // 0x6f2f90
    virtual char __cdecl ReadEl(::XmlElement const *, ::DrTableDef const &, char *, unsigned __int64, ::DrAliasMap &, unsigned __int64 const *) const;  // 0x6f3030
    virtual char __cdecl ReadDefaultEl(::XmlElement const *, ::DrTableDef const &, char *, unsigned __int64, ::DrAliasMap &, unsigned __int64 const *) const;  // 0x6f3150
};

bool __cdecl replaceEscaping(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> > &, wchar_t const *);  // 0x6f11c0
void __cdecl printSingleNode(::XmlNode const *, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> > &);  // 0x6f1360
void __cdecl printNodeStart(::XmlNode const *, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> > &);  // 0x6f15c0
void __cdecl printNodeEnd(::XmlNode const *, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> > &);  // 0x6f1820
void __cdecl xmlNodeTraverse(::XmlNode const *, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> > &);  // 0x6f18c0
void __cdecl printChildNode(::XmlNode const *, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::DrStlAllocator<wchar_t, 1> > &);  // 0x6f1960
