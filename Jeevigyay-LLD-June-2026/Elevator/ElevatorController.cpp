#include "ElevatorController.h"
#include "Elevator.h"

#include <chrono>
#include <limits>
#include <thread>

ElevatorController::ElevatorController(std::shared_ptr<Elevator> clpaElevator)
    : m_clpElevator(clpaElevator)
{
}

std::shared_ptr<Elevator> ElevatorController::fnGetElevator()
{
  return m_clpElevator;
}

void ElevatorController::start()
{
  m_bIsRunning = true;
  worker = std::thread(&ElevatorController::fnMoveElevator, this);
}

void ElevatorController::stop()
{
  m_bIsRunning = false;
  if (worker.joinable())
  {
    worker.join();
  }
}

void ElevatorController::fnMoveElevator()
{
  while (m_bIsRunning)
  {
    int destinationFloor = -1;
    Direction nextDirection = Direction::IDLE;

    {
      std::lock_guard<std::mutex> lock(m_mutex);
      if (m_iUpFloorSet.empty() && m_iDownFloorSet.empty())
      {
        if (m_clpElevator->fnGetElevatorState() != Elevator::ElevatorState::Stopped)
        {
          m_clpElevator->fnUdateElevatorState(Elevator::ElevatorState::Stopped);
          m_clpElevator->fnUpdateDirection(Direction::IDLE);
        }
        continue;
      }

      const int currentFloor = m_clpElevator->fnGetCurrentFloor();
      const Direction currentDirection = m_clpElevator->fnGetDirection();

      auto itCurrentUp = m_iUpFloorSet.find(currentFloor);
      if (itCurrentUp != m_iUpFloorSet.end())
      {
        destinationFloor = currentFloor;
        m_iUpFloorSet.erase(itCurrentUp);
      }
      else
      {
        auto itCurrentDown = m_iDownFloorSet.find(currentFloor);
        if (itCurrentDown != m_iDownFloorSet.end())
        {
          destinationFloor = currentFloor;
          m_iDownFloorSet.erase(itCurrentDown);
        }
        else if (currentDirection == Direction::Up)
        {
          auto it = m_iUpFloorSet.upper_bound(currentFloor);
          if (it != m_iUpFloorSet.end())
          {
            destinationFloor = *it;
            m_iUpFloorSet.erase(it);
            nextDirection = Direction::Up;
          }
          else if (!m_iDownFloorSet.empty())
          {
            auto itDown = m_iDownFloorSet.end();
            --itDown;
            destinationFloor = *itDown;
            m_iDownFloorSet.erase(itDown);
            nextDirection = Direction::Down;
          }
        }
        else if (currentDirection == Direction::Down)
        {
          auto it = m_iDownFloorSet.lower_bound(currentFloor);
          if (it != m_iDownFloorSet.begin())
          {
            --it;
            if (*it < currentFloor)
            {
              destinationFloor = *it;
              m_iDownFloorSet.erase(it);
              nextDirection = Direction::Down;
            }
          }
          if (destinationFloor < 0 && !m_iUpFloorSet.empty())
          {
            auto itUp = m_iUpFloorSet.begin();
            destinationFloor = *itUp;
            m_iUpFloorSet.erase(itUp);
            nextDirection = Direction::Up;
          }
        }
        else
        {
          int upDistance = std::numeric_limits<int>::max();
          int downDistance = std::numeric_limits<int>::max();

          if (!m_iUpFloorSet.empty())
          {
            upDistance = *m_iUpFloorSet.begin() - currentFloor;
          }
          if (!m_iDownFloorSet.empty())
          {
            downDistance = currentFloor - *m_iDownFloorSet.rbegin();
          }

          if (!m_iUpFloorSet.empty() && (upDistance <= downDistance))
          {
            auto itUp = m_iUpFloorSet.begin();
            destinationFloor = *itUp;
            m_iUpFloorSet.erase(itUp);
            nextDirection = Direction::Up;
          }
          else if (!m_iDownFloorSet.empty())
          {
            auto itDown = m_iDownFloorSet.end();
            --itDown;
            destinationFloor = *itDown;
            m_iDownFloorSet.erase(itDown);
            nextDirection = Direction::Down;
          }
        }
      }

      if (destinationFloor >= 0)
      {
        m_clpElevator->fnUdateElevatorState(Elevator::ElevatorState::Moving);
        if (nextDirection == Direction::IDLE)
        {
          nextDirection = (destinationFloor >= currentFloor) ? Direction::Up : Direction::Down;
        }
        m_clpElevator->fnUpdateDirection(nextDirection);
      }
    }

    if (destinationFloor < 0)
    {
      continue;
    }

    const int currentFloor = m_clpElevator->fnGetCurrentFloor();
    if (destinationFloor == currentFloor)
    {
      m_clpElevator->fnOpenDoor();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      m_clpElevator->fnCloseDoor();
      continue;
    }

    const int step = destinationFloor > currentFloor ? 1 : -1;
    int floor = currentFloor;
    while (m_bIsRunning && floor != destinationFloor)
    {
      floor += step;
      m_clpElevator->fnUpdateCurrentFloor(floor);
      m_clpElevator->fnUpdateDisplay();
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    m_clpElevator->fnOpenDoor();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m_clpElevator->fnCloseDoor();
  }
}

void ElevatorController::fnSubmitRequest(int iaDesinationFloor)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  const int currentFloor = m_clpElevator->fnGetCurrentFloor();
  if (iaDesinationFloor == currentFloor)
  {
    return;
  }

  if (iaDesinationFloor > currentFloor)
  {
    m_iUpFloorSet.insert(iaDesinationFloor);
  }
  else
  {
    m_iDownFloorSet.insert(iaDesinationFloor);
  }
}