#ifndef TICKETSERVICE_H
#define TICKETSERVICE_H

#include <ctime>
#include <memory>

#include "Ticket.h"

class TicketService
{
public:
  TicketService() = default;
  ~TicketService() = default;

  std::shared_ptr<Ticket> fnGenerateTicket(std::shared_ptr<Vehicle> clpaVehicle)
  {
    std::time_t currentTime = std::time(nullptr);
    std::string ticketId = "TICKET_" + std::to_string(currentTime);
    auto ticket = std::make_shared<Ticket>(ticketId, clpaVehicle, currentTime);
    return ticket;
  }
};

#endif // TICKETSERVICE_H
