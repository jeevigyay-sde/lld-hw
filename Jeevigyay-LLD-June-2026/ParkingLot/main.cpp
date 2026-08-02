#include "ParkingLotCreation.h"
#include "HourlyPricingStrategy.h"
#include "ParkingLot.h"
#include "NearestParkingStrategy.h"

int main()
{
  std::shared_ptr<ParkingLot> clpParkingLot = ParkingLotCreation::fnCreateParkingLot();
  std::shared_ptr<NearestParkingStrategy> clpNearestParkingStrategy = std::make_shared<NearestParkingStrategy>();
  clpNearestParkingStrategy->fnAddParkingSlotVector(ParkingLotCreation::fnGetParkingSlotVector());

  clpParkingLot->fnSetParkingStrategy(clpNearestParkingStrategy);

  std::shared_ptr<Vehicle> clpVehicle1 = std::make_shared<Vehicle>("V1", "KA-01-1234", Vehicle::VehicleType::CAR);
  std::shared_ptr<ParkingSlot> clpParkingSlot1 = clpParkingLot->fnAllocateParkingSlot(clpVehicle1);
  if (clpParkingSlot1)
  {
    std::shared_ptr<Ticket> clpTicket1 = clpParkingLot->fnGenerateTicket(clpVehicle1);
    std::shared_ptr<PricingStrategy> clpPricingStrategy = std::make_shared<HourlyPricingStrategy>();
    std::shared_ptr<Receipt> clpReceipt1 = clpParkingLot->fnGenerateReceipt(clpTicket1, ParkingSlot::ParkingSlotType::COMPACT, clpPricingStrategy);
    clpParkingLot->fnUpdateParkingSlotStatus(clpParkingSlot1, true);
    clpNearestParkingStrategy->fnAddParkingSlot(clpParkingSlot1);
  }
}
