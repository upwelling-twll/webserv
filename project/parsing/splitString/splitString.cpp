#include "../Parser.hpp"

void printStringVector(const std::vector<std::string>& vec) {
	std::cout << "The Line: [" << vec.size() << "] ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "[" << vec[i] << "]   ";
    }
	std::cout << std::endl;
}

std::vector<std::string> splitAndRemoveSpaces(const std::string& input) {
    std::istringstream iss(input);
    std::string word;
    std::vector<std::string> result;

    while (iss >> word) {
        result.push_back(word);
    }
	printStringVector(result);
    return result;
}
