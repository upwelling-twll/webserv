#include "Connection.hpp"

/*Member functions*/

void	Connection::changeSocketMode(short mode, pollfd& pollFd)
{
	pollFd.events = mode;
	std::cout << "Socket mode changed successfully "<< std::endl;
}

void	Connection::processConnectionStatusResponce(pollfd& pollFd)
{
	(void)pollFd; // to avoid unused parameter warning
	if (_status == SENT_TO_CLIENT)
	{
		std::cout << "Connection has sent response to client, changing socket mode to POLLIN" << std::endl;
		// changeSocketMode(POLLIN, pollFd);
		_status = IDLE; // Reset status to IDLE after sending response
	}
	else
	{
		std::cout << "Connection is in default state, no changes" << std::endl;
	}
}

void	Connection::processConnectionStatus(pollfd& pollFd)
{
	(void)pollFd; // to avoid unused parameter warning
	std::cout << "	process Connection Status, status:" << _status << std::endl;
	if (_status == READY_FOR_FORMATTING_RESPONSE)
	{
		// changeSocketMode(POLLOUT, pollFd);
		std::cout << "Connection is ready for formatting response" << std::endl;
		std::cout << "		*raw request*	\n" << _rawMessage << std::endl;
		//TODO : form response and send it to client
		_status = PREPARED_RESPONSE; // Set status to PREPARED_RESPONSE after formatting response
	}
	else if (_status == CLENT_CLOSED_READY_FOR_FORMATTING_RESPONSE)
	{
		// changeSocketMode(POLLOUT, pollFd);
		// TODO : form response and send it to client 
		// TODO : if request had "Connection : close" header, then close the connection after sending response
		// TODO : if request had "Connection : keep-alive" header, then keep the connection open for further requests
		_status = PREPARED_RESPONSE; // Set status to PREPARED_RESPONSE after formatting response
		std::cout << "Connection is ready for formatting response after client closed sending side" << std::endl;
	}
	else if ( _status == CLIENT_CLOSED_ERROR_RECEIVING_DATA || _status == ERROR_REQUEST_RECEIVED)
	{
		// changeSocketMode(POLLOUT, pollFd);
		//TODO : will form BadRequest error responce and send it to client and then close the connection
		// set Connection status to ERROR_CONNECTION (?)
		std::cout << "Connection is in error state" << std::endl;
	}
	else if (_status == WAITING_FOR_DATA)
	{
		std::cout << "Connection is waiting for data, no changes" << std::endl;
	}
	else if (_status == ERROR_RECEIVING_DATA_CLOSE_CONNECTION)
	{
		//TODO : just close the connection, no response to send
		// set Connection status to ERROR_CONNECTION (?)
		std::cout << "Connection is in seriouse error state, close it" << std::endl;
	}
	else
	{
		// changeSocketMode(POLLIN, pollFd);
		// set Connection status to ERROR_CONNECTION (?)
		std::cout << "Connection is in default state" << std::endl;
	}
}

void	Connection::receiveMessage()
{
	// std::cout << "	Handling my input event" << std::endl;
	int 	i;
	char	buf[1000];
	RequestStatus rstatus;

	rstatus = _request->getStatus();
	while (rstatus != ERROR_REQUEST && rstatus != READY)
	{
		i = recv(_clientConnectionSocket->getFd(), buf, sizeof(buf), 0);
		if (i > 0)
		{
			buf[i] = '\0'; // Null-terminate the buffer to treat it as a string
			std::cout << "buf:" << buf <<"$, i=" << i << std::endl;
			_rawMessage += buf; // Append the received data to _rawMessage
			
			std::memset(buf, 0, sizeof(buf)); // Clear the buffer for the next read
			if (locateSymbol(_rawMessage, '\n') == true)
			{
				std::cout << "Enough data to parse request (have nl)" << std::endl;
				rstatus = _request->insert(_rawMessage);
				if (rstatus == READY)
				{
					_status = READY_FOR_FORMATTING_RESPONSE;
					std::cout << "Request is ready to form response" << std::endl;
					_rawMessage.clear(); // Clear the raw message after processing
					return ;
				}
				else if (rstatus == ERROR_REQUEST)
				{
					_status = ERROR_REQUEST_RECEIVED;
					std::cout << "Error in request parsing" << std::endl;
					_rawMessage.clear(); // Clear the raw message after processing
					break ;
				}
				else if (rstatus == WAITING_START_LINE || 
						rstatus == WAITING_HEADER || 
						rstatus == WAITING_BODY)
				{
					_status = WAITING_FOR_DATA;
					std::cout << "Request is not ready yet, waiting for more data" << std::endl;
					_rawMessage.clear(); // Clear the raw message after processing
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
	std::cout << "	Need to check my response" << std::endl; 
	//TODO : might check through _reponse->status == READY_RESPONSE and remove PREPARED_RESPONSE from connection statuses
	if (_status == PREPARED_RESPONSE)
		return (true);
	return (false);
}

bool	Connection::sendToClient()
{	
	//TODO check that responce data is updated and cleaned properly
	std::cout << "	Giving my response to the client" << std::endl;
	std::string responseMock = "HTTP/1.1 200 OK\r\n"
								"Content-Type: text/plain\r\n"
								"Content-Length: 13\r\n"
								"\r\n"
								"How uncivilized\r\n";
	// n = send(_clientConnectionSocket->getFd(), _responce->getResponseMessage().c_str(), 
	// 								_response->getResponseMessage().size(), 0);
	int n = send(_clientConnectionSocket->getFd(), responseMock.c_str(), 
									responseMock.size(), 0);
	if (n < 0)
	{
		std::cerr << "Error sending response to client: " << strerror(errno) << std::endl;
		_status = ERROR_CONNECTION; // Set status to ERROR_CONNECTION if sending fails
		return (false);
	}
	else if (n == 0)
	{
		std::cout << "Client has closed the receiving side" << std::endl;
		_status = CLIENT_CLOSED_ERROR_SENDING_DATA_CONNECTION; // Set status to CLIENT_CLOSED_ERROR_RECEIVING_DATA
		return (false);
	}
	else
	{
		std::cout << "Response sent successfully, bytes sent: " << n << std::endl;
		_status = SENT_TO_CLIENT;
	}	
	_buffer.clear();
	_rawMessage.clear();
	return (false);
}

struct pollfd Connection::createConnectionSocket(ListeningSocket* serverListeningSocket)
{
	struct sockaddr	addr;
	socklen_t		size = sizeof(addr);
	int				_fd = accept(serverListeningSocket->getFd(), &addr, &size);
	struct pollfd	newPollFd;
	
	newPollFd.fd = _fd;
	newPollFd.events = POLLIN | POLLOUT;
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
															   _bytesSent(0),
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

