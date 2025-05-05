#include "Port.hpp"

/*Member functions*/
//   bind() assigns a name to an unnamed socket.  When a socket is created with socket(2) it
//exists in a name space (address family) but has no name assigned.  bind() requests that
///address be assigned to the socket.

void	Port::bindSocket()
{
	int	i;
	struct sockaddr_in	addr;

	addr.sin_len = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_port);
	addr.sin_addr.s_addr = inet_addr( this->_ip.c_str());
	std::cout << "	Binding socket start" << std::endl;
	i = bind(this->_listenSocket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
	std::cout << i << std::endl;
	if (i < 0)
		throw std::runtime_error("bind() failed"); //TODO : if error, a value of -1 is returned and the global integer variable errno is set to indicate the error
	std::cout << "	Binding socket complete" << std::endl;
	return ;
}

int	Port::createSocket()
{
	int	s_fd;
	
	std::cout << "	Creating socket" << std::endl;
	s_fd = socket(S_DOMAIN, SOCK_STREAM, 0);
	if (s_fd == -1)
		throw;
	//TODO : there is a list of errors returned in case of socket() fail, i may need to catch them as they all a macros 
	return (s_fd);
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
// 		// Assinment variables
// 	}
// 	return (*this);
// }

std::ostream& operator<<(std::ostream& output_stream, Port& src)
{
	output_stream << "Port instance: ip=" << src.getIp() << ", port=" \
		 << src.getPort() << ", listenSocket=" << src.getListenSocket() << std::endl;
	return output_stream;
}

