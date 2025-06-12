#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <string>
#include <map>
#include <iostream>

enum VarKey
{
	METHOD = 0,
	URI,
	VERSION,
	BODY
};

enum HeaderKey
{
	HOST = 0,
	USER_AGENT,
	ACCEPT,
	ACCEPT_LANGUAGE,
	ACCEPT_ENCODING,
	CONNECTION,
	CONTENT_TYPE,
	CONTENT_LENGTH,
	COOKIE,
	REFERER,
	CACHE_CONTROL,
	UPGRADE_INSECURE_REQUESTS
};
class HttpRequest
{
private:
	std::map<std::string, std::string> vars;
	std::map<std::string, std::string> headers;

	static const char *const stdHeaders[];
	static const std::size_t stdHeadersCount;

	static std::string trimSides(const std::string &s);
	static void removeTrailingCRLF(std::string &s);

public:
	explicit HttpRequest(std::string req);

	void setHeader(std::string key, std::string value);

	std::string get(HeaderKey key);
	std::string get(VarKey key);

	void print() const;
	~HttpRequest();
};

#endif