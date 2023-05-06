#include <string>
#ifndef __PASSENGER_HPP
#define __PASSENGER_HPP
class Passenger {
 public:
  std::string name;
  std::string gender;
  int age;
  std::string idType;
  std::string idNumber;
  std::string contact;
  std::string password;

  Passenger()=default;
  Passenger(std::string name, std::string gender, int age, std::string idType,
            std::string idNumber, std::string contact);

  Passenger(std::string name, std::string gender, int age, std::string idType,
            std::string idNumber, std::string contact, std::string password);


  void displayPassengerInfo();

  void updateName(std::string newName);

  void updateContact(std::string newContact);

  void updateID(std::string newIDType, std::string newIDNumber);
};
#endif // !PASSENGER_HPP
