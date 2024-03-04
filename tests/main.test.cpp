#include <gtest/gtest.h>
#include "banking_system/global_parameters/time.test.cpp"
#include "banking_system/message_handling/MessageHandler.test.cpp"
#include "banking_system/Account.test.cpp"
#include "banking_system/Bank.test.cpp"
#include "banking_system/Client.test.cpp"
#include "banking_system/Command.test.cpp"
#include "banking_system/CommandLineInterface.test.cpp"
#include "banking_system/CreditAccount.test.cpp"
#include "banking_system/DebitAccount.test.cpp"
#include "banking_system/Deposit.test.cpp"
#include "banking_system/Replenish.test.cpp"
#include "banking_system/Transfer.test.cpp"
#include "banking_system/Withdraw.test.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}