#ifndef EXTERNALREQUEST_H
#define EXTERNALREQUEST_H

#include "Direction.h"

class ExternalRequest
{
public:
  ExternalRequest(int iaSourceFloor, Direction enmaDirection)
  {
    m_iSourceFloor = iaSourceFloor;
    m_enmDirection = enmaDirection;
  }
  int fnGetSourceFloor()
  {
    return m_iSourceFloor;
  }
  Direction fnGetDirection()
  {
    return m_enmDirection;
  }

private:
  int m_iSourceFloor = -1;
  Direction m_enmDirection;
};

#endif // EXTERNALREQUEST_H