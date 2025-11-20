#include "../includes/StrProcessing.h"

namespace StrProcessing {
    // Remove all whitespaces from a string
    std::string &RemoveWhitespace(std::string &str) {
        str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
            return std::isspace(static_cast<unsigned char>(c));
        }), str.end());
        return str;
    }

    // Checks for invalid parentheses patterns and count
    void AreParenthesesCorrect(const std::string &str) {
        int openPar {0}, closePar {0};
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '(') {
                if (closePar > openPar) {
                    throw IncorrectParenthesesOrder();
                }
                openPar++;
            } else if (str[i] == ')') {
                closePar++;
            }
        }
        if (openPar != closePar) {
            throw IncorrectParenthesesCount(openPar, closePar);
        }
    }

    // Returns if a string only contains valid characters
    bool ContainsInvalidChars(const std::string &str) {
        return std::ranges::any_of(str.begin(), str.end(), [](unsigned char c) {return c < '(' || c > '9';});
    }

    // Returns if a char is a supported operator or a parenthesis
    bool IsOperator(const char c) {
        return c == '+' || c == '-' || c == '/' || c == '*' || c == '(' || c ==')';
    }

    // Returns a precedence level of an operator
    int GetOperatorPrecedence(const char c) {
        if (c == '+' || c == '-') {
            return 0;
        }
        if (c == '/' || c == '*') {
            return 1;
        }
        if (c == '(' || c == ')') {
            return 10;
        } else {
            return -1;
        }
    }

    // Returns the precedence of the operator in str[0]
    int GetOperatorPrecedence(const std::string &str) {
        const unsigned char c {static_cast<unsigned char>(str[0])};
        if (c == '+' || c == '-') {
            return 0;
        }
        if (c == '/' || c == '*') {
            return 1;
        }
        if (c == '(' || c == ')') {
            return 10;
        } else {
            return -1;
        }
    }


    // Checks if string is a valid double
    bool CanConvertToDouble(const std::string &str) {
        try {
            double d {std::stod(str)};
            return true;
        } catch (std::exception &e) {
            return false;
        }
    }

    // Using a Shunting Yard algorithm, tokenise a vector of operators and numbers (as strings) to postfix
    std::vector<std::string> InfixToPostfix(const std::vector<std::string> &vec) {
        std::vector<std::string> output;
        std::stack<std::string> stack;

        // Loop through the expression
        for (std::string input : vec) {
            // If the current input is a number, we push it to the output vector
            if (CanConvertToDouble(input)){
                output.push_back(input);
                continue;
            }
            // If the current input is an operand we:
            if (IsOperator(input[0])) {
                // If we encounter a ')' pop all elements till we find the '('
                if (input == ")") {
                    while (stack.top() != "(") {
                        output.push_back(stack.top());
                        stack.pop();
                    }
                    // Remove the extra '(' in the stack
                    stack.pop();
                    continue;
                }
                if (input == "(") {
                    stack.push(input);
                    continue;
                }
                // If its precedence is higher than the top operand on the stack, we push it to the stack
                if (stack.empty() || GetOperatorPrecedence(input) > GetOperatorPrecedence(stack.top())) {
                    stack.push(input);
                    continue;
                } else {
                    while (!stack.empty() && stack.top() != "(" && GetOperatorPrecedence(stack.top()) >= GetOperatorPrecedence(input)) {
                        output.push_back(stack.top());
                        stack.pop();
                    }
                    stack.push(input);
                    continue;
                }
            }
            // If it's not a number nor an operant, we throw an error
            throw PostfixParsingError();
        }
        // Pop remaining elements from the stack to the operation
        while (!stack.empty()) {
            output.push_back(stack.top());
            stack.pop();
        }
        return output;
    }

}