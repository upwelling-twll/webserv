#include "Server.hpp"


Server::Server(ServerStruct server_struct)
{

   std::cout << "Server parameterized constructor is called" << std::endl;
}

Server::Server()
{
    std::cout << "Server default constructor is called" << std::endl;
}

/*Destructors*/
Server::~Server( void )
{
    std::cout << "Server destructor is called" << std::endl;
}

/*Overload operators*/
Server& Server::operator=(const Server& src)
{
	std::cout << "Server copy assignment is called" << std::endl;
	if (this != &src)
	{
		// Assinment variables
	}
	return (*this);
}

std::ostream& operator<<(std::ostream& output_stream, Server& src)
{
	output_stream << "* Server Class info*" << std::endl;
	return output_stream;
}

