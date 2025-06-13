#include "Connection.hpp"

/*Member functions*/

bool locateSymbol(const std::string& string, char symbol)
{
	std::string::size_type pos = string.find(symbol);
	if (pos != std::string::npos)
		return true;
	else
		return false;
}

void	Connection::handleInEvent()
{
	// std::cout << "	Handling my input event" << std::endl;
	int 	i;
	char	buf[1000];
	RequestStatus rstatus;

	std::cout << "ConnectionSocket::handleInEvent() is called" << std::endl;
	rstatus = _request->getStatus();
	while (rstatus != ERROR_REQUEST && rstatus != READY)
	{
		i = recv(_clientConnectionSocket->getFd(), buf, sizeof(buf), 0);
		if (i > 0)
		{
			buf[i] = '\0'; // Null-terminate the buffer to treat it as a string
			std::cout << "buf:" << buf <<"$, i=" << i << std::endl;
			_rawMessage += buf; // Append the received data to _rawMessage
			if (locateSymbol(_rawMessage, '\n') == true)
			{
				std::cout << "Enough data to parse request (have nl)" << std::endl;
				rstatus = _request->insert(_rawMessage);
				if (rstatus == READY)
				{
					_status = "readyForFormattingResponse";
					std::cout << "Request is ready for formatting response" << std::endl;
					return ;
				}
				else if (rstatus == ERROR_REQUEST)
				{
					_status = "errorrRequest";
					std::cout << "Error in request parsing" << std::endl;
					break ;
				}
				else if (rstatus == WAITING_START_LINE || 
						rstatus == WAITING_HEADER || 
						rstatus == WAITING_BODY)
				{
					_status = "waitingForData";
					std::cout << "Request is not ready yet, waiting for more data" << std::endl;
				}
			}
			else
			{
				std::cout << "Not enough data to parse request (no nl)" << std::endl;
				continue ;
			}
		}
		if (i == 0)
		{
			std::cout << "Client has closed the connection" << std::endl;
			_status = "clientClosed";
			return ;
		}
		else if (i == EAGAIN || i == EWOULDBLOCK)
		{
			std::cout << "No more data to read, waiting for more data chunks" << std::endl;
			_status = "waitingForData";
			return ;
		}
		else
		{
			std::cerr << "Error receiving data from client: " << strerror(errno) << std::endl;
			_status = "errorReceivingData";
			return ;
		}
	}
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

std::string Connection::getRawMessage() const
{
	return _rawMessage;
}

std::string Connection::getBuffer() const
{
	return _buffer;
}
std::string Connection::getStatus() const
{
	return _status;
}

time_t Connection::getTimeLastUsed() const
{
	return _timeLastUsed;
}
ListeningSocket* Connection::getServerListeningSocket() const
{
	return _serverListeningSocket;
}
ConnectionSocket* Connection::getClientConnectionSocket() const
{
	return _clientConnectionSocket;
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
	AHttpRequest* newRequest = new AHttpRequest();
	_request = newRequest;
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

