#ifndef HOURLYPRICINGSTRATEGY_H
#define HOURLYPRICINGSTRATEGY_H

#include "PricingStrategy.h"

class HourlyPricingStrategy : public PricingStrategy
{
public:
  double fnCalculatePrice(double duration, ParkingSlot::ParkingSlotType slotType) override
  {
    double price = 0.0;
    switch (slotType)
    {
    case ParkingSlot::ParkingSlotType::TWOWHEELER:
      price = (duration / 3600.0) * 20.0; // Example rate for two-wheeler
      break;
    case ParkingSlot::ParkingSlotType::COMPACT:
      price = (duration / 3600.0) * 50.0; // Example rate for compact
      break;
    case ParkingSlot::ParkingSlotType::LARGE:
      price = (duration / 3600.0) * 100.0; // Example rate for large
      break;
    default:
      break;
    }
    return price;
  }
};

#endif // HOURLYPRICINGSTRATEGY_H