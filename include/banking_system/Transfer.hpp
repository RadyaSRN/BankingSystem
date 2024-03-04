#pragma once

#include <string>
#include "banking_system/Account.hpp"
#include "banking_system/Command.hpp"

namespace banking_system {
class Transfer : public Command {
 public:
  long long second_balance_change;
  Account* second_account;
  std::string message = "";

  Transfer(const long long& sum,
           Account* first_account,
           Account* second_account,
           const std::string& message = "");
  void execute() final;
  void undo() final;
};
} 