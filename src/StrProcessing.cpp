#include "../includes/StrProcessing.h"

#include <cmath>

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
        return std::ranges::any_of(str.begin(), str.end(), [](unsigned char c) {
            return (c < '(' || c > '9') && c != '^';
        });
    }

    // Returns if a char is a supported operator or a parenthesis
    bool IsOperator(const char c) {
        return c == '+' || c == '-' || c == '/' || c == '*' || c == '(' || c ==')' || c == '^';
    }

    // Returns if a char is a parenthesis
    bool IsParenthesis(const char c) {
        return c == '(' || c ==')';
    }

    // Returns if a char is a number
    bool IsDigitNum(const char c) {
        unsigned char uc {static_cast<unsigned char>(c)};
        return uc >= '0' && uc <= '9';
    }

    // Returns a precedence level of an operator
    int GetOperatorPrecedence(const char c) {
        if (c == '+' || c == '-') {
            return 0;
        }
        if (c == '/' || c == '*') {
            return 1;
        }
        if (c == '^') {
            return 2;
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
        if (c == '^') {
            return 2;
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

    // Tokenize a string into a vector
    std::vector<std::string> Tokenize(const std::string &str) {
        std::vector<std::string> output;
        std::string temp;

        for (int i = 0; i < str.length(); i++) {
            unsigned char c {static_cast<unsigned char>(str[i])};
            // DECIMAL MARK CHECK
            if (c == ',' || c == '.') {
                // Assume 0 before empty decimal marks
                if (temp.empty()) {
                    temp.push_back('0');
                    temp.push_back('.');
                    continue;
                }
                temp.push_back('.');
                continue;
            }

            // NUMBER OPERATIONS
            if (IsDigitNum(c)) {
                // If the last operator is a ), put a * between it and the number
                if (i > 0 && str[i - 1] == ')') {
                    output.push_back("*");
                }
                temp.push_back(c);
                if (i + 1 == str.length() || IsOperator(str[i + 1])) {
                    output.push_back(temp);
                    temp.clear();
                    if (i + 1 != str.length() && str[i + 1] == '(') {
                        output.push_back("*");
                    }
                }
                continue;
            }

            // CHECK IF A NUMBER IS NEGATIVE
            if (c == '-' && (i == 0 || IsOperator(str[i - 1])) && temp.empty()) {
                temp.push_back('-');
                continue;
            }

            // OTHER OPERATOR HANDLE
            if (IsOperator(str[i])) {
                output.push_back(std::string(1, str[i]));
            }
        }
        return output;
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

    // Evaluating the postfix notation
    long double EvalPostfix (const std::vector<std::string> &vec) {
        std::stack<long double> stack;

        for (int i = 0; i < vec.size(); i++) {
            if (CanConvertToDouble(vec[i])) {
                stack.push(std::stod(vec[i]));
                continue;
            }

            if (IsOperator(vec[i][0])) {
                long double a {0}, b {0};
                b = stack.top();
                stack.pop();
                a = stack.top();
                stack.pop();
                stack.push(Solve(a, b, vec[i][0]));
            }
        }
        return stack.top();
    }

    long double Solve (long double a, long double b, char op) {
        switch (op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                if (b == 0) throw DivisionByZeroError();
                return a / b;
            case '^':
                return std::pow(a, b);
            default:
                return 0;
        }
    }

}
