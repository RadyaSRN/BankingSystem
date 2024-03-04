#pragma once

#include <string>
#include <vector>
#include "banking_system/Bank.hpp"
#include "banking_system/Client.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/Replenish.hpp"
#include "banking_system/Withdraw.hpp"
#include "banking_system/Transfer.hpp"

namespace banking_system {
class CommandLineInterface {
 public:
  enum class Session { Owner, User };

  std::vector<Bank*> banks;
  std::vector<Client*> clients;
  std::vector<Command*> commands;
  Session session = Session::Owner;
  Client* current_client = nullptr;

  CommandLineInterface(std::vector<Bank*>& banks,
                       std::vector<Client*>& clients,
                       std::vector<Command*>& commands);

  void printOutput();

  void Print();

  void SetClientMode();
  void SetOwnerMode();

  void CreateClient();
  void AddAdress();
  void AddPassportData();

  void CreateBank();

  void CreateAccount();

  Bank* FindBank(std::string& bank_name);
  Account* FindAccount(Bank* user_bank, std::string& id);

  void SelectOption();
  void WithdrawOption();
  void ReplenishOption();
  void TransferOption();
  void CancelTransaction();
  void ViewCapitalisation();
  void ViewTotalBalance();
};
} 