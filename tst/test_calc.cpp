#include "string"

#include "Expression.h"
#include "gtest/gtest.h"
#include <gtest/gtest_prod.h>
#include "../googletest/googlemock/include/gmock/gmock-matchers.h"

using ::testing::MatchesRegex;
using ::testing::ContainsRegex;

using namespace std;

const string &regex = "[A-Za-z()]";

//Check expression xontains unsupported symbols
TEST(ExpressionTest, calc) {
    Expression expr;
    string infixExpr = "2+3*(2-1)/2";
    string postfix = expr.convertInfix2Postfix(infixExpr);
//    postfix += "asas";
    cout << postfix << endl;
    ASSERT_THAT(postfix, Not(ContainsRegex(regex)));
}

TEST(ExpressionTest1, calc) {
    Expression expr;
//    string infixExpr = "(4 * (12 + 3) / 2 * (50 + 5) - (250 * 2))/2"; // 575
//    string infixExpr = "(4 * (12 + 3) / 2 * (50 + 5) - (250.3 * 2))/2"; // 574.7
    string infixExpr = "-10  + (8 * 2.5) -  (3 / 1.5)"; // 8
    float result = expr.calc(infixExpr);
//    EXPECT_EQ(result, 575);
//    EXPECT_EQ(result, 574.7);
    EXPECT_EQ(result, 8);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}