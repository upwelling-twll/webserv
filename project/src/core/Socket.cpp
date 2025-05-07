#include "Socket.hpp"

/*Member functions*/


// void Socket::method()
// {
// 	// Method implementation
// }

//int	Socket::receiveRequest()
// {

// }

//int	Socket::sentResponce()
// {

// }

/*Getters and Setters*/
void    Socket::setHandler(SocketHandler func)
{
	this->handler = func;
}

int	Socket::getFd()
{
	return(this->_fd);
}

/*Constructors*/
Socket::Socket(int fd) : _fd(fd)
{
   std::cout << "Socket parameterized constructor is called" << std::endl;
}

// Socket::Socket()
// {
//     std::cout << "Socket default constructor is called" << std::endl;
// }

/*Destructors*/
Socket::~Socket( void )
{
    std::cout << "Socket destructor is called" << std::endl;
}

/*Overload operators*/
// Socket& Socket::operator=(const Socket& src)
// {
// 	std::cout << "Socket copy assignment is called" << std::endl;
// 	if (this != &src)
// 	{
// 		// Assinment variables
// 	}
// 	return (*this);
// }

std::ostream& operator<<(std::ostream& output_stream, Socket& src)
{
	output_stream << "Socket: fd=" << src.getFd() << std::endl;
	return output_stream;
}

