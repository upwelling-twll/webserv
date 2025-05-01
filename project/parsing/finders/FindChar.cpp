#include "../Parser.hpp"
int FindChar(std::string line, char character) {
	for (std::size_t i = 0; i < line.length(); ++i) {
		if (line[i] == character){
			std::cout << "The Line: \"" << line << "\" has charecter: \"" << character << "\" at position: "<< "[" << i << "]" << std::endl;
			return static_cast<int>(i);
		}
	}
	return -1;
}