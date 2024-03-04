#include <gtest/gtest.h>
#include "banking_system/Command.hpp"
#include "banking_system/Transfer.hpp"
#include "banking_system/Replenish.hpp"
#include "banking_system/Account.hpp"
#include "banking_system/DebitAccount.hpp"

TEST(TransferTest, TransferWorks) {
  banking_system::Client::Builder first_builder("Ivan", "Ivanov");
  banking_system::Client::Builder second_builder("Pyotr", "Petrov");
  banking_system::Client* first_client = new banking_system::Client(first_builder);
  banking_system::Client* second_client = new banking_system::Client(second_builder);
  banking_system::Account* first_debit_account = new banking_system::DebitAccount("id1", banking_system::AccountType::Debit, 500, 500, first_client);
  banking_system::Account* second_debit_account = new banking_system::DebitAccount("id2", banking_system::AccountType::Debit, 500, 500, second_client);
  banking_system::Command* replenish_first_account = new banking_system::Replenish(500, first_debit_account);
  banking_system::Command* replenish_second_account = new banking_system::Replenish(400, second_debit_account);
  banking_system::Command* transfer = new banking_system::Transfer(200, first_debit_account, second_debit_account, "This is a new transfer");
  replenish_first_account->execute();
  replenish_second_account->execute();
  transfer->execute();
  EXPECT_EQ(first_debit_account->balance, 300);
  EXPECT_EQ(second_debit_account->balance, 600);
  delete transfer;
  delete replenish_second_account;
  delete replenish_first_account;
  delete second_debit_account;
  delete first_debit_account;
  delete second_client;
  delete first_client;
}

TEST(TransferTest, TransferUndoWorks) {
  banking_system::Client::Builder first_builder("Ivan", "Ivanov");
  banking_system::Client::Builder second_builder("Pyotr", "Petrov");
  banking_system::Client* first_client = new banking_system::Client(first_builder);
  banking_system::Client* second_client = new banking_system::Client(second_builder);
  banking_system::Account* first_debit_account = new banking_system::DebitAccount("id1", banking_system::AccountType::Debit, 500, 500, first_client);
  banking_system::Account* second_debit_account = new banking_system::DebitAccount("id2", banking_system::AccountType::Debit, 500, 500, second_client);
  banking_system::Command* replenish_first_account = new banking_system::Replenish(500, first_debit_account);
  banking_system::Command* replenish_second_account = new banking_system::Replenish(400, second_debit_account);
  banking_system::Command* transfer = new banking_system::Transfer(200, first_debit_account, second_debit_account, "This is a new transfer");
  replenish_first_account->execute();
  replenish_second_account->execute();
  transfer->execute();
  transfer->undo();
  EXPECT_EQ(first_debit_account->balance, 500);
  EXPECT_EQ(second_debit_account->balance, 400);
  delete transfer;
  delete replenish_second_account;
  delete replenish_first_account;
  delete second_debit_account;
  delete first_debit_account;
  delete second_client;
  delete first_client;
}