#include "HallButton.h"
#include "CabinButton.h"
#include "ElevatorManagementSystem.h"

#include <future>
#include <chrono>
#include <iostream>
#include <thread>

int main()
{
  auto elevatorSystem = std::make_shared<ElevatorManagementSystem>(2);

  // Start elevator worker threads
  elevatorSystem->fnMoveElevator();

  auto submitHallRequest =
      [](std::shared_ptr<ElevatorManagementSystem> system,
         Direction direction,
         int floor) -> std::shared_ptr<ElevatorController>
  {
    auto button = std::make_shared<HallButton>(system, direction, floor);
    button->fnPressButton();

    auto hallButton = std::dynamic_pointer_cast<HallButton>(button);
    return hallButton ? hallButton->fnGetElevatorController() : nullptr;
  };

  auto submitCabinRequest =
      [](std::shared_ptr<ElevatorController> controller,
         int floor)
  {
    if (!controller)
      return;

    auto cabinButtons =
        controller->fnGetElevator()->fnGetCabinButtons();

    if (floor < 0 || floor >= (int)cabinButtons.size())
      return;

    cabinButtons[floor]->fnPressButton();
  };

  /******************** SCENARIO 1 ************************/

  std::cout << "\n===== Initial Hall Requests =====\n";

  auto future1 = std::async(std::launch::async,
                            submitHallRequest,
                            elevatorSystem,
                            Direction::Up,
                            4);

  auto future2 = std::async(std::launch::async,
                            submitHallRequest,
                            elevatorSystem,
                            Direction::Up,
                            2);

  auto controller1 = future1.get();
  auto controller2 = future2.get();

  /******************** SCENARIO 2 ************************/

  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << "\nPassengers entered elevators.\n";

  auto cabinFuture1 =
      std::async(std::launch::async,
                 submitCabinRequest,
                 controller1,
                 8);

  auto cabinFuture2 =
      std::async(std::launch::async,
                 submitCabinRequest,
                 controller1,
                 6);

  auto cabinFuture3 =
      std::async(std::launch::async,
                 submitCabinRequest,
                 controller2,
                 1);

  cabinFuture1.wait();
  cabinFuture2.wait();
  cabinFuture3.wait();

  /******************** SCENARIO 3 ************************/

  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cout << "\nNew hall requests while elevators are moving.\n";

  auto future3 =
      std::async(std::launch::async,
                 submitHallRequest,
                 elevatorSystem,
                 Direction::Down,
                 9);

  auto future4 =
      std::async(std::launch::async,
                 submitHallRequest,
                 elevatorSystem,
                 Direction::Up,
                 5);

  auto controller3 = future3.get();
  auto controller4 = future4.get();

  /******************** SCENARIO 4 ************************/

  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << "\nPassengers enter newly arrived elevators.\n";

  auto cabinFuture4 =
      std::async(std::launch::async,
                 submitCabinRequest,
                 controller3,
                 0);

  auto cabinFuture5 =
      std::async(std::launch::async,
                 submitCabinRequest,
                 controller4,
                 7);

  cabinFuture4.wait();
  cabinFuture5.wait();

  /******************** SCENARIO 5 ************************/

  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << "\nPeak hour: Multiple requests arrive simultaneously.\n";

  std::vector<std::future<std::shared_ptr<ElevatorController>>> peakHourRequests;

  peakHourRequests.push_back(
      std::async(std::launch::async,
                 submitHallRequest,
                 elevatorSystem,
                 Direction::Up,
                 3));

  peakHourRequests.push_back(
      std::async(std::launch::async,
                 submitHallRequest,
                 elevatorSystem,
                 Direction::Down,
                 8));

  peakHourRequests.push_back(
      std::async(std::launch::async,
                 submitHallRequest,
                 elevatorSystem,
                 Direction::Up,
                 6));

  peakHourRequests.push_back(
      std::async(std::launch::async,
                 submitHallRequest,
                 elevatorSystem,
                 Direction::Down,
                 1));

  for (auto &future : peakHourRequests)
  {
    future.wait();
  }

  /******************** SCENARIO 6 ************************/

  std::this_thread::sleep_for(std::chrono::seconds(10));

  std::cout << "\nStopping Elevator System...\n";

  for (auto &controller : elevatorSystem->fnGetElevatorControllers())
  {
    controller->stop();
  }

  return 0;
}