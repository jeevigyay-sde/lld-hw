#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle
{
public:
  enum class VehicleType
  {
    BIKE,
    CAR,
    BUS
  };

  Vehicle(std::string id, std::string vehicleNo, VehicleType enmaVehicleType)
  {
    uniqueId = id;
    m_sVehicleNo = vehicleNo;
    m_enmVehicleType = enmaVehicleType;
  }

  VehicleType fnGetVehicleType()
  {
    return m_enmVehicleType;
  }

private:
  std::string uniqueId;
  VehicleType m_enmVehicleType;
  std::string m_sVehicleNo;
};

#endif // VEHICLE_H