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
		// std::cout << "DEBUG: End of headers reached" << std::endl;
		// std::cout << "DEBUG: buf after headers: [" << buf << "]" << std::endl;
		//  if (!buf.empty() && buf[0] == '\r')
		// 	buf.erase(0, 1);
		// if (!buf.empty() && buf[0] == '\n')
       	// 	buf.erase(0, 1);
		// std::cout << "DEBUG: after removing CRLF" << std::endl;
		// std::cout << "DEBUG: buf after removing CRLF: [" << buf << "]" << std::endl;
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