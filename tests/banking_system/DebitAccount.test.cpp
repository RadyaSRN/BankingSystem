#include <gtest/gtest.h>
#include "banking_system/Bank.hpp"
#include "banking_system/Client.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/CommandLineInterface.hpp"
#include "banking_system/DebitAccount.hpp"


TEST(SystemTest, Debit_Account_test) {
  std::string name = "Rayan";
  std::string surname = "Gosling";
  banking_system::Client::Builder builder(name, surname);
  banking_system::Client* client = new banking_system::Client(builder);

  banking_system::Bank* bank = new banking_system::Bank("Sber", 95, 95, 3000, 100);

  std::string id_1 = "Sber_0";
  banking_system::DebitAccount* deb = new banking_system::DebitAccount(id_1, banking_system::AccountType::Debit, bank->withdraw_limit, bank->transfer_limit, client);

  EXPECT_EQ(deb->balance, 0);

  deb->replenish(100);
  EXPECT_EQ(deb->balance, 100);

  EXPECT_THROW(deb->withdraw(96), std::string);
  EXPECT_THROW(deb->withdrawForTransfer(96), std::string);

  std::string new_address = "53 63 one tabo apartment 6";
  std::string new_passport = "3425 645";
  client->address.SetAdress(new_address);
  client->passport_data.SetPassport(new_passport);
  client->TryToRemoveSuspicion();

  deb->withdraw(50);
  EXPECT_EQ(deb->balance, 50);

  EXPECT_THROW(deb->withdraw(200), std::string);
  EXPECT_THROW(deb->withdrawForTransfer(200), std::string);

  deb->undo(50);
  EXPECT_EQ(deb->balance, 100);

  deb->withdrawForTransfer(20);
  EXPECT_EQ(deb->balance, 80);

  delete client;
  delete bank;
  delete deb;
}
