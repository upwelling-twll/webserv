#include "./HttpParser.hpp"
#include <sstream>

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

const char *const HttpRequest::stdHeaders[] = {
	"Host", "User-Agent", "Accept", "Accept-Language",
	"Accept-Encoding", "Connection", "Content-Type",
	"Content-Length", "Cookie", "Referer",
	"Cache-Control", "Upgrade-Insecure-Requests"};

const std::size_t HttpRequest::stdHeadersCount =
	sizeof(HttpRequest::stdHeaders) / sizeof(HttpRequest::stdHeaders[0]);

HttpRequest::HttpRequest(std::string req)
{
	for (std::size_t i = 0; i < stdHeadersCount; ++i)
		headers[stdHeaders[i]] = "";

	std::istringstream ss(req);
	std::string line;

	if (std::getline(ss, line))
	{
		removeTrailingCRLF(line);
		std::istringstream rl(line);
		std::string method, uri, version;
		rl >> method >> uri >> version;
		vars["method"] = method;
		vars["uri"] = uri;
		vars["version"] = version;
	}

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

	std::string bodyBuf;
	while (std::getline(ss, line))
	{
		removeTrailingCRLF(line);
		bodyBuf += line;
		if (!ss.eof())
			bodyBuf += '\n';
	}
	vars["body"] = bodyBuf;
}

std::string HttpRequest::get(VarKey key)
{
	switch (key)
	{
		case METHOD:  return vars["method"];
		case URI:     return vars["uri"];
		case VERSION: return vars["version"];
		case BODY:    return vars["body"];
		default:      return "";
	}
}

std::string HttpRequest::get(HeaderKey key)
{
	static const char *const hdrNames[] = {
		"Host", "User-Agent", "Accept", "Accept-Language",
		"Accept-Encoding", "Connection", "Content-Type",
		"Content-Length", "Cookie", "Referer",
		"Cache-Control", "Upgrade-Insecure-Requests"};

	const std::size_t idx = static_cast<std::size_t>(key);
	if (idx >= sizeof(hdrNames) / sizeof(hdrNames[0]))
		return "";

	std::map<std::string, std::string>::const_iterator it =
		headers.find(hdrNames[idx]);
	return it != headers.end() ? it->second : "";
}

void HttpRequest::setHeader(std::string key, std::string value)
{
	headers[key] = value;
}

void HttpRequest::print() const
{
	std::cout << "==== Parsed HTTP request ====\n";
	std::cout << vars.find("method")->second << ' '
			  << vars.find("uri")->second << ' '
			  << vars.find("version")->second << '\n';
	for (std::map<std::string, std::string>::const_iterator it = headers.begin();
		 it != headers.end(); ++it)
		std::cout << it->first << ": "
				  << (it->second.empty() ? "<empty>" : it->second) << '\n';
	if (!vars.find("body")->second.empty())
		std::cout << "\n" << vars.find("body")->second << '\n';
	std::cout << "=============================\n";
}

HttpRequest::~HttpRequest() {}