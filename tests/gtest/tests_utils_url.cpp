#include "utils/url.h"
#include "gtest/gtest.h"
#include "iostream"

namespace {
    TEST(UrlEncodeTest, Normal) {
        EXPECT_EQ("q%3Dhello%26w%3Dworld", rtcfg::URLEncode("q=hello&w=world"));
    }
}