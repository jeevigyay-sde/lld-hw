#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie
{
public:
  Movie(std::string name)
  {
    m_sName = name;
  }

  std::string fnGetName()
  {
    return m_sName;
  }

private:
  std::string m_sName;
};

#endif // MOVIE_H