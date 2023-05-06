#include <cstdlib>
#include <string>

#ifndef __FLIGHT_HPP
#define __FLIGHT_HPP
class Flight {
 public:
  std::string flightNumber;
  std::string departureTime;
  std::string arrivalTime;
  std::string departureAirport;
  std::string arrivalAirport;
  std::string airline;
  std::string aircraftType;
  int totalSeats;
  int availableSeats;
  int price;

  Flight(std::string flightNumber, std::string departureTime,
         std::string arrivalTime, std::string departureAirport,
         std::string arrivalAirport, std::string airline,
         std::string aircraftType, int totalSeats, int availableSeats);

  Flight(std::string flightNumber, std::string departureTime,
         std::string arrivalTime, std::string departureAirport,
         std::string arrivalAirport, std::string airline,
         std::string aircraftType, int totalSeats);

  inline std::string getFlightNumber() { return flightNumber; }

  inline std::string getDepartureTime() { return departureTime; }

  inline std::string getArrivalTime() { return arrivalTime; }

  inline std::string getDepartureAirport() { return departureAirport; }

  inline std::string getArrivalAirport() { return arrivalAirport; }

  inline std::string getAirline() { return airline; }

  inline std::string getAircraftType() { return aircraftType; }

  inline int getTotalSeats() { return totalSeats; }

  inline int getAvailableSeats() { return availableSeats; }

  void displayFlightInfo();

  bool reserveSeat(int numSeats);

  bool cancelReservation(int numSeats);
};

#endif  // FLIGHT_HPP
