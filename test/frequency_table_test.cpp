#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

#include "frequency_table.h"


TEST(FrequencyTableTest, FrequencyTable){
  std::vector<uint32_t> base_frequency(256, 0);
  FrequencyTable table(base_frequency);
  table.Increment(12);
  table.Increment(13);
  table.Increment(12);

  EXPECT_EQ(table.Get(12), 2);
  EXPECT_EQ(table.Get(13), 1);
  EXPECT_EQ(table.Get(1), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}