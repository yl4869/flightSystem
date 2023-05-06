#include "bookingsystem.hpp"

#include <cstdio>
#include <vector>
void BookingSystem::addFlight(Flight flight) {
  flights.push_back(flight);  // add flight to flight list
}

void BookingSystem::addPassenger(Passenger passenger) {
  passengers.push_back(passenger);  // add passenger to passenger list
}

void BookingSystem::addReservation(Reservation reservation) {
  reservations.push_back(reservation);  // add passenger to passenger list
}

void BookingSystem::addTicket(Ticket ticket) { tickets.push_back(ticket); }

void BookingSystem::addPayment(Payment payment) { payments.push_back(payment); }

std::vector<Flight> BookingSystem::getFlights() { return flights; }

std::vector<Passenger> BookingSystem::getPassengers() { return passengers; }
std::vector<Ticket> BookingSystem::findPassengerTickets(std::string idNumber) {
  std::vector<Ticket> result;
  for (int i = 0; i < tickets.size(); i++) {
    if (tickets[i].passenger.idNumber == idNumber) {
      result.push_back(tickets[i]);
    }
  }
  return result;
}

Reservation BookingSystem::bookFlight(std::string flightNumber,
                                      Passenger passenger) {
  // create new reservation
  std::string reservationNumber = generateReservationNumber();
  std::string reservationTime = getCurrentTime();
  std::string status = "booked";
  Reservation reservation(reservationNumber, flightNumber, passenger,
                          reservationTime, status);
  for(auto &i : flights) {
    if (i.flightNumber == flightNumber) {
      i.reserveSeat(1);
    }
  }
  reservations.push_back(reservation);  // add reservation to reservation list
  return reservation;                   // return new reservation
}

bool BookingSystem::cancelReservation(std::string reservationNumber) {
  for (int i = 0; i < reservations.size(); i++) {
    if (reservations[i].reservationNumber == reservationNumber) {
      reservations[i].updateStatus("cancelled");  // update reservation status
      return true;                                // cancellation successful
    }
  }
  return false;  // reservation not found
}

bool BookingSystem::cancelTicket(std::string ticketNumber) {
  for (int i = 0; i < tickets.size(); i++) {
    if (tickets[i].ticketNumber == ticketNumber) {
      for(auto &j: flights) {
        if(j.flightNumber == tickets[i].flightNumber) {
          j.availableSeats += 1;
        }
      }
      tickets.erase(tickets.begin() + i);
      return true;  // cancellation successful
    }
  }
  return false;  // reservation not found
}

bool BookingSystem::cancelFlight(std::string flightNumber) {
  for (int i = 0; i < flights.size(); i++) {
    if (flights[i].flightNumber == flightNumber) {
      flights.erase(flights.begin() + i);
      return true;  // cancellation successful
    }
  }
  return false;  // reservation not found
}


bool BookingSystem::cancelPassenger(std::string idNumber) {
  for (int i = 0; i < passengers.size(); i++) {
    if (passengers[i].idNumber == idNumber) {
      passengers.erase(passengers.begin() + i);
      return true;  // cancellation successful
    }
  }
  return false;  // reservation not found
}


Ticket BookingSystem::generateTicket(Reservation reservation) {
  // create new ticket
  std::string ticketNumber = generateTicketNumber();
  std::string flightNumber = reservation.flightNumber;
  Passenger passenger = reservation.passenger;
  std::string seatNumber = generateSeatNumber(flightNumber);
  std::string gate = getGate(flightNumber);
  std::string boardingTime = getBoardingTime(flightNumber);
  Ticket ticket(ticketNumber, flightNumber, passenger, seatNumber, gate,
                boardingTime);
  tickets.push_back(ticket);  // add ticket to ticket list
  return ticket;              // return new ticket
}

Payment BookingSystem::makePayment(std::string paymentMethod, double amount) {
  // create new payment
  std::string paymentTime = getCurrentTime();
  std::string status = "paid";
  Payment payment(paymentMethod, amount, paymentTime, status);
  payments.push_back(payment);  // add payment to payment list
  return payment;               // return new payment
}

std::vector<Flight> BookingSystem::findFlights(std::string departureAirport,
                                               std::string arrivalAirport) {
  std::vector<Flight> result;
  for (int i = 0; i < flights.size(); i++) {
    if (flights[i].departureAirport == departureAirport &&
        flights[i].arrivalAirport == arrivalAirport) {
      result.push_back(flights[i]);  // add matching flight to result list
    }
  }
  return result;  // return list of matching flights
}

Flight BookingSystem::getFlightInfo(std::string flightNumber) {
  for (int i = 0; i < flights.size(); i++) {
    if (flights[i].flightNumber == flightNumber) {
      return flights[i];  // return matching flight
    }
  }
  return Flight("", "", "", "", "", "", "", 0, 0);  // no matching flight found
}

Passenger BookingSystem::getPassengerInfo(std::string idNumber) {
  for (int i = 0; i < passengers.size(); i++) {
    if (passengers[i].idNumber == idNumber) {
      return passengers[i];  // return matching passenger
    }
  }
  return Passenger("", "", 0, "", "", "");  // no matching passenger found
}

std::string BookingSystem::generateReservationNumber() {
  // generate unique reservation number
  return "R" + std::to_string(reservations.size() + 1);
}

std::string BookingSystem::generateTicketNumber() {
  // generate unique ticket number
  return "T" + std::to_string(tickets.size() + 1);
}

std::string BookingSystem::generateSeatNumber(std::string flightNumber) {
  // generate seat number for given flight
  int seatCount = 0;
  for (int i = 0; i < tickets.size(); i++) {
    if (tickets[i].flightNumber == flightNumber) {
      seatCount++;
    }
  }
  return "S" + std::to_string(seatCount + 1);
}

std::string BookingSystem::getGate(std::string flightNumber) {
  // get gate for given flight
  for (int i = 0; i < flights.size(); i++) {
    if (flights[i].flightNumber == flightNumber) {
      return "G" + std::to_string(i + 1);
    }
  }
  return "";
}

std::string BookingSystem::getCurrentTime() {
  // get current time in YYYY-MM-DD HH:MM:SS format
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d:%X", &tstruct);
  return buf;
}

std::string BookingSystem::getBoardingTime(std::string flightNumber) {
  for (int i = 0; i < flights.size(); i++) {
    if (flights[i].flightNumber == flightNumber) {
      return flights[i].departureTime + " - 30 minutes";
    }
  }
  return "";
}
