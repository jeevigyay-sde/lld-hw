#ifndef NEARESTNEIGHBOURSCHEDULINGSTRATEGY_H
#define NEARESTNEIGHBOURSCHEDULINGSTRATEGY_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <vector>

#include "Elevator.h"
#include "ElevatorController.h"
#include "ElevatorSchedulingStrategy.h"

class NearestNeighbourSchedulingStrategy : public ElevatorSchedulingStrategy
{
public:
  ~NearestNeighbourSchedulingStrategy() override = default;

  std::shared_ptr<ElevatorController> fnScheduleElevator(std::vector<std::shared_ptr<ElevatorController>> clpaElevatorVector,
                                                         std::shared_ptr<ExternalRequest> clpaExternalRequest) override
  {
    if (clpaElevatorVector.empty() || !clpaExternalRequest)
    {
      return nullptr;
    }

    int iRequestedFloor = clpaExternalRequest->fnGetSourceFloor();
    Direction enmRequestedDirection = clpaExternalRequest->fnGetDirection();

    std::lock_guard<std::mutex> lock(m_mutex);

    int iBestIndex = -1;
    int iBestScore = std::numeric_limits<int>::max();

    for (size_t i = 0; i < clpaElevatorVector.size(); ++i)
    {
      auto clpController = clpaElevatorVector[i];
      if (!clpController)
      {
        continue;
      }

      auto clpElevator = clpController->fnGetElevator();
      int iElevatorFloor = clpElevator->fnGetCurrentFloor();
      Direction enmDirection = clpElevator->fnGetDirection();
      Elevator::ElevatorState enmState = clpElevator->fnGetElevatorState();
      int iDistance = std::abs(iRequestedFloor - iElevatorFloor);
      int iScore = iDistance;

      if (Direction::Up == enmRequestedDirection)
      {
        if (iRequestedFloor < iElevatorFloor)
        {
          iScore += 10;
        }
        else if (Direction::Down == enmDirection && Elevator::ElevatorState::Moving == enmState)
        {
          iScore += 5;
        }
      }
      else if (Direction::Down == enmRequestedDirection)
      {
        if (iRequestedFloor > iElevatorFloor)
        {
          iScore += 10;
        }
        else if (Direction::Up == enmDirection && Elevator::ElevatorState::Moving == enmState)
        {
          iScore += 5;
        }
      }

      if (Direction::IDLE == enmDirection && Elevator::ElevatorState::Stopped == enmState)
      {
        iScore += 1;
      }

      bool bUseRoundRobinTie = (iScore < iBestScore) ||
                               (iScore == iBestScore && i == (m_iNextElevatorIndex % clpaElevatorVector.size()));

      if (bUseRoundRobinTie)
      {
        iBestIndex = static_cast<int>(i);
        iBestScore = iScore;
      }
    }

    if (iBestIndex < 0)
    {
      iBestIndex = static_cast<int>(m_iNextElevatorIndex % clpaElevatorVector.size());
    }

    m_iNextElevatorIndex = (m_iNextElevatorIndex + 1) % clpaElevatorVector.size();

    std::cout << "Selected Elevator " << iBestIndex << std::endl;
    return clpaElevatorVector[iBestIndex];
  }

private:
  std::size_t m_iNextElevatorIndex = 0;
  std::mutex m_mutex;
};

#endif // NEARESTNEIGHBOURSCHEDULINGSTRATEGY_H