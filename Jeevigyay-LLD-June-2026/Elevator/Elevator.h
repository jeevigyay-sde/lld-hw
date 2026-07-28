#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <memory>
#include <vector>
#include <thread>
#include <mutex>

#include "Direction.h"
#include "Door.h"
#include "Display.h"
#include "Button.h"

class ElevatorController;

class Elevator
{
public:
  enum class ElevatorState
  {
    Stopped,
    Moving
  };

  explicit Elevator(int iInitialFloor = 0);

  int fnGetCurrentFloor() const;
  Direction fnGetDirection() const;
  ElevatorState fnGetElevatorState() const;

  static std::mutex m_mutex;

  void fnUpdateDirection(Direction enmDirection);
  void fnUpdateCurrentFloor(int iFloor);
  void fnUpdateDisplay();
  void fnOpenDoor();
  void fnCloseDoor();
  void fnUdateElevatorState(ElevatorState enmState);

  void fnUpdateFloorRange(int iMinFloor, int iMaxFloor);
  void fnInitializeCabinButtons(std::shared_ptr<ElevatorController> clpController);
  std::vector<std::shared_ptr<Button>> fnGetCabinButtons();

private:
  int m_iCurrentFloor;
  Direction m_enmDirection;
  ElevatorState m_enmState;
  int m_iMinFloor = 0;
  int m_iMaxFloor = 0;
  std::shared_ptr<Door> m_clpDoor;
  std::shared_ptr<Display> m_clpDisplay;
  std::vector<std::shared_ptr<Button>> m_clpCabinButtons;
};

#endif // ELEVATOR_H