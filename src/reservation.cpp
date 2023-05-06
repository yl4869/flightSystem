#include "reservation.hpp"
#include <iostream>
Reservation::Reservation(std::string reservationNumber,
                         std::string flightNumber, Passenger passenger,
                         std::string reservationTime, std::string status) {
  this->reservationNumber = reservationNumber;
  this->flightNumber = flightNumber;
  this->passenger = passenger;
  this->reservationTime = reservationTime;
  this->status = status;
}

void Reservation::displayReservationInfo() {
  std::cout << "Reservation Number: " << reservationNumber << std::endl;
  std::cout << "Flight Number: " << flightNumber << std::endl;
  std::cout << "Passenger Info: " << std::endl;
  passenger.displayPassengerInfo();
  std::cout << "Reservation Time: " << reservationTime << std::endl;
  std::cout << "Status: " << status << std::endl;
}

void Reservation::updateStatus(std::string newStatus) {
  status = newStatus;  // update reservation status
}
