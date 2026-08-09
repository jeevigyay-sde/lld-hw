#ifndef UPIPAYMENTSTRATEGY_H
#define UPIPAYMENTSTRATEGY_H

#include <iostream>

#include "PaymentStrategy.h"

class UPIPaymentStrategy : public PaymentStrategy
{
public:
  void fnPay(double amount) override
  {
    std::cout << "Payment of " << amount << "is made" << std::endl;
  }
};

#endif // UPIPAYMENTSTRATEGY_H