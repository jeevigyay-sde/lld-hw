#include <memory>
#include <vector>
#include <unordered_map>
#include <future>

#include "User.h"
#include "Theatre.h"
#include "Movie.h"
#include "Show.h"
#include "Seat.h"
#include "Screen.h"
#include "ShowSearchStrategy.h"
#include "SearchService.h"
#include "Booking.h"
#include "SeatService.h"
#include "BookingService.h"

int main()
{
  std::shared_ptr<User> clpUser1 = std::make_shared<User>("User1", "abcd");
  std::shared_ptr<User> clpUser2 = std::make_shared<User>("User2", "abcdef");

  std::vector<std::shared_ptr<Show>> clpShowVector;
  std::vector<std::shared_ptr<Screen>> clpScreenVector;
  std::vector<std::shared_ptr<Seat>> clpSeatVector;
  std::vector<std::vector<std::shared_ptr<Seat>>> clpSeatVectors;

  std::shared_ptr<Location> loc = std::make_shared<Location>("Bengaluru");

  std::shared_ptr<Movie> clpMovie = std::make_shared<Movie>("XYZ");

  for (int i = 0; i < 10; i++)
  {
    std::vector<std::shared_ptr<Seat>> clpSeatVectorTemp;
    for (int j = 0; j < 5; j++)
    {
      Seat::SeatType enmSeatType;
      double price = 0;
      if (i < 5)
      {
        enmSeatType = Seat::SeatType::Normal;
        price = 200;
      }
      else
      {
        enmSeatType = Seat::SeatType::Premium;
        price = 400;
      }
      std::shared_ptr<Seat> clpSeat = std::make_shared<Seat>(i, j, enmSeatType, Seat::SeatStatus::AVAILABLE, price);
      clpSeatVector.push_back(clpSeat);
      clpSeatVectorTemp.push_back(clpSeat);
    }
    clpSeatVectors.push_back(clpSeatVectorTemp);
  }

  std::shared_ptr<SeatService> clpSeatService = std::make_shared<SeatService>(clpSeatVectors);

  auto clpShow1 = std::make_shared<Show>(clpSeatVector, "10:00 am", "1:00 pm", 3, clpMovie);
  auto clpShow2 = std::make_shared<Show>(clpSeatVector, "1:00 am", "4:00 pm", 3, clpMovie);
  clpShowVector.push_back(clpShow1);
  clpShowVector.push_back(clpShow2);
  std::shared_ptr<Screen> clpScreen = std::make_shared<Screen>(clpShowVector);
  clpScreenVector.push_back(clpScreen);

  std::vector<std::shared_ptr<Movie>> clpMovieVector;
  clpMovieVector.push_back(clpMovie);

  std::shared_ptr<Theatre> clpTheatre = std::make_shared<Theatre>("ABCD", clpScreenVector, clpMovieVector, loc);

  std::unordered_map<
      std::string, // movie
      std::unordered_map<
          std::string, // city
          std::unordered_map<
              std::shared_ptr<Theatre>,
              std::vector<std::shared_ptr<Show>>>>>
      clpShowMap;
  clpShowMap["Bengaluru"]["XYZ"][clpTheatre] = clpShowVector;
  auto clpShowSearchStrategy = std::make_shared<ShowSearchStrategy>();
  clpShowSearchStrategy->fnSetTheatreToShowMap(clpShowMap);

  auto clpSearchService = std::make_shared<SearchService>();
  clpSearchService->fnSetStrategy(clpShowSearchStrategy);

  std::shared_ptr<SearchCriteria> criteria = std::make_shared<SearchCriteria>();
  criteria->fnSetCityName("Bengaluru");
  criteria->fnSetMovieName("XYZ");

  auto clpSearchResult = clpSearchService->fnSearch(criteria);
  std::shared_ptr<ShowSearchResult> clpShowSearchResult = std::dynamic_pointer_cast<ShowSearchResult>(clpSearchResult);
  std::vector<std::shared_ptr<Show>> clpTheatreToShowVectorResult;
  if (clpShowSearchResult)
  {
    auto clpTemp = clpShowSearchResult->fnGetTheatreToShowList();
    clpTheatreToShowVectorResult = clpTemp[clpTheatre];
  }

  std::vector<std::shared_ptr<Seat>> clpSeatVector1;
  std::vector<std::shared_ptr<Seat>> clpSeatVector2;
  auto clpSeat1 = clpSeatService->fnGetSeat(0, 0);
  auto clpSeat2 = clpSeatService->fnGetSeat(0, 1);

  auto clpSeat3 = clpSeatService->fnGetSeat(1, 0);
  auto clpSeat4 = clpSeatService->fnGetSeat(1, 1);

  auto clpSeat1Future = std::async(std::launch::async, [clpSeatService, clpSeat1]()
                                   { return clpSeatService->fnLockSeat(clpSeat1); });
  auto clpSeat2Future = std::async(std::launch::async, [clpSeatService, clpSeat2]()
                                   { return clpSeatService->fnLockSeat(clpSeat2); });
  auto clpSeat3Future = std::async(std::launch::async, [clpSeatService, clpSeat3]()
                                   { return clpSeatService->fnLockSeat(clpSeat3); });
  auto clpSeat4Future = std::async(std::launch::async, [clpSeatService, clpSeat4]()
                                   { return clpSeatService->fnLockSeat(clpSeat4); });

  if (clpSeat1Future.get())
  {
    clpSeatVector1.push_back(clpSeat1);
  }
  if (clpSeat2Future.get())
  {
    clpSeatVector1.push_back(clpSeat2);
  }

  if (clpSeat3Future.get())
  {
    clpSeatVector2.push_back(clpSeat3);
  }
  if (clpSeat4Future.get())
  {
    clpSeatVector2.push_back(clpSeat4);
  }

  auto clpBooking1 = std::async(std::launch::async, [clpUser1, clpTheatre, clpShow1, clpSeatVector1]()
                                { auto clpBookingService = std::make_shared<BookingService>();
                                return clpBookingService->fnCreateBooking(clpUser1, clpTheatre, clpShow1, clpSeatVector1); });

  auto clpBooking2 = std::async(std::launch::async, [clpUser2, clpTheatre, clpShow1, clpSeatVector2]()
                                { auto clpBookingService = std::make_shared<BookingService>();
                                return clpBookingService->fnCreateBooking(clpUser2, clpTheatre, clpShow1, clpSeatVector2); });

  if (clpBooking1.get())
  {
    std::cout << "Booking 1 is made";
  }
  if (clpBooking2.get())
  {
    std::cout << "Booking 2 is made";
  }

  return 0;
}