#ifndef THEATRE_H
#define THEATRE_H

#include <vector>
#include <string>
#include <memory>

#include "Movie.h"
#include "Screen.h"
#include "Location.h"

class Theatre
{

public:
  Theatre(std::string name, std::vector<std::shared_ptr<Screen>> clpScreenVector,
          std::vector<std::shared_ptr<Movie>> clpMovieVector,
          std::shared_ptr<Location> loc)
  {
    m_sName = name;
    m_clpScreenVector = clpScreenVector;
    m_clpMovieVector = clpMovieVector;
    m_clpLoc = loc;
  }

  std::string fnGetName()
  {
    return m_sName;
  }

  std::vector<std::shared_ptr<Movie>> fnGetMovieList()
  {
    return m_clpMovieVector;
  }

  std::shared_ptr<Location> fnGetLocation()
  {
    return m_clpLoc;
  }

private:
  std::string m_sName;
  std::vector<std::shared_ptr<Screen>> m_clpScreenVector;
  std::vector<std::shared_ptr<Movie>> m_clpMovieVector;
  std::shared_ptr<Location> m_clpLoc;
};

#endif // THEATRE_H