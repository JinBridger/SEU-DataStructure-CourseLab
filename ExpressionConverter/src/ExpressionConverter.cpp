/**
 *  @file      ExpressionConverter.cpp
 *  @brief     ExpressionConverter Class
 *  @details   ~
 *  @author    JinBridge
 *  @date      13.10.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#include "ExpressionConverter.h"

/**
 *  @brief  Convert infix to prefix
 *  @param  infix - infix expression
 *  @retval prefix - prefix expression
 */
std::string ExpressionConverter::infix2prefix(std::string infix) {
    std::stack<char> optStack;
    std::stack<char> prefixStack;

    for (int i = infix.length() - 1; i >= 0; --i) {
        if (infix[i] >= 'A' && infix[i] <= 'Z') {
            prefixStack.push(infix[i]);
        }
        else {
            if (infix[i] == '(') {
                while (optStack.top() != ')') {
                    prefixStack.push(optStack.top());
                    optStack.pop();
                }
                optStack.pop();
            }
            if (infix[i] == ')') {
                optStack.push(infix[i]);
            }
            if (infix[i] == '+' || infix[i] == '-') {
                while (!optStack.empty() && (optStack.top() == '*' || optStack.top() == '/')) {
                    prefixStack.push(optStack.top());
                    optStack.pop();
                }
                optStack.push(infix[i]);
            }
            if (infix[i] == '*' || infix[i] == '/') {
                optStack.push(infix[i]);
            }
        }
    }
    while (!optStack.empty()) {
        prefixStack.push(optStack.top());
        optStack.pop();
    }

    std::string retVal = "";
    while (!prefixStack.empty()) {
        retVal += prefixStack.top();
        prefixStack.pop();
    }
    return retVal;
}

/**
 *  @brief  Convert prefix to infix
 *  @param  prefix - prefix expression
 *  @retval infix - infix expression, may including extra brackets
 */
std::string ExpressionConverter::prefix2infix(std::string prefix) {
    std::stack<char> infixStack;

    for (int i = prefix.length() - 1; i >= 0; --i) {
        if (prefix[i] >= 'A' && prefix[i] <= 'Z') {
            infixStack.push(prefix[i]);
        }
        else {
            std::string subExpression1 = getSubexpression(infixStack);
            std::string subExpression2 = getSubexpression(infixStack);
            std::string inStackVal     = '(' + subExpression1 + prefix[i] + subExpression2 + ')';
            for (int j = 0; j < inStackVal.length(); ++j) {
                infixStack.push(inStackVal[j]);
            }
        }
    }

    std::stack<char> reverseStk;
    while (!infixStack.empty()) {
        reverseStk.push(infixStack.top());
        infixStack.pop();
    }
    std::string retVal = "";
    while (!reverseStk.empty()) {
        retVal += reverseStk.top();
        reverseStk.pop();
    }
    return retVal;
}

/**
 *  @brief  Extract subexpression from stack
 *  @param  stk - stack
 *  @retval subsxpression - subexpression
 */
std::string ExpressionConverter::getSubexpression(std::stack<char>& stk) {
    std::string retVal = "";

    if (stk.top() != ')') {
        retVal += stk.top();
        stk.pop();
        return retVal;
    }

    std::stack<char> tempStk;
    int              rtBracketCnt = 1;
    stk.pop();
    tempStk.push(')');
    while (rtBracketCnt) {
        if (stk.top() == '(') {
            rtBracketCnt--;
        }
        if (stk.top() == ')') {
            rtBracketCnt++;
        }
        tempStk.push(stk.top());
        stk.pop();
    }

    while (!tempStk.empty()) {
        retVal += tempStk.top();
        tempStk.pop();
    }
    return retVal;
}