#include "CodeReader.h"
#include <iostream>

int main()
{
	CodeReader programFile("H:\\Jonathan\\repros\\Interpreter\\Code\\FirstProgram.source");

	std::cout << programFile;
	std::cin.get();
}