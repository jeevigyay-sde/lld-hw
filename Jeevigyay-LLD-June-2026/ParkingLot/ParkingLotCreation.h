#include <memory>
#include <unordered_map>
#include <vector>

#include "ParkingSlot.h"
#include "ParkingLot.h"
#include "Vehicle.h"

class ParkingLotCreation
{
public:
  static std::shared_ptr<ParkingLot> fnCreateParkingLot()
  {
    auto fnpCreateParkingSlot = [&](std::string id, int iaFloor, int iaDistanceFromEntrance, ParkingSlot::ParkingSlotType enmaParkingSlotType)
    {
      auto clpParkingSlot = std::make_shared<ParkingSlot>(id, iaFloor, iaDistanceFromEntrance, enmaParkingSlotType);
      m_clParkingSlotVector.push_back(clpParkingSlot);
    };

    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 50; j++)
      {
        fnpCreateParkingSlot("TWOWHEELER_" + std::to_string(i) + "_" + std::to_string(j), i, 10 + j + i, ParkingSlot::ParkingSlotType::TWOWHEELER);
        fnpCreateParkingSlot("COMPACT_" + std::to_string(i) + "_" + std::to_string(j), i, 1000 + j + i, ParkingSlot::ParkingSlotType::COMPACT);
        fnpCreateParkingSlot("LARGE_" + std::to_string(i) + "_" + std::to_string(j), i, 5000 + j + i, ParkingSlot::ParkingSlotType::LARGE);
      }
    }
    std::unordered_map<Vehicle::VehicleType, ParkingSlot::ParkingSlotType> clParkingSlottoVehicleMap;

    clParkingSlottoVehicleMap[Vehicle::VehicleType::BIKE] = ParkingSlot::ParkingSlotType::TWOWHEELER;
    clParkingSlottoVehicleMap[Vehicle::VehicleType::CAR] = ParkingSlot::ParkingSlotType::COMPACT;
    clParkingSlottoVehicleMap[Vehicle::VehicleType::BUS] = ParkingSlot::ParkingSlotType::LARGE;

    std::shared_ptr<ParkingLot> clpParkingLot = std::make_shared<ParkingLot>(2, clParkingSlottoVehicleMap);
    return clpParkingLot;
  }
  static std::vector<std::shared_ptr<ParkingSlot>> fnGetParkingSlotVector()
  {
    return m_clParkingSlotVector;
  }

private:
  inline static std::vector<std::shared_ptr<ParkingSlot>> m_clParkingSlotVector;
};