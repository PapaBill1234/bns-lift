// MarketStatement.h (MarketDealerDaemon PDB). No code in the PDB. Layout from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include <stddef.h>

class MarketStatement
{
public:
    wchar_t _statementTitle[65];
    wchar_t _statementBody[1025];
};
static_assert(sizeof(MarketStatement) == 0x884, "sizeof MarketStatement");
static_assert(offsetof(MarketStatement, _statementBody) == 0x82, "MarketStatement::_statementBody");
