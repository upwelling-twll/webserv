#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <string>
#include <map>
#include <iostream>

class HttpRequest
{
	private:
		std::string method;
		std::string uri;
		std::string version;
		std::map<std::string, std::string> headers;
		std::string body;

		static const char *const stdHeaders[];
		static const std::size_t stdHeadersCount;

		static std::string trimSides(const std::string &s);
		static void removeTrailingCRLF(std::string &s);

	public:
		explicit HttpRequest(std::string req);
		std::string getHeader(std::string key);
		void setHeader(std::string key, std::string value);
		void print() const;
		~HttpRequest();
};

#endif