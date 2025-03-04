#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "computron.h"
#include "vector"

TEST_CASE("Basic Read Operation", "[read]")
{
    // step 1: initialization
    std::array<int, memorySize> memory = { 0 };
    int accumulator = 0;
    size_t instructionCounter = 0;
    int instructionRegister = 0;
    size_t operationCode = 0;
    size_t operand = 0;
    std::vector<int> inputs = { 42, 389, -1232, 3189 };

    // step 2: setting the memory location for read
    memory[0] = 1020;
    memory[1] = 1021;
    memory[2] = 1022;
    memory[3] = 1023;
    memory[4] = 4300;

    // step 3: calling the necessary functions for testing
    execute(memory, &accumulator, &instructionCounter, &instructionRegister,
        &operationCode, &operand, inputs);

    // step 4: verify the results
    REQUIRE(instructionCounter == 4);
    REQUIRE(instructionRegister == 4300);
    REQUIRE(memory[0] == 1020);
    REQUIRE(memory[20] == 42);
    REQUIRE(memory[21] == 389);
    REQUIRE(memory[22] == -1232);
    REQUIRE(memory[23] == 3189);
}

TEST_CASE("Basic Load & Store Operation", "[load][store][valid]")
{
    SECTION("Load Operation") 
    {
        // step 1: initialization
        std::array<int, memorySize> memory = { 0 };
        int accumulator = 0;
        size_t instructionCounter = 0;
        int instructionRegister = 0;
        size_t operationCode = 0;
        size_t operand = 0;
        std::vector<int> inputs = { 0 };

        // step 2: setting the memory location at 25 index for the load operator
        memory[25] = 853;

        // loading the value at memory location "25" into the accumulator
        memory[0] = 2025;

        // step 3: halt the program
        memory[1] = 4300;

        execute(memory, &accumulator, &instructionCounter, &instructionRegister,
            &operationCode, &operand, inputs);

        // step 4: verify the results
        REQUIRE(instructionCounter == 1);
        REQUIRE(accumulator == 853);
        REQUIRE(memory[25] == 853);
    }

    SECTION("Store Operation") 
    {
        // step 1: initialization
        std::array<int, memorySize> memory = { 0 };
        int accumulator = -47;
        size_t instructionCounter = 0;
        int instructionRegister = 0;
        size_t operationCode = 0;
        size_t operand = 0;
        std::vector<int> inputs = { 0 };

        // step 2: setting the instruction inside memory at index 0
        // storing the value from the accumulator into the memory location "25" into the accumulator
        memory[0] = 2148;

        // step 3: halt the program
        memory[1] = 4300;

        execute(memory, &accumulator, &instructionCounter, &instructionRegister,
            &operationCode, &operand, inputs);

        // step 4: verify the results
        REQUIRE(instructionCounter == 1);
        REQUIRE(memory[48] == -47);
    }
}

TEST_CASE("Add, Subtract, Multiply, & Divide", "[add][subtract][multiply][divide][valid]") 
{
    SECTION("Add Operation") 
    {
        // step 1: initialization
        std::array<int, memorySize> memory = { 0 };
        int accumulator = 2016;
        size_t instructionCounter = 0;
        int instructionRegister = 0;
        size_t operationCode = 0;
        size_t operand = 0;
        std::vector<int> inputs = { 0 };

        // step 2: picking the word at a specific memory location, then adding it to the accumulator
        memory[89] = 853;

        // loading the value at memory location "25" into the accumulator
        memory[0] = 3089;

        // step 3: halt the program
        memory[1] = 4300;

        execute(memory, &accumulator, &instructionCounter, &instructionRegister,
            &operationCode, &operand, inputs);

        // step 4: verify the results
        REQUIRE(instructionCounter == 1);
        REQUIRE(accumulator == 2869);
        REQUIRE(memory[89] == 853);
    }

    SECTION("Subtract Operation")
    {
        // step 1: initialization
        std::array<int, memorySize> memory = { 0 };
        int accumulator = -4168;
        size_t instructionCounter = 0;
        int instructionRegister = 0;
        size_t operationCode = 0;
        size_t operand = 0;
        std::vector<int> inputs = { 0 };

        // step 2: picking the word at a specific memory location, then adding it to the accumulator
        memory[38] = 180;

        // loading the value at memory location "25" into the accumulator
        memory[0] = 3138;

        // step 3: halt the program
        memory[1] = 4300;

        execute(memory, &accumulator, &instructionCounter, &instructionRegister,
            &operationCode, &operand, inputs);

        // step 4: verify the results
        REQUIRE(instructionCounter == 1);
        // After taking the absolute value of the accumulator
        REQUIRE(accumulator == -4348);
        REQUIRE(memory[38] == 180);
    }
    SECTION("Divide Operation")
    {
        // step 1: initialization
        std::array<int, memorySize> memory = { 0 };
        int accumulator = 2016;
        size_t instructionCounter = 0;
        int instructionRegister = 0;
        size_t operationCode = 0;
        size_t operand = 0;
        std::vector<int> inputs = { 0 };

        // step 2: picking the word at a specific memory location, then adding it to the accumulator
        memory[89] = 4;

        // loading the value at memory location "25" into the accumulator
        memory[0] = 3289;

        // step 3: halt the program
        memory[1] = 4300;

        execute(memory, &accumulator, &instructionCounter, &instructionRegister,
            &operationCode, &operand, inputs);

        // step 4: verify the results
        REQUIRE(instructionCounter == 1);
        REQUIRE(accumulator == 504);
        REQUIRE(memory[89] == 4);
    }

    SECTION("Multiply Operation")
    {
        // step 1: initialization
        std::array<int, memorySize> memory = { 0 };
        int accumulator = 2016;
        size_t instructionCounter = 0;
        int instructionRegister = 0;
        size_t operationCode = 0;
        size_t operand = 0;
        std::vector<int> inputs = { 0 };

        // step 2: picking the word at a specific memory location, then adding it to the accumulator
        memory[89] = 4;

        // loading the value at memory location "25" into the accumulator
        memory[0] = 3389;

        // step 3: halt the program
        memory[1] = 4300;

        execute(memory, &accumulator, &instructionCounter, &instructionRegister,
            &operationCode, &operand, inputs);

        // step 4: verify the results
        REQUIRE(instructionCounter == 1);
        REQUIRE(accumulator == 8064);
        REQUIRE(memory[89] == 4);
    }
    SECTION("All Operands Combined") 
    {
        // step 1: initialization
        std::array<int, memorySize> memory = { 0 };
        int accumulator = 0;
        size_t instructionCounter = 0;
        int instructionRegister = 0;
        size_t operationCode = 0;
        size_t operand = 0;
        std::vector<int> inputs = { 10, 20, 30 , 40, 50 };

        // step 2: read the input values and store them into memory locations "20 - 23".
        memory[0] = 1020; //10
        memory[1] = 1021; //20
        memory[2] = 1022; //30
        memory[3] = 1023; //40
        memory[4] = 1024; //50

        // loading input value 10 into accumulator and add 20
        memory[5] = 2020; // load 10 into accumulator
        memory[6] = 3021; // adding 10 + 20 inside accumulator
        memory[7] = 2130; // storing results '30' this inside memory location 30

        memory[8] = 2022; // load 30 into accumulator
        memory[9] = 3123; // subtracting 30 - 40 inside accumulator
        memory[10] = 2131; // storing results '-10' this inside memory location 31

        memory[11] = 3330;// Multiplying 30 by -10, i should now get "-300"
        memory[12] = 3224;// dividing -300 by 50, i should now get "-6"
        memory[13] = 2199; // Storing this value at 99

        // step 3: halt the program
        memory[14] = 4300;

        execute(memory, &accumulator, &instructionCounter, &instructionRegister,
            &operationCode, &operand, inputs);

        // step 4: verify the results
        REQUIRE(instructionCounter == 14);

        REQUIRE(memory[20] == 10);
        REQUIRE(memory[21] == 20);
        REQUIRE(memory[22] == 30);
        REQUIRE(memory[23] == 40);
        REQUIRE(memory[24] == 50);

        REQUIRE(memory[30] == 30);
        REQUIRE(memory[31] == -10);
        REQUIRE(memory[99] == -6);

        // Proving results from all the calculations to be true.
        REQUIRE(accumulator == -6);
    }
}

//TEST_CASE("Branch, BranchNeg, BranchZero", "[branch][branchNeg][branchZero][valid]") 
//{
//   std::array<int, memorySize> memory = { 0 };
//   int accumulator = 0;
//   size_t instructionCounter = 0;
//   int instructionRegister = 0;
//   size_t operationCode = 0;
//   size_t operand = 0;
//   std::vector<int> inputs = { 0 };
//
//   memory[0] = 4030;
//
//
//}