#pragma once

#include "banking_system/Account.hpp"
#include "banking_system/Command.hpp"

namespace banking_system {
class Withdraw : public Command {
 public:
  Withdraw(const long long& sum, Account* account);
  void execute() final;
  void undo() final;
};
} 