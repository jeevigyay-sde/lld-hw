#ifndef ELEVATORCONTROLLER_H
#define ELEVATORCONTROLLER_H

#include <memory>
#include <mutex>
#include <set>
#include <thread>

#include "Direction.h"

class Elevator;

class ElevatorController
{
public:
  explicit ElevatorController(std::shared_ptr<Elevator> clpaElevator);
  std::shared_ptr<Elevator> fnGetElevator();
  void start();
  void stop();
  void fnMoveElevator();
  void fnSubmitRequest(int iaDesinationFloor);

private:
  std::shared_ptr<Elevator> m_clpElevator = nullptr;
  std::set<int> m_iUpFloorSet;
  std::set<int> m_iDownFloorSet;
  std::mutex m_mutex;
  std::thread worker;
  bool m_bIsRunning = false;
};

#endif // ELEVATORCONTROLLER_H