#include <string>
#include <vector>
#include <utility>
#include "banking_system/message_handling/MessageHandler.hpp"

namespace banking_system {
namespace message_handling {
void MessageHandler::add_message(const std::string& message) {
  messages.push(message);
}

std::vector<std::string> MessageHandler::get_all_messages() {
  std::vector<std::string> result;
  while (!messages.empty()) {
    result.push_back(std::move(messages.front()));
    messages.pop();
  }
  return result;
}

MessageHandler handler;
}
}
