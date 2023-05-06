#include <string>
#include "passenger.hpp"
#ifndef __TICKET_HPP
#define __TICKET_HPP
class Ticket {
 public:
  std::string ticketNumber;
  std::string flightNumber;
  Passenger passenger;
  std::string seatNumber;
  std::string gate;
  std::string boardingTime;

  Ticket(std::string ticketNumber, std::string flightNumber,
         Passenger passenger, std::string seatNumber, std::string gate,
         std::string boardingTime);

  void displayTicketInfo();

  void printTicket();

  void updateSeatNumber(std::string newSeatNumber);

  void updateGate(std::string newGate);

  void updateBoardingTime(std::string newBoardingTime);
};

#endif // !TICKET_HPP
