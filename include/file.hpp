#include <vector>
#include "bookingsystem.hpp"
#ifndef __FILE_HPP
#define __FILE_HPP
class File
{
public:
    static bool LoadSystem(BookingSystem &r);
    static bool FlushSystem(BookingSystem &r);
    static void Init();
    static bool LoadFlight(BookingSystem &r, std::string sFlight);
    static bool LoadPassenger(BookingSystem &r, std::string sPassenger);
    static bool LoadReservation(BookingSystem &r, std::string sReservation);
    static bool LoadTicket(BookingSystem &r, std::string sTicket);
    static bool LoadPayment(BookingSystem &r, std::string sPayment);
    static bool FlushFlight(BookingSystem &r, std::string sFlight);
    static bool FlushPassenger(BookingSystem &r, std::string sPassenger);
    static bool FlushReservation(BookingSystem &r, std::string sReservation);
    static bool FlushTicket(BookingSystem &r, std::string sTicket);
    static bool FlushPayment(BookingSystem &r, std::string sPayent);
};
#endif //LIBRARYSYSTEM_FILE_H
