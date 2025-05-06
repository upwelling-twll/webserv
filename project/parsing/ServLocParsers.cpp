#include "./Parser.hpp"

void locationParser(std::ifstream &file, std::string line)
{
	std::cout << "-----[START]-----Location Parser: " << std::endl;
	while (std::getline(file, line))
	{
		std::vector<std::string> buffer = splitAndRemoveSpaces(line);
		if (locateString(buffer, "}"))
			break;
		if (buffer.size() == 0)
			continue;
	}
	std::cout << "-----[END]-------Location Parser";
}

void serverParser(std::ifstream &file, std::string line)
{
	std::cout << "-----[START]-----Server Parser: " << std::endl;
	while (std::getline(file, line))
	{
		std::vector<std::string> buffer = splitAndRemoveSpaces(line);
		if (locateString(buffer, "}"))
			break;
		if (buffer.size() == 0)
			continue;
		if (locateString(buffer, "location") && locateString(buffer, "{"))
		{
			locationParser(file, line);
		}
	}
	std::cout << "-----[END]-------Server Parser";
}