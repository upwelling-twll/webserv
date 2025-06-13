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

void	Connection::changeSocketMode(short mode)
{
	_pollFd.events = mode;
	if (poll(&_pollFd, 1, 0) == -1)
	{
		std::cerr << "Error changing socket mode: " << strerror(errno) << std::endl;
		return ;
	}
	std::cout << "Socket mode changed successfully "<< std::endl;
}

void	Connection::updateConnection()
{
	if (_status == READY_FOR_FORMATTING_RESPONSE)
	{
		changeSocketMode(POLLOUT);
		std::cout << "Connection is ready for formatting response, changing socket mode to POLLOUT" << std::endl;
	}
	else if (_status == WAITING_FOR_DATA)
	{
		std::cout << "Connection is waiting for data, no changes" << std::endl;
	}
	else if ( _status == CLIENT_CLOSED_ERROR_RECEIVING_DATA || _status == ERROR_REQUEST_RECEIVED)
	{
		changeSocketMode(POLLOUT);
		//TODO : will form BadRequest error responce and send it to client and then close the connection
		std::cout << "Connection is in error state, changing socket mode to POLLIN" << std::endl;
	}
	else if (_status == ERROR_RECEIVING_DATA_CLOSE_CONNECTION)
	{
		//TODO : just close the connection, no response to send
		std::cout << "Connection is in seriouse error state, close it" << std::endl;
	}
	else if (_status == CLENT_CLOSED_READY_FOR_FORMATTING_RESPONSE)
	{
		changeSocketMode(POLLOUT);
		// TODO : form response and send it to client 
		// TODO : if request had "Connection : close" header, then close the connection after sending response
		// TODO : if request had "Connection : keep-alive" header, then keep the connection open for further requests
		std::cout << "Connection is ready for formatting response after client closed sending side, changing socket mode to POLLOUT" << std::endl;
	}
	else
	{
		changeSocketMode(POLLIN);
		std::cout << "Connection is in default state, changing socket mode to POLLIN" << std::endl;
	}
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
					_status = READY_FOR_FORMATTING_RESPONSE;
					std::cout << "Request is ready to form response" << std::endl;
					return ;
				}
				else if (rstatus == ERROR_REQUEST)
				{
					_status = ERROR_REQUEST_RECEIVED;
					std::cout << "Error in request parsing" << std::endl;
					break ;
				}
				else if (rstatus == WAITING_START_LINE || 
						rstatus == WAITING_HEADER || 
						rstatus == WAITING_BODY)
				{
					_status = WAITING_FOR_DATA;
					std::cout << "Request is not ready yet, waiting for more data" << std::endl;
					continue ;
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
			std::cout << "Client has closed the sending side" << std::endl;
			if (_request->getStatus() == READY)
			{
				_status = CLENT_CLOSED_READY_FOR_FORMATTING_RESPONSE;
				std::cout << "Request is ready to form response, client closed the sending side" << std::endl;
			}
			else
			{
				_status = CLIENT_CLOSED_ERROR_RECEIVING_DATA;
				std::cout << "Error receiving data from client, client closed the sending side" << std::endl;
			}
			return ;
		}
		else if (i == EAGAIN || i == EWOULDBLOCK)
		{
			_status = WAITING_FOR_DATA;
			std::cout << "No more data to read, waiting for more data chunks" << std::endl;
			return ;
		}
		else if (i == EINTR)
		{
			// Interrupted by a signal, continue receiving data
			std::cout << "Receiving data interrupted by a signal, continuing to receive data" << std::endl;
			continue ;
		}
		else
		{
			_status = ERROR_RECEIVING_DATA_CLOSE_CONNECTION;
			//TODO : might need to set request status to ERROR_REQUEST,
			// but must not send the responce, just !! close connection !!
			std::cerr << "Error receiving data from client: " << strerror(errno) << std::endl;
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
ConnectionStatus	Connection::getStatus() const
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
															   _status(IDLE),
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

