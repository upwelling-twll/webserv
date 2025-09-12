#include "./AHttpRequest.hpp"

std::string AHttpRequest::trimSides(const std::string &s)
{
	std::size_t first = 0;
	while (first < s.size() && (s[first] == ' ' || s[first] == '\t'))
		++first;
	std::size_t last = s.size();
	while (last > first && (s[last - 1] == ' ' || s[last - 1] == '\t'))
		--last;
	return s.substr(first, last - first);
}

std::string AHttpRequest::extractMultipartFile() const
{
    // 1. Get boundary from Content-Type header
    std::string contentType = headers.find("Content-Type") != headers.end() ? headers.at("Content-Type") : "";
    if (contentType.empty())
        return "";

    std::string boundary;
    std::size_t pos = contentType.find("boundary=");
    if (pos == std::string::npos)
        return ""; // no boundary found

    boundary = "--" + contentType.substr(pos + 9); // include leading --

    // 2. Locate first boundary in body
    std::size_t start = vars.find("body") != vars.end() ? vars.at("body").find(boundary) : std::string::npos;
    if (start == std::string::npos)
        return "";

    start += boundary.size();
    if (start < vars.at("body").size() && vars.at("body")[start] == '\r' && vars.at("body")[start+1] == '\n')
        start += 2;

    // 3. Locate next boundary (closing boundary)
    std::size_t end = vars.at("body").find(boundary, start);
    if (end == std::string::npos)
        return "";

    std::string part = vars.at("body").substr(start, end - start);

    // 4. Skip headers inside the part (until double CRLF)
    std::size_t headerEnd = part.find("\r\n\r\n");
    if (headerEnd == std::string::npos)
        return "";

    std::string fileContent = part.substr(headerEnd + 4);

    // 5. Remove possible trailing CRLF
    if (fileContent.size() >= 2 && fileContent.substr(fileContent.size()-2) == "\r\n")
        fileContent.erase(fileContent.size()-2);

    return fileContent;
}


void AHttpRequest::removeTrailingCRLF(std::string &s)
{
	while (!s.empty() && (s[s.size() - 1] == '\r' || s[s.size() - 1] == '\n'))
		s.erase(s.size() - 1);
}

const char *const AHttpRequest::stdHeaders[] = {
	"Host", "User-Agent", "Accept", "Accept-Language",
	"Accept-Encoding", "Connection", "Content-Type",
	"Content-Length", "Cookie", "Referer",
	"Cache-Control", "Upgrade-Insecure-Requests"};

const std::size_t AHttpRequest::stdHeadersCount =
	sizeof(AHttpRequest::stdHeaders) / sizeof(AHttpRequest::stdHeaders[0]);

AHttpRequest::AHttpRequest() : STATUS(WAITING_START_LINE), contentLength(0) {}

AHttpRequest::AHttpRequest(std::string req) : STATUS(WAITING_START_LINE), contentLength(0)
{
	insert(req);
}

std::string AHttpRequest::get(VarKey key)
{
	switch (key)
	{
	case METHOD:
		return vars["method"];
	case URI:
		return vars["uri"];
	case VERSION:
		return vars["version"];
	case BODY:
		return vars["body"];
	default:
		return "";
	}
}

std::string AHttpRequest::get(HeaderKey key)
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

void AHttpRequest::setHeader(std::string key, std::string value)
{
	headers[key] = value;
}

void AHttpRequest::print() const
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
		std::cout << "\n"
				  << vars.find("body")->second << '\n';
	std::cout << "=============================\n";
}

RequestStatus AHttpRequest::insert(std::string chunk)
{
	raw += chunk;
	buf += chunk;

	while (true)
	{
		switch (STATUS)
		{
		case WAITING_START_LINE:
			if (buf.find('\n') == std::string::npos)
				return STATUS;
			checkVars();
			break;
		case WAITING_HEADER:
			if (buf.find('\n') == std::string::npos)
				return STATUS;
			checkHeaders();
			break;
		case WAITING_BODY:
			// std::cout << "STATUS = WAITING BODY" << std::endl;
			checkBody();
			if (STATUS == WAITING_BODY)
				return STATUS;
			break;
		default:
			return STATUS;
		}
		if (STATUS == READY || STATUS == ERROR_REQUEST)
		{
			return STATUS;
		}
	}
}

AHttpRequest::~AHttpRequest() {}