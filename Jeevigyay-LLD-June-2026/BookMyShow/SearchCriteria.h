#ifndef SEARCHCRITERIA_H
#define SEARCHCRITERIA_H

#include <memory>

#include "Movie.h"
#include "Theatre.h"
#include "Location.h"

class SearchCriteria
{
public:
  void fnSetTheatre(std::shared_ptr<Theatre> clpTheatre)
  {
    m_clpTheatre = clpTheatre;
  }

  std::shared_ptr<Theatre> fnGetTheatre()
  {
    return m_clpTheatre;
  }

  void fnSetCityName(std::string cityName)
  {
    m_sCityName = cityName;
  }

  std::string fnGetCityName()
  {
    return m_sCityName;
  }

  void fnSetMovieName(std::string movieName)
  {
    m_sMovieName = movieName;
  }

  std::string fnGetMovieName()
  {
    return m_sMovieName;
  }

private:
  std::shared_ptr<Theatre> m_clpTheatre;
  std::string m_sCityName;
  std::string m_sMovieName;
};

#endif // SEARCHCRITERIA_H