#include "Connection.hpp"

/*Member functions*/

void	Connection::handleInEvent()
{
	// std::cout << "	Handling my input event" << std::endl;
	int 	i;
	char	buf[1000];

	std::cout << "ConnectionSocket::handleInEvent() is called" << std::endl;
	i = recv(_clientConnectionSocket->getFd(), buf, sizeof(buf), 0);
	std::cout << buf <<" i=" << i << std::endl;
	return ;
}

bool	Connection::haveResponse()
{
	// std::cout << "	Need to check my response" << std::endl;
	//TODO : check if we have response to send 
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
															   _active(true)
{
	std::cout << "Connection parameterized constructor is called. Time Last Used:" \
    << std::asctime(std::localtime(&_timeLastUsed)) << std::endl;
	_pollFd = createConnectionSocket(serverListeningSocket);
	ConnectionSocket* newClientConnectionSocket = new ConnectionSocket(_pollFd.fd);
	_clientConnectionSocket = newClientConnectionSocket;
}

/*Destructors*/
Connection::~Connection( void )
{
    std::cout << "Connection destructor is called" << std::endl;
}

/*Overload operators*/

std::ostream& operator<<(std::ostream& output_stream, Connection& src)
{
	output_stream << "* Connection Class info*" << std::endl;
	output_stream << "Status: " << src.getStatus() << std::endl;
	output_stream << "Time Last Used: " << src.getTimeLastUsed() << std::endl;
	output_stream << "Server Listening Socket FD: " << src.getServerListeningSocket()->getFd() << std::endl;
	output_stream << "Client Connection Socket FD: " << src.getClientConnectionSocket()->getFd() << std::endl;
	return output_stream;
}

