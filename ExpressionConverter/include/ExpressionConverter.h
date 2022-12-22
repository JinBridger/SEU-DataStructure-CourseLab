/**
 *  @file      ExpressionConverter.h
 *  @brief     ExpressionConverter Class
 *  @details   ~
 *  @author    JinBridge
 *  @date      13.10.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once

#include <stack>
#include <string>

/**
 *  @class   ExpressionConverter
 *  @brief   Convert between prefix and infix
 *  @details ~
 */
class ExpressionConverter {
public:
    std::string infix2prefix(std::string);
    std::string prefix2infix(std::string);

private:
    std::string getSubexpression(std::stack<char>&);
};