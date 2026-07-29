#ifndef RECEIPTSERVICE_H

#include <memory>
#include <ctime>

#include "Receipt.h"
#include "Ticket.h"
#include "ParkingSlot.h"
#include "PricingStrategy.h"

class ReceiptService
{
public:
  ReceiptService() = default;
  ~ReceiptService() = default;

  std::shared_ptr<Receipt> fnGenerateReceipt(std::shared_ptr<Ticket> clpaTicket, ParkingSlot::ParkingSlotType enmaParkingSlotType, std::shared_ptr<PricingStrategy> clpaPricingStrategy)
  {
    std::time_t currentTime = std::time(nullptr);
    double duration = std::difftime(currentTime, clpaTicket->fnGetCreatedDateTime());
    std::string receiptId = "RECEIPT_" + std::to_string(currentTime);
    double amount = clpaPricingStrategy->fnCalculatePrice(duration, enmaParkingSlotType);
    auto receipt = std::make_shared<Receipt>(receiptId, amount, duration);
    return receipt;
  }
};

#endif // RECEIPTSERVICE_H
