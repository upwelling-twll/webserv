#ifndef PARSER_HPP
#define PARSER_HPP
#include "../shared/Server.hpp"

class Parser
{
private:

public:
	Parser(const char *filename);
};

int FindChar(std::string line, char character);
int FindSubstringEnd(std::string line, std::string word);

#endif