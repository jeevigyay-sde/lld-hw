#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <memory>

#include "Show.h"

class Screen
{
public:
  Screen(std::vector<std::shared_ptr<Show>> shows)
  {
    m_clpShowVector = shows;
  }

private:
  std::vector<std::shared_ptr<Show>> m_clpShowVector;
};

#endif // SCREEN_H