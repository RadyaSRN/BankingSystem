#include <gtest/gtest.h>
#include "banking_system/Bank.hpp"
#include "banking_system/Client.hpp"
#include "banking_system/Command.hpp"
#include "banking_system/CommandLineInterface.hpp"


TEST(SystemTest, Client_test) {
  std::string name = "Rayan";
  std::string surname = "Gosling";
  banking_system::Client::Builder builder(name, surname);
  banking_system::Client* client = new banking_system::Client(builder);
  
  EXPECT_EQ(client->name.GetName(), "Rayan");
  EXPECT_EQ(client->surname.GetSurame(), "Gosling");
  EXPECT_EQ(client->address.GetAdress(), "None");
  EXPECT_EQ(client->passport_data.GetPassport_Data(), "None");
  EXPECT_EQ(client->is_suspicious, true);

  std::string new_address = "53 63 one tabo apartment 6";
  std::string new_passport = "3425 645";
  client->address.SetAdress(new_address);
  client->passport_data.SetPassport(new_passport);
  client->TryToRemoveSuspicion();
  EXPECT_EQ(client->address.GetAdress(), new_address);
  EXPECT_EQ(client->passport_data.GetPassport_Data(), new_passport);
  EXPECT_EQ(client->is_suspicious, false);

  delete client;
}

