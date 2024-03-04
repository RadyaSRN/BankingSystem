#include <gtest/gtest.h>
#include "banking_system/Bank.hpp"
#include "banking_system/Client.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/CommandLineInterface.hpp"
#include "banking_system/Deposit.hpp"


TEST(SystemTest, Deposit_Account_test) {
  std::string name = "Rayan";
  std::string surname = "Gosling";
  banking_system::Client::Builder builder(name, surname);
  banking_system::Client* client = new banking_system::Client(builder);

  banking_system::Bank* bank = new banking_system::Bank("Sber", 95, 95, 130, 10);

  std::string id_1 = "Sber_0";
  long long term = 20000;
  banking_system::Deposit* dep = new banking_system::Deposit(id_1, banking_system::AccountType::Deposit,
                                                             bank->withdraw_limit, bank->transfer_limit,
                                                             client, term);

  EXPECT_EQ(dep->balance, 0);

  dep->replenish(100);
  EXPECT_EQ(dep->balance, 100);

  EXPECT_THROW(dep->withdraw(10), std::string);
  EXPECT_THROW(dep->withdrawForTransfer(10), std::string);

  dep->term = 5000;
  EXPECT_THROW(dep->withdraw(96), std::string);
  EXPECT_THROW(dep->withdrawForTransfer(96), std::string);

  std::string new_address = "53 63 one tabo apartment 6";
  std::string new_passport = "3425 645";
  client->address.SetAdress(new_address);
  client->passport_data.SetPassport(new_passport);
  client->TryToRemoveSuspicion();

  EXPECT_THROW(dep->withdraw(200), std::string);
  EXPECT_THROW(dep->withdrawForTransfer(200), std::string);

  dep->withdraw(10);
  EXPECT_EQ(dep->balance, 90);

  dep->withdrawForTransfer(10);
  EXPECT_EQ(dep->balance, 80);

  dep->undo(10);
  EXPECT_EQ(dep->balance, 90);

  delete client;
  delete bank;
  delete dep;
}
