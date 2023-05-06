#include "passenger.hpp"

#include <iostream>
#include <string>
Passenger::Passenger(std::string name, std::string gender, int age,
                     std::string idType, std::string idNumber,
                     std::string contact) {
  this->name = name;
  this->gender = gender;
  this->age = age;
  this->idType = idType;
  this->idNumber = idNumber;
  this->contact = contact;
  this->password = "666666";
}

Passenger::Passenger(std::string name, std::string gender, int age,
                     std::string idType, std::string idNumber,
                     std::string contact, std::string password) {
  this->name = name;
  this->gender = gender;
  this->age = age;
  this->idType = idType;
  this->idNumber = idNumber;
  this->contact = contact;
  this->password = password;
}

void Passenger::displayPassengerInfo() {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Gender: " << gender << std::endl;
  std::cout << "Age: " << age << std::endl;
  std::cout << "ID Type: " << idType << std::endl;
  std::cout << "ID Number: " << idNumber << std::endl;
  std::cout << "Contact: " << contact << std::endl;
}

void Passenger::updateName(std::string newName) {
  name = newName;  // update passenger name
}

void Passenger::updateContact(std::string newContact) {
  contact = newContact;  // update passenger contact
}

void Passenger::updateID(std::string newIDType, std::string newIDNumber) {
  idType = newIDType;      // update passenger ID type
  idNumber = newIDNumber;  // update passenger ID number
}
