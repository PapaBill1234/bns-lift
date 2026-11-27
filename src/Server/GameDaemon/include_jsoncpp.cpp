// include_jsoncpp.cpp: jsoncpp.h (GameDaemon PDB, 2019 + PDB).
#include "jsoncpp.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1FastWriter@Json@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6761e0
// The body destroys document_ (StlAllocator<char, 2>) and then the inlined Json::Writer destructor.
__cdecl Json::FastWriter::~FastWriter(void)
{
}
