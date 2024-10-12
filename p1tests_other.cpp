#include <gtest/gtest.h>
#include "bset.hpp"

TEST(OtherTests, parseSet) {
    Set set;
    set.addElement("{c}");
    set.addElement("b");
    set.addElement("a");
    EXPECT_TRUE(set == parseSet("{a, b, {c}}"));
    EXPECT_TRUE(set == parseSet("{b, a, {c}}"));
    EXPECT_TRUE(set == parseSet("{a, {c}, b}"));
    EXPECT_TRUE(set == parseSet("{b, {c}, a}"));
    EXPECT_TRUE(set == parseSet("{{c}, a, b}"));
    EXPECT_TRUE(set == parseSet("{{c}, b, a}"));
}

TEST(OtherTests, isSet) {
    EXPECT_FALSE(isSet("a"));
    EXPECT_FALSE(isSet("a, b, c"));
    EXPECT_FALSE(isSet("a, b, c, {d, e}"));
    EXPECT_TRUE(isSet("{a, b, c}"));
    EXPECT_TRUE(isSet("{a, b, c, {d, e}}"));
}