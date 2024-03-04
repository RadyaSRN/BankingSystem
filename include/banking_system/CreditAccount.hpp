#pragma once

#include <string>
#include "banking_system/Account.hpp"
#include "banking_system/Client.hpp"

namespace banking_system {
class CreditAccount : public Account {
 public:
  long long credit_limit;
  long long overdraft_fee;

  CreditAccount(const std::string& id,
                AccountType account_type,
                long long withdraw_limit,
                long long transfer_limit,
                Client* owner,
                long long credit_limit,
                long long overdraft_fee);

  long long replenish(const long long& sum) final;
  long long withdraw(const long long& sum) final;
  long long withdrawForTransfer(const long long& sum) final;
  long long withdrawHelper(const long long& sum);
};
} 