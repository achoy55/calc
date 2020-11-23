#include "string"

#include "Expression.h"
#include "gtest/gtest.h"
#include <gtest/gtest_prod.h>
#include "../googletest/googlemock/include/gmock/gmock-matchers.h"

using ::testing::MatchesRegex;

using namespace std;

TEST(ExpressionTest, calc) {
    Expression expr;
    string infixExpr = "";
//    string postfix = expr.convertInfix2Postfix(infixExpr);
    string postfix = "5646";

    ASSERT_THAT(postfix, MatchesRegex("\\(\\)"));

//    EXPECT_EQ(postfix, expected);
}

//TEST(eval, DivideByZero) {
//    string rpm = "";
//    eval(rpn);
//    EXPECT_EQ("", "");
//}

//TEST(eval, RPN) {
//    string rpm = "";
//    eval(rpm);
//    EXPECT_EQ("", "");
//}

//TEST(calc, DivideByZero) {
//    EXPECT_EQ(0, i);
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}