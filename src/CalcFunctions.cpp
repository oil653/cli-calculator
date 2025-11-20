#include "../includes/CalcFunctions.h"
#include "../includes/StrProcessing.h"

namespace CalcFunctions {
    enum ExitCodes {
        Failed = -1,
        Normal = 0,
        UserInterrupt = 1,
    };

    std::string GetInput() {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    void PrintHelp() {
        std::cout << "Calculator thingy - a simple cli calculator\n" << std::endl;
        std::cout << "Supported operators: + - / * ^ ( )" << std::endl;
        std::cout << "Additional info:\n\t\tWhitespace doesn't matter"
                     "\n\t\tBoth . and , are supported for decimal markers"
                     "\n\t\tA decimal marker without a number before it is interpreted as 0.x"
                     "\n\t\tIf between a number and a parenthesis, there is no operator, it's interpreted as a multiplication"
        << std::endl;
    }

    int ProcessInput(std::string &input) {
        StrProcessing::RemoveWhitespace(input);
        // Check if user wants to leave
        if (input[0] == 'q') return UserInterrupt;
        if (input[0] == 'h') {
            PrintHelp();
            return Normal;
        };

        // Validate input
        try {
            StrProcessing::AreParenthesesCorrect(input);
        } catch (std::exception &e) {
            std::cout << RED << e.what() << RESET << std::endl;
            return Failed;
        }
        if (StrProcessing::ContainsInvalidChars(input)) {
            std::cout << RED << "Invalid character in input!" << RESET << std::endl;
            return Failed;
        }

        // Tokenise the string, make it postfix, evaluate it
        long double result {0};
        std::vector<std::string> tokenized;
        try {
            tokenized = StrProcessing::Tokenize(input);
            result = StrProcessing::EvalPostfix(StrProcessing::InfixToPostfix(tokenized));
        } catch (StrProcessing::DivisionByZeroError &e) {
            std::cout << RED << e.what() << RESET << std::endl;
            return Failed;
        } catch (std::exception &e) {
            std::cout << RED << e.what() << RESET << std::endl;
        }

        for (int i = 0; i < tokenized.size(); i++) {
            std::cout << tokenized[i] << ' ';
        }
        std::cout << "= " << result << std::endl;

        return 0;
    }

    int CalcLoop() {
        int status {0};
        std::cout << "WELCOME TO CALCULATOR LOOKING THING\nPress q to exit, h for help\nEnter an operation" << std::endl;
        while (true) {
            std::string input {GetInput()};
            status = ProcessInput(input);
            if (status == UserInterrupt) {
                std::cout << "Exiting..." << std::endl;
                return 0;
            }
        }
    }
}