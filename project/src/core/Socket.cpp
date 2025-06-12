#include "Socket.hpp"

/*Member functions*/

/*Getters and Setters*/

int	Socket::getFd() const
{
	return(this->_fd);
}

void	Socket::setAddrInfo(struct sockaddr_in _addr, socklen_t _addr_len, size_t _addr_text_len)
{
	this->_addr = _addr;
	this->_addr_len = _addr_len;
	this->_addr_text_len = _addr_text_len;
}

/*Constructors*/ 
Socket::Socket(int fd) : _fd(fd)
{
   std::cout << "Socket parameterized constructor is called" << std::endl;
}

/*Destructors*/
Socket::~Socket( void )
{
    std::cout << "Socket destructor is called" << std::endl;
}

/*Overload operators*/

std::ostream& operator<<(std::ostream& output_stream, Socket& src)
{
	output_stream << "Socket: fd=" << src.getFd() << ", listening=" << src.isListening() << std::endl;
	return output_stream;
}
