#include "Expression.h"

int main() {
    Expression expr;
    string expression;

    while(getline(cin, expression)) {
        if (expression == "q") break;
        float result = expr.calc(expression);
        cout << "Result: " << result << endl;
    }

    return 0;
}
