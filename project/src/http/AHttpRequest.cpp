#include "AHttpRequest.hpp"

/*Member functions*/
// void AHttpRequest::method()
// {
//     // Method implementation
// }

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

/*Constructors*/

AHttpRequest::AHttpRequest()
{
	method = "GET";
	url = "/";
	version = "HTTP/1.1";
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

