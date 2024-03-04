#pragma once

#include <queue>
#include <string>
#include <vector>

namespace banking_system {
namespace message_handling {
class MessageHandler {
 public:
  void add_message(const std::string& message);
  std::vector<std::string> get_all_messages();

 private:
  std::queue<std::string> messages;
};

extern MessageHandler handler;
}
}
