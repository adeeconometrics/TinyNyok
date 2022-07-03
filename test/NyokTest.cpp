#include "gtest/gtest.h"
#include "../include/forward_mode.h"
#include "../include/reverse_mode.h"

#include <cmath>

TEST (NyokTest, ForwardMode) {
    nyok::forward a{1.5f, 0}, b{2.5f, 1}; // wrt a

    auto add = a+b;
    auto sub = a-b;
    auto mul = a*b;
    auto div = a/b;

    EXPECT_FLOAT_EQ(add.dot(), 1.0f) << "Addition rule is incorrect.";
    EXPECT_FLOAT_EQ(sub.dot(), 1.0f) << "Subtraction rule is incorrect.";
    EXPECT_FLOAT_EQ(mul.dot(), b.value()) << "Multiplication rule is incorrect.";
    EXPECT_FLOAT_EQ(div.dot(), 1.0f/a.value()) << "Division rule is incorrect.";

    auto tsin = nyok::sin(a);
    auto tcos = nyok::cos(a);
    auto ttan = nyok::tan(a);
    auto tcot = nyok::cot(a);
    auto tsec = nyok::sec(a);
    auto tcsc = nyok::csc(a);

    EXPECT_FLOAT_EQ(tsin.dot(), std::cos(a.value())) << "sin function is incorrect.";
    EXPECT_FLOAT_EQ(tcos.dot(), -std::sin(a.value())) << "cos function is incorrect.";
    EXPECT_FLOAT_EQ(ttan.dot(), std::pow(1.0f/std::cos(a.value()), 2)) << "tan function is incorrect.";
}

TEST(NyokTest, ReverseMode) {
    EXPECT_TRUE(true);
}
