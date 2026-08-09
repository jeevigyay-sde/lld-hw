#ifndef BOOKING_H
#define BOOKING_H

#include <vector>
#include <memory>
#include <iostream>

#include "User.h"
#include "Show.h"
#include "Theatre.h"
#include "Seat.h"

class Booking
{
public:
  enum class BookingStatus
  {
    INVALID,
    Booked,
    Cancelled
  };

  Booking(std::shared_ptr<User> clpUser, std::shared_ptr<Theatre> clpTheatre, std::shared_ptr<Show> clpShow, std::vector<std::shared_ptr<Seat>> clpSeatVector)
  {
    std::cout << "Booking is generated for " << clpTheatre->fnGetName() << "  " << clpShow->fnGetMovie()->fnGetName() << " Size  " << clpSeatVector.size() << std::endl;
    fnUpdateBookingStatus(BookingStatus::Booked);
  }

  void fnUpdateBookingStatus(BookingStatus enmaBookingStatus)
  {
    m_enmBookingStatus = enmaBookingStatus;
    if (enmaBookingStatus == BookingStatus::Cancelled)
    {
      m_enmBookingStatus = BookingStatus::INVALID;
    }
  }

  BookingStatus fnGetBookingStatus()
  {
    return m_enmBookingStatus;
  }

private:
  BookingStatus m_enmBookingStatus = BookingStatus::INVALID;
};

#endif // BOOKING_H