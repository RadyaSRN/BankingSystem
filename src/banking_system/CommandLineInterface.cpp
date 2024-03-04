#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "banking_system/Account.hpp"
#include "banking_system/DebitAccount.hpp"
#include "banking_system/Deposit.hpp"
#include "banking_system/CreditAccount.hpp"
#include "banking_system/Bank.hpp"
#include "banking_system/Client.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/Replenish.hpp"
#include "banking_system/Withdraw.hpp"
#include "banking_system/Transfer.hpp"
#include "banking_system/CommandLineInterface.hpp"
#include "banking_system/message_handling/MessageHandler.hpp"

namespace banking_system {
CommandLineInterface::CommandLineInterface(std::vector<Bank*>& banks,
                                           std::vector<Client*>& clients,
                                           std::vector<Command*>& commands)
    : banks(banks), clients(clients), commands(commands) {}

void CommandLineInterface::printOutput() {
  std::vector<std::string>
      current_messages = message_handling::handler.get_all_messages();
  for (auto& message : current_messages) {
    std::cout << message << '\n' << '\n';
  }
}

void CommandLineInterface::Print() {
  std::cout << "Select the desired option" << '\n';
  std::cout << "0. Change mode" << '\n';
  if (session == Session::Owner) {
    std::cout << "1. Create the bank" << '\n';
    std::cout << "2. Create the client" << '\n';
    std::cout << "3. Cancel the transaction" << '\n';
    std::cout << "4. View the bank's capitalisation" << '\n';
  } else {
    std::cout << "1. Add an adress" << '\n';
    std::cout << "2. Add the passport information" << '\n';
    std::cout << "3. Create an account" << '\n';
    std::cout << "4. Withdraw money" << '\n';
    std::cout << "5. Replenish account" << '\n';
    std::cout << "6. Transfer to another account" << '\n';
    std::cout << "7. View your total balance" << '\n';
  }
  std::cout << '\n' << "Press Q to exit" << '\n' << '\n';
}

void CommandLineInterface::CreateBank() {
  std::string name;
  std::string str_withdraw_limit;
  std::string str_transfer_limit;
  std::string str_credit_limit;
  std::string str_overdraft_fee;
  std::cout
      << "Enter bank parametrs: name, withdraw limit, transfer limit, credit limit, overdraft fee"
      << '\n';
  std::cin >> name >> str_withdraw_limit >> str_transfer_limit >> str_credit_limit
           >> str_overdraft_fee;
  long long withdraw_limit;
  long long transfer_limit;
  long long credit_limit;
  long long overdraft_fee;
  try {
    withdraw_limit = std::stoll(str_withdraw_limit);
    transfer_limit = std::stoll(str_transfer_limit);
    credit_limit = std::stoll(str_credit_limit);
    overdraft_fee = std::stoll(str_overdraft_fee);
  } catch (...) {
    std::cout << "\nIncorrect input!\n\n";
    return;
  }
  Bank* new_bank = new Bank(name,
                            withdraw_limit,
                            transfer_limit,
                            credit_limit,
                            overdraft_fee);
  banks.push_back(new_bank);
  std::cout << "Bank has been created" << '\n' << '\n';
}

void CommandLineInterface::SetClientMode() {
  if (clients.empty()) {
    std::cout << "There are no clients in the system!" << '\n' << '\n';
  } else {
    std::cout << "Choose the client" << '\n';
    for (long long i = 1; i <= clients.size(); ++i) {
      std::cout << i << ". " << clients[i - 1]->name.GetName() << ' '
                << clients[i - 1]->surname.GetSurame() << '\n';
    }
    std::string str_client_num;
    std::cin >> str_client_num;
    long long client_num;
    try {
      client_num = std::stoll(str_client_num);
    } catch (...) {
      std::cout << "\nIncorrect input!\n\n";
      return;
    }
    if (client_num < 1 || client_num > clients.size()) {
      std::cout << "There is no such client!" << '\n' << '\n';
    } else {
      session = Session::User;
      current_client = clients[client_num - 1];
      std::cout << "Hello, " << clients[client_num - 1]->name.GetName() << ' '
                << clients[client_num - 1]->surname.GetSurame() << '!' << '\n'
                << '\n';
    }
  }
}

void CommandLineInterface::SetOwnerMode() {
  session = Session::Owner;
  current_client = nullptr;
  std::cout << "Hello, Owner!" << '\n' << '\n';
}

void CommandLineInterface::AddAdress() {
  std::cout << "Enter your adress:" << '\n';
  std::string adress;
  std::cin >> adress;
  current_client->address.SetAdress(adress);
  current_client->TryToRemoveSuspicion();
  printOutput();
}

void CommandLineInterface::CreateClient() {
  std::string name;
  std::string surname;
  std::cout << "Enter the name and the surname:" << '\n';
  std::cin >> name >> surname;
  Client::Builder builder(name, surname);
  Client* new_client = new Client(builder);
  clients.push_back(new_client);
  std::cout << "Client has been created" << '\n' << '\n';
}

void CommandLineInterface::AddPassportData() {
  std::cout << "Enter your passport information:" << '\n';
  std::string passport_data;
  std::cin >> passport_data;
  current_client->passport_data.SetPassport(passport_data);
  current_client->TryToRemoveSuspicion();
  printOutput();
}

void CommandLineInterface::CancelTransaction() {
  std::cout << "Enter the number of the transaction you want to cancel:"
            << '\n';
  std::string str_transaction_num;
  std::cin >> str_transaction_num;
  long long transaction_num;
  try {
    transaction_num = std::stoll(str_transaction_num);
  } catch (...) {
    std::cout << "\nIncorrect input!\n\n";
    return;
  }
  if (transaction_num <= 0 || transaction_num > commands.size()) {
    std::cout << "There is no transaction with this number" << '\n' << '\n';
  } else {
    Command* command = commands[transaction_num - 1];
    command->undo();
    printOutput();
  }
}

void CommandLineInterface::ViewCapitalisation() {
  if (banks.empty()) {
    std::cout << "\nThere are no banks in the system!" << '\n' << '\n';
    return;
  }
  std::cout << "Choose the bank" << '\n';
  for (long long i = 1; i <= banks.size(); ++i) {
    std::cout << i << ". " << banks[i - 1]->GetName() << '\n';
  }
  std::string str_bank_num;
  std::cin >> str_bank_num;
  long long bank_num;
  try {
    bank_num = std::stoll(str_bank_num);
  } catch (...) {
    std::cout << "\nIncorrect input!\n\n";
    return;
  }
  if (bank_num > banks.size()) {
    std::cout << "There is no such bank!" << '\n' << '\n';
    return;
  }
  Bank* bank = banks[bank_num - 1];
  long long capitalisation = 0;
  for (Account* account : bank->accounts) {
    capitalisation += account->balance;
  }
  std::cout << "\nThe capitalisation of the bank " << bank->GetName()
            << " is: " << capitalisation << '\n' << '\n';
}

void CommandLineInterface::CreateAccount() {
  if (banks.empty()) {
    std::cout << "\nSorry, but there are no any banks in the system!" << '\n' << '\n';
    return;
  }
  std::cout << "Choose the bank" << '\n';
  for (long long i = 1; i <= banks.size(); ++i) {
    std::cout << i << ". " << banks[i - 1]->GetName() << '\n';
  }
  std::string str_bank_num;
  std::cin >> str_bank_num;
  long long bank_num;
  try {
    bank_num = std::stoll(str_bank_num);
  } catch (...) {
    std::cout << "\nIncorrect input!\n\n";
    return;
  }
  if (bank_num > banks.size()) {
    std::cout << "There is no such bank!" << '\n' << '\n';
    return;
  }
  Bank* bank = banks[bank_num - 1];
  std::string
      id = bank->GetName() + "_" + std::to_string(bank->accounts.size());
  std::cout << "Select the type of bank account:" << '\n';
  std::cout << "1. Debit account" << '\n';
  std::cout << "2. Deposit" << '\n';
  std::cout << "3. Credit account" << '\n';
  std::string str_type;
  std::cin >> str_type;
  long long type;
  try {
    type = std::stoll(str_type);
  } catch (...) {
    std::cout << "\nIncorrect input!\n\n";
    return;
  }
  Account* new_account = nullptr;
  switch (type) {
    case 1:
      new_account = new DebitAccount(id,
                                     AccountType::Debit,
                                     bank->withdraw_limit,
                                     bank->transfer_limit,
                                     current_client);
      bank->accounts.push_back(new_account);
      current_client->accounts.push_back(new_account);
      std::cout << "Debit account has been created with id: " << id << '\n'
                << '\n';
      break;
    case 2:
      {
      std::string str_term;
      std::cout << "Enter the deposit term:" << '\n';
      std::cin >> str_term;
      long long term;
      try {
        term = std::stoll(str_term);
      } catch (...) {
        std::cout << "\nIncorrect input!\n\n";
        return;
      }
      new_account = new Deposit(id,
                                AccountType::Deposit,
                                bank->withdraw_limit,
                                bank->transfer_limit,
                                current_client,
                                term);
      bank->accounts.push_back(new_account);
      current_client->accounts.push_back(new_account);
      std::cout << "Deposit has been created with id: " << id << '\n' << '\n';
      }
      break;
    case 3:
      new_account = new CreditAccount(id,
                                      AccountType::Credit,
                                      bank->withdraw_limit,
                                      bank->transfer_limit,
                                      current_client,
                                      bank->credit_limit,
                                      bank->overdraft_fee);
      bank->accounts.push_back(new_account);
      current_client->accounts.push_back(new_account);
      std::cout << "Credit account has been created with id: " << id << '\n'
                << '\n';
      break;
    default:
      std::cout << "There is no such type of bank account!" << '\n' << '\n';
  }
  bool is_client_in_bank = false;
  for (long long i = 0; i < bank->clients.size(); ++i) {
    if (bank->clients[i] == current_client) {
      is_client_in_bank = true;
      break;
    }
  }
  if (!is_client_in_bank) {
    bank->clients.push_back(current_client);
  }
}

Bank* CommandLineInterface::FindBank(std::string& bank_name) {
  Bank* user_bank = nullptr;
  for (long long i = 0; i < banks.size(); ++i) {
    if (banks[i]->GetName() == bank_name) {
      user_bank = banks[i];
      break;
    }
  }
  return user_bank;
}

Account* CommandLineInterface::FindAccount(Bank* user_bank, std::string& id) {
  Account* user_account = nullptr;
  for (long long i = 0; i < user_bank->accounts.size(); ++i) {
    if (user_bank->accounts[i]->id == id) {
      user_account = user_bank->accounts[i];
      break;
    }
  }
  return user_account;
}

void CommandLineInterface::WithdrawOption() {
  std::string bank_name, id;
  std::cout << "Enter your bank and account id:" << '\n';
  std::cin >> bank_name >> id;
  Bank* user_bank = FindBank(bank_name);
  if (user_bank == nullptr) {
    std::cout << "There is no such bank!" << '\n' << '\n';
    return;
  }
  Account* user_account = FindAccount(user_bank, id);
  if (user_account == nullptr) {
    std::cout << "There is no such account!" << '\n' << '\n';
    return;
  }
  if (user_account->owner != current_client) {
    std::cout << "This is not your account!" << '\n' << '\n';
    return;
  }
  std::string str_sum;
  std::cout << "Enter the amount you want to withdraw from the account:"
            << '\n';
  std::cin >> str_sum;
  long long sum;
  try {
    sum = std::stoll(str_sum);
  } catch (...) {
    std::cout << "\nIncorrect input!\n\n";
    return;
  }
  Command* command = new Withdraw(sum, user_account);
  commands.push_back(command);
  command->execute();
  printOutput();
}

void CommandLineInterface::ReplenishOption() {
  std::string bank_name, id;
  std::cout << "Enter your bank and account id:" << '\n';
  std::cin >> bank_name >> id;
  Bank* user_bank = FindBank(bank_name);
  if (user_bank == nullptr) {
    std::cout << "There is no such bank!" << '\n' << '\n';
    return;
  }
  Account* user_account = FindAccount(user_bank, id);
  if (user_account == nullptr) {
    std::cout << "There is no such account!" << '\n' << '\n';
    return;
  }
  if (user_account->owner != current_client) {
    std::cout << "This is not your account!" << '\n' << '\n';
    return;
  }
  std::string str_sum;
  std::cout << "Enter the amount for which you want to replenish the account:"
            << '\n';
  std::cin >> str_sum;
  long long sum;
  try {
    sum = std::stoll(str_sum);
  } catch (...) {
    std::cout << "\nIncorrect input!\n\n";
    return;
  }
  Command* command = new Replenish(sum, user_account);
  commands.push_back(command);
  command->execute();
  printOutput();
}

void CommandLineInterface::TransferOption() {
  std::string bank_name1, id1, bank_name2, id2;
  std::cout << "Enter the bank and id of the first account:" << '\n';
  std::cin >> bank_name1 >> id1;
  std::cout << "Enter the bank and id of the second account:" << '\n';
  std::cin >> bank_name2 >> id2;
  Bank* user_bank1 = FindBank(bank_name1);
  if (user_bank1 == nullptr) {
    std::cout << "There is no such first bank!" << '\n' << '\n';
    return;
  }
  Bank* user_bank2 = FindBank(bank_name2);
  if (user_bank2 == nullptr) {
    std::cout << "There is no such second bank!" << '\n' << '\n';
    return;
  }
  Account* user_account1 = FindAccount(user_bank1, id1);
  if (user_account1 == nullptr) {
    std::cout << "There is no such first account!" << '\n' << '\n';
    return;
  }
  if (user_account1->owner != current_client) {
    std::cout << "This is not your account!" << '\n' << '\n';
    return;
  }
  Account* user_account2 = FindAccount(user_bank2, id2);
  if (user_account2 == nullptr) {
    std::cout << "There is no such second account!" << '\n' << '\n';
    return;
  }
  std::string str_sum;
  std::cout << "Enter the amount you want to transfer to another account:"
            << '\n';
  std::cin >> str_sum;
  long long sum;
  try {
    sum = std::stoll(str_sum);
  } catch (...) {
    std::cout << "\nIncorrect input!\n\n";
    return;
  }
  std::cout << "\nWould you like to attach a message to your transfer?\n";
  std::cout << "1. YES\n";
  std::cout << "2. NO\n";
  std::string usr_input;
  std::cin >> usr_input;
  Command* command;
  if (usr_input == "1") {
    std::cout << "\nPlease, enter your message:\n";
    std::string message;
    do {
      std::getline(std::cin, message);
    } while (message.length() == 0);
    command = new Transfer(sum, user_account1, user_account2, message);
  } else if (usr_input == "2") {
    command = new Transfer(sum, user_account1, user_account2);
  } else {
    std::cout << "\nIncorrect input!\n\n";
    return;
  }
  commands.push_back(command);
  command->execute();
  printOutput();
}

void CommandLineInterface::ViewTotalBalance() {
  long long total_balance = 0;
  for (Account* account : current_client->accounts) {
    total_balance += account->balance;
  }
  std::cout << "Your total balance is: " << total_balance << '\n' << '\n';
}

void CommandLineInterface::SelectOption() {
  std::string str;
  std::cin >> str;
  if (str == "Q") {
    throw std::string("Exit");
  }
  if (str.length() > 1 || str[0] >= '8' || str[0] < '0') {
    std::cout << "You don't have such option!" << '\n' << '\n';
    return;
  }
  long long number = str[0] - '0';
  switch (number) {
    case 0:
      if (session == Session::Owner) {
        SetClientMode();
      } else {
        SetOwnerMode();
      }
      break;
    case 1:
      if (session == Session::Owner) {
        CreateBank();
      } else {
        AddAdress();
      }
      break;
    case 2:
      if (session == Session::Owner) {
        CreateClient();
      } else {
        AddPassportData();
      }
      break;
    case 3:
      if (session == Session::Owner) {
        CancelTransaction();
      } else {
        CreateAccount();
      }
      break;
    case 4:
      if (session == Session::Owner) {
        ViewCapitalisation();
      } else {
        WithdrawOption();
      }
      break;
    case 5:
      if (session == Session::Owner) {
        std::cout << "You don't have such option!" << '\n' << '\n';
      } else {
        ReplenishOption();
      }
      break;
    case 6:
      if (session == Session::Owner) {
        std::cout << "You don't have such option!" << '\n' << '\n';
      } else {
        TransferOption();
      }
      break;
    case 7:
      if (session == Session::Owner) {
        std::cout << "You don't have such option!" << '\n' << '\n';
      } else {
        ViewTotalBalance();
      }
      break;
    default:
      std::cout << "You don't have such option!" << '\n' << '\n';
  }
}
} 