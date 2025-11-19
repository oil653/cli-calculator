#include "../includes/StrProcessing.h"

namespace StrProcessing {
    std::string &RemoveWhitespace(std::string &str) {
        str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
            return std::isspace(c);
        }), str.end());
        return str;
    }

    // Checks if all parentheses has been closed, and for invalid parentheses sequence
    // Returns false if there are problems with the parentheses
    bool AreParenthesesCorrect(const std::string &str) {
        int openPar {0}, closePar {0};
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '(') {
                if (closePar > openPar) {
                    for (int j = 0; j < str.length(); j++) {
                        std::cout << (i - 1 == j ? RED : RESET) << str[j] << RESET;
                    }
                    std::cout << std::endl;
                    std::cout << RED << "INCORRECT PARENTHESES ORDER" << RESET << std::endl;
                    return false;
                }
                openPar++;
            } else if (str[i] == ')') {
                closePar++;
            }
        }
        if (openPar != closePar) {
            std::cout << RED << "INCORRECT PARENTHESES COUNT, " << openPar << " \"(\" but " << closePar << " \")\""
                << RESET << std::endl;
            return false;
        }
        return true;
    }

    bool ContainsInvalidChars(const std::string &str) {
        for (char c : str) {
            if (c < '(' || c > '9') {
                std::cout << RED << "INCORRECT CHARACTER IN INPUT" << RESET << std::endl;
                return true;
            }
        }
        return false;
    }

    // A list of operators
    bool IsOperator(const std::string &str) {
        return str == "+" || str == "-" || str == "/" || str == "*" || str == "(" || str ==")";
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

    int GetPrecedence(const std::string &str) {
        if (str == "+" || str == "-") {
            return 0;
        }
        if (str == "/" || str == "*") {
            return 1;
        }
        if (str == "(" || str == ")") {
            return 10;
        } else {
            return -1;
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
            if (IsOperator(input)) {
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
                if (stack.empty() || GetPrecedence(input) > GetPrecedence(stack.top())) {
                    stack.push(input);
                    continue;
                } else {
                    while (!stack.empty() && stack.top() != "(" && GetPrecedence(stack.top()) >= GetPrecedence(input)) {
                        output.push_back(stack.top());
                        stack.pop();
                    }
                    stack.push(input);
                    continue;
                }
            }
            // If it's not a number nor an operant, we throw an error
            std::cout << RED << "FAILED TO CONVERT TO POSTFIX, THERE MIGHT BE SOME PROBLEMS WITH THE INPUT!" << input << RESET << std::endl;
        }
        // Pop remaining elements from the stack to the operation
        while (!stack.empty()) {
            output.push_back(stack.top());
            stack.pop();
        }
        return output;
    }

}