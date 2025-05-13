#ifndef PARSER_HPP
#define PARSER_HPP

#include "../shared/Server.hpp"
#include <vector>
#include <fstream>
#include <sstream>

class Parser
{
public:
	Parser(const char *filename, std::vector<Server> &servers);
};

std::vector<std::string> splitAndRemoveSpaces(const std::string &line);
void locationParser(std::ifstream &file, Location &location);
void serverParser(std::ifstream &file, Server &server);

#endif