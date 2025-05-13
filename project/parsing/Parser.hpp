#ifndef PARSER_HPP
#define PARSER_HPP
#include "../shared/Server.hpp"
#include <vector>
#include <sstream>
#include <fstream>

extern const char* ServersEnum[];
extern const char* LocationsEnum[];

class Parser
{
private:

public:
	Parser(const char *filename);
};

int FindChar(std::string line, char character);
int FindSubstringEnd(std::string line, std::string word);

std::vector<std::string> splitAndRemoveSpaces(const std::string& input);

bool locateString(const std::vector<std::string>& vectorStr, std::string the_line);
void serverParser(std::ifstream &file, std::string line);
void locationParser(std::ifstream &file, std::string line);

#endif