#include "./includes/main.h"
#include "./includes/CalcFunctions.h"
// #include "./includes/StrProcessing.h"

int main() {
    // std::vector<std::string> input {{"(", "1", "+", "2", ")", "*", "3"}};
    // std::vector<std::string> output {StrProcessing::InfixToPostfix(input)};
    // for (std::string x : output) {
    //     std::cout << x << ' ';
    // }
    // std::cout << std::endl;

    return CalcFunctions::CalcLoop();
}