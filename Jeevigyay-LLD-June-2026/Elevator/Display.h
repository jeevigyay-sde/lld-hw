#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>

#include "Direction.h"

class Display
{
public:
  void fnUpdateDisplay(Direction enmDirection, int iFloor)
  {
    std::cout << "Current Floor: " << iFloor << " Direction: " << (enmDirection == Direction::Up ? "Up" : (enmDirection == Direction::Down ? "Down" : "Idle")) << std::endl;
  }
};

#endif // DISPLAY_H