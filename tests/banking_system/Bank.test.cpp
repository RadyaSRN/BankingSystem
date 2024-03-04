#include <gtest/gtest.h>
#include "banking_system/Bank.hpp"
#include "banking_system/Client.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/CommandLineInterface.hpp"


TEST(SystemTest, Bank_test) {
  banking_system::Bank* bank = new banking_system::Bank("Sber", 1000, 2000, 3000, 100);
  EXPECT_EQ(bank->name, "Sber");
  EXPECT_EQ(bank->withdraw_limit, 1000);
  EXPECT_EQ(bank->transfer_limit, 2000);
  EXPECT_EQ(bank->credit_limit, 3000);
  EXPECT_EQ(bank->overdraft_fee, 100);
  EXPECT_EQ(bank->GetName(), "Sber");

  delete bank;
}

