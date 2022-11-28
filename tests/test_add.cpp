#include "demolib.h"
#include "gtest/gtest.h"

TEST(AddTest, Add)
{
    EXPECT_EQ(3, Demolib::add(1, 2));
}