#include <iostream>
#include <string>
#include <algorithm>

#define RED "\033[31m"
#define RESET "\033[0m"

std::string GetInput() {
    std::cout << "Be a good boy, and enter the stuff you wanna do >_< Enter q to quit\n> ";
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string &RemoveWhitespace(std::string &str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
        return std::isspace(c);
    }), str.end());
    return str;
}

// Checks if all parentheses has been closed, and for invalid parentheses sequence
// Returns false if there are problems with the parentheses
bool AreParenthesesCorrect(std::string &str) {
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

bool ContainsInvalidChars(std::string &str) {
    for (char c : str) {
        if (c < '(' || c > '9') {
            std::cout << RED << "INCORRECT CHARACTER IN INPUT" << RESET << std::endl;
            return true;
        }
    }
    return false;
}

int ProcessInput(std::string &input) {
    RemoveWhitespace(input);
    // Check if user want to leave
    if (input[0] == 'q') return -1;

    // std::cout << input << std::endl;

    if (!AreParenthesesCorrect(input) || ContainsInvalidChars(input)) {
        return 1;
    }
    return 0;
}

int main() {
    int status {0};
    while (true) {
        std::string input {GetInput()};
        status = ProcessInput(input);
        if (status == -1) {
            std::cout << "Exiting..." << std::endl;
            break;
        }
    }

    return 0;
}

// 1 + 5((2 * 2) + (-3 + -3)) / (15 - 1) - 1

// Tokenise it

// [1, +, 5, >>*,<< (( 2 * 2 ) + ( -3 + -3)), /, (, 15, -, 1, ), -, 1,]
// sqrt()

// () -> Loop through the chars, and solve the parentheses recursively
// * / -> Loop through it, and if there's a number and a ( assume * between the two
// + - solve stuff