#include "Controller.hpp"

/*Member functions*/
int Controller::writeToClient(const std::string& message, int fd)
{
	//TODO check that responce data is updated and cleaned properly
	std::cout << "	Controller writeToClient" << std::endl;
	int n = send(fd, message.c_str(), message.size(), 0);
	if (n < 0)
	{
		std::cerr << "Error writeToClient: " << strerror(errno) << std::endl;
		_status = ERROR; // Set status to ERROR if sending fails
		return (false);
	}
	else if (n == 0)
	{
		std::cout << "Client has closed the receiving side" << std::endl;
		_status = CLIENT_CLOSED_ERROR_SENDING_DATA_CONTROLLER; // Set status to CLIENT_CLOSED_ERROR_RECEIVING_DATA
		return (false);
	}
	else
	{
		std::cout << "Response sent successfully, bytes sent: " << n << std::endl;
		_status = SENT;
	}	
	_buffer.clear();
	return (false);
}

int Controller::readFromClient(int fd)
{
	// Method implementation
	return 0;
}

int Controller::writeToDemon(const std::string& message, int fd)
{
	// Method implementation
	return 0;
}

int Controller::readFromDemon(int fd)
{
	// Method implementation
	return 0;
}

/*Getters and Setters*/
int	Controller::getStatus() const
{
	return this->_status;
}

/*Constructors*/
Controller::Controller(/*Parameterized Constructor*/)
{
   std::cout << "Controller parameterized constructor is called" << std::endl;
}

Controller::Controller()
{
    std::cout << "Controller default constructor is called" << std::endl;
}

/*Destructors*/
Controller::~Controller( void )
{
    std::cout << "Controller destructor is called" << std::endl;
}

/*Overload operators*/

std::ostream& operator<<(std::ostream& output_stream, Controller& src)
{
	output_stream << "* Controller Class info*" << src.getStatus() << std::endl;
	return output_stream;
}

