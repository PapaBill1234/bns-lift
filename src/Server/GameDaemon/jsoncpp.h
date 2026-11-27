// jsoncpp.h: jsoncpp.cpp, jsoncpp.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include <deque>
#include <stack>

namespace Json {
// PDB: Json::ValueType (enumerator values of jsoncpp).
enum ValueType
{
    nullValue = 0,
    intValue,
    uintValue,
    realValue,
    stringValue,
    booleanValue,
    arrayValue,
    objectValue,
};

// PDB: Json::Features (GameDaemon), size 0x4. all() and the ctor are inlined.
class Features
{
public:
    static Features all() { return Features(); }
    Features() : allowComments_(true), strictRoot_(false), allowDroppedNullPlaceholders_(false), allowNumericKeys_(false) {}

    bool allowComments_;                // +0x0
    bool strictRoot_;                   // +0x1
    bool allowDroppedNullPlaceholders_; // +0x2
    bool allowNumericKeys_;             // +0x3
};
}

namespace Json {
// LIFT: the PDB base std::exception and the member msg_ (+0x18) are not added yet. No other lifted
// file links the CRT std::exception symbols. See the handoff (0x6a84d0 Not done).
class Exception
{
public:
    virtual __cdecl ~Exception(void);  // 0x6a83c0
    virtual char const * __cdecl what(void) const;  // 0x6a8420
    __cdecl Exception(::Json::Exception const &);  // 0x6a84d0
};
}

namespace Json {
// PDB: Json::Writer (abstract base, size 0x8). The destructor is inlined (empty).
class Writer
{
public:
    virtual ~Writer() {}
    virtual ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl write(::Json::Value const &) = 0;
};

// PDB layout: size 0x38.
class FastWriter : public Writer
{
public:
    virtual __cdecl ~FastWriter(void);  // 0x6761e0
    virtual ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl write(::Json::Value const &);  // 0x6aad70
private:
    void __cdecl writeValue(::Json::Value const &);  // 0x6aae10

    ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > document_;  // +0x08
    bool yamlCompatiblityEnabled_;  // +0x30
    bool dropNullPlaceholders_;     // +0x31
    bool omitEndingLineFeed_;       // +0x32
};
}

namespace Json {
class Reader
{
public:
    enum TokenType {};
    // PDB: Json::Reader::Token, size 0x18.
    class Token
    {
    public:
        TokenType type_;     // +0x0
        char const* start_;  // +0x8
        char const* end_;    // +0x10
    };
    // PDB: Json::Reader::ErrorInfo, size 0x48.
    class ErrorInfo
    {
    public:
        Token token_;  // +0x0
        ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > message_;  // +0x18
        char const* extra_;  // +0x40
    };
public:
    __cdecl ~Reader(void);  // 0x681060
    __cdecl Reader(void);  // 0x6a4eb0
    bool __cdecl parse(char const *, char const *, ::Json::Value &, bool);  // 0x6a4f40
private:
    bool __cdecl readValue(void);  // 0x6a5120
    void __cdecl skipCommentTokens(::Json::Reader::Token &);  // 0x6a5560
    bool __cdecl readToken(::Json::Reader::Token &);  // 0x6a58f0
    bool __cdecl readComment(void);  // 0x6a5c40
    void __cdecl addComment(char const *, char const *, ::Json::CommentPlacement);  // 0x6a5f90
    void __cdecl readNumber(void);  // 0x6a6040
    bool __cdecl readObject(::Json::Reader::Token &);  // 0x6a6120
    bool __cdecl readArray(::Json::Reader::Token &);  // 0x6a6970
    bool __cdecl decodeNumber(::Json::Reader::Token &);  // 0x6a6ec0
    bool __cdecl decodeNumber(::Json::Reader::Token &, ::Json::Value &);  // 0x6a70b0
    bool __cdecl decodeDouble(::Json::Reader::Token &, ::Json::Value &);  // 0x6a71f0
    bool __cdecl decodeString(::Json::Reader::Token &);  // 0x6a7600
    bool __cdecl decodeString(::Json::Reader::Token &, ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > &);  // 0x6a7860
    bool __cdecl decodeUnicodeCodePoint(::Json::Reader::Token &, char const *&, char const *, unsigned int &);  // 0x6a7c00
    bool __cdecl decodeUnicodeEscapeSequence(::Json::Reader::Token &, char const *&, char const *, unsigned int &);  // 0x6a7db0
    bool __cdecl addError(::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > const &, ::Json::Reader::Token &, char const *);  // 0x6a7f20
    bool __cdecl recoverFromError(::Json::Reader::TokenType);  // 0x6a8090
    ::Json::Value & __cdecl currentValue(void);  // 0x6a8100

    ::std::stack< ::Json::Value*, ::std::deque< ::Json::Value*, ::StlAllocator< ::Json::Value*, 2> > > nodes_;  // +0x0
    ::std::deque<ErrorInfo, ::StlAllocator<ErrorInfo, 2> > errors_;  // +0x30
    ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > document_;  // +0x60
    char const* begin_;         // +0x88
    char const* end_;           // +0x90
    char const* current_;       // +0x98
    char const* lastValueEnd_;  // +0xA0
    ::Json::Value* lastValue_;  // +0xA8
    ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > commentsBefore_;  // +0xB0
    ::Json::Features features_;  // +0xD8
    bool collectComments_;       // +0xDC
};
static_assert(sizeof(Reader) == 0xE0, "sizeof Json::Reader");
}

namespace Json {
class Value
{
public:
    class CZString;
    struct CommentInfo;
public:
    __cdecl Value(::Json::Value const &);  // 0x6a8850
    __cdecl ~Value(void);  // 0x6a8a10
    ::Json::Value & __cdecl operator=(::Json::Value);  // 0x6a8ae0
    ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl asString(void) const;  // 0x6a8b80
    int __cdecl asInt(void) const;  // 0x6a8d00
    __int64 __cdecl asInt64(void) const;  // 0x6a8ea0
    unsigned __int64 __cdecl asUInt64(void) const;  // 0x6a9010
    double __cdecl asDouble(void) const;  // 0x6a91a0
    float __cdecl asFloat(void) const;  // 0x6a9270
    bool __cdecl asBool(void) const;  // 0x6a9340
    unsigned int __cdecl size(void) const;  // 0x6a9400
    ::Json::Value & __cdecl operator[](unsigned int);  // 0x6a94b0
    ::Json::Value const & __cdecl operator[](unsigned int) const;  // 0x6a9780
    ::Json::Value const & __cdecl operator[](int) const;  // 0x6a98e0
private:
    ::Json::Value & __cdecl resolveReference(char const *, char const *);  // 0x6a9960
public:
    ::Json::Value const * __cdecl find(char const *, char const *) const;  // 0x6a9c80
    ::std::vector< ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> >, ::StlAllocator< ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> >, 2> > __cdecl getMemberNames(void) const;  // 0x6a9e50
    bool __cdecl isInt(void) const;  // 0x6aa080
    bool __cdecl isInt64(void) const;  // 0x6aa110
    bool __cdecl isUInt64(void) const;  // 0x6aa1b0
    void __cdecl setComment(char const *, unsigned __int64, ::Json::CommentPlacement);  // 0x6aa230

    static int const minInt = static_cast<int>(~(static_cast<unsigned int>(-1) / 2));
    static int const maxInt = static_cast<int>(static_cast<unsigned int>(-1) / 2);

private:
    // PDB: Json::Value::ValueHolder, size 0x8.
    union ValueHolder
    {
        __int64 int_;
        unsigned __int64 uint_;
        double real_;
        bool bool_;
        char* string_;
        void* map_;  // LIFT: PDB type ObjectValues* (std::map<CZString, Value>). The map type is not needed yet.
    };

    ValueHolder value_;             // +0x0
    ValueType type_ : 8;            // +0x8
    unsigned int allocated_ : 1;    // +0x8 bit 8
    CommentInfo* comments_;         // +0x10
    unsigned __int64 start_;        // +0x18
    unsigned __int64 limit_;        // +0x20
};
static_assert(sizeof(Value) == 0x28, "sizeof Json::Value");
}

namespace Json {
// PDB: Json::Value::CZString, size 0x10.
class Value::CZString
{
public:
    enum DuplicationPolicy
    {
        noDuplication = 0,
        duplicate,
        duplicateOnCopy,
    };

    __cdecl CZString(::Json::Value::CZString const &);  // 0x6a8720
    __cdecl ~CZString(void);  // 0x6a87a0
    bool __cdecl operator<(::Json::Value::CZString const &) const;  // 0x6a87d0

private:
    struct StringStorage
    {
        unsigned policy_ : 2;
        unsigned length_ : 30;
    };

    char const* cstr_;  // +0x0
    union
    {
        unsigned int index_;     // +0x8
        StringStorage storage_;  // +0x8
    };
};
static_assert(sizeof(Value::CZString) == 0x10, "sizeof Json::Value::CZString");
}

namespace Json {
// PDB: Json::Value::CommentInfo, size 0x8.
struct Value::CommentInfo
{
public:
    __cdecl ~CommentInfo(void);  // 0x6a8600
    void __cdecl setComment(char const *, unsigned __int64);  // 0x6a8620

    char* comment_;  // +0x0
};
}

namespace Json {
void __cdecl throwRuntimeError(::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > const &);  // 0x6a8440
void __cdecl throwLogicError(::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > const &);  // 0x6a8540
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl valueToString(__int64);  // 0x6aa2e0
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl valueToString(unsigned __int64);  // 0x6aa430
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl valueToString(double, bool, unsigned int);  // 0x6aa4f0
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl valueToString(double);  // 0x6aa650
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl valueToString(bool);  // 0x6aa680
}
