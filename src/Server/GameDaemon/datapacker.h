// datapacker.h: datapacker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class PathUtil
{
public:
    static void __cdecl Tokenlize(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > &, wchar_t *, wchar_t const *);  // 0x16cb0
    static bool __cdecl MatchPath(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > const &, ::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > const &, bool);  // 0x16db0
    static bool __cdecl MatchFile(::std::vector< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, ::StlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> >, 2> > &, ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::StlAllocator<wchar_t, 2> > &);  // 0x16ec0
};

// PDB layout (size 0x50): base XmlReaderIO (vfptr only) +0, _zfile +8, _fileList +0x10, _openFileArray +0x28, _openFileIdx +0x48.
// LIFT: the BloodLib XmlReaderIO declares int returns, not ErrCode. Thus this class does not derive from it yet.
// LIFT: the PDB containers use StlAllocator<T, 2>. The VS2010 std::allocator containers have the same layout.
class ZipPackedReaderIO
{
public:
    // PDB layout (size 0x68).
    struct FileName
    {
    public:
        __cdecl FileName(char const *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned int);  // 0x153d0
        __cdecl ~FileName(void);  // 0x157c0

        // PDB types: the strings use StlAllocator<wchar_t, 2> (the destructor frees through Memory::_Manager[2]).
        std::basic_string<wchar_t, std::char_traits<wchar_t>, StlAllocator<wchar_t, 2> > _pathW;  // +0x0
        std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, StlAllocator<wchar_t, 2> >,
                    StlAllocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, StlAllocator<wchar_t, 2> >, 2> >
            _pathTokenW;                           // +0x28
        unsigned __int64 _uncompressedSize;        // +0x48
        unsigned __int64 _posInZipDir;             // +0x50
        unsigned __int64 _numOfFile;               // +0x58
        unsigned int _crc;                         // +0x60
    };
    // LIFT: the PDB type of _fileList is std::list<FileName, StlAllocator<FileName, 2> > (size 0x18).
    // The VS2010 header set of this repo has no <list>. FileList keeps the size only. FileNode is the
    // VS2010 list node (_Next, _Prev, _Myval). A release list iterator holds only the node pointer.
    struct FileNode
    {
        FileNode * _Next;
        FileNode * _Prev;
        FileName _Myval;
    };
    struct FileList
    {
        void * _Myhead;
        unsigned __int64 _Mysize;
        void * _Alval;
    };
    typedef std::vector<FileNode *> FileItrArray;
public:
    __cdecl ~ZipPackedReaderIO(void);  // 0x154f0
    bool __cdecl OpenZip(wchar_t const *);  // 0x15580
    bool __cdecl Verify(char *, unsigned __int64);  // 0x15860
    void __cdecl CloseZip(void);  // 0x16290
    virtual ::XmlReaderIO::ErrCode __cdecl Open(wchar_t const *, wchar_t const *, bool);  // 0x16330
    virtual ::XmlReaderIO::ErrCode __cdecl Read(unsigned char *, unsigned int *) const;  // 0x169a0
    virtual unsigned int __cdecl GetFileSize(void) const;  // 0x16b60
    virtual wchar_t const * __cdecl GetFileName(void) const;  // 0x16bd0
    virtual ::XmlReaderIO::ErrCode __cdecl Next(void);  // 0x16c40
    virtual void __cdecl Close(void);  // 0x16c70
private:
    void * _zfile;
    FileList _fileList;
    FileItrArray _openFileArray;
    int _openFileIdx;
};

