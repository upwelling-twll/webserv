#include "Port.hpp"

/*Member functions*/
// void Port::method()
// {
//     // Method implementation
// }

/*Getters and Setters*/
std::string const Port::getIp()
{
	return (this->_ip);
}

unsigned int Port::getPort()
{
	return (this->_port);
}

/*Constructors*/
Port::Port(const std::string ip, const int port) : _ip(ip), _port(port)
{	
   std::cout << "Port parameterized constructor is called" << std::endl;
}

Port::Port() : _ip("127.0.0.1"), _port(8080)
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
		 << src.getPort() << std::endl;
	return output_stream;
}

