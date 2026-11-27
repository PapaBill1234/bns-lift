// propertydb.h: propertydb.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DbSyncDefine
{
protected:
    void __cdecl MakeWhereClause(::QueryString *, ::Field::Def const *, __int64) const;  // 0x6ae310
};

class QueryString
{
public:
    void __cdecl Append(wchar_t const *);  // 0x6ae400
};

