// source_jsoncpp.cpp: jsoncpp.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "jsoncpp.h"
#include "gameobject.h"
#include "LiftStub.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(linker, "/INCLUDE:??0Reader@Json@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1CommentInfo@Value@Json@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1CZString@Value@Json@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??MCZString@Value@Json@@QEBA_NAEBV012@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?isInt@Value@Json@@QEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?isUInt64@Value@Json@@QEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

namespace Json {
// PDB data: maxUInt64AsDouble (jsoncpp.cpp static).
static double const maxUInt64AsDouble = 18446744073709551615.0;

// LIFT: inlined helper of jsoncpp. No PDB function.
static inline bool IsIntegral(double d)
{
    double integral_part;
    return modf(d, &integral_part) == 0.0;
}

// LIFT: inlined helper of jsoncpp. No PDB function.
static inline void uintToString(unsigned __int64 value, char*& current)
{
    *--current = 0;
    do
    {
        *--current = static_cast<char>(value % 10U + static_cast<unsigned>('0'));
        value /= 10U;
    } while (value != 0);
}
}

namespace Json {
// 0x6a4ca0
static std::basic_string<char,std::char_traits<char>,StlAllocator<char,2> >  codePointToUTF8(unsigned)
{
    LIFT_STUB(0x6a4ca0);
}
}

// 0x6a4eb0
Json::Reader::Reader(void)
    : errors_(), document_(), begin_(), end_(), current_(), lastValueEnd_(), lastValue_(), commentsBefore_(),
      features_(Features::all()), collectComments_()
{
}

// 0x6a4f40
bool __cdecl Json::Reader::parse(char const *, char const *, ::Json::Value &, bool)
{
    LIFT_STUB(0x6a4f40);
}

// 0x6a5120
bool __cdecl Json::Reader::readValue(void)
{
    LIFT_STUB(0x6a5120);
}

// 0x6a5560
void __cdecl Json::Reader::skipCommentTokens(::Json::Reader::Token &)
{
    LIFT_STUB(0x6a5560);
}

// 0x6a58f0
bool __cdecl Json::Reader::readToken(::Json::Reader::Token &)
{
    LIFT_STUB(0x6a58f0);
}

// 0x6a5c40
bool __cdecl Json::Reader::readComment(void)
{
    LIFT_STUB(0x6a5c40);
}

namespace Json {
// 0x6a5da0
static std::basic_string<char,std::char_traits<char>,StlAllocator<char,2> >  normalizeEOL(const char*, const char*)
{
    LIFT_STUB(0x6a5da0);
}
}

// 0x6a5f90
void __cdecl Json::Reader::addComment(char const *, char const *, ::Json::CommentPlacement)
{
    LIFT_STUB(0x6a5f90);
}

// 0x6a6040
void __cdecl Json::Reader::readNumber(void)
{
    LIFT_STUB(0x6a6040);
}

// 0x6a6120
bool __cdecl Json::Reader::readObject(::Json::Reader::Token &)
{
    LIFT_STUB(0x6a6120);
}

// 0x6a6970
bool __cdecl Json::Reader::readArray(::Json::Reader::Token &)
{
    LIFT_STUB(0x6a6970);
}

// 0x6a6ec0
bool __cdecl Json::Reader::decodeNumber(::Json::Reader::Token &)
{
    LIFT_STUB(0x6a6ec0);
}

// 0x6a70b0
bool __cdecl Json::Reader::decodeNumber(::Json::Reader::Token &, ::Json::Value &)
{
    LIFT_STUB(0x6a70b0);
}

// 0x6a71f0
bool __cdecl Json::Reader::decodeDouble(::Json::Reader::Token &, ::Json::Value &)
{
    LIFT_STUB(0x6a71f0);
}

// 0x6a7600
bool __cdecl Json::Reader::decodeString(::Json::Reader::Token &)
{
    LIFT_STUB(0x6a7600);
}

// 0x6a7860
bool __cdecl Json::Reader::decodeString(::Json::Reader::Token &, ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > &)
{
    LIFT_STUB(0x6a7860);
}

// 0x6a7c00
bool __cdecl Json::Reader::decodeUnicodeCodePoint(::Json::Reader::Token &, char const *&, char const *, unsigned int &)
{
    LIFT_STUB(0x6a7c00);
}

// 0x6a7db0
bool __cdecl Json::Reader::decodeUnicodeEscapeSequence(::Json::Reader::Token &, char const *&, char const *, unsigned int &)
{
    LIFT_STUB(0x6a7db0);
}

// 0x6a7f20
bool __cdecl Json::Reader::addError(::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > const &, ::Json::Reader::Token &, char const *)
{
    LIFT_STUB(0x6a7f20);
}

// 0x6a8090
bool __cdecl Json::Reader::recoverFromError(::Json::Reader::TokenType)
{
    LIFT_STUB(0x6a8090);
}

// 0x6a8100
::Json::Value & __cdecl Json::Reader::currentValue(void)
{
    LIFT_STUB(0x6a8100);
}

namespace Json {
// 0x6a81d0
static char* duplicateStringValue(const char*, unsigned __int64)
{
    LIFT_STUB(0x6a81d0);
}
}

namespace Json {
// 0x6a8290
static char* duplicateAndPrefixStringValue(const char*, unsigned)
{
    LIFT_STUB(0x6a8290);
}
}

// 0x6a83c0
__cdecl Json::Exception::~Exception(void)
{
    LIFT_STUB(0x6a83c0);
}

// 0x6a8420
char const * __cdecl Json::Exception::what(void) const
{
    LIFT_STUB(0x6a8420);
}

// 0x6a8440
void __cdecl Json::throwRuntimeError(::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > const &)
{
    LIFT_STUB(0x6a8440);
}

// 0x6a8540
void __cdecl Json::throwLogicError(::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > const &)
{
    LIFT_STUB(0x6a8540);
}

// 0x6a8600
__cdecl Json::Value::CommentInfo::~CommentInfo(void)
{
    // LIFT: releaseStringValue is inlined (free).
    if (comment_ != nullptr)
        free(comment_);
}

// 0x6a8620
void __cdecl Json::Value::CommentInfo::setComment(char const *, unsigned __int64)
{
    LIFT_STUB(0x6a8620);
}

// 0x6a8720
__cdecl Json::Value::CZString::CZString(::Json::Value::CZString const &)
{
    LIFT_STUB(0x6a8720);
}

// 0x6a87a0
__cdecl Json::Value::CZString::~CZString(void)
{
    // LIFT: releaseStringValue is inlined (free).
    if (cstr_ != nullptr && storage_.policy_ == duplicate)
        free(const_cast<char*>(cstr_));
}

// 0x6a87d0
bool __cdecl Json::Value::CZString::operator<(::Json::Value::CZString const &other) const
{
    if (cstr_ == nullptr)
        return index_ < other.index_;
    unsigned int thisLen = storage_.length_;
    unsigned int otherLen = other.storage_.length_;
    unsigned int minLen = (thisLen < otherLen) ? thisLen : otherLen;
    int comp = memcmp(cstr_, other.cstr_, minLen);
    if (comp < 0)
        return true;
    if (comp > 0)
        return false;
    return thisLen < otherLen;
}

// 0x6a8850
__cdecl Json::Value::Value(::Json::Value const &)
{
    LIFT_STUB(0x6a8850);
}

// 0x6a8a10
__cdecl Json::Value::~Value(void)
{
    LIFT_STUB(0x6a8a10);
}

// 0x6a8ae0
::Json::Value & __cdecl Json::Value::operator=(::Json::Value)
{
    LIFT_STUB(0x6a8ae0);
}

// 0x6a8b80
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl Json::Value::asString(void) const
{
    LIFT_STUB(0x6a8b80);
}

// 0x6a8d00
int __cdecl Json::Value::asInt(void) const
{
    LIFT_STUB(0x6a8d00);
}

// 0x6a8ea0
__int64 __cdecl Json::Value::asInt64(void) const
{
    LIFT_STUB(0x6a8ea0);
}

// 0x6a9010
unsigned __int64 __cdecl Json::Value::asUInt64(void) const
{
    LIFT_STUB(0x6a9010);
}

// 0x6a91a0
double __cdecl Json::Value::asDouble(void) const
{
    LIFT_STUB(0x6a91a0);
}

// 0x6a9270
float __cdecl Json::Value::asFloat(void) const
{
    LIFT_STUB(0x6a9270);
}

// 0x6a9340
bool __cdecl Json::Value::asBool(void) const
{
    LIFT_STUB(0x6a9340);
}

// 0x6a9400
unsigned int __cdecl Json::Value::size(void) const
{
    LIFT_STUB(0x6a9400);
}

// 0x6a94b0
::Json::Value & __cdecl Json::Value::operator[](unsigned int)
{
    LIFT_STUB(0x6a94b0);
}

// 0x6a9780
::Json::Value const & __cdecl Json::Value::operator[](unsigned int) const
{
    LIFT_STUB(0x6a9780);
}

// 0x6a98e0
::Json::Value const & __cdecl Json::Value::operator[](int) const
{
    LIFT_STUB(0x6a98e0);
}

// 0x6a9960
::Json::Value & __cdecl Json::Value::resolveReference(char const *, char const *)
{
    LIFT_STUB(0x6a9960);
}

// 0x6a9c80
::Json::Value const * __cdecl Json::Value::find(char const *, char const *) const
{
    LIFT_STUB(0x6a9c80);
}

// 0x6a9e50
::std::vector< ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> >, ::StlAllocator< ::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> >, 2> > __cdecl Json::Value::getMemberNames(void) const
{
    LIFT_STUB(0x6a9e50);
}

// 0x6aa080
bool __cdecl Json::Value::isInt(void) const
{
    switch (type_)
    {
    case intValue:
        return value_.int_ >= minInt && value_.int_ <= maxInt;
    case uintValue:
        return value_.uint_ <= static_cast<unsigned int>(maxInt);
    case realValue:
        return value_.real_ >= minInt && value_.real_ <= maxInt && IsIntegral(value_.real_);
    default:
        break;
    }
    return false;
}

// 0x6aa110
bool __cdecl Json::Value::isInt64(void) const
{
    LIFT_STUB(0x6aa110);
}

// 0x6aa1b0
bool __cdecl Json::Value::isUInt64(void) const
{
    switch (type_)
    {
    case intValue:
        return value_.int_ >= 0;
    case uintValue:
        return true;
    case realValue:
        return value_.real_ >= 0 && value_.real_ < maxUInt64AsDouble && IsIntegral(value_.real_);
    default:
        break;
    }
    return false;
}

// 0x6aa230
void __cdecl Json::Value::setComment(char const *, unsigned __int64, ::Json::CommentPlacement)
{
    LIFT_STUB(0x6aa230);
}

// 0x6aa2e0
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl Json::valueToString(__int64)
{
    LIFT_STUB(0x6aa2e0);
}

// 0x6aa430
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl Json::valueToString(unsigned __int64 value)
{
    char buffer[3 * sizeof(unsigned __int64) + 1];  // LIFT: UIntToStringBuffer
    char* current = buffer + sizeof(buffer);
    uintToString(value, current);
    return current;
}

// 0x6aa4f0
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl Json::valueToString(double, bool, unsigned int)
{
    LIFT_STUB(0x6aa4f0);
}

// 0x6aa650
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl Json::valueToString(double value)
{
    return valueToString(value, false, 17);
}

// 0x6aa680
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl Json::valueToString(bool value)
{
    return value ? "true" : "false";
}

namespace Json {
// 0x6aa6e0
static std::basic_string<char,std::char_traits<char>,StlAllocator<char,2> >  valueToQuotedStringN(const char*, unsigned)
{
    LIFT_STUB(0x6aa6e0);
}
}

// 0x6aad60
__cdecl GameObjectIdManager::~GameObjectIdManager(void)
{
    LIFT_STUB(0x6aad60);
}

// 0x6aad70
::std::basic_string<char, ::std::char_traits<char>, ::StlAllocator<char, 2> > __cdecl Json::FastWriter::write(::Json::Value const &)
{
    LIFT_STUB(0x6aad70);
}

// 0x6aae10
void __cdecl Json::FastWriter::writeValue(::Json::Value const &)
{
    LIFT_STUB(0x6aae10);
}
