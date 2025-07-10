#include "SocketIO.hpp"

/*Member functions*/
int SocketIO::writeToClient(const std::string& message, int fd)
{
	//TODO check that responce data is updated and cleaned properly
	std::cout << "	SocketIO writeToClient" << std::endl;
	int n = send(fd, message.c_str(), message.size(), 0);
	if (n < 0)
	{
		std::cerr << "Error writeToClient: " << strerror(errno) << std::endl;
		_status = ERROR_SOCKETIO; // Set status to ERROR if sending fails
		return (false);
	}
	else if (n == 0)
	{
		std::cout << "Client has closed the receiving side" << std::endl;
		_status = CLOSED_ERROR_SENDING_SOCKETIO; // Set status to CLIENT_CLOSED_ERROR_RECEIVING_DATA
		return (false);
	}
	else if (n == static_cast<int>(message.size()))
	{
		std::cout << "Response sent successfully, bytes sent: " << n << std::endl;
		_status = SENT_SOCKETIO;
	}
	else if (n < static_cast<int>(message.size()))
	{
		std::cout << "Partial response sent, bytes sent: " << n << std::endl;
		_status = BUSY_SOCKETIO; // Set status to BUSY if partial data is sent
		return (false);
	}
	else
	{
		std::cerr << "Unexpected behavior in writeToClient, bytes sent: " << n << std::endl;
		return (false);
	}
	_buffer.clear();
	return (true);
}

int SocketIO::readFromClient(int fd, AHttpRequest* _request, std::string _rawMessage)
{
	int 	i;
	char	buf[1000];
	RequestStatus rstatus;

	rstatus = _request->getStatus();
	while (rstatus != ERROR_REQUEST && rstatus != READY)
	{
		i = recv(fd, buf, sizeof(buf), 0);
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
					_status = RECEIVED_SOCKETIO;
					std::cout << "Request is ready to form response" << std::endl;
					_rawMessage.clear(); // Clear the raw message after processing
					return (READY_FOR_FORMATTING_RESPONSE);
				}
				else if (rstatus == ERROR_REQUEST)
				{
					_status = RECEIVED_SOCKETIO; //may be ERROR_SOCKETIO would work better
					std::cout << "Error in request parsing" << std::endl;
					_rawMessage.clear(); // Clear the raw message after processing
					return (ERROR_REQUEST_RECEIVED);
				}
				else if (rstatus == WAITING_START_LINE || 
						rstatus == WAITING_HEADER || 
						rstatus == WAITING_BODY)
				{
					_status = BUSY_SOCKETIO;
					// CONNECTION STATUS : _status = WAITING_FOR_DATA;
					std::cout << "Request is not ready yet, waiting for more data" << std::endl;
					_rawMessage.clear(); // Clear the raw message after processing
					continue ;
				}
			}
			else
			{
				_status = BUSY_SOCKETIO;
				std::cout << "No enough data to parse request (no nl)" << std::endl;
				continue ;
			}
		}
		if (i == 0)
		{
			std::cout << "Client has closed the sending side" << std::endl;
			if (_request->getStatus() == READY)
			{
				_status = RECEIVED_SOCKETIO; 
				std::cout << "Request is ready to form response, client closed the sending side" << std::endl;
				return (CLENT_CLOSED_READY_FOR_FORMATTING_RESPONSE);
			}
			else
			{
				_status = CLOSED_ERROR_RECEIVING_SOCKETIO;
				std::cout << "Error receiving data from client, client closed the sending side" << std::endl;
				return (CLIENT_CLOSED_ERROR_RECEIVING_DATA);
			}
		}
		else if (i == EAGAIN || i == EWOULDBLOCK)
		{
			_status = BUSY_SOCKETIO;
			std::cout << "No more data to read, waiting for more data chunks" << std::endl;
			return (WAITING_FOR_DATA);
		}
		else if (i == EINTR)
		{
			// Interrupted by a signal, continue receiving data
			_status = BUSY_SOCKETIO;
			std::cout << "Receiving data interrupted by a signal, continuing to receive data" << std::endl;
			continue ;
		}
		else
		{
			_status = CLOSED_ERROR_RECEIVING_SOCKETIO;
			//TODO : might need to set request status to ERROR_REQUEST,
			// but must not send the responce, just !! close connection !!
			std::cerr << "Error receiving data from client: " << strerror(errno) << std::endl;
			return (ERROR_RECEIVING_DATA_CLOSE_CONNECTION);
		}
	}
	return (WAITING_FOR_DATA);
}

int SocketIO::writeToDemon(const std::string& message, int fd)
{
	// Method implementation
	(void)fd; // to avoid unused parameter warning
	(void)message; // to avoid unused parameter warning
	return 0;
}

int SocketIO::readFromDemon(int fd)
{
	// Method implementation
	(void)fd; // to avoid unused parameter warning
	return 0;
}

/*Getters and Setters*/
int	SocketIO::getStatus() const
{
	return this->_status;
}

/*Constructors*/

SocketIO::SocketIO() : _status(IDLE_SOCKETIO)
{
    std::cout << "SocketIO default constructor is called" << std::endl;
}

/*Destructors*/

SocketIO::~SocketIO( void )
{
    std::cout << "SocketIO destructor is called" << std::endl;
}

/*Overload operators*/

std::ostream& operator<<(std::ostream& output_stream, SocketIO& src)
{
	output_stream << "* SocketIO Class info*" << src.getStatus() << std::endl;
	return output_stream;
}

