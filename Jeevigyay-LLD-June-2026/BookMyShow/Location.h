#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location
{
public:
  Location(std::string city)
  {
    m_sCity = city;
  }

  std::string fnGetCity()
  {
    return m_sCity;
  }

private:
  std::string m_sCity;
};

#endif // LOCATION_H