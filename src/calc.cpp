#include "calc.h"

stack<float> _mainStack;
string errStr;

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

    while (i < (int) expression.size()) {
        while (isspace(expression[i])) {
            i++;
        }

        if (isdigit(expression[i]) || expression[i] == '.' || expression[i] == ',') {
            //if expression number is big or contains decimal number
            while (isdigit(expression[i]) || expression[i] == '.' || expression[i] == ',') {
                outputList += expression[i];
                i++;
            }
            if (i + 1 >= (int) expression.size() || !isdigit(expression[i + 1])) {
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
    while (i < (int) rpn.length()) {
        while (isspace(rpn[i])) {
            i++;
        }

        //Check digits and . and ,
        if (isdigit(rpn[i]) || rpn[i] == '.') {
            string allNum;
            while (isdigit(rpn[i]) || rpn[i] == '.') {
                allNum += rpn[i];
                i++;
            }
            push(stof(allNum)); //Push into stack number.
        }
            //Check operators
        else if (isOperator(rpn[i])) {
            // if operator is minus unary
            if (rpn[i] == '~') {
                ++i; // next operand
                if (isdigit(rpn[i])) {
                    push(-stof(&rpn[i]));
                }
            } else if (rpn[i] == '/') {
                float v1 = pop();
                float v2 = pop();
                if (v1 == 0 || v2 == 0) {
                    cerr << "Division by zero" << endl;
                    break;
                }
                float result = operations[rpn[i]](v2, v1);
                push(result);
//                cout << "Val: " << v1 <<", " << v2 << ", res: " << result << endl;
            } else {
                float v1 = pop();
                float v2 = pop();
                float result = operations[rpn[i]](v2, v1);
//                float result = operations[rpn[i]](pop(), pop());
                push(result);
//                cout << "Val: " << v1 <<", " << v2 << ", res: " << result << endl;
            }
            i++;
        } else {
            cout << "Invalid Expression <" << rpn[i] << ">" << endl;
            break;
        }
    }

    return pop();
}

void printStack(const stack<float> &stack) {
    cout << "[";
    for (std::stack<float> dump = stack; !dump.empty(); dump.pop())
        cout << dump.top() << ',';
    cout << "]" << endl;
}

bool isFull() {
    return _mainStack.size() >= MAX_STACK - 1;
}

void push(float value) {
    if (isFull()) return;
    _mainStack.push(value);
}

float pop() {
    float value = _mainStack.top();
    _mainStack.pop();
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
