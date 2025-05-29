#include "httpRequest.hpp"

/*Member functions*/
// void httpRequest::method()
// {
//     // Method implementation
// }

/*Getters and Setters*/
std::string httpRequest::getMethod() const
{
	return method;
}
std::string httpRequest::getUrl() const
{
	return url;
}
std::string httpRequest::getVersion() const
{
	return version;
}

/*Constructors*/

httpRequest::httpRequest()
{
	method = "GET";
	url = "/";
	version = "HTTP/1.1";
    std::cout << "httpRequest default constructor is called" << std::endl;
}

/*Destructors*/
httpRequest::~httpRequest( void )
{
    std::cout << "httpRequest destructor is called" << std::endl;
}

/*Overload operators*/
httpRequest& httpRequest::operator=(const httpRequest& src)
{
	std::cout << "httpRequest copy assignment is called" << std::endl;
	if (this != &src)
	{
		// Assinment variables
	}
	return (*this);
}

std::ostream& operator<<(std::ostream& output_stream, httpRequest& src)
{
	(void)src; // Suppress unused variable warning
	output_stream << "* httpRequest Class info*" << std::endl;
	return output_stream;
}

