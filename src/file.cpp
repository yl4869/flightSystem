#include "file.hpp"

#include <sqlite3.h>
#include <unistd.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void File::Init() {
  std::ofstream fout;
  if (access("./flights.db", F_OK) == -1) {
    fout.open("./flights.db");
    fout.close();
  }
  if (access("./passengers.db", F_OK) == -1) {
    fout.open("./passengers.db");
    fout.close();
  }
  if (access("./reservations.db", F_OK) == -1) {
    fout.open("./reservations.db");
    fout.close();
  }
  if (access("./tickets.db", F_OK) == -1) {
    fout.open("./tickets.db");
    fout.close();
  }
  if (access("./payments.db", F_OK) == -1) {
    fout.open("./payments.db");
    fout.close();
  }
}

bool File::LoadSystem(BookingSystem &r) {
  std::string sFlight = "./flights.db";
  std::string sPassenger = "./passengers.db";
  std::string sReservation = "./reservations.db";
  std::string sTicket = "./tickets.db";
  std::string sPayment = "./payments.db";
  File::LoadFlight(r, sFlight);
  File::LoadPassenger(r, sPassenger);
  File::LoadReservation(r, sReservation);
  File::LoadTicket(r, sTicket);
  File::LoadPayment(r, sPayment);
  return true;
}

bool File::LoadFlight(BookingSystem &r, std::string sFlight) {
  sqlite3 *db;
  int rc = sqlite3_open(sFlight.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  std::string sql = "SELECT * FROM flights";
  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    std::string flightNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    std::string departureTime =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    std::string arrivalTime =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    std::string departureAirport =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    std::string arrivalAirport =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    std::string airline =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    std::string aircraftType =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    int totalSeats = sqlite3_column_int(stmt, 7);

    if (sqlite3_column_type(stmt, 8) == SQLITE_NULL) {
      r.addFlight(Flight(flightNumber, departureTime, arrivalTime,
                         departureAirport, arrivalAirport, airline,
                         aircraftType, totalSeats));
    } else {
      int availableSeats = sqlite3_column_int(stmt, 8);
      r.addFlight(Flight(flightNumber, departureTime, arrivalTime,
                         departureAirport, arrivalAirport, airline,
                         aircraftType, totalSeats, availableSeats));
    }
  }

  if (rc != SQLITE_DONE) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return true;
}

bool File::LoadPassenger(BookingSystem &r, std::string sPassenger) {
  sqlite3 *db;
  int rc = sqlite3_open(sPassenger.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  std::string sql = "SELECT * FROM passengers";
  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    std::string name =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    std::string gender =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    int age = sqlite3_column_int(stmt, 2);
    std::string idType =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    std::string idNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    std::string contact =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));

    if (sqlite3_column_type(stmt, 6) == SQLITE_NULL) {
      r.addPassenger(Passenger(name, gender, age, idType, idNumber, contact));
    } else {
      std::string password =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
      r.addPassenger(
          Passenger(name, gender, age, idType, idNumber, contact, password));
    }
  }

  if (rc != SQLITE_DONE) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return true;
}

bool File::LoadReservation(BookingSystem &r, std::string sReservation) {
  sqlite3 *db;
  int rc = sqlite3_open(sReservation.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  std::string sql = "SELECT * FROM reservations";
  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    std::string reservationNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    std::string flightNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    std::string idNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    std::string reservationTime =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    std::string status =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));

    Passenger passenger = r.getPassengerInfo(idNumber);
    r.addReservation(Reservation(reservationNumber, flightNumber, passenger,
                                 reservationTime, status));
  }

  if (rc != SQLITE_DONE) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return true;
}

bool File::LoadTicket(BookingSystem &r, std::string sTicket) {
  sqlite3 *db;
  int rc = sqlite3_open(sTicket.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  std::string sql = "SELECT * FROM tickets";
  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    std::string ticketNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    std::string flightNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    std::string idNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    std::string seatNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    std::string gate =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    std::string boardingTime =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));

    std::cout << idNumber << std::endl;

    Passenger passenger = r.getPassengerInfo(idNumber);

    std::cout << passenger.name << std::endl;
    r.addTicket(Ticket(ticketNumber, flightNumber, passenger, seatNumber, gate,
                       boardingTime));
  }

  if (rc != SQLITE_DONE) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return true;
}

bool File::LoadPayment(BookingSystem &r, std::string sPayment) {
  sqlite3 *db;
  int rc = sqlite3_open(sPayment.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  std::string sql = "SELECT * FROM payments";
  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    std::string paymentMethod =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    double amount = sqlite3_column_double(stmt, 1);
    std::string paymentTime =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    std::string status =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

    if (sqlite3_column_type(stmt, 4) == SQLITE_NULL) {
      r.addPayment(Payment(paymentMethod, amount, paymentTime, status));
    } else {
      double refundAmount = sqlite3_column_double(stmt, 4);
      r.addPayment(
          Payment(paymentMethod, amount, paymentTime, status, refundAmount));
    }
  }

  if (rc != SQLITE_DONE) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return true;
}

bool File::FlushSystem(BookingSystem &r) {
  std::string sFlight = "./flights.db";
  std::string sPassenger = "./passengers.db";
  std::string sReservation = "./reservations.db";
  std::string sTicket = "./tickets.db";
  std::string sPayment = "./payments.db";
  File::FlushFlight(r, sFlight);
  File::FlushPassenger(r, sPassenger);
  File::FlushReservation(r, sReservation);
  File::FlushTicket(r, sTicket);
  File::FlushPayment(r, sPayment);
  return true;
}

bool File::FlushFlight(BookingSystem &r, std::string sFlight) {
  sqlite3 *db;
  char *errMsg = nullptr;
  int rc = sqlite3_open(sFlight.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return 1;
  }
  std::string s = "delete from flight";

  rc = sqlite3_exec(db, s.c_str(), nullptr, nullptr, &errMsg);

  std::string sql =
      "DROP TABLE IF EXISTS flights;"
      "CREATE TABLE flights ("
      "flightNumber TEXT,"
      "departureTime TEXT,"
      "arrivalTime TEXT,"
      "departureAirport TEXT,"
      "arrivalAirport TEXT,"
      "airline TEXT,"
      "aircraftType TEXT,"
      "totalSeats INTEGER,"
      "availableSeats INTEGER,"
      "price INTEGER);";

  rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
  }

  for (auto i = r.flights.begin(); i != r.flights.end(); i++) {
    std::string sql =
        "INSERT INTO flights (flightNumber, departureTime, arrivalTime, "
        "departureAirport, arrivalAirport, airline, aircraftType, totalSeats, "
        "availableSeats, price) "
        "VALUES ('" +
        i->flightNumber + "', '" + i->departureTime + "', '" + i->arrivalTime +
        "', '" + i->departureAirport + "', '" + i->arrivalAirport + "', '" +
        i->airline + "', '" + i->aircraftType + "', " +
        std::to_string(i->totalSeats) + ", " +
        std::to_string(i->availableSeats) + ", " + std::to_string(i->price) +
        ");";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
      return 1;
    }
  }

  std::cout << "Table created successfully" << std::endl;
  sqlite3_close(db);
  return 1;
}

bool File::FlushPassenger(BookingSystem &r, std::string sPassenger) {
  sqlite3 *db;
  int rc = sqlite3_open(sPassenger.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return 1;
  }

  std::string sql =
      "DROP TABLE IF EXISTS passengers;"
      "CREATE TABLE passengers ("
      "name TEXT,"
      "gender TEXT,"
      "age INTEGER,"
      "idType TEXT,"
      "idNumber TEXT,"
      "contact TEXT,"
      "password TEXT);";

  char *errMsg = nullptr;
  rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
  }

  for (auto i = r.passengers.begin(); i != r.passengers.end(); i++) {
    std::string sql =
        "INSERT INTO passengers (name, gender, age, idType, idNumber, contact, "
        "password) "
        "VALUES ('" +
        i->name + "', '" + i->gender + "', " + std::to_string(i->age) + ", '" +
        i->idType + "', '" + i->idNumber + "', '" + i->contact + "', '" +
        i->password + "');";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
      return 1;
    }
  }

  std::cout << "Table created successfully" << std::endl;

  sqlite3_close(db);
  return 0;
  return true;
}

bool File::FlushReservation(BookingSystem &r, std::string sReservation) {
  sqlite3 *db;
  int rc = sqlite3_open(sReservation.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return 1;
  }

  std::string sql =
      "DROP TABLE IF EXISTS reservations;"
      "CREATE TABLE reservations ("
      "reservationNumber TEXT,"
      "flightNumber TEXT,"
      "passengerName TEXT,"
      "reservationTime TEXT,"
      "status TEXT);";

  char *errMsg = nullptr;
  rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
  }

  for (auto i = r.reservations.begin(); i != r.reservations.end(); i++) {
    std::string sql =
        "INSERT INTO reservations (reservationNumber, flightNumber, "
        "passengerName, reservationTime, status) "
        "VALUES ('" +
        i->reservationNumber + "', '" + i->flightNumber + "', '" +
        i->passenger.idNumber + "', '" + i->reservationTime + "', '" + i->status +
        "');";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
      return 1;
    }
  }

  std::cout << "Table created successfully" << std::endl;

  sqlite3_close(db);
  return true;
}

bool File::FlushTicket(BookingSystem &r, std::string sTicket) {
  sqlite3 *db;
  int rc = sqlite3_open(sTicket.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return 1;
  }

  std::string sql =
      "DROP TABLE IF EXISTS tickets;"
      "CREATE TABLE tickets ("
      "ticketNumber TEXT,"
      "flightNumber TEXT,"
      "passengerName TEXT,"
      "seatNumber TEXT,"
      "gate TEXT,"
      "boardingTime TEXT);";

  char *errMsg = nullptr;
  rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
  }

  for (auto i = r.tickets.begin(); i != r.tickets.end(); i++) {
    std::string sql =
        "INSERT INTO tickets (ticketNumber, flightNumber, passengerName, "
        "seatNumber, gate, boardingTime) "
        "VALUES ('" +
        i->ticketNumber + "', '" + i->flightNumber + "', '" +
        i->passenger.idNumber + "', '" + i->seatNumber + "', '" + i->gate + "', '" +
        i->boardingTime + "');";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
      return 1;
    }
  }

  std::cout << "Table created successfully" << std::endl;

  sqlite3_close(db);
  return true;
}

bool File::FlushPayment(BookingSystem &r, std::string sPayment) {
  sqlite3 *db;
  int rc = sqlite3_open(sPayment.c_str(), &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return 1;
  }

  std::string sql =
      "DROP TABLE IF EXISTS payments;"
      "CREATE TABLE payments ("
      "paymentMethod TEXT,"
      "amount REAL,"
      "paymentTime TEXT,"
      "status TEXT,"
      "refundAmount REAL);";

  char *errMsg = nullptr;
  rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
  }

  for (auto i = r.payments.begin(); i != r.payments.end(); i++) {
    std::string sql =
        "INSERT INTO payments (paymentMethod, amount, paymentTime, status, "
        "refundAmount) "
        "VALUES ('" +
        i->paymentMethod + "', " + std::to_string(i->amount) + ", '" +
        i->paymentTime + "', '" + i->status + "', " +
        std::to_string(i->refundAmount) + ");";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
      return 1;
    }
  }

  std::cout << "Table created successfully" << std::endl;

  sqlite3_close(db);
  return true;
}
