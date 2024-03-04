#include <gtest/gtest.h>
#include "banking_system/Command.hpp"
#include "banking_system/Withdraw.hpp"
#include "banking_system/Replenish.hpp"
#include "banking_system/Account.hpp"
#include "banking_system/DebitAccount.hpp"

TEST(ReplenishTest, ReplenishChecksExecutionStatus) {
  banking_system::Client::Builder builder("Ivan", "Ivanov");
  banking_system::Client* client = new banking_system::Client(builder);
  banking_system::Account* debit_account = new banking_system::DebitAccount("id", banking_system::AccountType::Debit, 500, 500, client);
  banking_system::Command* replenish = new banking_system::Replenish(200, debit_account);
  replenish->execute();
  replenish->execute();
  EXPECT_EQ(debit_account->balance, 200);
  delete replenish;
  delete debit_account;
  delete client;
}

TEST(ReplenishTest, ReplenishWorks) {
  banking_system::Client::Builder builder("Ivan", "Ivanov");
  banking_system::Client* client = new banking_system::Client(builder);
  banking_system::Account* debit_account = new banking_system::DebitAccount("id", banking_system::AccountType::Debit, 500, 500, client);
  banking_system::Command* replenish1 = new banking_system::Replenish(200, debit_account);
  banking_system::Command* withdraw = new banking_system::Withdraw(100, debit_account);
  banking_system::Command* replenish2 = new banking_system::Replenish(400, debit_account);
  replenish1->execute();
  withdraw->execute();
  replenish2->execute();
  EXPECT_EQ(debit_account->balance, 500);
  delete replenish2;
  delete withdraw;
  delete replenish1;
  delete debit_account;
  delete client;
}

TEST(ReplenishTest, ReplenishUndoWorks) {
  banking_system::Client::Builder builder("Ivan", "Ivanov");
  banking_system::Client* client = new banking_system::Client(builder);
  banking_system::Account* debit_account = new banking_system::DebitAccount("id", banking_system::AccountType::Debit, 500, 500, client);
  banking_system::Command* replenish = new banking_system::Replenish(500, debit_account);
  replenish->execute();
  replenish->undo();
  EXPECT_EQ(debit_account->balance, 0);
  delete replenish;
  delete debit_account;
  delete client;
}