#ifndef SEATSERVICE_H
#define SEATSERVICE_H

#include <memory>
#include <mutex>

#include "Seat.h"

std::mutex m_Mutex;

class SeatService
{
public:
  SeatService(std::vector<std::vector<std::shared_ptr<Seat>>> clpSeatVector)
  {
    m_clpSeatVector = clpSeatVector;
  }

  std::shared_ptr<Seat> fnGetSeat(int row, int col)
  {
    return m_clpSeatVector[row][col];
  }

  bool fnLockSeat(std::shared_ptr<Seat> clpSeat)
  {
    if (nullptr == clpSeat)
    {
      return false;
    }

    std::lock_guard<std::mutex> lock(m_Mutex);

    if (clpSeat->fnGetSeatStatus() != Seat::SeatStatus::AVAILABLE)
    {
      return false;
    }

    clpSeat->fnSetSeatStatus(Seat::SeatStatus::LOCKED);
    return true;
  }

  void fnUnLockSeat(std::shared_ptr<Seat> clpSeat)
  {
    if (nullptr == clpSeat)
    {
      return;
    }
    clpSeat->fnSetSeatStatus(Seat::SeatStatus::AVAILABLE);
  }

  void fnBookSeat(std::shared_ptr<Seat> clpSeat)
  {
    if (nullptr == clpSeat)
    {
      return;
    }
    clpSeat->fnSetSeatStatus(Seat::SeatStatus::BOOKED);
  }

private:
  std::vector<std::vector<std::shared_ptr<Seat>>> m_clpSeatVector;
};

#endif // SEATSERVICE_H