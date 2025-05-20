#include "./Parser.hpp"

void locationParser(std::ifstream &file, Location &location)
{
	int depth = 1;
	std::string line;
	while (std::getline(file, line))
	{
		for (std::size_t j = 0; j < line.size(); ++j)
		{
			if (line[j] == '{') ++depth;
			if (line[j] == '}') --depth;
		}
		if (depth == 0) break;

		std::vector<std::string> buffer = splitAndRemoveSpaces(line);
		if (buffer.empty()) continue;

		if (location.hasProperty(buffer[0]))
		{
			std::string value;
			for (std::size_t i = 1; i < buffer.size(); ++i)
			{
				if (i > 1) value += ' ';
				value += buffer[i];
			}
			std::vector<std::string> v; v.push_back(value);
			location.reset(buffer[0], v);
		}
	}
}

void serverParser(std::ifstream &file, Server &server)
{
	int depth = 1;
	std::string line;
	while (std::getline(file, line))
	{
		for (std::size_t j = 0; j < line.size(); ++j)
		{
			if (line[j] == '{') ++depth;
			if (line[j] == '}') --depth;
		}
		if (depth == 0) break;

		std::vector<std::string> buffer = splitAndRemoveSpaces(line);
		if (buffer.empty()) continue;

		if (server.hasProperty(buffer[0]))
		{
			std::string value;
			for (std::size_t i = 1; i < buffer.size(); ++i)
			{
				if (i > 1) value += ' ';
				value += buffer[i];
			}
			std::vector<std::string> v; v.push_back(value);
			server.reset(buffer[0], v);
		}
		else if (buffer[0] == "location" && buffer.size() >= 2)
		{
			Location location;
			std::vector<std::string> v; v.push_back(buffer[1]);
			location.reset("path_prefix", v);
			locationParser(file, location);
			--depth;
			server.addLocation(location);
		}
	}
}