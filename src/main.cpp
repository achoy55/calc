#include "Expression.h"

int main() {
    Expression expr;
    string expression;

    getline(cin, expression);

    float result = expr.calc(expression);
    cout << "Result: " << result << endl;

    return 0;
}
