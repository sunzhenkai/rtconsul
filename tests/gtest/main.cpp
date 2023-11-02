#include "iostream"
#include "gtest/gtest.h"

int main() {
    testing::InitGoogleTest();
    assert(RUN_ALL_TESTS() == 0);
}

TEST(Main, Test) {
    ASSERT_TRUE(true);
}