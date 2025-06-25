#include "Parser.hpp"
#include <algorithm>

Parser::Parser(const char *fname, std::vector<ServerParse> &servers)
{
	std::ifstream file(fname);
	if (!file)
		return;
	std::string line;
	int depth = 0;
	while (std::getline(file, line))
	{
		for (std::size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] == '{')
				++depth;
			if (line[i] == '}')
				--depth;
		}
		std::vector<std::string> buffer = splitAndRemoveSpaces(line);
		if (depth == 1 && buffer.size() == 1 && buffer[0] == "server")
		{
			ServerParse server;
			serverParser(file, server);
			servers.push_back(server);
			depth = 0;
		}
	}
}