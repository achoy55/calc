#ifndef $PROJECT_NAME_CALC_H
#define $PROJECT_NAME_CALC_H

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

#endif //$PROJECT_NAME_CALC_H
