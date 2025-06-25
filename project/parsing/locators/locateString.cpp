#include "../Parser.hpp"

bool locateString(const std::vector<std::string> &vector, std::string line)
{
	return std::find(vector.begin(), vector.end(), line) != vector.end();
}