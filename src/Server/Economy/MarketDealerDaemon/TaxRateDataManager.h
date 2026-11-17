// TaxRateDataManager.obj (MarketDealerDaemon PDB). Layouts from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include <stddef.h>

class XmlDoc;

class SaleIncomeTaxRateData
{
public:
    enum Param
    {
        PARAM_INTERVAL = 0,
        PARAM_TAX_RATE = 1,
        MAX_PARAM_COUNT = 2,
    };
    long long _interval;
    int _taxRate;
};
static_assert(sizeof(SaleIncomeTaxRateData) == 0x10, "sizeof SaleIncomeTaxRateData");

class SaleIncomeTaxRateTable
{
public:
    int _taxRateCount;
    SaleIncomeTaxRateData _taxRateList[10];
};
static_assert(sizeof(SaleIncomeTaxRateTable) == 0xA8, "sizeof SaleIncomeTaxRateTable");
static_assert(offsetof(SaleIncomeTaxRateTable, _taxRateList) == 0x8, "SaleIncomeTaxRateTable::_taxRateList");

class GrossIncomeTaxRateData
{
public:
    enum Param
    {
        PARAM_INTERVAL = 0,
        PARAM_TAX_RATE = 1,
        MAX_PARAM_COUNT = 2,
    };
    long long _interval;
    int _taxRate;
};
static_assert(sizeof(GrossIncomeTaxRateData) == 0x10, "sizeof GrossIncomeTaxRateData");

class GrossIncomeTaxRateTable
{
public:
    int _taxRateCount;
    GrossIncomeTaxRateData _taxRateList[10];
};
static_assert(sizeof(GrossIncomeTaxRateTable) == 0xA8, "sizeof GrossIncomeTaxRateTable");
static_assert(offsetof(GrossIncomeTaxRateTable, _taxRateList) == 0x8, "GrossIncomeTaxRateTable::_taxRateList");

class TaxRateDataManager
{
public:
    enum TaxRateType
    {
        TAXRATETYPE_INVALID_TYPE = 0,
        TAXRATETYPE_SALE_INCOME = 1,
        TAXRATETYPE_GROSS_INCOME = 2,
        MAX_TAXRATETYPE = 3,
    };

    TaxRateDataManager();  // Inlined in the MarketDealerDaemon code (later card). No body here.
    bool SetTaxRateTable(int const taxRateType);  // 0x2ecd0

private:
    bool initDataManager();                                   // 0x2eb30
    bool setSaleIncomeTaxRateTable(XmlDoc* const doc);        // 0x2f040
    bool setGrossIncomeTaxRateTable(XmlDoc* const doc);       // 0x2f4f0

    wchar_t _saleIncomeTaxRateDataFilePath[260];
    wchar_t _grossIncomeTaxRateDataFilePath[260];
};
static_assert(sizeof(TaxRateDataManager) == 0x410, "sizeof TaxRateDataManager");
