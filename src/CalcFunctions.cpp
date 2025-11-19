#include "../includes/CalcFunctions.h"
#include "../includes/StrProcessing.h"

namespace CalcFunctions {
    enum ExitCodes {
        Failed = -1,
        Normal = 0,
        UserInterrupt = 1,
    };

    std::string GetInput() {
        std::cout << "Be a good boy, and enter the stuff you wanna do >_< Enter q to quit\n> ";
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    int ProcessInput(std::string &input) {
        StrProcessing::RemoveWhitespace(input);
        // Check if user wants to leave
        if (input[0] == 'q') return UserInterrupt;

        if (!StrProcessing::AreParenthesesCorrect(input) || StrProcessing::ContainsInvalidChars(input)) {
            return Failed;
        }

        return 0;
    }

    int CalcLoop() {
        int status {0};
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