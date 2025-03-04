#include "computron.h"
#include <iostream>
using namespace std;

int main() {
    std::array<int, memorySize> memory{ 0 };
    int accumulator{ 0 };
    size_t instructionCounter{ 0 };
    int instructionRegister{ 0 };
    size_t operationCode{ 0 };
    size_t operand{ 0 };

    std::vector<int> dummyVec{ 1007, 1008, 2007, 3008, 2109, 1109, 4300, 0000, 0000, 0000, -99999 };

    for (int i = 0; i <= dummyVec.size() - 1; i++) 
    {
        memory[i] = dummyVec[i];
    }

    const std::vector<int> inputs{ 4, 5 };

    // load_from_file(memory, "p1.txt");

    execute(memory, &accumulator,
        &instructionCounter, &instructionRegister,
        &operationCode, &operand, inputs);

    //dump(memory, accumulator,instructionCounter, instructionRegister,
    //        operationCode, operand);
}