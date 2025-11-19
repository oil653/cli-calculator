#ifndef CLI_CALC_PREPROCESSING_H
#define CLI_CALC_PREPROCESSING_H

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stack>
#include <vector>

#include "../includes/main.h"

namespace StrProcessing {
    // Removes all whitespaces from a string
    std::string &RemoveWhitespace(std::string &str);

    // Checks for invalid parentheses pattern and count
    bool AreParenthesesCorrect(const std::string &str);

    // Checks if input string only has valid characters
    bool ContainsInvalidChars(const std::string &str);

    // Returns true if a string is a valid, supported operator
    bool IsOperator(const std::string &str);

    // Checks if string can be converted to double
    bool CanConvertToDouble(const std::string &str);

    // Returns a precedence level of an operator
    int GetPrecedence(const std::string &str);

    // Using a Shunting Yard algorithm, tokenise a vector of operators and numbers (as strings) to postfix
    std::vector<std::string> InfixToPostfix(const std::vector<std::string> &vec);
}

#endif