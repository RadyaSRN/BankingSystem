#include <string>
#include "banking_system/Bank.hpp"

namespace banking_system {
Bank::Bank(const std::string& name,
           const long long& withdraw_limit,
           const long long& transfer_limit,
           const long long& credit_limit,
           const long long& overdraft_fee)
    : name(name),
      withdraw_limit(withdraw_limit),
      transfer_limit(transfer_limit),
      credit_limit(credit_limit),
      overdraft_fee(overdraft_fee) {}

std::string Bank::GetName() {
  return name;
}
} 