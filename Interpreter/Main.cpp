#include <iostream>
#include "CodeReader.h"

int main()
{
	CodeReader programFile("..\\Code\\FirstProgram.source");

	std::cout << programFile;
	std::cin.get();
}