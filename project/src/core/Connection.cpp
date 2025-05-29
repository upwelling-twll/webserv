#include "Connection.hpp"

/*Member functions*/
void Connection::method()
{
    // Method implementation
}

/*Getters and Setters*/

/*Constructors*/
Connection::Connection(/*Parameterized Constructor*/)
{
   std::cout << "Connection parameterized constructor is called" << std::endl;
}

Connection::Connection()
{
    std::cout << "Connection default constructor is called" << std::endl;
}

/*Destructors*/
Connection::~Connection( void )
{
    std::cout << "Connection destructor is called" << std::endl;
}

/*Overload operators*/
Connection& Connection::operator=(const Connection& src)
{
	std::cout << "Connection copy assignment is called" << std::endl;
	if (this != &src)
	{
		// Assinment variables
	}
	return (*this);
}

std::ostream& operator<<(std::ostream& output_stream, Connection& src)
{
	output_stream << "* Connection Class info*" << std::endl;
	return output_stream;
}

