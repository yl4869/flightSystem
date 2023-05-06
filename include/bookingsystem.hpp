#include <vector>
#ifndef __BOOKINGSYSTEM_HPP
#define __BOOKINGSYSTEM_HPP
#include "flight.hpp"
#include "passenger.hpp"
#include "payment.hpp"
#include "reservation.hpp"
#include "ticket.hpp"
class BookingSystem {
 public:
  std::vector<Flight> flights;
  std::vector<Passenger> passengers;
  std::vector<Reservation> reservations;
  std::vector<Ticket> tickets;
  std::vector<Payment> payments;

  std::vector<Ticket> findPassengerTickets(std::string idNumber);

  void addFlight(Flight flight);

  std::vector<Flight> getFlights();

  void addPassenger(Passenger passenger);

  void addReservation(Reservation reservation);

  void addTicket(Ticket ticket);

  void addPayment(Payment payment);

  Reservation bookFlight(std::string flightNumber, Passenger passenger);

  bool cancelReservation(std::string reservationNumber);

  bool cancelTicket(std::string ticketNumber);

  bool cancelPassenger(std::string idNumber);

  bool cancelFlight(std::string flightNumber);

  Ticket generateTicket(Reservation reservation);

  Payment makePayment(std::string paymentMethod, double amount);

  std::vector<Flight> findFlights(std::string departureAirport,
                                  std::string arrivalAirport);

  std::vector<Passenger> getPassengers();

  Flight getFlightInfo(std::string flightNumber);

  Passenger getPassengerInfo(std::string idNumber);

 private:
  std::string generateReservationNumber();

  std::string generateTicketNumber();

  std::string generateSeatNumber(std::string flightNumber);

  std::string getGate(std::string flightNumber);

  std::string getCurrentTime();

  std::string getBoardingTime(std::string flightNumber);

};

#endif  // !BOOKINGSYSTEM_HPP
