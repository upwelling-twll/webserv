#include "Controller.hpp"

/*Member functions*/
void	Controller::send(Connection* connection)
{
	std::cout << "Controller send method called" << std::endl;
	size_t	sentSize = 0;
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
		sentSize = socketIO.writeToClient(connection->getResponse()->getResponseMessage(), connection->getClientConnectionSocket()->getFd());
		if (sentSize == (connection->getResponse()->getResponseMessage()).length())
		{
			std::cout << "Response sent successfully, bytes sent: " << sentSize << std::endl;
			connection->setStatus(SENT_TO_CLIENT);
		}
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
	SocketIOStatus socketIOStatus;

	std::cout << "Controller receive method called" << std::endl;
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
		socketIOStatus = socketIO.readFromClient(connection->getClientConnectionSocket()->getFd(), connection->getRequest());
		RequestStatus requestStatus = connection->getRequest()->getStatus();
		if (socketIOStatus == RECEIVED_SOCKETIO && requestStatus == READY)
			connection->setStatus(READY_FOR_FORMATTING_RESPONSE);

		else if (socketIOStatus == RECEIVED_SOCKETIO && requestStatus == ERROR_REQUEST)
			connection->setStatus(ERROR_REQUEST_RECEIVED);
		
		else if (socketIOStatus == BUSY_SOCKETIO && (requestStatus == WAITING_START_LINE || 
						requestStatus == WAITING_HEADER || 
						requestStatus == WAITING_BODY))
			;
			// nothing for now
		else if (socketIOStatus == RECEIVED_SOCKETIO && requestStatus == READY /*&& i = 0*/)
			connection->setStatus(CLENT_CLOSED_READY_FOR_FORMATTING_RESPONSE);
		
		else if (socketIOStatus == CLOSED_ERROR_RECEIVING_SOCKETIO)
			connection->setStatus(CLIENT_CLOSED_ERROR_RECEIVING_DATA);
		
		else if (socketIOStatus == BUSY_SOCKETIO) // EAGAIN || EWOULDBLOCK
			connection->setStatus(WAITING_FOR_DATA);
		
		else if (socketIOStatus == BUSY_SOCKETIO) // EINTR
			; //nothing for now
		
		else if (socketIOStatus == CLOSED_ERROR_RECEIVING_SOCKETIO)
			connection->setStatus(ERROR_RECEIVING_DATA_CLOSE_CONNECTION);
		
		else
			connection->setStatus(WAITING_FOR_DATA);
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

