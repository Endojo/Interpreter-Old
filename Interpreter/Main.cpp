#include <iostream>
#include "CodeReader.h"

int main()
{
	CodeReader programFile("H:\\Jonathan\\repros\\Interpreter\\Code\\FirstProgram.source");

	std::cout << programFile;
	std::cin.get();
}