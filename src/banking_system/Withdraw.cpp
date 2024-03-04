#include <string>
#include "banking_system/Withdraw.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/Account.hpp"
#include "banking_system/message_handling/MessageHandler.hpp"

namespace banking_system {
Withdraw::Withdraw(const long long& sum, Account* account) : Command(sum,
                                                                     account) {}

void Withdraw::execute() {
  try {
    checkExecutionStatus(true);
  } catch (std::string& error_message) {
    message_handling::handler.add_message(error_message);
    return;
  }
  try {
    first_balance_change = first_account->withdraw(sum);
    is_executed = true;
    message_handling::handler.add_message(
        "The withdrawal was successful! Current balance: "
            + std::to_string(first_account->balance));
  } catch (std::string& error_message) {
    message_handling::handler.add_message("The transaction has failed!");
    message_handling::handler.add_message(error_message);
  }
}

void Withdraw::undo() {
  try {
    checkExecutionStatus(false);
  } catch (std::string& error_message) {
    message_handling::handler.add_message(error_message);
    return;
  }
  first_account->undo(first_balance_change);
  is_executed = false;
  message_handling::handler.add_message(
      "The transaction was cancelled successfully! Current balance: "
          + std::to_string(first_account->balance));
}
} 