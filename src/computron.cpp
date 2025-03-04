#include "computron.h"
#include <fstream>
#include <iomanip>
using namespace std;

void load_from_file(array<int, memorySize>& memory, const string& filename)
{
	constexpr int sentinel{ -99999 };
	size_t i{ 0 };
	string line;
	int instruction;

	ifstream inputFile(filename);

    if (!inputFile) throw runtime_error("Invalid Input!");

    while (getline(inputFile, line))
    {
        instruction = stoi(line);
        if (instruction == sentinel) break;
        // Checking if word is valid before putting in memory location
        if (validWord(instruction)) 
        {
            memory[i] = instruction;
        }
        else 
        {
        // Throw an error is invalid
            throw runtime_error("Invalid Instruction!");
        }   
        // Increment the index
        i++;
    }
	inputFile.close();
}

Command opCodeToCommand(size_t opCode)
{
	switch (opCode)
	{
        // Implementing all different instructions for each opcode
		case 10: return Command::read;
        case 11: return Command::write;
        case 20: return Command::load;
        case 21: return Command::store;
        case 30: return Command::add;
        case 31: return Command::subtract;
        case 32: return Command::divide;
        case 33: return Command::multiply;
        case 40: return Command::branch;
        case 41: return Command::branchNeg;
        case 42: return Command::branchZero;
        case 43: return Command::halt;
        default:
            // halt the program as a default to prevent getting stuck
            return Command::halt;
	}
}

void execute(std::array<int, memorySize>& memory, int* const acPtr, size_t* const icPtr,
    int* const irPtr, size_t* const opCodePtr, size_t* const opPtr, const std::vector<int>& inputs) 
{
    size_t inputIndex{ 0 }; // Tracks input

    do {
        //instruction counter to register
        *irPtr = memory [*icPtr];
        *opCodePtr = *irPtr / 100; // divide
        *opPtr = *irPtr % 100; // remainder

        switch (int word{}; opCodeToCommand(*opCodePtr)) {
        case Command::read:
            word = inputs[inputIndex];
            // Assign the value of 'word' to the memory location pointed to by 'opPtr'
            if (!validWord(word)) throw runtime_error("Invalid Value!");

            memory[*opPtr] = word;
            // Increment the instruction counter (icPtr) to point to the next instruction
            (*icPtr)++;
            inputIndex++;
            break;

        case Command::write:
            // use the below cout if needed but comment before submission
            //std::cout << "Contents of " << std::setfill('0') << std::setw(2) 
            //          << *opPtr << " : +" << memory[*opPtr] << "\n";
            //Dereference 'icPtr' to access the instruction counter and increment its value by 1
            (*icPtr)++;
            break;

        case Command::load:
            //Load the value from the memory location pointed to by 'opPtr' into the accumulator (acPtr)
            word = memory[*opPtr];
            if (!validWord(word)) throw runtime_error("Invalid Value!");
            *acPtr = word;

            (*icPtr)++;
            //Increment the instruction counter (icPtr) to point to the next instruction
            break;
        case Command::store:
            // Store the value in the accumulator (acPtr) into the memory location pointed to by 'opPtr'
            word = *acPtr;
            memory[*opPtr] = word;
            // Increment the instruction counter (icPtr) to move to the next instruction
            (*icPtr)++;
            break;
        case Command::add:
            // Add the value in the accumulator (acPtr) to the value in memory at the location pointed to by 'opPtr' and store the result in 'word'
            word = *acPtr + memory[*opPtr];

            // If the result is invalid, throw a runtime error 
            if (!validWord(word)) 
            {
                throw runtime_error("Invalid Results!");
            }
            else 
            {
            // If the result is valid, store it in the accumulator and increment the instruction counter
                *acPtr = word;
                (*icPtr)++;
            }

            break;

        case Command::subtract:
            // Subtract the value in memory at the location pointed to by 'opPtr' from the value in the accumulator (acPtr) and store the result in 'word'
            word = *acPtr - memory[*opPtr];
            if (!validWord(word)) 
            {
                // / If the result is invalid, throw a runtime error 
                throw runtime_error("Invalid Results!");
            } 
            else 
            {
                // If the result is valid, store it in the accumulator and increment the instruction counter
                *acPtr = word;
                (*icPtr)++;
            }
            break;
         
        case Command::multiply:
            // as above do it for multiplication
            word = (*acPtr) * (memory[*opPtr]);

            if (!validWord(word))
            {
                // / If the result is invalid, throw a runtime error 
                throw runtime_error("Invalid Results!");
            }
            else
            {
                // If the result is valid, store it in the accumulator and increment the instruction counter
                *acPtr = word;
                (*icPtr)++;
            }
            break;
         
        case Command::divide:
            // as above do it for division
            if (memory[*opPtr] == 0) throw runtime_error("Division by Zero Error!");
            word = (*acPtr) / (memory[*opPtr]);

            // If the result is invalid, throw a runtime error 
            if (!validWord(word)) throw runtime_error("Invalid Results!");
            else
            {
                // If the result is valid, store it in the accumulator and increment the instruction counter
                *acPtr = word;
                (*icPtr)++;
            }
            break;
         
        case Command::branch:
            *icPtr = *opPtr;
            break;

        case Command::branchNeg:
            *acPtr < 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;

        case Command::branchZero:
            *acPtr == 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;

        case Command::halt:
            // dump(memory, *acPtr, *icPtr, *irPtr, *opCodePtr, *opPtr);
            break;

        default:
            if (!validWord)
            {
                throw runtime_error("Invalid Value!");
            }
            break;
        };

    // You may modify the below while condition if required
    } while (opCodeToCommand(*opCodePtr) != Command::halt);
};

// Checking if the words are within bounds, return true if it is
bool validWord(int word)
{
    if (word < minWord || word > maxWord) return false;

    return true;
}

// Helper functions for the dump function. These helpers helps reduce the line of code within the dump function and makes it more understandable
// Helper #1: output function which prints all of the register values into the terminal
void output(const int& accumulator,
    const size_t& instructionCounter, const size_t& instructionRegister,
    const size_t& operationCode, const size_t& operand)
{
    // using the "setfill" and "setw" functions from iomanip to print the desirable results
    cout << "Registers" << endl;
    // Checking if accumulator is negative, to display it with a negative sign
    if (accumulator < 0) 
    {
        cout << "accumulator          -" << std::setfill('0') << std::setw(4) << abs(accumulator) << endl;
    }
    else 
    {
        cout << "accumulator          +" << std::setfill('0') << std::setw(4) << accumulator << endl;
    }
    cout << "instructionCounter   " << std::setfill('0') << std::setw(2) << instructionCounter << endl;
    cout << "instructionRegister  +" << std::setfill('0') << std::setw(4) << instructionRegister << endl;
    cout << "operationCode        " << operationCode << endl;
    cout << "operand              " << std::setfill('0') << std::setw(2) << operand << endl;
    cout << endl;
}
// Helper #2: Just a small helper function that prints all of the necessary columns for the memory block
void printMemomryCols() 
{
    cout << "Memory:" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << setfill(' ') << setw(5) << i;
    }
    cout << endl;
}
// Helper #3: Goes into the memory array and prints out everything 
void printMemoryBlock(int&& memoryIndex, const array<int, memorySize>& memory) 
{
    // Utilizing double for loops to print all the memory blocks in a matrix like format
    for (int i = 0; i < 10; i++)
    {
        cout << setfill(' ') << setw(2) << 10 * i << ' ';

        for (int j = 0; j < 10; j++)
        {
            int word = memory[memoryIndex];
            // Checking if word is valid or not. In case of sentinel '-99999' then turn into +0000
            if (!validWord(word))
            {
                cout << '+' << setfill('0') << setw(5);
            }
            // If the word is valid 
            else
            {
                // Checking to see if the number is negative or not
                if (word < 0) 
                {
                    cout << '-' << setfill('0') << setw(4) << abs(word);
                }
                else 
                {
                    cout << '+' << setfill('0') << setw(4) << word;
                }
            }
            // Increment index
            memoryIndex++;
        }
        cout << endl;
    }
    cout << endl;
}

void dump(std::array<int, memorySize>& memory, int accumulator,
    size_t instructionCounter, size_t instructionRegister,
    size_t operationCode, size_t operand) 
{
    // Printing Output
    output(accumulator, instructionCounter, instructionRegister, operationCode, operand);
    // Memory Block::
    printMemomryCols();
    printMemoryBlock(0, memory);
};