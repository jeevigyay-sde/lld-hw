#ifndef DOOR_H
#define DOOR_H

#include <iostream>

class Door
{
public:
  enum class DoorStatus
  {
    IDLE,
    OPEN,
    CLOSED
  };

  void fnCloseDoor()
  {
    std::cout << "Door has closed";
  }
  void fnOpenDoor()
  {
    std::cout << "Door has open";
  }
};

#endif // DOOR_H