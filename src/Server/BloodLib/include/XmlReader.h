// Interfaces of XmlReader_sv64.dll (CacheGate PDB). Only the vtable layout is used.
// The slot lists are from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>

class XmlDoc;
class XmlElement;
class XmlNode;
class XmlTextNode;
class XmlPieceReader;
class XmlReaderIO;
class XmlReaderLog;

class XmlDoc
{
public:
    virtual bool IsValid() const = 0;                     // slot 0
    virtual wchar_t const* Name() const = 0;              // slot 1
    virtual XmlElement* Root() = 0;                       // slot 2
    virtual int BinarySize() const = 0;                   // slot 3
    virtual void SerializeTo(char* buffer, int size) const = 0;  // slot 4
    virtual void SerializeFrom(char* buffer, int size) = 0;      // slot 5
};

class XmlElement
{
public:
    virtual int ChildElementCount() const = 0;                                   // slot 0
    virtual XmlElement const* FirstChildElement() const = 0;                     // slot 1
    virtual XmlElement const* NextElement() const = 0;                           // slot 2
    virtual wchar_t const* Name() const = 0;                                     // slot 3
    virtual long LineNumber() const = 0;                                         // slot 4
    virtual int AttributeCount() const = 0;                                      // slot 5
    virtual wchar_t const* Attribute(wchar_t const* name) const = 0;             // slot 8
    virtual wchar_t const* Attribute(int index) const = 0;                       // slot 7
    virtual wchar_t const* Attribute(unsigned int index, wchar_t const* name) const = 0;  // slot 6
    virtual wchar_t const* AttributeName(int index) const = 0;                   // slot 9
    virtual int AttributeIndex(wchar_t const* name) const = 0;                   // slot 10
    virtual XmlNode* ToXmlNode() = 0;                                            // slot 12
    virtual XmlNode const* ToXmlNode() const = 0;                                // slot 11
};

class XmlNode
{
public:
    virtual int Type() const = 0;                                  // slot 0
    virtual bool IsValid() const = 0;                              // slot 1
    virtual wchar_t const* Name() const = 0;                       // slot 2
    virtual XmlDoc const* GetDoc() const = 0;                      // slot 3
    virtual XmlNode const* Parent() const = 0;                     // slot 4
    virtual int ChildCount() const = 0;                            // slot 5
    virtual XmlNode const* FirstChild() const = 0;                 // slot 6
    virtual XmlNode const* Child(int index) const = 0;             // slot 7
    virtual XmlNode const* Next() const = 0;                       // slot 8
    virtual long LineNumber() const = 0;                           // slot 9
    virtual wchar_t const* GetURI() const = 0;                     // slot 10
    virtual int MemSize() const = 0;                               // slot 11
    virtual int Clone(char* buffer, int size) const = 0;           // slot 12
    virtual XmlNode* CloneNode(char* buffer, int size) const = 0;  // slot 13
    virtual int BinarySize() const = 0;                            // slot 14
    virtual void SerializeTo(char*& buffer, int& size) const = 0;  // slot 15
    virtual void SerializeFrom(char*& buffer, int& size) = 0;      // slot 16
    virtual XmlElement* ToXmlElement() = 0;                        // slot 18
    virtual XmlElement const* ToXmlElement() const = 0;            // slot 17
    virtual XmlTextNode* ToXmlTextNode() = 0;                      // slot 20
    virtual XmlTextNode const* ToXmlTextNode() const = 0;          // slot 19
};

class XmlTextNode
{
public:
    virtual wchar_t const* Value() const = 0;        // slot 0
    virtual XmlNode* ToXmlNode() = 0;                // slot 2
    virtual XmlNode const* ToXmlNode() const = 0;    // slot 1
};

class XmlPieceReader
{
public:
    virtual bool Read(XmlDoc* doc) = 0;          // slot 0
    virtual int GetMaxNodeCountPerPiece() = 0;   // slot 1
};

class XmlReaderIO
{
public:
    virtual int Open(wchar_t const* fileName, wchar_t const* mode, bool flag) = 0;  // slot 0
    virtual int Read(unsigned char* buffer, unsigned int* size) const = 0;         // slot 1
    virtual unsigned int GetFileSize() const = 0;                                  // slot 2
    virtual wchar_t const* GetFileName() const = 0;                                // slot 3
    virtual int Next() = 0;                                                        // slot 4
    virtual void Close() = 0;                                                      // slot 5
    // LIFT: GameDaemon only (card lift-gamedaemon-0c). Declarations for the wave-0 stubs in
    // src/Server/GameDaemon. They add no code to the other exes.
public:
    enum ErrCode {};  // GameDaemon PDB type
};

class XmlReaderLog
{
public:
    virtual void Error(wchar_t const* message, void* param) const = 0;  // slot 0
    virtual void Debug(wchar_t const* message, void* param) const = 0;  // slot 1
    virtual void Trace(wchar_t const* message, void* param) const = 0;  // slot 2
};

class XmlReader
{
public:
    virtual bool Initialize(XmlReaderIO* io, XmlReaderLog const* log, bool flag) const = 0;  // slot 0
    virtual XmlReaderLog const* SetLog(XmlReaderLog const* log) const = 0;                    // slot 1
    virtual XmlReaderLog const* GetLog() const = 0;                                           // slot 2
    virtual void Cleanup(bool flag) const = 0;                                                // slot 3
    virtual XmlReaderIO* GetIO() const = 0;                                                   // slot 4
    virtual XmlDoc* Read(unsigned char const* buffer, unsigned int size, wchar_t const* fileName,
                         XmlPieceReader* pieceReader) const = 0;                              // slot 7
    virtual XmlDoc* Read(wchar_t const* fileName, XmlPieceReader* pieceReader) const = 0;    // slot 6
    virtual bool Read(wchar_t const* fileName, void* param) const = 0;                        // slot 5
    virtual void Close(XmlDoc* doc) const = 0;                                                // slot 8
    virtual XmlDoc* NewDoc() const = 0;                                                       // slot 9
    virtual bool IsBinary(unsigned char const* buffer, unsigned int size) const = 0;          // slot 11
    virtual bool IsBinary(wchar_t const* fileName) const = 0;                                 // slot 10
};

// Function types of the XmlReader_sv64.dll exports (PDB typedefs).
typedef void* (*XriMallocFunc)(unsigned long long);
typedef void* (*XriReallocFunc)(void*, unsigned long long);
typedef void (*XriFreeFunc)(void*);
typedef wchar_t const* (*XriGetInterfaceVersion)();
typedef void (*XriSetMemAllocator)(XriMallocFunc, XriReallocFunc, XriFreeFunc);  // not called
typedef XmlReader const* (*XriCreateFunc)();
typedef void (*XriDestoryFunc)(XmlReader const*);
