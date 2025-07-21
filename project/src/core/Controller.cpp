#include "Controller.hpp"

/*Member functions*/
void	Controller::send(Connection* connection)
{
	std::cout << "Controller send method called" << std::endl;

	SocketIO socketIO;

	if (!connection)
	{
		std::cerr << "Error: Connection is null" << std::endl;
		return;
	}
	ConnectionSocketType socketType = connection->getClientConnectionSocket()->getSocketType();


	if (socketType == CLIENT_CONNECTION_SOCKET)
	{
		std::cout << "Sending to ClientConnectionSocket" << std::endl;
		socketIO.writeToClient(connection->getResponse()->getResponseMessage(), connection->getClientConnectionSocket()->getFd());
	}
	else if (socketType == DEMON_CONNECTION_SOCKET)
	{
		std::cout << "Sending to DemonConnectionSocket" << std::endl;
		// connection->writeToDemon();
	}
	else if (socketType == CGI_CONNECTION_SOCKET)
	{
		std::cout << "Sending to CgiConnectionSocket" << std::endl;
		// connection->writeToCgi();
	}
	connection->processConnectionStatusSending();
}


void	Controller::receive(Connection* connection)
{
	SocketIO socketIO;

	std::cout << "Engine receive method called" << std::endl;
	if (!connection)
	{
		std::cerr << "Error: Connection is null" << std::endl;
		return;
	}

	ConnectionSocketType socketType = connection->getClientConnectionSocket()->getSocketType();
	if (socketType == CLIENT_CONNECTION_SOCKET)
	{
		std::cout << "Receiving from ClientConnectionSocket" << std::endl;
		//socketIO.readFromClient(connection->getClientConnectionSocket()->getFd(), connection->getRequest());
		 connection->receiveMessage();
	}
	else if (socketType == DEMON_CONNECTION_SOCKET)
	{
		std::cout << "Receiving from DemonConnectionSocket" << std::endl;
		// connection->readFromDemon();
	}
	else if (socketType == CGI_CONNECTION_SOCKET)
	{
		std::cout << "Receiving from CgiConnectionSocket" << std::endl;
		// connection->readFromCgi();
	}
	connection->processConnectionStatusReceiving();
}

/*Getters and Setters*/

/*Constructors*/
// Controller::Controller(/*Parameterized Constructor*/)
// {
//    std::cout << "Controller parameterized constructor is called" << std::endl;
// }

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
// Controller& Controller::operator=(const Controller& src)
// {
// 	std::cout << "Controller copy assignment is called" << std::endl;
// 	if (this != &src)
// 	{
// 		// Assinment variables
// 	}
// 	return (*this);
// }

// std::ostream& operator<<(std::ostream& output_stream, Controller& src)
// {
// 	output_stream << "* Controller Class info*" << std::endl;
// 	return output_stream;
// }

