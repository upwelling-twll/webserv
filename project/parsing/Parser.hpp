#ifndef PARSER_HPP
#define PARSER_HPP

#include "../shared/ServerParse.hpp"
#include <vector>
#include <fstream>
#include <sstream>

class Parser
{
public:
	Parser(const char *filename, std::vector<ServerParse> &servers);
};

std::vector<std::string> splitAndRemoveSpaces(const std::string &line);
void locationParser(std::ifstream &file, LocationParse &location);
void serverParser(std::ifstream &file, ServerParse &server);

#endif