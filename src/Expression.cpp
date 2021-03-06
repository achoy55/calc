#include "Expression.h"

Expression::Expression() :
        m_mainStack(),
        m_opStack(),
        m_errStr(),
        m_outputList() {}

Expression::~Expression() {}

float Expression::calc(const string &expression) {
    string postfix = convertInfix2Postfix(expression);
//    cout << "RPN: " << postfix << endl;

    if (postfix.empty() && !m_errStr.empty()) {
        cerr << m_errStr << endl;
        return 0;
    }

    float result = eval(postfix);
//    cout << "Result: " << result << ", rounded: " << roundUp(result) << endl;
    return roundUp(result);
}

const string &Expression::convertInfix2Postfix(const string &infix) {
    if (infix.empty()) {
        m_errStr = "Expression is empty";
        return m_outputList;
    }

    string expression = replaceComma2Period(infix); // replace comma to period

    clearOpStack();
    m_errStr = "";
    int i = 0;
    int bracketCnt = 0;

    while (i < (int) expression.length()) {
        while (isspace(expression[i])) {
            i++;
        }

        if (isdigit(expression[i]) || expression[i] == '.' || expression[i] == ',') {
            //if expression number is big or contains decimal number
            while (isdigit(expression[i]) || expression[i] == '.' || expression[i] == ',') {
                m_outputList += expression[i];
                i++;
            }

            if (i + 1 >= (int) expression.length() || !isdigit(expression[i])) {
                m_outputList += ' ';
            }
            continue;
        } else if (isOperator(expression[i])) {
            if ((expression[i] == '-' && (expression[i - 1] == '(' || m_outputList.empty()))
//                || (expression[i] == '-' &&
//                    (isOperator(expression[i - 1]) || isOperator(expression[i + 1]) || isdigit(expression[i + 1])))
                    ) {
                m_outputList.push_back('~');
            } else if (expression[i] == expression[i + 1]) {
                m_errStr = "Invalid Expression, identical operators < ";
                m_errStr += expression[i];
                m_errStr += " > in a row!";
                clearOpStack();
                break;
            } else {
                while (!m_opStack.empty() && m_opStack.top() != '(' &&
                       getPriority(m_opStack.top()) >= getPriority(expression[i])) {
                    m_outputList.push_back(m_opStack.top());
                    m_opStack.pop();
                }
                m_opStack.push(expression[i]); //swap operators priority
            }
        } else if (expression[i] == '(') {
            m_opStack.push(expression[i]);
            ++bracketCnt;
        } else if (expression[i] == ')') {
            while (!m_opStack.empty() && m_opStack.top() != '(') {
                m_outputList.push_back(m_opStack.top());
                m_opStack.pop();
            }
            m_opStack.pop();
            --bracketCnt;
        } else {
            if (!isspace(expression[i]) && isalpha(expression[i])) {
                string wrongSymbols;
                //collect all aplha symbols
                while (isalpha(expression[i])) {
                    wrongSymbols += expression[i];
                    ++i;
                }

                m_errStr = "Invalid input, string contains invalid symbols " + wrongSymbols;
                clearOpStack();
                break;
            }
        }
        i++;
    }

    if (bracketCnt < 0) {
        m_errStr = "There is close parenthesis without open";
        clearOpStack();
    }
    if (bracketCnt) {
        clearOpStack();
        m_errStr = "There are more open parentheses than closing ones";
    }

    while (!m_opStack.empty()) {
        m_outputList.push_back(m_opStack.top());
        m_opStack.pop();
    }

    return m_outputList;
}

float Expression::eval(const string &rpn) {
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
            string holeNumber;
            while (isdigit(rpn[i]) || rpn[i] == '.') {
                holeNumber += rpn[i];
                i++;
            }
            push(stof(holeNumber)); //Push into stack number.
        }
            //Check operators
        else if (isOperator(rpn[i])) {
            // if operator is minus unary
            if (rpn[i] == '~') {
                ++i;
                string holeNum;
                while (isdigit(rpn[i]) || rpn[i] == '.') {
                    holeNum += rpn[i];
                    ++i;
                }
                if (holeNum.empty()) {
                    cerr << "Unary operator, is not a number" << endl;
                    break;
                }
                push(-stof(holeNum.c_str()));
            } else if (rpn[i] == '/') {
                float v1 = pop();
                float v2 = pop();
                if (v1 == 0 || v2 == 0) {
                    cerr << "Division by zero" << endl;
                    break;
                }
                float result = operations[rpn[i]](v2, v1);
                push(result);
            } else {
                float result = operations[rpn[i]](pop(), pop());
                push(result);
            }
            i++;
        } else {
            cerr << "Invalid Expression <" << rpn[i] << ">" << endl;
            break;
        }
    }

    return pop();
}

float Expression::roundUp(float value) {
    return roundf(value * 100) / 100;
}

void Expression::printStack(const stack<float> &stack) {
    cout << "[";
    for (std::stack<float> dump = stack; !dump.empty(); dump.pop())
        cout << dump.top() << ',';
    cout << "]" << endl;
}

bool Expression::isFull() {
    return m_mainStack.size() >= MAX_STACK - 1;;
}

float Expression::pop() {
    float value = m_mainStack.top();
    m_mainStack.pop();
    return value;
}

void Expression::push(float value) {
    if (isFull()) return;
    m_mainStack.push(value);
}

bool Expression::isOperator(char op) {
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

int Expression::getPriority(char op) {
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

void Expression::clearOpStack() {
    m_outputList.clear();
    while (!m_opStack.empty())
        m_opStack.pop();
}

const string &Expression::getErrStr() const {
    return m_errStr;
}

string Expression::replaceComma2Period(const string &expression) {
    string tmp = expression;
    replace(tmp.begin(), tmp.end(), ',', '.');
    return tmp;
}
