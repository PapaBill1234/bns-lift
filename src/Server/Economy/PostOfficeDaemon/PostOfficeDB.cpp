// PostOfficeDB.obj (PostOfficeDaemon PDB).
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>
#include <new>
#include "PostOfficeDB.h"
#include "Db.h"
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "PostContext.h"
#include "PostOfficeDaemon.h"
#include "UnsentPostContext.h"

#define POSTOFFICEDB_FILE L"PostOfficeDB.cpp"
#define MODULE_NAME L"postoffice db"  // PDB MODULE_NAME; literal as in CacheEconomyPacketHandler.cpp

#define FAIL_ACQUIRE L"[%s], %s; failed to acquire transaction, dbId:%d"
#define FAIL_PREPARE L"[%s], %s; failed to prepare sql, query:%s"
#define FAIL_BIND L"[%s], %s; failed to bind parameter"
#define FAIL_EXECUTE L"[%s], %s; failed to execute stored procedure, dbRetValue:%d"
#define FAIL_FETCH L"[%s], %s; failed to fetch"
#define FAIL_ADD_CRASH L"== CRASH == [%s], %s; exception occurred; failed to add post context, postId:0x%I64X"
#define FAIL_ADD_EXISTS L"[%s], %s; exception occurred; failed to add post context; post context already exists, postId:0x%I64X"
#define FAIL_REGISTER_UNSENT L"[%s], %s; exception occurred; failed to register unsent post, recipientWid:%u, postId:0x%I64X"
#define FAIL_REMOVE_CRASH L"== CRASH == [%s], %s; exception occurred; failed to remove post context, postId:0x%I64X"

namespace
{
unsigned int const kDbId = 1;
unsigned long long const kNullData = static_cast<unsigned long long>(-1);  // SQL_NULL_DATA
unsigned long long const kNts = static_cast<unsigned long long>(-3);       // SQL_NTS
int const kMaxAttachedItem = 10;
int const kItemColumnCount = 7;

wchar_t* Query(wchar_t const* text) { return const_cast<wchar_t*>(text); }

// LIFT: lift helper, no PDB name. Inlined zero ctor of AttachedItemInfo / AttachedItemContext (0x14e50 loop: fields
// to 0, memset 0x802 of the XML text).
template <typename Item>
__forceinline void ZeroItem(Item& item)
{
    item._itemNo = 0;
    item._itemType = 0;
    item._itemCategory = 0;
    item._itemInstanceId = 0;
    item._itemDataId = 0;
    item._itemLevel = 0;
    item._itemAmount = 0;
    memset(item._itemXmlData, 0, sizeof(item._itemXmlData));
}

__forceinline void ClearRow(PostInfo& postInfo, AttachedItemInfo* items)  // LIFT: lift helper name, not in any PDB
{
    memset(&postInfo, 0, sizeof(postInfo));
    memset(items, 0, sizeof(AttachedItemInfo) * kMaxAttachedItem);
}

// LIFT: Not a PDB function. Inlined in each loader: allocate the PostContext and copy the fetched row.
__forceinline PostContext* MakePostContext(PostInfo const& postInfo, AttachedItemInfo* items,
                                           unsigned long long (*itemLen)[kItemColumnCount], int contextLine,
                                           int itemLine)
{
    PostContext* postContext;
    void* const memory = Memory::_Manager[2]->Alloc(sizeof(PostContext), POSTOFFICEDB_FILE, contextLine);
    if (memory != nullptr)
        postContext = ::new (memory) PostContext();
    else
        postContext = nullptr;
    // BUG: 0x14e50 no null check after the PostContext Alloc (same in all loaders).
    memcpy(&postContext->_postInfo, &postInfo, sizeof(PostInfo));
    for (int i = 0; i < kMaxAttachedItem; ++i)
    {
        if (itemLen[i][0] == kNullData)
            break;
        items[i]._itemNo = static_cast<char>(i + 1);
        ++postContext->_attachedItemCount;
    }
    if (postContext->_attachedItemCount > 0)
    {
        int const count = postContext->_attachedItemCount;
        // 0x15c85-0x15cc0 (one inlined copy): Alloc(count * 0x828 + 8). The code stores no count and uses the raw pointer.
        AttachedItemContext* list = static_cast<AttachedItemContext*>(Memory::_Manager[2]->Alloc(
            sizeof(AttachedItemContext) * static_cast<long long>(count) + 8, POSTOFFICEDB_FILE, itemLine));
        if (list != nullptr)
        {
            for (int i = 0; i < count; ++i)
                ZeroItem(list[i]);
        }
        postContext->_attachedItemList = list;
        // BUG: 0x14e50 no null check after the item list Alloc.
        for (int i = 0; i < postContext->_attachedItemCount; ++i)
            postContext->_attachedItemList[i] = items[i];
    }
    return postContext;
}
}  // namespace

// LIFT: no PDB name. The DbTransaction::BindCol body (Db.cpp:286, POD 0x2d010) inlined at the 17 post column binds.
// The original then merges the 17 statmentErrorLog tails and the 17 "Not initialized" logs into one site each (0x15fa0).
__forceinline bool BindColInline(DbTransaction* const tran, unsigned int index, void* buffer, long long bufferSize,
                                 unsigned int varType, unsigned long long* result)
{
    if (tran->StmtHandle == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"source\\Db.cpp", 286, L"DbTransaction::BindCol(), Not initialized");
        return false;
    }
    *result = static_cast<unsigned long long>(SQL_NTS);
    SQLRETURN const bindRet = SQLBindCol(tran->StmtHandle, static_cast<SQLUSMALLINT>(index),
                                         static_cast<SQLSMALLINT>(varType), buffer, bufferSize,
                                         reinterpret_cast<SQLLEN*>(result));
    if (SQL_SUCCESS == bindRet || SQL_SUCCESS_WITH_INFO == bindRet)
    {
        tran->BoundCol = true;
        return true;
    }
    tran->statmentErrorLog(L"SQLBindCol(%d, %d, %d, %p, %p)", index, varType, buffer, bufferSize, result);
    return false;
}

// LIFT: bind macros, no PDB name. The loaders zero the length arrays after Prepare, set SQL_NTS for the text columns,
// and bind the 17 post columns inline (DB_BIND_COL_NI). The 70 item columns use DbTransaction::BindCol (0x14e50).
#define POST_ZERO_ROW()                                                  \
    postLen[0] = 0;                                                      \
    memset(&postLen[1], 0, sizeof(postLen) - sizeof(postLen[0]));        \
    itemLen[0][0] = 0;                                                   \
    memset(&itemLen[0][1], 0, sizeof(itemLen) - sizeof(itemLen[0][0])); \
    postLen[15] = kNts;                                                  \
    postLen[14] = kNts;                                                  \
    postLen[13] = kNts;                                                  \
    postLen[10] = kNts;                                                  \
    postLen[9] = kNts

#define POST_ZERO_ITEMS()                      \
    for (int i = 0; i < kMaxAttachedItem; ++i) \
    ZeroItem(attachedItemInfo[i])

#define POST_BIND(index, buffer, bufferSize, varType)                                \
    if (!BindColInline(t, index, buffer, bufferSize, varType, &postLen[(index) - 1])) \
    goto BIND_ERROR

#define POST_BIND_COLUMNS()                                                                                \
    POST_BIND(1, &postInfo._postId, 0, SQL_C_SBIGINT);                                                     \
    POST_BIND(2, &postInfo._invoiceId, 0, SQL_C_SBIGINT);                                                  \
    POST_BIND(3, &postInfo._postType, 0, SQL_C_STINYINT);                                                  \
    POST_BIND(4, &postInfo._deliveryReason, 0, SQL_C_STINYINT);                                            \
    POST_BIND(5, &postInfo._postHint, 0, SQL_C_SBIGINT);                                                   \
    POST_BIND(6, &postInfo._senderServiceType, 0, SQL_C_STINYINT);                                         \
    POST_BIND(7, &postInfo._senderWid, 0, SQL_C_SSHORT);                                                   \
    POST_BIND(8, &postInfo._senderPcId, 0, SQL_C_SBIGINT);                                                 \
    POST_BIND(9, &postInfo._senderAccountId, 0, SQL_C_GUID);                                               \
    POST_BIND(10, postInfo._senderWorldName, 66, SQL_C_WCHAR);                                             \
    POST_BIND(11, postInfo._senderName, 66, SQL_C_WCHAR);                                                  \
    POST_BIND(12, &postInfo._recipientWid, 0, SQL_C_SSHORT);                                               \
    POST_BIND(13, &postInfo._recipientPcId, 0, SQL_C_SBIGINT);                                             \
    POST_BIND(14, postInfo._recipientName, 66, SQL_C_WCHAR);                                               \
    POST_BIND(15, postInfo._postTitle, 130, SQL_C_WCHAR);                                                  \
    POST_BIND(16, postInfo._postMessage, 2050, SQL_C_WCHAR);                                               \
    POST_BIND(17, &postInfo._postStatus, 0, SQL_C_STINYINT);                                               \
    column = 17;                                                                                           \
    for (int i = 0; i < kMaxAttachedItem; ++i)                                                             \
    {                                                                                                      \
        if (!t->BindCol(++column, &attachedItemInfo[i]._itemType, 0, SQL_C_STINYINT, &itemLen[i][0]))      \
            goto BIND_ERROR;                                                                               \
        if (!t->BindCol(++column, &attachedItemInfo[i]._itemCategory, 0, SQL_C_STINYINT, &itemLen[i][1]))  \
            goto BIND_ERROR;                                                                               \
        if (!t->BindCol(++column, &attachedItemInfo[i]._itemInstanceId, 0, SQL_C_SBIGINT, &itemLen[i][2])) \
            goto BIND_ERROR;                                                                               \
        if (!t->BindCol(++column, &attachedItemInfo[i]._itemDataId, 0, SQL_C_SLONG, &itemLen[i][3]))       \
            goto BIND_ERROR;                                                                               \
        if (!t->BindCol(++column, &attachedItemInfo[i]._itemLevel, 0, SQL_C_SSHORT, &itemLen[i][4]))       \
            goto BIND_ERROR;                                                                               \
        if (!t->BindCol(++column, &attachedItemInfo[i]._itemAmount, 0, SQL_C_SBIGINT, &itemLen[i][5]))     \
            goto BIND_ERROR;                                                                               \
        itemLen[i][6] = kNts;                                                                              \
        if (!t->BindCol(++column, attachedItemInfo[i]._itemXmlData, 0x802, SQL_C_WCHAR, &itemLen[i][6]))   \
            goto BIND_ERROR;                                                                               \
    }

#define POST_BIND_TAIL(bindLine)                                                                       \
BIND_ERROR:                                                                                            \
    Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, bindLine, FAIL_BIND, MODULE_NAME, fn);                \
    return false

inline AutoDbTran::AutoDbTran(unsigned int dbId, int timeoutSec) : Tran(Db::AllocTransaction(dbId)), TimeoutSec(10)
{
    if (Tran != nullptr)
    {
        TimeoutSec = timeoutSec;
        SQLSetStmtAttrW(Tran->StmtHandle, SQL_QUERY_TIMEOUT,
                        reinterpret_cast<SQLPOINTER>(static_cast<long long>(timeoutSec)), 0);
    }
}

// 0x14e00
AutoDbTran::~AutoDbTran()
{
    if (Tran != nullptr)
    {
        if (TimeoutSec != 10)
            SQLSetStmtAttrW(Tran->StmtHandle, SQL_QUERY_TIMEOUT,
                            reinterpret_cast<SQLPOINTER>(static_cast<long long>(TimeoutSec)), 0);
        Db::ReleaseTransaction(Tran);
        Tran = nullptr;
    }
}

// 0x14e50
bool PostOfficeDB::LoadPostList(int* dbRetValue)
{
    wchar_t const* const fn = L"PostOfficeDB::LoadPostList";
    AutoDbTran tran(kDbId, 0);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 29, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }

    wchar_t const* const query = L"{?=CALL dbo.usp_LoadPostList}";
    DbTransaction* const t = tran.Tran;
    if (!t->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 35, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[1] = {0};
    unsigned long long postLen[17];
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount];
    unsigned int column;
    POST_ZERO_ROW();
    PostInfo postInfo;
    AttachedItemInfo attachedItemInfo[kMaxAttachedItem];
    POST_ZERO_ITEMS();
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]))
        goto BIND_ERROR;
    POST_BIND_COLUMNS();
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 88, FAIL_EXECUTE, MODULE_NAME, fn, *dbRetValue);
        return false;
    }
    {
        PostContextManager* const postContextManager = PostOfficeDaemon::_instance->_postContextManager;
        for (;;)
        {
            ClearRow(postInfo, attachedItemInfo);
            int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch 0x2d350 does not read it.
            if (result == -1)
            {
                Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 103, FAIL_FETCH, MODULE_NAME, fn);
                return false;
            }
            if (result == 0)
                break;

            PostContext* const postContext = MakePostContext(postInfo, attachedItemInfo, itemLen, 109, 121);
            if (!postContextManager->AddContext(postContext))
            {
                Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 127, FAIL_ADD_CRASH, MODULE_NAME, fn, postInfo._postId);
                AlertSender::Write(POSTOFFICEDB_FILE, 127, FAIL_ADD_CRASH, MODULE_NAME, fn, postInfo._postId);
                postContext->removeReferenceCount(POSTOFFICEDB_FILE, 128);
            }
            else
            {
                postContext->removeReferenceCount(POSTOFFICEDB_FILE, 132);
                if (!PostOfficeDaemon::_instance->_unsentPostContextManager->RegisterUnsentPost(postInfo._recipientWid,
                                                                                              postInfo._postId, true))
                {
                    Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 135, FAIL_REGISTER_UNSENT, MODULE_NAME, fn,
                               static_cast<unsigned int>(postInfo._recipientWid), postInfo._postId);
                    if (!postContextManager->RemoveContext(postInfo._postId))
                    {
                        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 138, FAIL_REMOVE_CRASH, MODULE_NAME, fn,
                                   postInfo._postId);
                        AlertSender::Write(POSTOFFICEDB_FILE, 138, FAIL_REMOVE_CRASH, MODULE_NAME, fn,
                                           postInfo._postId);
                    }
                }
            }
        }
    }
    if (*dbRetValue != 0)
        return false;
    return true;

    POST_BIND_TAIL(150);
}

// 0x15fa0
bool PostOfficeDB::LoadSinglePost(int* dbRetValue, long long postId)
{
    wchar_t const* const fn = L"PostOfficeDB::LoadSinglePost";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 158, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadSinglePost(?)}";
    DbTransaction* const t = tran.Tran;
    if (!t->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 164, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[2] = {0, 0};
    unsigned long long postLen[17];
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount];
    unsigned int column;
    POST_ZERO_ROW();
    PostInfo postInfo;
    AttachedItemInfo attachedItemInfo[kMaxAttachedItem];
    POST_ZERO_ITEMS();
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
        goto BIND_ERROR;
    POST_BIND_COLUMNS();
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 219, FAIL_EXECUTE, MODULE_NAME, fn, *dbRetValue);
        return false;
    }
    {
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch 0x2d350 does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 228, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 232, L"[%s], %s; there is no such post, postId:0x%I64X",
                       MODULE_NAME, fn, postId);
            return false;
        }
        if (*dbRetValue != 0)
            return false;

        PostContext* const postContext = MakePostContext(postInfo, attachedItemInfo, itemLen, 242, 254);
        if (!PostOfficeDaemon::_instance->_postContextManager->AddContext(postContext))
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 260, FAIL_ADD_CRASH, MODULE_NAME, fn, postInfo._postId);
            AlertSender::Write(POSTOFFICEDB_FILE, 260, FAIL_ADD_CRASH, MODULE_NAME, fn, postInfo._postId);
            postContext->removeReferenceCount(POSTOFFICEDB_FILE, 261);
            return false;
        }
        postContext->removeReferenceCount(POSTOFFICEDB_FILE, 265);
        return true;
    }

    POST_BIND_TAIL(271);
}

#define Q10 L"?,?,?,?,?,?,?,?,?,?,"

// 0x16f20
bool PostOfficeDB::RegisterPost(int* dbRetValue, PostInfo* postInfo, AttachedItemContext* const attachedItemList,
                                unsigned int attachedItemCount)
{
    wchar_t const* const fn = L"PostOfficeDB::RegisterPost";
    if (attachedItemCount > static_cast<unsigned int>(kMaxAttachedItem))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 278, L"== CRASH == [%s], %s; invalid parameter, attachedItemCount:%d",
                   MODULE_NAME, fn, attachedItemCount);
        AlertSender::Write(POSTOFFICEDB_FILE, 278, L"== CRASH == [%s], %s; invalid parameter, attachedItemCount:%d",
                           MODULE_NAME, fn, attachedItemCount);
        return false;
    }
    if (attachedItemCount > 0 && attachedItemList == nullptr)
    {
        // BUG: 0x16f20 logs the error but does not return. The code continues with a null list.
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 283, L"== CRASH == [%s], %s; invalid parameter, attachedItemList:0x%p",
                   MODULE_NAME, fn, static_cast<void*>(nullptr));
        AlertSender::Write(POSTOFFICEDB_FILE, 283, L"== CRASH == [%s], %s; invalid parameter, attachedItemList:0x%p",
                           MODULE_NAME, fn, static_cast<void*>(nullptr));
    }

    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 290, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query =
        L"{?=CALL dbo.usp_RegisterPost(" Q10 Q10 Q10 Q10 Q10 Q10 Q10 Q10 L"?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 306, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long retLen = 0;
    unsigned long long postLen[16] = {0};
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount] = {{0}};
    postLen[13] = kNts;
    if (postInfo->_invoiceId == 0) postLen[1] = kNullData;
    if (postInfo->_postHint == 0) postLen[4] = kNullData;
    if (postInfo->_senderPcId == 0) postLen[7] = kNullData;
    if (postInfo->_senderAccountId.id[0] == 0 && postInfo->_senderAccountId.id[1] == 0) postLen[8] = kNullData;
    postLen[9] = postInfo->_senderWorldName[0] == L'\0' ? kNullData : kNts;
    postLen[10] = postInfo->_senderName[0] == L'\0' ? kNullData : kNts;
    postLen[14] = postInfo->_postTitle[0] == L'\0' ? kNullData : kNts;
    postLen[15] = postInfo->_postMessage[0] == L'\0' ? kNullData : kNts;

    DbTransaction* const t = tran.Tran;
    bool bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        t->BindParam(2, SQL_PARAM_OUTPUT, &postInfo->_postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[0]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &postInfo->_invoiceId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[1]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &postInfo->_postType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &postLen[2]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &postInfo->_deliveryReason, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &postLen[3]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &postInfo->_postHint, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[4]) &&
        t->BindParam(7, SQL_PARAM_INPUT, &postInfo->_senderServiceType, 0, 0, SQL_TINYINT, SQL_C_STINYINT,
                     &postLen[5]) &&
        t->BindParam(8, SQL_PARAM_INPUT, &postInfo->_senderWid, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &postLen[6]) &&
        t->BindParam(9, SQL_PARAM_INPUT, &postInfo->_senderPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[7]) &&
        t->BindParam(10, SQL_PARAM_INPUT, &postInfo->_senderAccountId, 0, 0, SQL_GUID, SQL_C_GUID, &postLen[8]) &&
        t->BindParam(11, SQL_PARAM_INPUT, postInfo->_senderWorldName, 0x42, 0x20, SQL_WVARCHAR, SQL_C_WCHAR,
                     &postLen[9]) &&
        t->BindParam(12, SQL_PARAM_INPUT, postInfo->_senderName, 0x42, 0x20, SQL_WVARCHAR, SQL_C_WCHAR, &postLen[10]) &&
        t->BindParam(13, SQL_PARAM_INPUT, &postInfo->_recipientWid, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &postLen[11]) &&
        t->BindParam(14, SQL_PARAM_INPUT, &postInfo->_recipientPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[12]) &&
        t->BindParam(15, SQL_PARAM_INPUT, postInfo->_recipientName, 0x42, 0x20, SQL_WVARCHAR, SQL_C_WCHAR,
                     &postLen[13]) &&
        t->BindParam(16, SQL_PARAM_INPUT, postInfo->_postTitle, 0x82, 0x40, SQL_WVARCHAR, SQL_C_WCHAR, &postLen[14]) &&
        t->BindParam(17, SQL_PARAM_INPUT, postInfo->_postMessage, 0x802, 0x400, SQL_WVARCHAR, SQL_C_WCHAR,
                     &postLen[15]);

    for (int i = 0; bound && i < kMaxAttachedItem; ++i)
    {
        unsigned int const index = 18 + kItemColumnCount * i;
        unsigned long long* const len = itemLen[i];
        if (static_cast<unsigned int>(i) < attachedItemCount)
        {
            AttachedItemContext& item = attachedItemList[i];
            if (item._itemInstanceId == 0) len[2] = kNullData;
            if (item._itemDataId == 0) len[3] = kNullData;
            if (item._itemLevel == 0) len[4] = kNullData;
            len[6] = item._itemXmlData[0] == L'\0' ? kNullData : kNts;
            bound = t->BindParam(index + 0, SQL_PARAM_INPUT, &item._itemType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &len[0]) &&
                    t->BindParam(index + 1, SQL_PARAM_INPUT, &item._itemCategory, 0, 0, SQL_TINYINT, SQL_C_STINYINT,
                                 &len[1]) &&
                    t->BindParam(index + 2, SQL_PARAM_INPUT, &item._itemInstanceId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT,
                                 &len[2]) &&
                    t->BindParam(index + 3, SQL_PARAM_INPUT, &item._itemDataId, 0, 0, SQL_INTEGER, SQL_C_SLONG, &len[3]) &&
                    t->BindParam(index + 4, SQL_PARAM_INPUT, &item._itemLevel, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &len[4]) &&
                    t->BindParam(index + 5, SQL_PARAM_INPUT, &item._itemAmount, 0, 0, SQL_BIGINT, SQL_C_SBIGINT,
                                 &len[5]) &&
                    t->BindParam(index + 6, SQL_PARAM_INPUT, item._itemXmlData, 0x802, 0x400, SQL_WVARCHAR, SQL_C_WCHAR,
                                 &len[6]);
        }
        else
        {
            for (int c = 0; c < kItemColumnCount; ++c)
                len[c] = kNullData;
            bound = t->BindParam(index + 0, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &len[0]) &&
                    t->BindParam(index + 1, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &len[1]) &&
                    t->BindParam(index + 2, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &len[2]) &&
                    t->BindParam(index + 3, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_INTEGER, SQL_C_SLONG, &len[3]) &&
                    t->BindParam(index + 4, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &len[4]) &&
                    t->BindParam(index + 5, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &len[5]) &&
                    t->BindParam(index + 6, SQL_PARAM_INPUT, nullptr, 0, 0x400, SQL_WVARCHAR, SQL_C_WCHAR, &len[6]);
        }
    }
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 404, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 394, FAIL_EXECUTE, MODULE_NAME, fn, *dbRetValue);
        return false;
    }
    return *dbRetValue == 0;
}

#undef Q10

namespace
{
// LIFT: Not a PDB function. The two UpdateStatusToDelivery* functions have the same body (inlined twice).
__forceinline bool UpdatePostStatus(int* dbRetValue, long long postId, wchar_t const* fn, wchar_t const* query,
                                    int acquireLine, int prepareLine, int bindLine, int executeLine)
{
    unsigned long long paramLen[2];
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, acquireLine, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, prepareLine, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    paramLen[0] = 0;
    paramLen[1] = 0;
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !tran.Tran->BindParam(2, SQL_PARAM_INPUT, &postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, bindLine, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, executeLine, FAIL_EXECUTE, MODULE_NAME, fn, *dbRetValue);
        return false;
    }
    return *dbRetValue == 0;
}
}  // namespace

// 0x17bf0
// LIFT: noinline. The orig calls it out of line (POD 0x17bf0).
__declspec(noinline) bool PostOfficeDB::UpdateStatusToDeliverySuccess(int* dbRetValue, long long postId)
{
    return UpdatePostStatus(dbRetValue, postId, L"PostOfficeDB::UpdateStatusToDeliverySuccess",
                            L"{?=CALL dbo.usp_UpdateStatusToDeliverySuccess(?)}", 412, 418, 447, 437);
}

// 0x17e00
// LIFT: noinline. The orig calls it out of line (POD 0x17e00).
__declspec(noinline) bool PostOfficeDB::UpdateStatusToDeliveryFailure(int* dbRetValue, long long postId)
{
    return UpdatePostStatus(dbRetValue, postId, L"PostOfficeDB::UpdateStatusToDeliveryFailure",
                            L"{?=CALL dbo.usp_UpdateStatusToDeliveryFailure(?)}", 455, 461, 490, 480);
}

// 0x18010
bool PostOfficeDB::LoadRetryReadySinglePost(int* dbRetValue, long long postId, long long invoiceId,
                                            long long recipientPcId)
{
    wchar_t const* const fn = L"PostOfficeDB::LoadRetryReadySinglePost";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 498, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadRetryReadySinglePost(?,?,?)}";
    DbTransaction* const t = tran.Tran;
    if (!t->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 504, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[4];
    unsigned long long postLen[17];
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount];
    unsigned int column;
    long long nullInd = 0;  // LIFT: orig keeps the indicator in a register (0x18010)
    paramLen[0] = 0;
    paramLen[1] = 0;
    paramLen[3] = 0;
    POST_ZERO_ROW();
    PostInfo postInfo;
    AttachedItemInfo attachedItemInfo[kMaxAttachedItem];
    POST_ZERO_ITEMS();
    if (invoiceId == 0)
        nullInd = -1;
    paramLen[2] = static_cast<unsigned long long>(nullInd);
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) ||
        !t->BindParam(3, SQL_PARAM_INPUT, &invoiceId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) ||
        !t->BindParam(4, SQL_PARAM_INPUT, &recipientPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]))
        goto BIND_ERROR;
    POST_BIND_COLUMNS();
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 567, FAIL_EXECUTE, MODULE_NAME, fn, *dbRetValue);
        return false;
    }
    {
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch 0x2d350 does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 576, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
        {
            // LIFT: full text in .rdata 0x7f710.
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 580,
                       L"[%s], %s; there is no such post, postId:0x%I64X, invoiceId:0x%I64X, recipientPcId:0x%I64X",
                       MODULE_NAME, fn, postId, invoiceId, recipientPcId);
            return false;
        }
        if (*dbRetValue != 0)
            return false;

        PostContext* const postContext = MakePostContext(postInfo, attachedItemInfo, itemLen, 590, 602);
        // LIFT: 0x18010 reads PostOfficeDaemon::_instance once for AddContext and once for the register and remove calls; the failed register block comes first.
        if (!PostOfficeDaemon::_instance->_postContextManager->AddContext(postContext))
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 608, FAIL_ADD_EXISTS, MODULE_NAME, fn, postInfo._postId);
            postContext->removeReferenceCount(POSTOFFICEDB_FILE, 609);
            return false;
        }
        postContext->removeReferenceCount(POSTOFFICEDB_FILE, 613);
        PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
        if (!daemon->_unsentPostContextManager->RegisterUnsentPost(postInfo._recipientWid, postInfo._postId, true))
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 616, FAIL_REGISTER_UNSENT, MODULE_NAME, fn,
                       static_cast<unsigned int>(postInfo._recipientWid), postInfo._postId);
            if (!daemon->_postContextManager->RemoveContext(postInfo._postId))
            {
                Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 619, FAIL_REMOVE_CRASH, MODULE_NAME, fn, postInfo._postId);
                AlertSender::Write(POSTOFFICEDB_FILE, 619, FAIL_REMOVE_CRASH, MODULE_NAME, fn, postInfo._postId);
            }
            return false;
        }
        return true;
    }

    POST_BIND_TAIL(628);
}

// 0x190f0
bool PostOfficeDB::LoadRetryReadyPostList(int* dbRetValue)
{
    wchar_t const* const fn = L"PostOfficeDB::LoadRetryReadyPostList";
    AutoDbTran tran(kDbId, 0);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 636, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }

    wchar_t const* const query = L"{?=CALL dbo.usp_LoadRetryReadyPostList}";
    DbTransaction* const t = tran.Tran;
    if (!t->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 642, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[1] = {0};
    unsigned long long postLen[17];
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount];
    unsigned int column;
    POST_ZERO_ROW();
    PostInfo postInfo;
    AttachedItemInfo attachedItemInfo[kMaxAttachedItem];
    POST_ZERO_ITEMS();
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]))
        goto BIND_ERROR;
    POST_BIND_COLUMNS();
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 695, FAIL_EXECUTE, MODULE_NAME, fn, *dbRetValue);
        return false;
    }
    {
        PostContextManager* const postContextManager = PostOfficeDaemon::_instance->_postContextManager;
        for (;;)
        {
            ClearRow(postInfo, attachedItemInfo);
            int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch 0x2d350 does not read it.
            if (result == -1)
            {
                Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 710, FAIL_FETCH, MODULE_NAME, fn);
                return false;
            }
            if (result == 0)
                break;

            PostContext* const postContext = MakePostContext(postInfo, attachedItemInfo, itemLen, 716, 728);
            if (!postContextManager->AddContext(postContext))
            {
                Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 734, FAIL_ADD_EXISTS, MODULE_NAME, fn, postInfo._postId);
                postContext->removeReferenceCount(POSTOFFICEDB_FILE, 735);
                continue;
            }
            postContext->removeReferenceCount(POSTOFFICEDB_FILE, 739);
            if (!PostOfficeDaemon::_instance->_unsentPostContextManager->RegisterUnsentPost(postInfo._recipientWid,
                                                                                          postInfo._postId, true))
            {
                Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 742, FAIL_REGISTER_UNSENT, MODULE_NAME, fn,
                           static_cast<unsigned int>(postInfo._recipientWid), postInfo._postId);
                if (!postContextManager->RemoveContext(postInfo._postId))
                {
                    Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 745, FAIL_REMOVE_CRASH, MODULE_NAME, fn,
                               postInfo._postId);
                    AlertSender::Write(POSTOFFICEDB_FILE, 745, FAIL_REMOVE_CRASH, MODULE_NAME, fn, postInfo._postId);
                }
            }
        }
    }
    return *dbRetValue == 0;

    POST_BIND_TAIL(757);
}

// 0x1a220
bool PostOfficeDB::UpdateStatusToRetryReady(int* dbRetValue, long long postId, long long invoiceId,
                                            long long recipientPcId)
{
    wchar_t const* const fn = L"PostOfficeDB::UpdateStatusToRetryReady";
    unsigned long long paramLen[4];
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 765, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToRetryReady(?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 771, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    long long nullInd = 0;  // LIFT: orig keeps the indicator in a register (0x1a220)
    paramLen[0] = 0;
    paramLen[1] = 0;
    paramLen[3] = 0;
    if (invoiceId == 0)
        nullInd = -1;
    paramLen[2] = static_cast<unsigned long long>(nullInd);
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !tran.Tran->BindParam(2, SQL_PARAM_INPUT, &postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) ||
        !tran.Tran->BindParam(3, SQL_PARAM_INPUT, &invoiceId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) ||
        !tran.Tran->BindParam(4, SQL_PARAM_INPUT, &recipientPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 808, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 798, FAIL_EXECUTE, MODULE_NAME, fn, *dbRetValue);
        return false;
    }
    return *dbRetValue == 0;
}

// 0x1a500
bool PostOfficeDB::ResetAllDeliveryFailurePost(int* dbRetValue)
{
    wchar_t const* const fn = L"PostOfficeDB::ResetAllDeliveryFailurePost";
    unsigned long long paramLen[1] = {0};
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 816, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ResetAllDeliveryFailurePost}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 822, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 849, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 839, FAIL_EXECUTE, MODULE_NAME, fn, *dbRetValue);
        return false;
    }
    // LIFT: the original keeps both returns apart (0x1a500): one Db::ReleaseTransaction per branch.
    if (*dbRetValue != 0)
        return false;
    return true;
}
