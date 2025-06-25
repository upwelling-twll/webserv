#include "./Parser.hpp"

void locationParser(std::ifstream &file, LocationParse &location)
{
	int depth = 1;
	std::string line;
	while (std::getline(file, line))
	{
		for (std::size_t j = 0; j < line.size(); ++j)
		{
			if (line[j] == '{')
				++depth;
			if (line[j] == '}')
				--depth;
		}
		if (depth == 0)
			break;
		std::vector<std::string> buffer = splitAndRemoveSpaces(line);
		if (buffer.empty())
			continue;
		if (location.hasProperty(buffer[0]))
		{
			std::string value;
			for (std::size_t i = 1; i < buffer.size(); ++i)
			{
				if (i > 1)
					value += ' ';
				value += buffer[i];
			}
			location.set(buffer[0], value);
		}
	}
}

void serverParser(std::ifstream &file, ServerParse &server)
{
	int depth = 1;
	std::string line;
	while (std::getline(file, line))
	{
		for (std::size_t j = 0; j < line.size(); ++j)
		{
			if (line[j] == '{')
				++depth;
			if (line[j] == '}')
				--depth;
		}
		if (depth == 0)
			break;
		std::vector<std::string> buffer = splitAndRemoveSpaces(line);
		if (buffer.empty())
			continue;
		if (server.hasProperty(buffer[0]))
		{
			std::string value;
			for (std::size_t i = 1; i < buffer.size(); ++i)
			{
				if (i > 1)
					value += ' ';
				value += buffer[i];
			}
			server.set(buffer[0], value);
		}
		else if (buffer[0] == "location" && buffer.size() >= 2)
		{
			LocationParse location;
			location.set("path_prefix", buffer[1]);
			locationParser(file, location);
			--depth;
			server.addLocation(location);
		}
	}
}