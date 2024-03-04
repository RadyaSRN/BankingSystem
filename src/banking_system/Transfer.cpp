#include <string>
#include "banking_system/Transfer.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/Account.hpp"
#include "banking_system/message_handling/MessageHandler.hpp"

namespace banking_system {
Transfer::Transfer(const long long& sum,
                   Account* first_account,
                   Account* second_account,
                   const std::string& message)
    : Command(sum, first_account),
      second_balance_change(0),
      second_account(second_account) {
  this->message = message;
}

void Transfer::execute() {
  try {
    checkExecutionStatus(true);
  } catch (std::string& error_message) {
    message_handling::handler.add_message(error_message);
    return;
  }
  try {
    first_balance_change = first_account->withdrawForTransfer(sum);
  } catch (std::string& error_message) {
    message_handling::handler.add_message(
        "The transaction has failed! Problem with the first account:");
    message_handling::handler.add_message(error_message);
    return;
  }
  try {
    second_balance_change = second_account->replenish(sum);
    is_executed = true;
    message_handling::handler.add_message("The transfer was successful!");
    message_handling::handler.add_message("First account current balance: "
                                              + std::to_string(first_account->balance));
    message_handling::handler.add_message("Second account current balance: "
                                              + std::to_string(second_account->balance));
  } catch (std::string& error_message) {
    first_account->undo(first_balance_change);
    message_handling::handler.add_message(
        "The transaction has failed! Problem with the second account:");
    message_handling::handler.add_message(error_message);
  }
}

void Transfer::undo() {
  try {
    checkExecutionStatus(false);
  } catch (std::string& error_message) {
    message_handling::handler.add_message(error_message);
    return;
  }
  first_account->undo(first_balance_change);
  second_account->undo(-second_balance_change);
  is_executed = false;
  message_handling::handler.add_message(
      "The transaction was cancelled successfully!");
  message_handling::handler.add_message("First account current balance: "
                                            + std::to_string(first_account->balance));
  message_handling::handler.add_message("Second account current balance: "
                                            + std::to_string(second_account->balance));
  if (message != "") {
    message_handling::handler.add_message("The message was: " + message);
  }
}
} 