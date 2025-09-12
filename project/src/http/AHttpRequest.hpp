#ifndef AHTTPREQUEST_HPP
#define AHTTPREQUEST_HPP

#include <iostream>
#include "../../inc/webserv.hpp"
#include <string>
#include <map>
#include <regex>
#include <sstream>

enum RequestStatus
{
	WAITING_START_LINE, //0
	WAITING_HEADER, //1
	WAITING_BODY, //2
	READY, //3
	ERROR_REQUEST, //4
};

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

class AHttpRequest
{
private:
	RequestStatus STATUS;
	std::map<std::string, std::string> vars;
	std::map<std::string, std::string> headers;

	static const char *const stdHeaders[];
	static const std::size_t stdHeadersCount;
	std::string extractMultipartFile() const;


	std::string buf;
	std::string raw;
	std::size_t contentLength;

	void checkVars();
	void checkHeaders();
	void checkBody();

	static std::string trimSides(const std::string &s);
	static void removeTrailingCRLF(std::string &s);

public:
	AHttpRequest();
	explicit AHttpRequest(std::string req);

	void setHeader(std::string key, std::string value);
	std::string get(HeaderKey key);
	std::string get(VarKey key);

	RequestStatus insert(std::string buffer);
	RequestStatus getStatus(){
		return this->STATUS;
	}

	void print() const;
	~AHttpRequest();
};

#endif