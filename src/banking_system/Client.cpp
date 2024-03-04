#include <vector>
#include <string>
#include "banking_system/Client.hpp"
#include "banking_system/message_handling/MessageHandler.hpp"

namespace banking_system {
Name::Name(const std::string& name) : name(name) {}

void Name::SetName(std::string& new_name) {
  name = new_name;
}

std::string Name::GetName() {
  return name;
}

Surname::Surname(const std::string& surname) : surname(surname) {}

void Surname::SetSurame(std::string& new_surname) {
  surname = new_surname;
}

std::string Surname::GetSurame() {
  return surname;
}

Adress::Adress(const std::string& adress) : adress(adress) {}

void Adress::SetAdress(std::string& new_adress) {
  adress = new_adress;
}

std::string Adress::GetAdress() {
  return adress;
}

Passport::Passport(const std::string& passport_data) : passport_data(
    passport_data) {}

void Passport::SetPassport(std::string& new_passport_data) {
  passport_data = new_passport_data;
}

std::string Passport::GetPassport_Data() {
  return passport_data;
}

Client::Builder::Builder(const std::string& name, const std::string& surname)
    : name(name), surname(surname) {}

Client::Client(Builder& builder)
    : name(Name(builder.name)), surname(Surname(builder.surname)) {}

void Client::TryToRemoveSuspicion() {
  if (address.GetAdress() != "None"
      && passport_data.GetPassport_Data() != "None"
      && is_suspicious) {
    is_suspicious = false;
    message_handling::handler.add_message("\nYou are no longer suspicious!");
  }
}
}