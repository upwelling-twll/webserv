#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <iostream>
# include "../../inc/webserv.hpp"

class httpRequest
{
private:
	/*Private members*/
	std::string							method;
	std::string							url; //target 
	std::string							version;

	std::string							startLine;
	std::map<std::string, std::string>	headers; //optional
	std::string							body;

	
	public:
	/*Parsing member functions*/
	// void parseRequestLine(const std::string& requestLine);
	// void parseHeaders(const std::string& headers);
	// void parseBody(const std::string& body);
	
	/*Handling request member functions*/
    // void method();

	/*Getters and Setters*/
	std::string getMethod() const;
	std::string getUrl() const;
	std::string getVersion() const;

	/*Constructors*/
	httpRequest(void);

	/*Destructors*/
    ~httpRequest( void );

	/*Overload operators*/
	httpRequest &operator=(const httpRequest& src);
};

std::ostream& operator<<(std::ostream &output_stream, httpRequest& src);

#endif // HTTPREQUEST_HPP
