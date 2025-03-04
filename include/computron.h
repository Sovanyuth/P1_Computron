#ifndef COMPUTRON_H
#define COMPUTRON_H

#include <iostream>
#include <array>
#include <string>
#include <vector>
using namespace std;

constexpr size_t memorySize{ 100 };
constexpr int minWord{ -9999 };
constexpr int maxWord{ 9999 };

enum class Command
{
	read = 10, write,
	load = 20, store,
	add = 30, subtract, divide, multiply,
	branch = 40, branchNeg, branchZero, halt
};

void load_from_file(array<int, memorySize>& memory, const string& filename);

void execute(array<int, memorySize>& memory, int* const acptr,
	size_t* const icPtr, int* const irPtr, size_t* const opCopePtr, size_t* const opPtr,
	const vector<int>& inputs);

bool validWord(int word);

void dump(std::array<int, memorySize>& memory, int accumulator,
	size_t instructionCounter, size_t instructionRegister,
	size_t operationCode, size_t operand);

#endif // COMPUTRON_H