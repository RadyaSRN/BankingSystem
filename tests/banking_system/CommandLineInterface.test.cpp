#include <gtest/gtest.h>
#include "banking_system/Bank.hpp"
#include "banking_system/Client.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/CommandLineInterface.hpp"
#include "banking_system/DebitAccount.hpp"

TEST(SystemTest, Interface_test) {
  std::vector<banking_system::Bank*> banks;
  std::vector<banking_system::Client*> clients;
  std::vector<banking_system::Command*> commands;
  banking_system::CommandLineInterface
      command_line_interface(banks, clients, commands);
  EXPECT_EQ(command_line_interface.session, banking_system::CommandLineInterface::Session::Owner);
  command_line_interface.session = banking_system::CommandLineInterface::Session::User;
  command_line_interface.SetOwnerMode();
  EXPECT_EQ(command_line_interface.session, banking_system::CommandLineInterface::Session::Owner);

  std::string name = "Rayan";
  std::string surname = "Gosling";
  banking_system::Client::Builder builder(name, surname);
  banking_system::Client* client = new banking_system::Client(builder);
  banking_system::Bank* bank = new banking_system::Bank("Sber", 95, 95, 3000, 100);
  std::string id_1 = "Sber_0";
  banking_system::DebitAccount* deb = new banking_system::DebitAccount(id_1, banking_system::AccountType::Debit, bank->withdraw_limit, bank->transfer_limit, client);
  command_line_interface.banks.push_back(bank);
  command_line_interface.clients.push_back(client);
  bank->clients.push_back(client);
  client->accounts.push_back(deb);
  bank->accounts.push_back(deb);

  std::string bank_name = bank->GetName();
  EXPECT_EQ(command_line_interface.FindBank(bank_name), bank);

  std::string acc_id = id_1;
  EXPECT_EQ(command_line_interface.FindAccount(bank, acc_id), deb);

  std::string not_exist_bank = "pep";
  EXPECT_EQ(command_line_interface.FindBank(not_exist_bank), nullptr);

  std::string not_exist_acc = "pep";
  EXPECT_EQ(command_line_interface.FindAccount(bank ,not_exist_acc), nullptr);

  delete client;
  delete bank;
  delete deb;
}
