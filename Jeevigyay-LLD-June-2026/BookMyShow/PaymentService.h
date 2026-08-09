#ifndef PAYMENTSERVICE_H
#define PAYMENTSERVICE_H

#include <memory>

#include "PaymentStrategy.h"

class PaymentService
{
public:
  void fnSetPaymentStrategy(std::shared_ptr<PaymentStrategy> clpStrategy)
  {
    m_clpStrategy = clpStrategy;
  }

  void fnMakePayment(double amount)
  {
    m_clpStrategy->fnPay(amount);
  }

private:
  std::shared_ptr<PaymentStrategy> m_clpStrategy;
};

#endif // PAYMENTSERVICE_H