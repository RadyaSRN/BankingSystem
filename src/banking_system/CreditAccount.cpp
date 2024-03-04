#include <string>
#include "banking_system/Account.hpp"
#include "banking_system/CreditAccount.hpp"
#include "banking_system/Client.hpp"

namespace banking_system {
CreditAccount::CreditAccount(const std::string& id,
                             AccountType account_type,
                             long long withdraw_limit,
                             long long transfer_limit,
                             Client* owner,
                             long long credit_limit,
                             long long overdraft_fee) : Account(id,
                                                                account_type,
                                                                withdraw_limit,
                                                                transfer_limit,
                                                                owner),
                                                        credit_limit(
                                                            credit_limit),
                                                        overdraft_fee(
                                                            overdraft_fee) {}

long long CreditAccount::replenish(const long long& sum) {
  if (balance >= 0) {
    return Account::replenish(sum);
  }
  if (balance + sum - overdraft_fee < -credit_limit) {
    throw std::string("The resulting balance is lower than the credit limit!");
  }
  balance += sum - overdraft_fee;
  return sum - overdraft_fee;
}

long long CreditAccount::withdraw(const long long& sum) {
  if (owner->is_suspicious && sum > withdraw_limit) {
    throw std::string(
        "The withdrawal sum is too large for a user with an unverified profile!");
  }
  return withdrawHelper(sum);
}

long long CreditAccount::withdrawForTransfer(const long long& sum) {
  if (owner->is_suspicious && sum > transfer_limit) {
    throw std::string(
        "The withdrawal for transfer sum is too large for a user with an unverified profile!");
  }
  return withdrawHelper(sum);
}

long long CreditAccount::withdrawHelper(const long long& sum) {
  if ((balance >= 0 && balance - sum < -credit_limit)
      || (balance < 0 && balance - sum - overdraft_fee < -credit_limit)) {
    throw std::string("The resulting balance is lower than the credit limit!");
  }
  if (balance >= 0) {
    balance -= sum;
    return sum;
  }
  balance -= sum + overdraft_fee;
  return sum + overdraft_fee;
}
} 
