#include <string>
#include "passenger.hpp"
#ifndef __RESERVATION_HPP
#define __RESERVATION_HPP
class Reservation {
 public:
  std::string reservationNumber;
  std::string flightNumber;
  Passenger passenger;
  std::string reservationTime;
  std::string status;

  Reservation(std::string reservationNumber, std::string flightNumber,
              Passenger passenger, std::string reservationTime,
              std::string status);

  void displayReservationInfo();

  void updateStatus(std::string newStatus);
};
#endif // !RESERVATION_HPP

