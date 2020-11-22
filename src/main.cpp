#include "calc.h"
#include "Expression.h"

int main() {
//    string expression = " -1 + 5 - 3";
//    string expression = "-10  + (8 *  2.5) -  (3 / 1.5)";
//    string expression = "-10  + (8 *  2.5) -  (3 / 1,5)";
//    string expression = "1 + (2 * (2.5 + 2.5 + (3- 2))) -  (3 / 1.5)";
//    string expression = "1.1 + + 2.1 + bc";
//    string expression = "";

//    string test = "4 12 3 + * 2 / 5 5 + * 100.5 2 * - 2 /";
//    cout << "TST: " << test << endl;

//    string expression = "(-4 * (12.3698 + 3) / 2 * (5 + 5) - (100.54 * 2))/2";
    string expression = "(4 * (12 + 3) / 2 * (5 + 5) - (100 * 2))/2";
//    string expression = "(4 * (12 + 3) / 0 * (5 + 5) - (100 * 2))/2";

//    getline(cin, expression);
//    cout << calc(expression) << endl;
    calc(expression);

    Expression expr;
    float result = expr.calc(expression);
    cout << "ExprRes: " << result << endl;

    return 0;
}
