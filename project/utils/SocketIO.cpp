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
		_status = CLIENT_CLOSED_ERROR_SENDING_SOCKETIO; // Set status to CLIENT_CLOSED_ERROR_RECEIVING_DATA
		return (false);
	}
	else
	{
		std::cout << "Response sent successfully, bytes sent: " << n << std::endl;
		_status = SENT_SOCKETIO;
	}	
	_buffer.clear();
	return (false);
}

int SocketIO::readFromClient(int fd)
{
	// Method implementation
	(void)fd; // to avoid unused parameter warning
	return 0;
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

