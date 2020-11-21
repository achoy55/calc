#include <iostream>
#include <cmath>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <cctype>
#include <stack>
#include <algorithm>
#include <sstream>

using namespace std;

#define MAX_STACK 10000000
stack<float> _stack;
string errStr;

void calc(const string &expression);
float round(const string &str);
float eval(const string &rpn);
void printStack(stack<float> stack);
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

    string test = "4 12 3 + * 2 / 5 5 + * 100.5 2 * - 2 /";
    cout << "TST: " << test << endl;

    string expression = "(-4 * (12 + 3) / 2 * (5 + 5) - (100.5 * 2))/2";
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

    cout << eval(postfix) << endl;
}

void printStack(stack<float> stack) {
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

string convertInfix2Postfix(string expression) {
    if (expression.empty()) throw invalid_argument("Expression is empty");;

//    replaceComma2Period(expression); // replace comma to period

    errStr = "";
    std::locale loc;
    stack<char> _stack;
    string outputList;
    int i = 0;
    int bracketCnt = 0;

    while (i < expression.size()) {
        while (isspace(expression[i])) {
            i++;
        }

        if (isdigit(expression[i], loc) || expression[i] == '.' || expression[i] == ',') {
            //if expression is big or contains decimal number
            while (isdigit(expression[i]) || expression[i] == '.' || expression[i] == ',') {
                outputList += expression[i];
                i++;
            }
            if (i + 1 >= expression.size() || !isdigit(expression[i + 1], loc)) {
                outputList += ' ';
            }
            continue;
        } else if (isOperator(expression[i])) {
            if (expression[i] == '-' && (expression[i - 1] == '(' || outputList.empty())) {
                outputList.push_back('~');
            } else {
                while (!_stack.empty() && _stack.top() != '(' && getPriority(_stack.top()) >= getPriority(expression[i])) {
                    outputList.push_back(_stack.top());
                    _stack.pop();
                }
                _stack.push(expression[i]); //swap operators priority
            }
        } else if (expression[i] == '(') {
            _stack.push(expression[i]);
            ++bracketCnt;
        } else if (expression[i] == ')') {
            while (!_stack.empty() && _stack.top() != '(') {
                outputList.push_back(_stack.top());
                _stack.pop();
            }
            _stack.pop();
            --bracketCnt;
        } else {
            if (!isspace(expression[i]) && isalpha(expression[i])) {
                string wrongSymbols;
                while (isalpha(expression[i])) {
                    wrongSymbols += expression[i];
                    ++i;
                }
                errStr = "Invalid input, string contains invalid symbols " + wrongSymbols;

                clear(_stack);
                outputList.clear();
                break;
            }
        }
        i++;
    }

    if (bracketCnt < 0) {
        errStr = "There is close parenthesis without open";
        outputList.clear();
        clear(_stack);
    }
    if (bracketCnt) {
        errStr = "There are more open parentheses than closing ones";
        outputList.clear();
        clear(_stack);
    }

    while (!_stack.empty()) {
        outputList.push_back(_stack.top());
        _stack.pop();
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
    string token = "";

    while (i < rpn.length()) {
        while (isspace(rpn[i])) {
            i++;
        }

//        cout << rpn[i] << endl;

        //Check digits and . and ,
        if (isdigit(rpn[i]) | rpn[i] == '.') {
            while (isdigit(rpn[i]) | rpn[i] == '.') {
                token += rpn[i];
                i++;
            }
            push(atof(token.c_str())); //Push into stack number.
            token = "";
        }
            //Check operators
        else if (isOperator(rpn[i])) {
            // if operator is minus unary
            if (rpn[i] == '~') {
                ++i;
                push(-stod(&rpn[i]));
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

float round(const string &str) {
    return roundf(atof(str.c_str()) * 100) / 100;
}
