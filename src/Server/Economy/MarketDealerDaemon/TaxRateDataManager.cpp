// TaxRateDataManager.obj (MarketDealerDaemon PDB). Source: .scratch/hr/TaxRateDataManager.c
#include "TaxRateDataManager.h"
#include <windows.h>
#include <io.h>
#include <stdlib.h>
#include <wchar.h>
#include "AlertSender.h"
#include "Log.h"
#include "XmlReader.h"
#include "MarketDB.h"
#include "MarketDealerDaemon.h"

namespace
{
wchar_t const* const TAX_RATE_FILE = L"TaxRateDataManager.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const XML_READER_DLL = L"XmlReader_sv64.dll";     // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const XML_READER_VERSION = L"15";                 // LIFT: No PDB symbol. The binary uses the literal.
}
static wchar_t const* const MODULE_NAME = L"tax rate data manager";  // PDB MODULE_NAME

#define TAX_RATE_CRASH(line, fmt, ...)                                     \
    do                                                                     \
    {                                                                      \
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, line, fmt, __VA_ARGS__);  \
        AlertSender::Write(TAX_RATE_FILE, line, fmt, __VA_ARGS__);         \
    } while (0)

// 0x2eb30
bool TaxRateDataManager::initDataManager()
{
    if (_wmakepath_s(_saleIncomeTaxRateDataFilePath, 260, nullptr, MarketDealerDaemon::_instance->_config->_dataPath,
                     L"MarketSaleIncomeTaxRateData.xml", nullptr) != 0)
    {
        Log::Write(TAX_RATE_FILE, 38, GetLastError(), L"[%s], %s; failed to make sale income tax rate data file path",
                   MODULE_NAME, L"TaxRateDataManager::initDataManager");
        return false;
    }
    if (_wmakepath_s(_grossIncomeTaxRateDataFilePath, 260, nullptr, MarketDealerDaemon::_instance->_config->_dataPath,
                     L"MarketGrossIncomeTaxRateData.xml", nullptr) != 0)
    {
        Log::Write(TAX_RATE_FILE, 42, GetLastError(), L"[%s], %s; failed to make gross income tax rate data file path",
                   MODULE_NAME, L"TaxRateDataManager::initDataManager");
        return false;
    }
    if (_waccess(_saleIncomeTaxRateDataFilePath, 0) != 0)
    {
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 47, L"[%s], %s; there is no sale income tax rate data file, filePath:%s",
                   MODULE_NAME, L"TaxRateDataManager::initDataManager", _saleIncomeTaxRateDataFilePath);
        return false;
    }
    if (_waccess(_grossIncomeTaxRateDataFilePath, 0) != 0)
    {
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 51, L"[%s], %s; there is no gross income tax rate data file, filePath:%s",
                   MODULE_NAME, L"TaxRateDataManager::initDataManager", _grossIncomeTaxRateDataFilePath);
        return false;
    }
    return true;
}

// 0x2ecd0
bool TaxRateDataManager::SetTaxRateTable(int const taxRateType)
{
    bool result = false;
    XmlDoc* doc = nullptr;
    HMODULE library = LoadLibraryW(XML_READER_DLL);
    if (library == nullptr)
    {
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 68, L"[%s], %s; failed to initialize xml reader interface, dll name:%s",
                   MODULE_NAME, L"TaxRateDataManager::SetTaxRateTable", XML_READER_DLL);
        return false;
    }
    XriGetInterfaceVersion getInterfaceVersion =
        reinterpret_cast<XriGetInterfaceVersion>(GetProcAddress(library, "GetInterfaceVersion"));
    GetProcAddress(library, "SetMemAllocator");
    XriCreateFunc createXmlReader = reinterpret_cast<XriCreateFunc>(GetProcAddress(library, "CreateXmlReader"));
    XriDestoryFunc destroyXmlReader = reinterpret_cast<XriDestoryFunc>(GetProcAddress(library, "DestroyXmlReader"));
    XmlReader const* reader = createXmlReader();
    if (reader == nullptr)
    {
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 74, L"[%s], %s; failed to create xml reader", MODULE_NAME,
                   L"TaxRateDataManager::SetTaxRateTable");
        goto $_FIN;
    }
    {
        wchar_t const* const loadVersion = getInterfaceVersion();
        if (_wcsicmp(loadVersion, XML_READER_VERSION) != 0)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 80,
                       L"[%s], %s; xml interface version mismatch, current-version:%s, load-version:%s", MODULE_NAME,
                       L"TaxRateDataManager::SetTaxRateTable", XML_READER_VERSION, loadVersion);
            goto $_FIN;
        }
    }
    if (!reader->Initialize(nullptr, nullptr, false))
    {
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 85, L"[%s], %s; failed to initialize xml reader", MODULE_NAME,
                   L"TaxRateDataManager::SetTaxRateTable");
        goto $_FIN;
    }

    if (taxRateType == TAXRATETYPE_SALE_INCOME)
    {
        doc = reader->Read(_saleIncomeTaxRateDataFilePath, static_cast<XmlPieceReader*>(nullptr));
        if (doc == nullptr)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 92,
                       L"[%s], %s; failed to read sale income tax rate data file, filePath:%s", MODULE_NAME,
                       L"TaxRateDataManager::SetTaxRateTable", _saleIncomeTaxRateDataFilePath);
            goto $_FIN;
        }
        if (!setSaleIncomeTaxRateTable(doc))
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 97, L"[%s], %s; failed to set sale income tax rate table, filePath:%s",
                       MODULE_NAME, L"TaxRateDataManager::SetTaxRateTable", _saleIncomeTaxRateDataFilePath);
            goto $_FIN;
        }
        Log::Write(Log::LT_NOTICE, TAX_RATE_FILE, 100,
                   L"[%s], %s; succeeded to set sale income tax rate table, filePath:%s", MODULE_NAME,
                   L"TaxRateDataManager::SetTaxRateTable", _saleIncomeTaxRateDataFilePath);
    }
    else if (taxRateType == TAXRATETYPE_GROSS_INCOME)
    {
        doc = reader->Read(_grossIncomeTaxRateDataFilePath, static_cast<XmlPieceReader*>(nullptr));
        if (doc == nullptr)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 105,
                       L"[%s], %s; failed to read gross income tax rate data file, filePath:%s", MODULE_NAME,
                       L"TaxRateDataManager::SetTaxRateTable", _grossIncomeTaxRateDataFilePath);
            goto $_FIN;
        }
        if (!setGrossIncomeTaxRateTable(doc))
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 110,
                       L"[%s], %s; failed to set gross income tax rate table, filePath:%s", MODULE_NAME,
                       L"TaxRateDataManager::SetTaxRateTable", _grossIncomeTaxRateDataFilePath);
            goto $_FIN;
        }
        Log::Write(Log::LT_NOTICE, TAX_RATE_FILE, 113,
                   L"[%s], %s; succeeded to set gross income tax rate table, filePath:%s", MODULE_NAME,
                   L"TaxRateDataManager::SetTaxRateTable", _grossIncomeTaxRateDataFilePath);
    }
    // An unknown taxRateType also gives true (original logic).
    result = true;

$_FIN:
    if (reader != nullptr)
    {
        if (doc != nullptr)
            reader->Close(doc);
        destroyXmlReader(reader);
    }
    FreeLibrary(library);
    return result;
}

// 0x2f040
// LIFT: LTCG removes the unused `this` argument. The binary gives doc in rcx.
bool TaxRateDataManager::setSaleIncomeTaxRateTable(XmlDoc* const doc)
{
    if (doc == nullptr)
    {
        TAX_RATE_CRASH(134, L"== CRASH == [%s], %s; invalid parameter, xml doc:0x%p", MODULE_NAME,
                       L"TaxRateDataManager::setSaleIncomeTaxRateTable", nullptr);
        return false;
    }
    XmlElement const* root = doc->Root();
    if (root == nullptr)
    {
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 140, L"[%s], %s; root element is nothing", MODULE_NAME,
                   L"TaxRateDataManager::setSaleIncomeTaxRateTable");
        return false;
    }

    SaleIncomeTaxRateTable taxRateTable;
    taxRateTable._taxRateCount = 0;
    for (int i = 0; i < 10; ++i)
    {
        taxRateTable._taxRateList[i]._interval = 0;
        taxRateTable._taxRateList[i]._taxRate = 0;
    }

    for (XmlElement const* element = root->FirstChildElement(); element != nullptr; element = element->NextElement())
    {
        if (!element->ToXmlNode()->IsValid())
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 148, L"[%s], %s; invalid xml node, line:%d", MODULE_NAME,
                       L"TaxRateDataManager::setSaleIncomeTaxRateTable", static_cast<int>(element->LineNumber()));
            return false;
        }
        if (_wcsicmp(element->Name(), L"record") != 0)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 154, L"[%s], %s; unknown element, elementName:%s, line:%d",
                       MODULE_NAME, L"TaxRateDataManager::setSaleIncomeTaxRateTable", element->Name(),
                       static_cast<int>(element->LineNumber()));
            return false;
        }
        if (taxRateTable._taxRateCount >= 10)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 160,
                       L"[%s], %s; too many tax rate interval data, currentCount:%d, maxCount:%d", MODULE_NAME,
                       L"TaxRateDataManager::setSaleIncomeTaxRateTable", taxRateTable._taxRateCount, 10);
            return false;
        }
        wchar_t const* intervalStr = element->Attribute(L"interval");
        wchar_t const* taxRateStr = element->Attribute(L"tax-rate");
        if (intervalStr == nullptr || taxRateStr == nullptr)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 168,
                       L"[%s], %s; invalid attribute; attribute string is null, intervalStr:0x%p, taxRateStr:0x%p, line:%d",
                       MODULE_NAME, L"TaxRateDataManager::setSaleIncomeTaxRateTable", intervalStr, taxRateStr,
                       static_cast<int>(element->LineNumber()));
            return false;
        }
        if (wcslen(intervalStr) == 0 || wcslen(taxRateStr) == 0)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 172,
                       L"[%s], %s; invalid attribute; string length is zero, intervalStr:%s, taxRateStr:%s, line:%d",
                       MODULE_NAME, L"TaxRateDataManager::setSaleIncomeTaxRateTable", intervalStr, taxRateStr,
                       static_cast<int>(element->LineNumber()));
            return false;
        }
        SaleIncomeTaxRateData taxRateData;
        taxRateData._taxRate = _wtoi(taxRateStr);
        taxRateData._interval = _wtoi64(intervalStr);
        if (taxRateData._interval < 0 || taxRateData._taxRate < 0)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 178,
                       L"[%s], %s; invalid tax rate data, interval:%I64d, taxRate:%d, line:%d", MODULE_NAME,
                       L"TaxRateDataManager::setSaleIncomeTaxRateTable", taxRateData._interval, taxRateData._taxRate,
                       static_cast<int>(element->LineNumber()));
            return false;
        }
        taxRateTable._taxRateList[taxRateTable._taxRateCount] = taxRateData;
        ++taxRateTable._taxRateCount;
        Log::Write(Log::LT_DEBUG, TAX_RATE_FILE, 184,
                   L"[%s], %s; loaded sale income tax rate data, interval:%I64d, taxRate:%d, dataCount:%d", MODULE_NAME,
                   L"TaxRateDataManager::setSaleIncomeTaxRateTable", taxRateData._interval, taxRateData._taxRate,
                   taxRateTable._taxRateCount);
    }

    int dbRetValue = 0;
    if (!MarketDB::SetSaleIncomeTaxRateTable(dbRetValue, taxRateTable))
    {
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 191, L"[%s], %s; failed to set sale income tax rate table, dbRetValue:%d",
                   MODULE_NAME, L"TaxRateDataManager::setSaleIncomeTaxRateTable", dbRetValue);
        return false;
    }
    Log::Write(Log::LT_DEBUG, TAX_RATE_FILE, 195, L"[%s], %s; succeeded to set sale income tax rate table", MODULE_NAME,
               L"TaxRateDataManager::setSaleIncomeTaxRateTable");
    return true;
}

// 0x2f4f0
// LIFT: LTCG removes the unused `this` argument. The binary gives doc in rcx.
bool TaxRateDataManager::setGrossIncomeTaxRateTable(XmlDoc* const doc)
{
    if (doc == nullptr)
    {
        TAX_RATE_CRASH(203, L"== CRASH == [%s], %s; invalid parameter, xml doc:0x%p", MODULE_NAME,
                       L"TaxRateDataManager::setGrossIncomeTaxRateTable", nullptr);
        return false;
    }
    XmlElement const* root = doc->Root();
    if (root == nullptr)
    {
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 209, L"[%s], %s; root element is nothing", MODULE_NAME,
                   L"TaxRateDataManager::setGrossIncomeTaxRateTable");
        return false;
    }

    GrossIncomeTaxRateTable taxRateTable;
    taxRateTable._taxRateCount = 0;
    for (int i = 0; i < 10; ++i)
    {
        taxRateTable._taxRateList[i]._interval = 0;
        taxRateTable._taxRateList[i]._taxRate = 0;
    }

    for (XmlElement const* element = root->FirstChildElement(); element != nullptr; element = element->NextElement())
    {
        if (!element->ToXmlNode()->IsValid())
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 217, L"[%s], %s; invalid xml node, line:%d", MODULE_NAME,
                       L"TaxRateDataManager::setGrossIncomeTaxRateTable", static_cast<int>(element->LineNumber()));
            return false;
        }
        if (_wcsicmp(element->Name(), L"record") != 0)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 223, L"[%s], %s; unknown element, elementName:%s, line:%d",
                       MODULE_NAME, L"TaxRateDataManager::setGrossIncomeTaxRateTable", element->Name(),
                       static_cast<int>(element->LineNumber()));
            return false;
        }
        if (taxRateTable._taxRateCount >= 10)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 229,
                       L"[%s], %s; too many tax rate interval data, currentCount:%d, maxCount:%d", MODULE_NAME,
                       L"TaxRateDataManager::setGrossIncomeTaxRateTable", taxRateTable._taxRateCount, 10);
            return false;
        }
        wchar_t const* intervalStr = element->Attribute(L"interval");
        wchar_t const* taxRateStr = element->Attribute(L"tax-rate");
        if (intervalStr == nullptr || taxRateStr == nullptr)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 237,
                       L"[%s], %s; invalid attribute; attribute string is null, intervalStr:0x%p, taxRateStr:0x%p, line:%d",
                       MODULE_NAME, L"TaxRateDataManager::setGrossIncomeTaxRateTable", intervalStr, taxRateStr,
                       static_cast<int>(element->LineNumber()));
            return false;
        }
        if (wcslen(intervalStr) == 0 || wcslen(taxRateStr) == 0)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 241,
                       L"[%s], %s; invalid attribute; string length is zero, intervalStr:%s, taxRateStr:%s, line:%d",
                       MODULE_NAME, L"TaxRateDataManager::setGrossIncomeTaxRateTable", intervalStr, taxRateStr,
                       static_cast<int>(element->LineNumber()));
            return false;
        }
        GrossIncomeTaxRateData taxRateData;
        taxRateData._taxRate = _wtoi(taxRateStr);
        taxRateData._interval = _wtoi64(intervalStr);
        if (taxRateData._interval < 0 || taxRateData._taxRate < 0)
        {
            Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 247,
                       L"[%s], %s; invalid tax rate data, interval:%I64d, taxRate:%d, line:%d", MODULE_NAME,
                       L"TaxRateDataManager::setGrossIncomeTaxRateTable", taxRateData._interval, taxRateData._taxRate,
                       static_cast<int>(element->LineNumber()));
            return false;
        }
        taxRateTable._taxRateList[taxRateTable._taxRateCount] = taxRateData;
        ++taxRateTable._taxRateCount;
        Log::Write(Log::LT_DEBUG, TAX_RATE_FILE, 253,
                   L"[%s], %s; loaded gross income tax rate data, interval:%I64d, taxRate:%d, dataCount:%d", MODULE_NAME,
                   L"TaxRateDataManager::setGrossIncomeTaxRateTable", taxRateData._interval, taxRateData._taxRate,
                   taxRateTable._taxRateCount);
    }

    int dbRetValue = 0;
    if (!MarketDB::SetGrossIncomeTaxRateTable(dbRetValue, taxRateTable))
    {
        Log::Write(Log::LT_ERROR, TAX_RATE_FILE, 260,
                   L"[%s], %s; failed to set gross income tax rate table, dbRetValue:%d", MODULE_NAME,
                   L"TaxRateDataManager::setGrossIncomeTaxRateTable", dbRetValue);
        return false;
    }
    Log::Write(Log::LT_DEBUG, TAX_RATE_FILE, 264, L"[%s], %s; succeeded to set gross income tax rate table", MODULE_NAME,
               L"TaxRateDataManager::setGrossIncomeTaxRateTable");
    return true;
}
