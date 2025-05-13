#include "../Parser.hpp"

int FindChar(std::string line, char the_letter)
{
	for (std::size_t i = 0; i < line.length(); ++i)
	{
		if (line[i] == the_letter)
		{
			std::cout << "The Line: \"" << line << "\" has character: \"" << the_letter << "\" at position: [" << i << "]\n";
			return static_cast<int>(i);
		}
	}
	return -1;
}