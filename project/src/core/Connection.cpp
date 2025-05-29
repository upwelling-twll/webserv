#include "Connection.hpp"

/*Member functions*/


bool	Connection::haveResponse(struct pollfd fd)
{
	// std::cout << "	Need to check my response" << std::endl;
	if (fd.fd)
		return (true);
	return (false);
}

bool	Connection::sendToClients()
{
	//TODO move this methos to Connection class
	// std::cout << "	Giving my response to the client" << std::endl;
	return (false);
}

struct pollfd Connection::createConnectionSocket(ListeningSocket* serverListeningSocket)
{
	struct sockaddr	addr;
	socklen_t		size = sizeof(addr);
	int				_fd = accept(serverListeningSocket->getFd(), &addr, &size);
	struct pollfd	newPollFd;
	
	newPollFd.fd = _fd;
	newPollFd.events = POLLIN;
	newPollFd.revents = 0;
	return (newPollFd);
}

/*Getters and Setters*/
bool Connection::isActive()
{
	return _active;
}

struct pollfd Connection::getPollFd() const
{
	return _pollFd;
}

/*Constructors*/
Connection::Connection(ListeningSocket* serverListeningSocket) :
															   _buffer(""), 
															   _status("establisted"),
															   _serverListeningSocket(serverListeningSocket),   
															   _clientConnectionSocket(nullptr),  
															   _request(nullptr), 
															   _active(true)
{
	_timeLastUsed = std::time(nullptr);
	std::cout << "Connection parameterized constructor is called. Time Last Used:" \
    << std::asctime(std::localtime(&_timeLastUsed)) << std::endl;
	_pollFd = createConnectionSocket(serverListeningSocket);
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

