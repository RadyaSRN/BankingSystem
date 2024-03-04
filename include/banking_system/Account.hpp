#pragma once

#include <string>
#include "banking_system/Client.hpp"

namespace banking_system {
enum class AccountType { Debit, Deposit, Credit };

class Account {
 public:
  std::string id;
  AccountType account_type;
  long long withdraw_limit;
  long long transfer_limit;
  Client* owner;
  long long balance = 0;

  Account(const std::string& id,
          AccountType account_type,
          long long withdraw_limit,
          long long transfer_limit,
          Client* owner);
  virtual ~Account() = default;
  virtual long long replenish(const long long& sum) = 0;
  virtual long long withdraw(const long long& sum) = 0;
  virtual long long withdrawForTransfer(const long long& sum) = 0;
  void undo(const long long& sum);
};
}