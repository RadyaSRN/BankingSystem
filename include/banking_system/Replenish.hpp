#pragma once

#include "banking_system/Account.hpp"
#include "banking_system/Command.hpp"

namespace banking_system {
class Replenish : public Command {
 public:
  Replenish(const long long& sum, Account* account);

  void execute() final;
  void undo() final;
};
} 