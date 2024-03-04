#include <string>
#include "banking_system/global_parameters/time.hpp"
#include "banking_system/Account.hpp"
#include "banking_system/Deposit.hpp"
#include "banking_system/Client.hpp"

namespace banking_system {
Deposit::Deposit(const std::string& id,
                 AccountType account_type,
                 long long withdraw_limit,
                 long long transfer_limit,
                 Client* owner,
                 long long term) : Account(id,
                                           account_type,
                                           withdraw_limit,
                                           transfer_limit,
                                           owner), term(term) {}

long long Deposit::replenish(const long long& sum) {
  return Account::replenish(sum);
}

long long Deposit::withdraw(const long long& sum) {
  checkTermStatus();
  return Account::withdraw(sum);
}

long long Deposit::withdrawForTransfer(const long long& sum) {
  checkTermStatus();
  return Account::withdrawForTransfer(sum);
}

void Deposit::checkTermStatus() {
  if (global_parameters::time <= term) {
    throw std::string("The term for this deposit account hasn't passed yet!");
  }
}
} 