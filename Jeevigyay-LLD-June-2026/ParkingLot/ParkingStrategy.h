#ifndef PARKING_STRATEGY_H
#define PARKING_STRATEGY_H

#include <memory>
#include <vector>

#include "ParkingSlot.h"

class ParkingStrategy
{
public:
  virtual void fnAddParkingSlotVector(std::vector<std::shared_ptr<ParkingSlot>> clpaParkingSlotVector) = 0;
  virtual void fnAddParkingSlot(std::shared_ptr<ParkingSlot> clpaParkingSlot) = 0;
  virtual std::shared_ptr<ParkingSlot> fnAllocateParkingSlot(ParkingSlot::ParkingSlotType enmaParkingSlotType) = 0;
  virtual ~ParkingStrategy() = default;
};

#endif // PARKING_STRATEGY_H