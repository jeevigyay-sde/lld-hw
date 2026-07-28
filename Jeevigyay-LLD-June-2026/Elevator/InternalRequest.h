#ifndef INTERNALREQUEST_H
#define INTERNALREQUEST_H

class InternalRequest
{
public:
  InternalRequest(int iaDestinationFloor)
  {
    m_iDestinationFloor = iaDestinationFloor;
  }
  int fnGetDestinationFloor()
  {
    return m_iDestinationFloor;
  }

private:
  int m_iDestinationFloor = -1;
};

#endif // INTERNALREQUEST_H