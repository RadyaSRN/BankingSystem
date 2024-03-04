#include <gtest/gtest.h>
#include "banking_system/Command.hpp"
#include "banking_system/Withdraw.hpp"
#include "banking_system/Replenish.hpp"
#include "banking_system/Account.hpp"
#include "banking_system/DebitAccount.hpp"

TEST(WithdrawTest, WithdrawChecksExecutionStatus) {
  banking_system::Client::Builder builder("Ivan", "Ivanov");
  banking_system::Client* client = new banking_system::Client(builder);
  banking_system::Account* debit_account = new banking_system::DebitAccount("id", banking_system::AccountType::Debit, 500, 500, client);
  banking_system::Command* withdraw = new banking_system::Withdraw(200, debit_account);
  withdraw->execute();
  EXPECT_EQ(debit_account->balance, 0);
  delete withdraw;
  delete debit_account;
  delete client;
}

TEST(WithdrawTest, WithdrawWorks) {
  banking_system::Client::Builder builder("Ivan", "Ivanov");
  banking_system::Client* client = new banking_system::Client(builder);
  banking_system::Account* debit_account = new banking_system::DebitAccount("id", banking_system::AccountType::Debit, 500, 500, client);
  banking_system::Command* replenish = new banking_system::Replenish(300, debit_account);
  banking_system::Command* withdraw = new banking_system::Withdraw(100, debit_account);
  replenish->execute();
  withdraw->execute();
  EXPECT_EQ(debit_account->balance, 200);
  delete withdraw;
  delete replenish;
  delete debit_account;
  delete client;
}

TEST(WithdrawTest, WithdrawUndoWorks) {
  banking_system::Client::Builder builder("Ivan", "Ivanov");
  banking_system::Client* client = new banking_system::Client(builder);
  banking_system::Account* debit_account = new banking_system::DebitAccount("id", banking_system::AccountType::Debit, 500, 500, client);
  banking_system::Command* replenish = new banking_system::Replenish(300, debit_account);
  banking_system::Command* withdraw = new banking_system::Withdraw(100, debit_account);
  replenish->execute();
  withdraw->execute();
  withdraw->undo();
  EXPECT_EQ(debit_account->balance, 300);
  delete withdraw;
  delete replenish;
  delete debit_account;
  delete client;
}