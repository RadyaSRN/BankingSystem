#include <string>
#include "banking_system/Account.hpp"
#include "banking_system/DebitAccount.hpp"
#include "banking_system/Client.hpp"

namespace banking_system {
DebitAccount::DebitAccount(const std::string& id,
                           AccountType account_type,
                           long long withdraw_limit,
                           long long transfer_limit,
                           Client* owner) : Account(id,
                                                    account_type,
                                                    withdraw_limit,
                                                    transfer_limit,
                                                    owner) {}

long long DebitAccount::replenish(const long long& sum) {
  return Account::replenish(sum);
}

long long DebitAccount::withdraw(const long long& sum) {
  return Account::withdraw(sum);
}

long long DebitAccount::withdrawForTransfer(const long long& sum) {
  return Account::withdrawForTransfer(sum);
}
} 