// MarketDB.obj (MarketDealerDaemon PDB). Card lift-marketdealerdaemon-4 lifts the load functions.
// Cards 5, 6 and 7 add the other bodies to MarketDB.cpp.
#pragma once

#include "Db.h"

class SaleIncomeTaxRateTable;
class GrossIncomeTaxRateTable;
class MarketStatement;
class DeliveryRelation;
class RetrieveSaleListJob;
class RetrieveBidListJob;
class RetrieveReservationListJob;
class ReserveSaleJob;
class CancelSaleReservationJob;
class RegisterSaleJob;
class UpdateSalePriceJob;
class AbandonSaleJob;
class ReserveBidJob;
class CancelBidReservationJob;
class RegisterBidJob;
class UpdateBidPriceJob;
class AbandonBidJob;
class ReservePurchaseJob;
class CancelPurchaseReservationJob;
class RegisterPurchaseJob;
class UpdateStatusToReportSuccessJob;
class UpdateStatusToPawnRemovalSuccessJob;
class UpdateStatusToPawnRemovalFailureJob;
class UpdateStatusToPostRegistrationSuccessJob;
class UpdateStatusToPostRegistrationFailureJob;
class UpdateStatusToRetryReadyJob;
class SuspendSaleManagementJob;
class RetrySingleDeliveryFailureManagementJob;
class UpdateStatusToReportFailureManagementJob;

// RAII holder of a DbTransaction. The ctor is inlined in the callers.
struct AutoDbTran
{
    // LIFT: Inlined ctor.
    explicit AutoDbTran(unsigned int dbId) : Tran(Db::AllocTransaction(dbId)), TimeoutSec(10) {}
    ~AutoDbTran();  // 0x1b170

    DbTransaction* Tran;
    int TimeoutSec;
};

// The PDB return type of all members is type 0x1626 (taken as bool const).
// ❓ The names of the job parameters (the PDB gives the types only). The name `job` is a guess.
class MarketDB
{
public:
    static bool const SetSaleIncomeTaxRateTable(int& dbRetValue, SaleIncomeTaxRateTable& taxRateTable);    // 0x1b1c0
    static bool const SetGrossIncomeTaxRateTable(int& dbRetValue, GrossIncomeTaxRateTable& taxRateTable);  // 0x1b4f0
    static bool const LoadSaleList(int& dbRetValue);                                                       // 0x1b820
    static bool const LoadBidList(int& dbRetValue);                                                        // 0x1cf40
    static bool const LoadPurchaseList(int& dbRetValue);                                                   // 0x1d9b0
    static bool const LoadDeliveryList(int& dbRetValue);                                                   // 0x1e400
    static bool const RetrieveSaleList(int& dbRetValue, RetrieveSaleListJob& job);                         // 0x1f840
    static bool const RetrieveBidList(int& dbRetValue, RetrieveBidListJob& job);                           // 0x20000
    static bool const RetrieveReservationList(int& dbRetValue, RetrieveReservationListJob& job);           // 0x20760
    static bool const ReserveSale(int& dbRetValue, ReserveSaleJob& job);                                   // 0x20b90
    static bool const CancelSaleReservation(int& dbRetValue, CancelSaleReservationJob& job);               // 0x21150
    static bool const RegisterSale(int& dbRetValue, RegisterSaleJob& job);                                 // 0x213c0
    static bool const UpdateSalePrice(int& dbRetValue, UpdateSalePriceJob& job);                           // 0x21b00
    static bool const AbandonSale(int& dbRetValue, AbandonSaleJob& job);                                   // 0x21ec0
    static bool const ReserveBid(int& dbRetValue, ReserveBidJob& job);                                     // 0x222a0
    static bool const CancelBidReservation(int& dbRetValue, CancelBidReservationJob& job);                 // 0x22710
    static bool const RegisterBid(int& dbRetValue, RegisterBidJob& job);                                   // 0x22980
    static bool const UpdateBidPrice(int& dbRetValue, UpdateBidPriceJob& job);                             // 0x22d20
    static bool const AbandonBid(int& dbRetValue, AbandonBidJob& job);                                     // 0x23070
    static bool const ReservePurchase(int& dbRetValue, ReservePurchaseJob& job);                           // 0x23450
    static bool const CancelPurchaseReservation(int& dbRetValue, CancelPurchaseReservationJob& job);       // 0x238d0
    static bool const RegisterPurchase(int& dbRetValue, RegisterPurchaseJob& job);                         // 0x23b40
    // Parameter names of ExpireSale and ExpireAuction come from the PDB locals (pdbq fn).
    static bool const ExpireSale(int& dbRetValue, long long saleId, long long& outItemDeliveryId,
                                 MarketStatement& outMarketStatement);                                     // 0x24100
    static bool const ExpireAuction(int& dbRetValue, long long saleId, int ruleResetTime, int& outDeliveryCount,
                                    DeliveryRelation*& deliveryRelation, int const arraySize);             // 0x24490
    static bool const UpdateStatusToReporting(int& dbRetValue, long long deliveryId);                      // 0x24e90
    static bool const UpdateStatusToReportSuccess(int& dbRetValue, UpdateStatusToReportSuccessJob& job);   // 0x25110
    static bool const UpdateStatusToPawnRemovalSuccess(int& dbRetValue,
                                                       UpdateStatusToPawnRemovalSuccessJob& job);           // 0x25320
    static bool const UpdateStatusToPawnRemovalFailure(int& dbRetValue,
                                                       UpdateStatusToPawnRemovalFailureJob& job);           // 0x25530
    static bool const UpdateStatusToPostRegistrationSuccess(int& dbRetValue,
                                                            UpdateStatusToPostRegistrationSuccessJob& job); // 0x25740
    static bool const UpdateStatusToPostRegistrationFailure(int& dbRetValue,
                                                            UpdateStatusToPostRegistrationFailureJob& job); // 0x259b0
    static bool const UpdateStatusToRetryReady(int& dbRetValue, UpdateStatusToRetryReadyJob& job);         // 0x25bc0
    static bool const LoadRetryReadySingleDelivery(int& dbRetValue, long long deliveryId);                 // 0x25dd0
    static bool const ResetUncompletedDeliveryStatus(int& dbRetValue, int& resetCount);                    // 0x27230
    static bool const SuspendSaleByManager(int& dbRetValue, SuspendSaleManagementJob& job);                // 0x27440
    static bool const ResetDeliveryFailureByManager(int& dbRetValue,
                                                    RetrySingleDeliveryFailureManagementJob& job);          // 0x276b0
    static bool const ResetAllDeliveryFailureByManager(int& dbRetValue);                                   // 0x27970
    static bool const LoadRetryReadyDeliveryList(int& dbRetValue);                                         // 0x27b50
    static bool const UpdateStatusToReportFailure(int& dbRetValue,
                                                  UpdateStatusToReportFailureManagementJob& job);           // 0x28f50

private:
    MarketDB();
    MarketDB(MarketDB const&);
    ~MarketDB();
    MarketDB& operator=(MarketDB const&);
};
