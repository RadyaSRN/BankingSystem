#pragma once

#include "banking_system/Account.hpp"

namespace banking_system {
class Command {
 public:
  bool is_executed;
  long long sum;
  long long first_balance_change;
  Account* first_account;

  Command(const long long& sum, Account* first_account);
  virtual ~Command() = default;
  virtual void execute() = 0;
  virtual void undo() = 0;
  void checkExecutionStatus(bool which_one);
};
} 