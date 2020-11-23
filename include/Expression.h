#ifndef $PROJECT_NAME_EXPRESSION_H
#define $PROJECT_NAME_EXPRESSION_H

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

class Expression {
    stack<float> m_mainStack;
    stack<char> m_opStack;
    string m_errStr;
    string m_outputList;

private:
    const string &convertInfix2Postfix(const string &expression);

    float eval(const string &rpn);

    float roundUp(float value);

    bool isFull();

    float pop();

    void push(float value);

    bool isOperator(char op);

    int getPriority(char op);

    void clearOpStack();

//    void replaceComma2Period(const string &expr);

public:
    Expression();

    virtual ~Expression();

    float calc(const string &expression);

    void printStack(const stack<float> &stack);

    const string &getErrStr() const;

};


#endif //$PROJECT_NAME_EXPRESSION_H
