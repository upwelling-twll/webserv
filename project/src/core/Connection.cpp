#include "Connection.hpp"

/*Member functions*/

void	Connection::receiveRequest()
{
	int 	i;

	while ( _rstatus != END || _rstatus != ERROR )
	{
		i = recv(_clientConnectionSocket->getFd(), _buffer.data(), _buffer.size(), 0);
		if (i > 0)
		{
			std::cout << "Received data: " << _buffer.data() << std::endl;
			_rawMessage.append(_buffer.data(), i);
			if (_rstatus == OTHER_METHOD)
				continue;
			else if (_rstatus == NO_METHOD)
				parseMethod(_rawMessage);
			if (_rstatus == HTTP_GET_METHOD)
				parseContentLength(_rawMessage);
			if (_rstatus == PARSE_CONTENT_LENGTH_VALUE)
				parseContentLengthValue(_rawMessage);
			if (_rstatus == RECEIVING_BODY)
				checkCurrentBodyLength(_rawMessage);
			if (_rstatus == MORE_CHUNKS)
				checkMoreChunks(_rawMessage);
			if (_rstatus == END)
			{
				std::cout << "Request received successfully." << std::endl;
				//TODO : prepare engine to send response
				_rstatus = START; // Reset status for next request
				break;
			}
			if (_rstatus == ERROR)
			{
				std::cerr << "Error parsing request: " << _rawMessage << std::endl;
				//TODO : client is disconnecting,close Socket,clean Connection to Engine with REMOVE_SOCKET flag
				break ;
			}
			
		}
		else if (i == 0)
		{
			std::cout << "Client disconnected" << std::endl;
			_cstatus = CLIENT_CLOSED;
			_rstatus = END;
			//TODO : client is disconnecting,close Socket,clean Connection to Engine with REMOVE_SOCKET flag
			break ;
		}
		else if (i == EAGAIN || i == EWOULDBLOCK)
		{
			std::cout << "No data available to read at the moment." << std::endl;
			_rstatus = MORE_CHUNKS;
			// No data available, continue to wait for more data
			break;
		}
		else
		{
			std::cerr << "Error receiving data from client: " << strerror(errno) << std::endl;
			_cstatus = ERROR;
			_rstatus = END;
			//TODO : client is disconnecting,close Socket,clean Connection to Engine with REMOVE_SOCKET flag
			break ;
		}
	}
}

void	Connection::handleInEvent()
{
	std::cout << "	Handling my input event" << std::endl;
	std::cout << "ConnectionSocket::handleInEvent() is called" << std::endl;
	_timeLastUsed = std::time(0);
	switch (_cstatus)
	{
		case IDLE:
			receiveRequest();
			_cstatus = RECEIVING_REQUEST;
			break;
		case RECEIVING_REQUEST:
			receiveRequest();
			break;
		case CLIENT_CLOSED:
			break;
		case ERROR:
			receiveRequest();
	}
	return ;
}

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
															   _cstatus(IDLE),
															   _serverListeningSocket(serverListeningSocket),
															   _active(true),
															   _rstatus(START),
{
	std::cout << "Connection parameterized constructor is called. Time Last Used:" \
    << std::asctime(std::localtime(&_timeLastUsed)) << std::endl;
	_buffer.resize(8192); 
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

