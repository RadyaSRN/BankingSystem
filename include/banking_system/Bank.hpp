#pragma once

#include <string>
#include <vector>
#include "banking_system/Account.hpp"
#include "banking_system/Client.hpp"

namespace banking_system {
class Bank {
 public:
  std::string name;
  long long withdraw_limit;
  long long transfer_limit;
  long long credit_limit;
  long long overdraft_fee;
  std::vector<Account*> accounts;
  std::vector<Client*> clients;

  Bank(const std::string& name,
       const long long& withdraw_limit,
       const long long& transfer_limit,
       const long long& credit_limit,
       const long long& overdraft_fee);

  std::string GetName();
};
} 