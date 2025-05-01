#include "../Parser.hpp"

int FindSubstringEnd(std::string line, std::string word) {
	std::size_t pos = line.find(word);
	if (pos == std::string::npos)
		return -1;
	std::cout << "The Line: \"" << line << "\" has substring: \"" << word << "\" at end position: " << (pos + word.length() - 1) << std::endl;
	return static_cast<int>(pos + word.length() - 1);
}