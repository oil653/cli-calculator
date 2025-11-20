#ifndef CLI_CALC_CALCFUNCTIONS_H
#define CLI_CALC_CALCFUNCTIONS_H

#include <iostream>
#include <string>

namespace CalcFunctions {
    // Get input from the user
    std::string GetInput();

    // Process the inputs, and print the result
    int ProcessInput(std::string &input);

    // A loop that runs until user exits, and calls ProcessInput
    int CalcLoop();

    // A simple function that prints helps and supported operators
    void PrintHelp();
}

#endif