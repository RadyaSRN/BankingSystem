#pragma once

#include <string>
#include <vector>

namespace banking_system {
class Name {
 public:
  std::string name;

  Name() = default;
  Name(const std::string& name);
  void SetName(std::string& new_name);
  std::string GetName();
};

class Surname {
 public:
  std::string surname;

  Surname() = default;
  Surname(const std::string& surname);
  void SetSurame(std::string& new_surname);
  std::string GetSurame();
};

class Adress {
 public:
  std::string adress = "None";

  Adress() = default;
  Adress(const std::string& adress);
  void SetAdress(std::string& new_adress);
  std::string GetAdress();
};

class Passport {
 public:
  std::string passport_data = "None";

  Passport() = default;
  Passport(const std::string& passport_data);
  void SetPassport(std::string& new_passport_data);
  std::string GetPassport_Data();
};

class Account;

class Client {
 public:
  Name name;
  Surname surname;
  Adress address;
  Passport passport_data;
  bool is_suspicious = true;
  std::vector<Account*> accounts;

  class Builder {
   public:
    std::string name;
    std::string surname;
    std::string adress = "None";
    std::string passport_data = "None";
    bool is_suspicious = true;

    Builder(const std::string& name, const std::string& surname);
  };

  Client(Builder& builder);

  void TryToRemoveSuspicion();
};
}