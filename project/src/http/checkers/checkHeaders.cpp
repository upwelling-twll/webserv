#include "../AHttpRequest.hpp"

void AHttpRequest::checkHeaders()
{
	std::size_t pos = buf.find('\n');
	if (pos == std::string::npos)
		return;
	std::string line = buf.substr(0, pos + 1);
	buf.erase(0, pos + 1);
	removeTrailingCRLF(line);
	if (line.empty())
	{
		if (vars["method"] == "POST" || vars["method"] == "PUT")
		{
			std::string cl = headers["Content-Length"];
			if (!cl.empty())
				contentLength = static_cast<std::size_t>(std::stoul(cl));
			if (contentLength > 0)
			{
				STATUS = WAITING_BODY;
				return;
			}
		}
		STATUS = READY;
		return;
	}
	std::size_t sep = line.find(':');
	if (sep == std::string::npos)
	{
		STATUS = ERROR_REQUEST;
		return;
	}
	std::string key = trimSides(line.substr(0, sep));
	std::string val = trimSides(line.substr(sep + 1));
	headers[key] = val;
}