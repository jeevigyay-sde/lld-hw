#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

class PaymentStrategy
{
public:
  virtual ~PaymentStrategy() = default;
  virtual void fnPay(double amount) = 0;
};

#endif // PAYMENTSTRATEGY_H