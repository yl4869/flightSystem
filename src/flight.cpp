#include "flight.hpp"

#include <random>
#include <iostream>

Flight::Flight(std::string flightNumber, std::string departureTime,
               std::string arrivalTime, std::string departureAirport,
               std::string arrivalAirport, std::string airline,
               std::string aircraftType, int totalSeats) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(500, 1000);
  this->flightNumber = flightNumber;
  this->departureTime = departureTime;
  this->arrivalTime = arrivalTime;
  this->departureAirport = departureAirport;
  this->arrivalAirport = arrivalAirport;
  this->airline = airline;
  this->aircraftType = aircraftType;
  this->totalSeats = totalSeats;
  this->availableSeats = totalSeats;
  this->price = distr(gen);
}

Flight::Flight(std::string flightNumber, std::string departureTime,
               std::string arrivalTime, std::string departureAirport,
               std::string arrivalAirport, std::string airline,
               std::string aircraftType, int totalSeats, int availableSeats) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(500, 1000);
  this->flightNumber = flightNumber;
  this->departureTime = departureTime;
  this->arrivalTime = arrivalTime;
  this->departureAirport = departureAirport;
  this->arrivalAirport = arrivalAirport;
  this->airline = airline;
  this->aircraftType = aircraftType;
  this->totalSeats = totalSeats;
  this->availableSeats = availableSeats;
  this->price = distr(gen);
}

void Flight::displayFlightInfo() {
  std::cout << "Flight Number: " << flightNumber << std::endl;
  std::cout << "Departure Time: " << departureTime << std::endl;
  std::cout << "Arrival Time: " << arrivalTime << std::endl;
  std::cout << "Departure Airport: " << departureAirport << std::endl;
  std::cout << "Arrival Airport: " << arrivalAirport << std::endl;
  std::cout << "Airline: " << airline << std::endl;
  std::cout << "Aircraft Type: " << aircraftType << std::endl;
  std::cout << "Total Seats: " << totalSeats << std::endl;
  std::cout << "Available Seats: " << availableSeats << std::endl;
}

bool Flight::reserveSeat(int numSeats) {
  if (numSeats > availableSeats) {
    return false;  // not enough seats available
  }
  availableSeats -= numSeats;  // reserve seats
  return true;                 // reservation successful
}

bool Flight::cancelReservation(int numSeats) {
  if (numSeats > totalSeats - availableSeats) {
    return false;  // not enough seats reserved
  }
  availableSeats += numSeats;  // cancel reservation
  return true;                 // cancellation successful
}
