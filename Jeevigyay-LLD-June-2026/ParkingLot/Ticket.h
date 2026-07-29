#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <memory>
#include <ctime>

#include "Vehicle.h"

class Ticket
{
public:
  Ticket(std::string id, std::shared_ptr<Vehicle> clpaVehicle, std::time_t createdDateTime)
  {
    uniqueId = id;
    m_clpVehicle = clpaVehicle;
    m_clpCreatedDateTime = createdDateTime;
  }
  ~Ticket() = default;

  std::shared_ptr<Vehicle> fnGetVehicle()
  {
    return m_clpVehicle;
  }

  std::time_t fnGetCreatedDateTime()
  {
    return m_clpCreatedDateTime;
  }

private:
  std::string uniqueId;
  std::shared_ptr<Vehicle> m_clpVehicle;
  std::time_t m_clpCreatedDateTime;
};

#endif // TICKET_H