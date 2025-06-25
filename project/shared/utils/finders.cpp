#include "../Server.hpp"

std::string trimSides(const std::string &s)
{
	std::size_t first = 0;
	while (first < s.size() && (s[first] == ' ' || s[first] == '\t'))
		++first;
	std::size_t last = s.size();
	while (last > first && (s[last - 1] == ' ' || s[last - 1] == '\t'))
		--last;
	return s.substr(first, last - first);
}

void removeTrailingCRLF(std::string &s)
{
	while (!s.empty() && (s[s.size() - 1] == '\r' || s[s.size() - 1] == '\n')) s.erase(s.size() - 1);
}


std::string locateHeader(const std::string& line, const std::string& header)
{
	std::size_t pos = line.find(':');
	if (pos == std::string::npos)
		return "";

	std::string key = trimSides(line.substr(0, pos));
	if (key != header)
		return "";

	return trimSides(line.substr(pos + 1));
}