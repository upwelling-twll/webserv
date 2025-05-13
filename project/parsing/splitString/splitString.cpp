#include "../Parser.hpp"

std::vector<std::string> splitAndRemoveSpaces(const std::string &input)
{
	std::istringstream iss(input);
	std::string word, clean;
	std::vector<std::string> res;
	while (iss >> word)
	{
		clean = word;
		while (!clean.empty() && (clean.back() == '{' || clean.back() == '}' || clean.back() == ';'))
			clean.erase(clean.size() - 1);
		if (!clean.empty())
			res.push_back(clean);
	}
	return res;
}