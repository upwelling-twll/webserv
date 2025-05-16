#include "ConnectionSocket.hpp"

/*Member functions*/
bool	isListening()
{
	return false;
}

int		handle()
{
	return 0;
}

/*Getters and Setters*/

/*Constructors*/
ConnectionSocket::ConnectionSocket(int fd) : Socket(fd)
{
   std::cout << "ConnectionSocket parameterized constructor is called" << std::endl;
   _listening = false;
}

/*Destructors*/
ConnectionSocket::~ConnectionSocket( void )
{
    std::cout << "ConnectionSocket destructor is called" << std::endl;
}

/*Overload operators*/

std::ostream& operator<<(std::ostream& output_stream, ConnectionSocket& src)
{
	output_stream << "* ConnectionSocket Class info*" << std::endl;

	return output_stream;
}

