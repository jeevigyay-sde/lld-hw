#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <iostream>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <memory>

#include "ParkingSlot.h"
#include "Vehicle.h"
#include "Ticket.h"
#include "TicketService.h"
#include "Receipt.h"
#include "ReceiptService.h"

std::mutex m_clMutex;

class ParkingLot
{
public:
  ParkingLot(int iaFloors, std::unordered_map<ParkingSlot::ParkingSlotType, std::vector<std::shared_ptr<ParkingSlot>>> claParkingSlotMap, std::unordered_map<Vehicle::VehicleType, ParkingSlot::ParkingSlotType> claParkingSlottoVehicleMap)
  {
    m_iNoOfFloors = iaFloors;
    m_clParkingSlotMap = claParkingSlotMap;
    m_clParkingSlotToVehicleMap = claParkingSlottoVehicleMap;
  }
  ~ParkingLot() = default;

  std::shared_ptr<Ticket> fnGenerateTicket(std::shared_ptr<Vehicle> clpaVehicle)
  {
    TicketService clTicketService;
    std::cout << "Ticket is generated for Vehicle: " << std::endl;
    return clTicketService.fnGenerateTicket(clpaVehicle);
  }

  std::shared_ptr<ParkingSlot> fnGetParkingSlot(std::shared_ptr<Vehicle> clpaVehicle)
  {
    std::lock_guard<std::mutex> lock(m_clMutex);
    ParkingSlot::ParkingSlotType enmParkingSlotType = m_clParkingSlotToVehicleMap[clpaVehicle->fnGetVehicleType()];
    auto clpParkingSlotVector = m_clParkingSlotMap[enmParkingSlotType];
    for (auto clpParkingSlot : clpParkingSlotVector)
    {
      if (clpParkingSlot && clpParkingSlot->fnGetParkingSlotAvailability())
      {
        std::cout << "Parking Slot Found for Vehicle: " << std::endl;
        return clpParkingSlot;
      }
    }
    return nullptr;
  }

  void fnUpdateParkingSlotStatus(std::shared_ptr<ParkingSlot> clpaParkingSlot, bool baAvailable)
  {
    if (clpaParkingSlot)
    {
      clpaParkingSlot->fnUpdateParkingSlotAvailability(baAvailable);
    }
  }

  std::shared_ptr<Receipt> fnGenerateReceipt(std::shared_ptr<Ticket> clpaTicket,
                                             ParkingSlot::ParkingSlotType enmaParkingSlotType,
                                             std::shared_ptr<PricingStrategy> clpaPricingStrategy)
  {
    ReceiptService clReceiptService;
    std::cout << "Receipt is generated for Vehicle: " << std::endl;
    return clReceiptService.fnGenerateReceipt(clpaTicket, enmaParkingSlotType, clpaPricingStrategy);
  }

private:
  int m_iNoOfFloors = 0;
  std::unordered_map<ParkingSlot::ParkingSlotType, std::vector<std::shared_ptr<ParkingSlot>>> m_clParkingSlotMap;
  std::unordered_map<Vehicle::VehicleType, ParkingSlot::ParkingSlotType> m_clParkingSlotToVehicleMap;
};

#endif // PARKINGLOT_H