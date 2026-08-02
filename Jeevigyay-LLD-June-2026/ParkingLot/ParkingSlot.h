#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include <string>

class ParkingSlot
{
public:
  enum class ParkingSlotType
  {
    TWOWHEELER,
    COMPACT,
    LARGE
  };

  ParkingSlot(std::string id, int iaFloor, int iaDistanceFromEntrance, ParkingSlotType enmaParkingSlotType)
  {
    sUniqueId = id;
    m_enmParkingSlotType = enmaParkingSlotType;
    m_iCurrentFloor = iaFloor;
    m_iDistanceFromEntrance = iaDistanceFromEntrance;
  }
  ~ParkingSlot() = default;

  void fnUpdateParkingSlotAvailability(bool baIsAvailable)
  {
    m_bIsAvailable = baIsAvailable;
  }

  bool fnGetParkingSlotAvailability()
  {
    return m_bIsAvailable;
  }

  ParkingSlotType fnGetParkingSlotType()
  {
    return m_enmParkingSlotType;
  }

  int fnGetDistanceFromEntrance()
  {
    return m_iDistanceFromEntrance;
  }

private:
  std::string sUniqueId;
  ParkingSlotType m_enmParkingSlotType;
  bool m_bIsAvailable = true;
  int m_iCurrentFloor = -1;
  int m_iDistanceFromEntrance = -1;
};

#endif // PARKINGSLOT_H