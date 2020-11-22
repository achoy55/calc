#include <iostream>
#include <cmath>
#include <string>
#include <functional>
#include <map>
#include <cctype>
#include <stack>
#include <algorithm>

using namespace std;

#define MAX_STACK 10000000
stack<float> _stack;
string errStr;

void calc(const string &expression);

float roundUp(float value);

float eval(const string &rpn);

void printStack(const stack<float>& stack);

bool isFull();

float pop();

void push(float value);

bool isOperator(char op);

int getPriority(char op);

string convertInfix2Postfix(string expression);

void clear(stack<char> &stack);

int main() {
//    string expression = " -1 + 5 -​ 3";
//    string expression = "-10  + (8 *  2.5) -  (3 / 1.5)";
//    string expression = "-10  + (8 *  2.5) -  (3 / 1,5)";
//    string expression = "1​ + (2​ * (2.5 +​ 2.5​ +​ (3​- 2))) -  (3​ / 1.5)";
//    string expression = "1.1 + + 2.1 + bc";
//    string expression = "";

//    string test = "4 12 3 + * 2 / 5 5 + * 100.5 2 * - 2 /";
//    cout << "TST: " << test << endl;

    string expression = "(-4 * (12.3698 + 3) / 2 * (5 + 5) - (100.54 * 2))/2";
//    string expression = "(4 * (12 + 3) / 2 * (5 + 5) - (100 * 2))/2";

//    getline(cin, expression);
//    cout << calc(expression) << endl;

    calc(expression);

    return 0;
}

void calc(const string &expression) {
    string postfix = convertInfix2Postfix(expression);
    cout << "RPN: " << postfix << endl;

    if (postfix.empty() && !errStr.empty()) {
        cout << errStr << endl;
    }

    float result = eval(postfix);
    cout << "Result: " << result << ", rounded: " << roundUp(result) << endl;
}

string convertInfix2Postfix(string expression) {
    if (expression.empty()) throw invalid_argument("Expression is empty");;

//    replaceComma2Period(expression); // replace comma to period

    errStr = "";
    stack<char> _opStack;
    string outputList;
    int i = 0;
    int bracketCnt = 0;

    while (i < expression.size()) {
        while (isspace(expression[i])) {
            i++;
        }

        if (isdigit(expression[i]) || expression[i] == '.' || expression[i] == ',') {
            //if expression number is big or contains decimal number
            while (isdigit(expression[i]) || expression[i] == '.' || expression[i] == ',') {
                outputList += expression[i];
                i++;
            }
            if (i + 1 >= expression.size() || !isdigit(expression[i + 1])) {
                outputList += ' ';
            }
            continue;
        } else if (isOperator(expression[i])) {
            if (expression[i] == '-' && (expression[i - 1] == '(' || outputList.empty())) {
                outputList.push_back('~');
            } else {
                while (!_opStack.empty() && _opStack.top() != '(' &&
                       getPriority(_opStack.top()) >= getPriority(expression[i])) {
                    outputList.push_back(_opStack.top());
                    _opStack.pop();
                }
                _opStack.push(expression[i]); //swap operators priority
            }
        } else if (expression[i] == '(') {
            _opStack.push(expression[i]);
            ++bracketCnt;
        } else if (expression[i] == ')') {
            while (!_opStack.empty() && _opStack.top() != '(') {
                outputList.push_back(_opStack.top());
                _opStack.pop();
            }
            _opStack.pop();
            --bracketCnt;
        } else {
            if (!isspace(expression[i]) && isalpha(expression[i])) {
                string wrongSymbols;
                while (isalpha(expression[i])) {
                    wrongSymbols += expression[i];
                    ++i;
                }
                errStr = "Invalid input, string contains invalid symbols " + wrongSymbols;

                clear(_opStack);
                outputList.clear();
                break;
            }
        }
        i++;
    }

    if (bracketCnt < 0) {
        errStr = "There is close parenthesis without open";
        outputList.clear();
        clear(_opStack);
    }
    if (bracketCnt) {
        errStr = "There are more open parentheses than closing ones";
        outputList.clear();
        clear(_opStack);
    }

    while (!_opStack.empty()) {
        outputList.push_back(_opStack.top());
        _opStack.pop();
    }

    return outputList;
}

float eval(const string &rpn) {
    map<char, function<float(const float &, const float &)>> operations;
    operations['+'] = [](const float &a, const float &b) constexpr { return a + b; };
    operations['-'] = [](const float &a, const float &b) constexpr { return a - b; };
    operations['*'] = [](const float &a, const float &b) constexpr { return a * b; };
    operations['/'] = [](const float &a, const float &b) constexpr { return a / b; };

    int i = 0;
    string token;

    while (i < rpn.length()) {
        while (isspace(rpn[i])) {
            i++;
        }

        //Check digits and . and ,
        if (isdigit(rpn[i]) || rpn[i] == '.') {
            while (isdigit(rpn[i]) || rpn[i] == '.') {
                token += rpn[i];
                i++;
            }
            push(stof(token)); //Push into stack number.
            token = "";
        }
            //Check operators
        else if (isOperator(rpn[i])) {
            // if operator is minus unary
            if (rpn[i] == '~') {
                ++i; // next operand
                if (isdigit(rpn[i])) {
                    push(-stof(&rpn[i]));
                }
            } else {
                float result = operations[rpn[i]](pop(), pop());
                push(result);
            }
            i++;
        } else {
            cout << "Invalid Expression <" << rpn[i] << ">" << endl;
            break;
        }
    }

    return pop();
}

void printStack(const stack<float>& stack) {
    cout << "[";
    for (std::stack<float> dump = stack; !dump.empty(); dump.pop())
        cout << dump.top() << ',';
    cout << "]" << endl;
}

bool isFull() {
    return _stack.size() >= MAX_STACK - 1;
}

void push(float value) {
    if (isFull()) return;
    _stack.push(value);
}

float pop() {
    float value = _stack.top();
    _stack.pop();
    return value;
}

bool isOperator(char op) {
    switch (op) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '~':
            return true;
        default:
            return false;
    }
}

int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void replaceComma2Period(string &expression) { replace(expression.begin(), expression.end(), ',', '.'); }

void clear(stack<char> &stack) {
    while (!stack.empty())
        stack.pop();
}

float roundUp(float value) {
    return roundf(value * 100) / 100;
}
