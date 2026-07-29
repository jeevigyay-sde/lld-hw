#ifndef PRICINGSTRATEGY_H
#define PRICINGSTRATEGY_H

#include <ctime>

#include "ParkingSlot.h"

class PricingStrategy
{
public:
  virtual double fnCalculatePrice(double duration,
                                  ParkingSlot::ParkingSlotType) = 0;
};

#endif // PRICINGSTRATEGY_H