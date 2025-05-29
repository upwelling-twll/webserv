#include "Connection.hpp"

/*Member functions*/
// void Connection::method()
// {
//     // Method implementation
// }

/*Getters and Setters*/

/*Constructors*/
Connection::Connection(ListeningSocket* serverListeningSocket) :
															   _buffer(""), 
															   _status("establisted"),
															   _serverListeningSocket(serverListeningSocket),   
															   _clientConnectionSocket(nullptr),  
															   _request(nullptr), 
															   _stayAlive(true)
{
	_timeLastConnection = std::time(nullptr);
	std::cout << "Connection parameterized constructor is called. Time:" \
    << std::asctime(std::localtime(&_timeLastConnection)) << std::endl;
}

/*Destructors*/
Connection::~Connection( void )
{
    std::cout << "Connection destructor is called" << std::endl;
}

/*Overload operators*/

std::ostream& operator<<(std::ostream& output_stream, Connection& src)
{
	(void)src; // Suppress unused variable warning
	output_stream << "* Connection Class info*" << std::endl;
	return output_stream;
}

