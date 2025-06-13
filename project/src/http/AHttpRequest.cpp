#include "AHttpRequest.hpp"

/*Member functions*/
RequestStatus AHttpRequest::insert(std::string rawMessage)
{
	(void)rawMessage; // Suppress unused variable warning
	status = READY;
	return (status);
    // Method implementation
}

/*Getters and Setters*/
std::string AHttpRequest::getMethod() const
{
	return method;
}
std::string AHttpRequest::getUrl() const
{
	return url;
}
std::string AHttpRequest::getVersion() const
{
	return version;
}

RequestStatus AHttpRequest::getStatus() const
{
	return status;
}

/*Constructors*/

AHttpRequest::AHttpRequest()
{
	method = "";
	url = "";
	version = "";
	status = WAITING_START_LINE;
    std::cout << "AHttpRequest default constructor is called" << std::endl;
}

/*Destructors*/
AHttpRequest::~AHttpRequest( void )
{
    std::cout << "AHttpRequest destructor is called" << std::endl;
}

/*Overload operators*/
AHttpRequest& AHttpRequest::operator=(const AHttpRequest& src)
{
	std::cout << "AHttpRequest copy assignment is called" << std::endl;
	if (this != &src)
	{
		// Assinment variables
	}
	return (*this);
}

std::ostream& operator<<(std::ostream& output_stream, AHttpRequest& src)
{
	(void)src; // Suppress unused variable warning
	output_stream << "* AHttpRequest Class info*" << std::endl;
	return output_stream;
}

