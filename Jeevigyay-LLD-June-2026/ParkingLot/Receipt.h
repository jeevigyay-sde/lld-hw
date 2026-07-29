#ifndef RECEIPT_H
#define RECEIPT_H

#include <string>
#include <ctime>

#include "Ticket.h"

class Receipt
{
public:
  Receipt(std::string id, double amount, double totalDuration)
  {
    uniqueId = id;
    m_dAmount = amount;
    m_clTotalDuration = totalDuration;
  }
  ~Receipt() = default;

private:
  std::string uniqueId;
  double m_dAmount = 0.0;
  double m_clTotalDuration = 0.0;
};

#endif // RECEIPT_H