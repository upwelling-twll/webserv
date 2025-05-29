#include "httpRequest.hpp"

/*Member functions*/
void httpRequest::method()
{
    // Method implementation
}

/*Getters and Setters*/

/*Constructors*/
httpRequest::httpRequest(/*Parameterized Constructor*/)
{
   std::cout << "httpRequest parameterized constructor is called" << std::endl;
}

httpRequest::httpRequest()
{
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
	output_stream << "* httpRequest Class info*" << std::endl;
	return output_stream;
}

