#ifndef ELEVATORMANAGEMENTSYSTEM_H
#define ELEVATORMANAGEMENTSYSTEM_H

#include <vector>
#include <memory>

#include "Elevator.h"
#include "ElevatorController.h"
#include "NearestNeighourSchedulingStrategy.h"

class ElevatorManagementSystem
{
public:
  ElevatorManagementSystem(int numOfElevators)
  {
    m_clpStrategy = std::make_shared<NearestNeighbourSchedulingStrategy>();

    for (int iI = 0; iI < numOfElevators; iI++)
    {
      std::shared_ptr<Elevator> clpElevator = std::make_shared<Elevator>(0);
      std::shared_ptr<ElevatorController> clpController = std::make_shared<ElevatorController>(clpElevator);
      clpElevator->fnUpdateFloorRange(0, 10);
      clpElevator->fnInitializeCabinButtons(clpController);
      m_clpElevatorController.push_back(clpController);
    }
  }

  std::vector<std::shared_ptr<ElevatorController>> fnGetElevatorControllers()
  {
    return m_clpElevatorController;
  }

  void fnSetSchedulingStrategy(std::shared_ptr<ElevatorSchedulingStrategy> clpaStrategy)
  {
    m_clpStrategy = clpaStrategy;
  }

  void fnMoveElevator()
  {
    for (auto clpController : m_clpElevatorController)
    {
      clpController->start();
    }
  }

  std::shared_ptr<ElevatorController> fnSubmitRequest(std::shared_ptr<ExternalRequest> clpaRequest)
  {
    if (clpaRequest)
    {
      auto clpController = m_clpStrategy->fnScheduleElevator(m_clpElevatorController, clpaRequest);
      clpController->fnSubmitRequest(clpaRequest->fnGetSourceFloor());
      return clpController;
    }
    return nullptr;
  }

private:
  std::vector<std::shared_ptr<ElevatorController>> m_clpElevatorController;
  std::shared_ptr<ElevatorSchedulingStrategy> m_clpStrategy = nullptr;
};

#endif // ELEVATORMANAGEMENTSYSTEM_H