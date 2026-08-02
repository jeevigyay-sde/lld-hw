#ifndef NEAREST_PARKING_STRATEGY_H
#define NEAREST_PARKING_STRATEGY_H

#include "ParkingStrategy.h"

#include <mutex>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>

std::mutex m_clMutex;

class NearestParkingStrategy : public ParkingStrategy
{
public:
  void fnAddParkingSlotVector(std::vector<std::shared_ptr<ParkingSlot>> clpaParkingSlotVector) override
  {
    for (const auto &slot : clpaParkingSlotVector)
    {
      m_clParkingSlotMap[slot->fnGetParkingSlotType()][slot->fnGetDistanceFromEntrance()].push_back(slot);
    }
  }

  void fnAddParkingSlot(std::shared_ptr<ParkingSlot> clpaParkingSlot) override
  {
    std::lock_guard<std::mutex> lock(m_clMutex);
    m_clParkingSlotMap[clpaParkingSlot->fnGetParkingSlotType()][clpaParkingSlot->fnGetDistanceFromEntrance()].push_back(clpaParkingSlot);
  }

  std::shared_ptr<ParkingSlot> fnAllocateParkingSlot(ParkingSlot::ParkingSlotType enmaParkingSlotType) override
  {
    std::lock_guard<std::mutex> lock(m_clMutex);
    auto clpParkingSlotMap = m_clParkingSlotMap[enmaParkingSlotType];
    auto clpParkingSlotIt = clpParkingSlotMap.begin();
    auto &clpParkingSlotVector = clpParkingSlotIt->second;
    if (!clpParkingSlotVector.empty())
    {
      std::shared_ptr<ParkingSlot> clpAllocatedSlot = clpParkingSlotVector.back();
      clpParkingSlotVector.pop_back();
      std::cout << "Parking is allocated " << std::endl;
      clpAllocatedSlot->fnUpdateParkingSlotAvailability(false);
      std::cout << "Allocated Parking Slot" << std::endl;

      return clpAllocatedSlot;
    }
    return nullptr;
  }
  ~NearestParkingStrategy() override = default;

private:
  std::unordered_map<ParkingSlot::ParkingSlotType, std::map<int, std::vector<std::shared_ptr<ParkingSlot>>>> m_clParkingSlotMap;
};

#endif // NEAREST_PARKING_STRATEGY_H