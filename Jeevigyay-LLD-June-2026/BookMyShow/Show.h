#ifndef SHOW_H
#define SHOW_H

#include <vector>
#include <memory>
#include <string>

#include "Movie.h"
#include "Seat.h"

class Show
{
public:
  Show(std::vector<std::shared_ptr<Seat>> clpSeatVector, std::string startTime,
       std::string endTime, double runningHour, std::shared_ptr<Movie> clpMovie)
  {
    m_clpSeatVector = clpSeatVector;
    m_sStartTime = startTime;
    m_sEndTime = endTime;
    m_dRunningDuration = runningHour;
    m_clpMovie = clpMovie;
  }

  std::shared_ptr<Movie> fnGetMovie()
  {
    return m_clpMovie;
  }

private:
  std::vector<std::shared_ptr<Seat>> m_clpSeatVector;
  std::string m_sStartTime;
  std::string m_sEndTime;
  double m_dRunningDuration;
  std::shared_ptr<Movie> m_clpMovie;
};

#endif // SHOW_H