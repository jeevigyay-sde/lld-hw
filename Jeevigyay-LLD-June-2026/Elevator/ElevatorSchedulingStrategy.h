#ifndef ELEVATORSCHEDULINGSTRATEGY_H
#define ELEVATORSCHEDULINGSTRATEGY_H

#include <vector>
#include <memory>

#include "ElevatorController.h"
#include "ExternalRequest.h"

class ElevatorSchedulingStrategy
{
public:
  virtual ~ElevatorSchedulingStrategy() = default;
  virtual std::shared_ptr<ElevatorController> fnScheduleElevator(std::vector<std::shared_ptr<ElevatorController>> clpaElevatorVector, std::shared_ptr<ExternalRequest> clpaExternalRequest) = 0;
};

#endif // ELEVATORSCHEDULINGSTRATEGY_H