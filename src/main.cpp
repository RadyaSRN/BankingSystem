#include <string>
#include <vector>
#include "banking_system/Bank.hpp"
#include "banking_system/Client.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/CommandLineInterface.hpp"

int main() {
  std::vector<banking_system::Bank*> banks;
  std::vector<banking_system::Client*> clients;
  std::vector<banking_system::Command*> commands;
  banking_system::CommandLineInterface
      command_line_interface(banks, clients, commands);
  while (true) {
    command_line_interface.Print();
    try {
      command_line_interface.SelectOption();
    } catch (std::string& exit_command) {
      break;
    }
  }
  for (long long i = 0; i < banks.size(); ++i) {
    banking_system::Bank* bank = banks[i];
    for (long long j = 0; j < bank->accounts.size(); ++j) {
      delete bank->accounts[j];
    }
    delete bank;
  }
  for (long long i = 0; i < clients.size(); ++i) {
    delete clients[i];
  }
  for (long long i = 0; i < commands.size(); ++i) {
    delete commands[i];
  }
  return 0;
}