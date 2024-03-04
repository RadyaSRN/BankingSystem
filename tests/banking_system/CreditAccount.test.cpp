#include <gtest/gtest.h>
#include "banking_system/Bank.hpp"
#include "banking_system/Client.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/CommandLineInterface.hpp"
#include "banking_system/CreditAccount.hpp"


TEST(SystemTest, Credit_Account_test) {
  std::string name = "Rayan";
  std::string surname = "Gosling";
  banking_system::Client::Builder builder(name, surname);
  banking_system::Client* client = new banking_system::Client(builder);

  banking_system::Bank* bank = new banking_system::Bank("Sber", 95, 95, 130, 10);

  std::string id_1 = "Sber_0";
  banking_system::CreditAccount* cred = new banking_system::CreditAccount(id_1, banking_system::AccountType::Credit,
                                                                          bank->withdraw_limit, bank->transfer_limit, client,
                                                                          bank->credit_limit, bank->overdraft_fee);

  EXPECT_EQ(cred->balance, 0);

  EXPECT_THROW(cred->withdraw(96), std::string);
  EXPECT_THROW(cred->withdrawForTransfer(96), std::string);

  std::string new_address = "53 63 one tabo apartment 6";
  std::string new_passport = "3425 645";
  client->address.SetAdress(new_address);
  client->passport_data.SetPassport(new_passport);
  client->TryToRemoveSuspicion();

  EXPECT_THROW(cred->withdraw(200), std::string);
  EXPECT_THROW(cred->withdrawForTransfer(200), std::string);

  cred->withdraw(10);
  EXPECT_EQ(cred->balance, -10);

  cred->withdraw(10);
  EXPECT_EQ(cred->balance, -30);

  cred->withdrawForTransfer(10);
  EXPECT_EQ(cred->balance, -50);

  cred->undo(10);
  EXPECT_EQ(cred->balance, -40);

  delete client;
  delete bank;
  delete cred;
}
