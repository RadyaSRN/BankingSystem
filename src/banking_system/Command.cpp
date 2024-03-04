#include "banking_system/Command.hpp"
#include "banking_system/Account.hpp"

namespace banking_system {
Command::Command(const long long& sum, Account* first_account)
    : is_executed(false),
      sum(sum),
      first_balance_change(0),
      first_account(first_account) {}

void Command::checkExecutionStatus(bool which_one) {
  if (which_one == true && is_executed) {
    throw std::string("Can't execute the already executed command!");
  }
  if (which_one == false && !is_executed) {
    throw std::string("Can't undo the command that hasn't been executed!");
  }
}
} 