#include <string>
#include "banking_system/Account.hpp"
#include "banking_system/Client.hpp"

namespace banking_system {
Account::Account(const std::string& id,
                 AccountType account_type,
                 long long withdraw_limit,
                 long long transfer_limit,
                 Client* owner)
    : id(id),
      account_type(account_type),
      withdraw_limit(withdraw_limit),
      transfer_limit(transfer_limit),
      owner(owner) {}

void Account::undo(const long long& sum) {
  balance += sum;
}

long long Account::replenish(const long long& sum) {
  balance += sum;
  return sum;
}

long long Account::withdraw(const long long& sum) {
  if (sum > balance) {
    throw std::string("Can't withdraw more than the existing balance!");
  }
  if (owner->is_suspicious && sum > withdraw_limit) {
    throw std::string(
        "The withdrawal sum is too large for a user with an unverified profile!");
  }
  balance -= sum;
  return sum;
}

long long Account::withdrawForTransfer(const long long& sum) {
  if (sum > balance) {
    throw std::string(
        "Can't withdraw for transfer more than the existing balance!");
  }
  if (owner->is_suspicious && sum > transfer_limit) {
    throw std::string(
        "The withdrawal for transfer sum is too large for a user with an unverified profile!");
  }
  balance -= sum;
  return sum;
}
}