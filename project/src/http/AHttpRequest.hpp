#ifndef AHTTPREQUEST_HPP
# define AHTTPREQUEST_HPP

# include <iostream>
# include "../../inc/webserv.hpp"

class AHttpRequest
{
private:
	/*Private members*/
	std::string							method;
	std::string							url; //target 
	std::string							version;

	std::string							startLine;
	std::map<std::string, std::string>	headers; //optional
	// std::string							body;

	
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
	AHttpRequest(void);

	/*Destructors*/
    ~AHttpRequest( void );

	/*Overload operators*/
	AHttpRequest &operator=(const AHttpRequest& src);
};

std::ostream& operator<<(std::ostream &output_stream, AHttpRequest& src);

#endif // AHTTPREQUEST_HPP
