
#include <iostream>
#include "./parsing/Parser.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
		return 1;
	const char* file = argv[1];

	try {
		Parser parser(file);
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}