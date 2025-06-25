#include "../AHttpRequest.hpp"

void AHttpRequest::checkVars()
{
	std::size_t pos = buf.find('\n');
	if (pos == std::string::npos)
		return;
	std::string line = buf.substr(0, pos + 1);
	buf.erase(0, pos + 1);
	removeTrailingCRLF(line);
	std::regex r("^(GET|POST|PUT|DELETE|HEAD|OPTIONS|PATCH)\\s+\\S+\\s+HTTP\\/\\d\\.\\d$");
	if (!std::regex_match(line, r))
	{
		STATUS = ERROR_REQUEST;
		return;
	}
	std::istringstream rl(line);
	std::string method, uri, version;
	rl >> method >> uri >> version;
	vars["method"] = method;
	vars["uri"] = uri;
	vars["version"] = version;
	STATUS = WAITING_HEADER;
}
