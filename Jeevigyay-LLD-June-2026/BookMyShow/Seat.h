#ifndef SEAT_H
#define SEAT_H

class Seat
{
public:
  enum class SeatType
  {
    Normal,
    Premium
  };

  enum class SeatStatus
  {
    LOCKED,
    BOOKED,
    AVAILABLE
  };

  Seat(int row, int col, SeatType enmaSeatType, SeatStatus enmaSeatStatus, double dPrice)
  {
    m_iRow = row;
    m_iCol = col;
    m_enmSeatStatus = enmaSeatStatus;
    m_enmSeatType = enmaSeatType;
    m_dPrice = dPrice;
  }

  void fnSetSeatStatus(SeatStatus enmaSeatStatus)
  {
    m_enmSeatStatus = enmaSeatStatus;
  }

  SeatStatus fnGetSeatStatus()
  {
    return m_enmSeatStatus;
  }

  double fnGetPrice()
  {
    return m_dPrice;
  }

private:
  int m_iRow;
  int m_iCol;
  SeatType m_enmSeatType;
  SeatStatus m_enmSeatStatus;
  double m_dPrice;
};

#endif // SEAT_H