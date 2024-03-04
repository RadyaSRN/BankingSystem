#include <gtest/gtest.h>
#include "banking_system/global_parameters/time.hpp"

TEST(TimeTest, TimeIsSetProperly) {
  EXPECT_EQ(banking_system::global_parameters::time, 10000);
}