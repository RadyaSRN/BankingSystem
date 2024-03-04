#include <gtest/gtest.h>
#include "banking_system/message_handling/MessageHandler.hpp"

TEST(MessageHandlerTest, MessageHandlerWorks) {
  banking_system::message_handling::handler.add_message("First message");
  banking_system::message_handling::handler.add_message("Second message");
  std::vector<std::string> all_messages = banking_system::message_handling::handler.get_all_messages();
  EXPECT_EQ("First message", all_messages[0]);
  EXPECT_EQ("Second message", all_messages[1]);
}

TEST(MessageHandlerTest, MessageHandlerWorksWithEmptyState) {
  banking_system::message_handling::handler.add_message("First message");
  std::vector<std::string> all_messages_first = banking_system::message_handling::handler.get_all_messages();
  EXPECT_EQ("First message", all_messages_first[0]);
  std::vector<std::string> all_messages_second = banking_system::message_handling::handler.get_all_messages();
  EXPECT_EQ(true, all_messages_second.empty());
}