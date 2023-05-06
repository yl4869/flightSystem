#include "ticket.hpp"

#include <iostream>

Ticket::Ticket(std::string ticketNumber, std::string flightNumber,
               Passenger passenger, std::string seatNumber, std::string gate,
               std::string boardingTime) {
  this->ticketNumber = ticketNumber;
  this->flightNumber = flightNumber;
  this->passenger = passenger;
  this->seatNumber = seatNumber;
  this->gate = gate;
  this->boardingTime = boardingTime;
}

void Ticket::displayTicketInfo() {
  std::cout << "Ticket Number: " << ticketNumber << std::endl;
  std::cout << "Flight Number: " << flightNumber << std::endl;
  std::cout << "Passenger Info: " << passenger.name << std::endl;
  passenger.displayPassengerInfo();
  std::cout << "Seat Number: " << seatNumber << std::endl;
  std::cout << "Gate: " << gate << std::endl;
  std::cout << "Boarding Time: " << boardingTime << std::endl;
}

void Ticket::printTicket() {
  // print ticket information
}

void Ticket::updateSeatNumber(std::string newSeatNumber) {
  seatNumber = newSeatNumber;  // update seat number
}

void Ticket::updateGate(std::string newGate) {
  gate = newGate;  // update gate
}

void Ticket::updateBoardingTime(std::string newBoardingTime) {
  boardingTime = newBoardingTime;  // update boarding time
}
