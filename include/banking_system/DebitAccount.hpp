#pragma once

#include <string>
#include "banking_system/Account.hpp"
#include "banking_system/Client.hpp"

namespace banking_system {
  class DebitAccount: public Account {
 public:
  DebitAccount(const std::string& id, AccountType account_type, long long withdraw_limit, long long transfer_limit, Client* owner);

  long long replenish(const long long& sum) final;
  long long withdraw(const long long& sum) final;
  long long withdrawForTransfer(const long long& sum) final;
};
} 