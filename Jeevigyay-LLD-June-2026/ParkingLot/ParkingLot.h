#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

#include "ParkingSlot.h"
#include "Vehicle.h"
#include "Ticket.h"
#include "TicketService.h"
#include "Receipt.h"
#include "ReceiptService.h"
#include "PricingStrategy.h"
#include "ParkingStrategy.h"

class ParkingLot
{
public:
  ParkingLot(int iaFloors, std::unordered_map<Vehicle::VehicleType, ParkingSlot::ParkingSlotType> claParkingSlottoVehicleMap)
  {
    m_iNoOfFloors = iaFloors;
    m_clParkingSlotToVehicleMap = claParkingSlottoVehicleMap;
  }
  ~ParkingLot() = default;

  void fnSetParkingStrategy(std::shared_ptr<ParkingStrategy> clpaParkingStrategy)
  {
    m_clParkingStrategy = clpaParkingStrategy;
  }

  std::shared_ptr<Ticket> fnGenerateTicket(std::shared_ptr<Vehicle> clpaVehicle)
  {
    TicketService clTicketService;
    std::cout << "Ticket is generated for Vehicle: " << std::endl;
    return clTicketService.fnGenerateTicket(clpaVehicle);
  }

  std::shared_ptr<ParkingSlot> fnAllocateParkingSlot(std::shared_ptr<Vehicle> clpaVehicle)
  {
    ParkingSlot::ParkingSlotType enmParkingSlotType = m_clParkingSlotToVehicleMap[clpaVehicle->fnGetVehicleType()];
    if (m_clParkingStrategy)
    {
      return m_clParkingStrategy->fnAllocateParkingSlot(enmParkingSlotType);
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
  std::unordered_map<Vehicle::VehicleType, ParkingSlot::ParkingSlotType> m_clParkingSlotToVehicleMap;
  std::shared_ptr<ParkingStrategy> m_clParkingStrategy;
};

#endif // PARKINGLOT_H