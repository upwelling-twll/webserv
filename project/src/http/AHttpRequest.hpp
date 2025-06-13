#ifndef AHTTPREQUEST_HPP
# define AHTTPREQUEST_HPP

# include <iostream>
# include "../../inc/webserv.hpp"

enum RequestStatus
{
	WAITING_START_LINE,
	WAITING_HEADER,
	WAITING_BODY,
	READY,
	ERROR_REQUEST,
};

class AHttpRequest
{
private:
	/*Private members*/
	std::string							method;
	std::string							url; //target 
	std::string							version;
	RequestStatus						status;

	std::string							startLine;
	std::map<std::string, std::string>	headers; //optional
	// std::string							body; //optional

	
	public:
	/*Parsing member functions*/
	// void parseStartingLine(const std::string& requestLine);
	// void parseHeaders(const std::string& headers);
	// void parseBody(const std::string& body);
	
	/*Member functions*/
    RequestStatus	insert(std::string rawMessage);

	/*Getters and Setters*/
	std::string 	getMethod() const;
	std::string 	getUrl() const;
	std::string		getVersion() const;
	// std::string getBody() const;
	// std::map<std::string, std::string> getHeaders() const;	

	RequestStatus	getStatus() const;

	/*Constructors*/
	AHttpRequest(void);

	/*Destructors*/
    ~AHttpRequest( void );

	/*Overload operators*/
	AHttpRequest &operator=(const AHttpRequest& src);
};

std::ostream& operator<<(std::ostream &output_stream, AHttpRequest& src);

#endif // AHTTPREQUEST_HPP
