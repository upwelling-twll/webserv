#include "Port.hpp"

/*Member functions*/

void	Port::closeFd()
{
	if (this->_listenSocket != -1)
	{
		std::cout << "	Closing listen socket" << std::endl;
		close(this->_listenSocket);
	}
	else
	{
		std::cout << "	Listen socket already closed" << std::endl;
	}
	return ;
}

/*Getters and Setters*/
void	Port::setListenSocket(int s)
{
	if (s < 0)
		throw;
	else
	{
		this->_listenSocket = s;
	}
}	

int	Port::getListenSocket()
{
	return(this->_listenSocket);
}

std::string const Port::getIp()
{
	return (this->_ip);
}

unsigned int Port::getPort()
{
	return (this->_port);
}

/*Constructors*/
Port::Port(const std::string ip, const int port) : _ip(ip), _port(port), _listenSocket(-1)
{	
   std::cout << "Port parameterized constructor is called" << std::endl;
}

Port::Port() : _ip("127.0.0.1"), _port(8080), _listenSocket(-1)
{
    std::cout << "Port default constructor is called" << std::endl;
}

/*Destructors*/
Port::~Port( void )
{
    std::cout << "Port destructor is called" << std::endl;
}

/*Overload operators*/
// Port& Port::operator=(const Port& src)
// {
// 	std::cout << "Port copy assignment is called" << std::endl;
// 	if (this != &src)
// 	{
		
// 	}
// 	return (*this);
// }

std::ostream& operator<<(std::ostream& output_stream, Port& src)
{
	output_stream << "Port instance: ip=" << src.getIp() << ", port=" \
		 << src.getPort() << ", listenSocket=" << src.getListenSocket() << std::endl;
	return output_stream;
}

