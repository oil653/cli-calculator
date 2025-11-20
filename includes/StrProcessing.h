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
    // CUSTOM THROWS
        class IncorrectParenthesesOrder : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Incorrect parentheses order";
            }
        };

        class IncorrectParenthesesCount : public std::exception {
            private:
                int openingCount;
                int closingCount;
            public:
            IncorrectParenthesesCount(int openingCount, int closingCount) : openingCount(openingCount), closingCount(closingCount) {} ;

            const char* what() const noexcept override {
                return "Incorrect parentheses count";
            }

            int GetOpeningCount() const {
                return openingCount;
            }
            int GetClosingCount() const {
                return closingCount;
            }
        };

        class PostfixParsingError : public std::exception {
            public:
                const char* what() const noexcept {
                    return "Failed to convert to Postfix expression";
                }
        };

    // FUNCTIONS
        // Removes all whitespaces from a string
        std::string &RemoveWhitespace(std::string &str);

        // Checks for invalid parentheses patterns and count
        void AreParenthesesCorrect(const std::string &str);

        // Returns if a string only contains valid characters
        bool ContainsInvalidChars(const std::string &str);

        // Returns if a char is a supported operator or parenthesis
        bool IsOperator(const char c);

        // Returns if a char is a parenthesis
        bool IsParenthesis(const char c);

        // Returns if an char is a number
        bool IsDigitNum(const char c);

        // Returns a precedence level of an operator
        int GetOperatorPrecedence(const char c);

            // Returns the precedence of the operator in str[0]
            int GetOperatorPrecedence(const std::string &str);

        // Checks if string can be converted to a double
        bool CanConvertToDouble(const std::string &str);

        // Tokenize a string into a vector
        std::vector<std::string> Tokenize(const std::string &str);

        // Using a Shunting Yard algorithm, tokenise a vector of operators and numbers (as strings) to postfix
        std::vector<std::string> InfixToPostfix(const std::vector<std::string> &vec);
}

#endif