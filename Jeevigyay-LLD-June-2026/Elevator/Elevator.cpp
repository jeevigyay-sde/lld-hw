#include "Elevator.h"
#include "ElevatorController.h"
#include "CabinButton.h"

std::mutex Elevator::m_mutex;

Elevator::Elevator(int iInitialFloor)
    : m_iCurrentFloor(iInitialFloor), m_enmDirection(Direction::IDLE), m_enmState(ElevatorState::Stopped)
{
  m_clpDoor = std::make_shared<Door>();
  m_clpDisplay = std::make_shared<Display>();
}

int Elevator::fnGetCurrentFloor() const
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_iCurrentFloor;
}

Direction Elevator::fnGetDirection() const
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_enmDirection;
}

void Elevator::fnUpdateFloorRange(int iMinFloor, int iMaxFloor)
{
  if (iMinFloor > iMaxFloor)
  {
    int temp = iMinFloor;
    iMinFloor = iMaxFloor;
    iMaxFloor = temp;
  }

  m_iMinFloor = iMinFloor;
  m_iMaxFloor = iMaxFloor;
}

void Elevator::fnInitializeCabinButtons(std::shared_ptr<ElevatorController> clpController)
{
  m_clpCabinButtons.clear();

  for (int floor = m_iMinFloor; floor <= m_iMaxFloor; ++floor)
  {
    m_clpCabinButtons.push_back(std::make_shared<CabinButton>(clpController, floor));
  }
}

std::vector<std::shared_ptr<Button>> Elevator::fnGetCabinButtons()
{
  return m_clpCabinButtons;
}

Elevator::ElevatorState Elevator::fnGetElevatorState() const
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_enmState;
}

void Elevator::fnUpdateDirection(Direction enmDirection)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_enmDirection = enmDirection;
}

void Elevator::fnUpdateCurrentFloor(int iFloor)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_iCurrentFloor = iFloor;
}

void Elevator::fnUpdateDisplay()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_clpDisplay->fnUpdateDisplay(m_enmDirection, m_iCurrentFloor);
}

void Elevator::fnOpenDoor()
{
  m_clpDoor->fnOpenDoor();
}

void Elevator::fnCloseDoor()
{
  m_clpDoor->fnCloseDoor();
}

void Elevator::fnUdateElevatorState(ElevatorState enmState)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_enmState = enmState;
}