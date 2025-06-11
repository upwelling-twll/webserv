#include "./HttpParser.hpp"
#include <sstream>

// HELPERS ----------------------------------------------------------
std::string HttpRequest::trimSides(const std::string &s)
{
	std::size_t first = 0;
	while (first < s.size() && (s[first] == ' ' || s[first] == '\t'))
		++first;
	std::size_t last = s.size();
	while (last > first && (s[last - 1] == ' ' || s[last - 1] == '\t'))
		--last;
	return s.substr(first, last - first);
}

void HttpRequest::removeTrailingCRLF(std::string &s)
{
	while (!s.empty() && (s[s.size() - 1] == '\r' || s[s.size() - 1] == '\n'))
		s.erase(s.size() - 1);
}
// HELPERS ----------------------------------------------------------



// HEADERS ----------------------------------------------------------
const char *const HttpRequest::stdHeaders[] = {
	"Host", "User-Agent", "Accept", "Accept-Language",
	"Accept-Encoding", "Connection", "Content-Type",
	"Content-Length", "Cookie", "Referer",
	"Cache-Control", "Upgrade-Insecure-Requests"};

const std::size_t HttpRequest::stdHeadersCount =
	sizeof(HttpRequest::stdHeaders) / sizeof(HttpRequest::stdHeaders[0]);
// HEADERS ----------------------------------------------------------



// CONSTRUCTOR ----------------------------------------------------------
HttpRequest::HttpRequest(std::string req)
{

	for (std::size_t i = 0; i < stdHeadersCount; ++i)
		headers[stdHeaders[i]] = "";
	std::istringstream ss(req);
	std::string line;

	// request-line -----------------------------------------------------------
	if (std::getline(ss, line))
	{
		removeTrailingCRLF(line);
		std::istringstream rl(line);
		rl >> method >> uri >> version;
	}

	// headers ----------------------------------------------------------------
	while (std::getline(ss, line))
	{
		removeTrailingCRLF(line);
		if (line.empty())
			break;
		std::size_t pos = line.find(':');
		if (pos == std::string::npos)
			continue;
		std::string key = trimSides(line.substr(0, pos));
		std::string val = trimSides(line.substr(pos + 1));
		headers[key] = val;
	}

	// body -------------------------------------------------------------------
	std::string bodyBuf;
	while (std::getline(ss, line))
	{
		removeTrailingCRLF(line);
		bodyBuf += line;
		if (!ss.eof())
			bodyBuf += '\n';
	}
	body = bodyBuf;
}
// CONSTRUCTOR ----------------------------------------------------------



std::string HttpRequest::getHeader(std::string key)
{
	std::map<std::string, std::string>::iterator it = headers.find(key);
	return it == headers.end() ? std::string("") : it->second;
}

void HttpRequest::print() const
{
	std::cout << "==== Parsed HTTP request ====\n";
	std::cout << method << ' ' << uri << ' ' << version << '\n';

	for (std::map<std::string, std::string>::const_iterator it = headers.begin();
		 it != headers.end(); ++it)
		std::cout << it->first << ": "
				  << (it->second.empty() ? "<empty>" : it->second) << '\n';

	if (!body.empty())
		std::cout << "\n"
				  << body << '\n';

	std::cout << "=============================\n";
}

void HttpRequest::setHeader(std::string key, std::string value)
{
	headers[key] = value;
}

HttpRequest::~HttpRequest() {}
