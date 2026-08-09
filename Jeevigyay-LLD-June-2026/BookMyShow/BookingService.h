#ifndef BOOKINGSERVICE_H
#define BOOKINGSERVICE_H

#include <vector>
#include <memory>

#include "User.h"
#include "Show.h"
#include "Theatre.h"
#include "Seat.h"
#include "Booking.h"

class BookingService
{
public:
  std::shared_ptr<Booking> fnCreateBooking(std::shared_ptr<User> clpUser, std::shared_ptr<Theatre> clpTheatre, std::shared_ptr<Show> clpShow, std::vector<std::shared_ptr<Seat>> clpSeatVector)
  {
    return std::make_shared<Booking>(clpUser, clpTheatre, clpShow, clpSeatVector);
  }
};

#endif // BOOKINGSERVICE_H