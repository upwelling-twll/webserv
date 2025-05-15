#include "ConnectionSocket.hpp"

/*Member functions*/
void ConnectionSocket::method()
{
    // Method implementation
}

/*Getters and Setters*/

/*Constructors*/
ConnectionSocket::ConnectionSocket(/*Parameterized Constructor*/)
{
   std::cout << "ConnectionSocket parameterized constructor is called" << std::endl;
}

ConnectionSocket::ConnectionSocket()
{
    std::cout << "ConnectionSocket default constructor is called" << std::endl;
}

/*Destructors*/
ConnectionSocket::~ConnectionSocket( void )
{
    std::cout << "ConnectionSocket destructor is called" << std::endl;
}

/*Overload operators*/
ConnectionSocket& ConnectionSocket::operator=(const ConnectionSocket& src)
{
	std::cout << "ConnectionSocket copy assignment is called" << std::endl;
	if (this != &src)
	{
		// Assinment variables
	}
	return (*this);
}

std::ostream& operator<<(std::ostream& output_stream, ConnectionSocket& src)
{
	output_stream << "* ConnectionSocket Class info*" << std::endl;
	return output_stream;
}

