#include "ConnectionSocket.hpp"

/*Member functions*/
bool	ConnectionSocket::isListening() const
{
	return false;
}

int		ConnectionSocket::handle()
{
	int 	i;
	char	buf[1000];

	i = recv(_fd, buf, sizeof(buf), 0);
	std::cout << buf <<" i=" << i << std::endl;
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
	output_stream << "ConnectionSocket Class info:" << src.getFd() << std::endl;

	return output_stream;
}

