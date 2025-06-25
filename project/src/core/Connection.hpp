#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include <iostream>
# include <ctime>

# include "../../inc/webserv.hpp"
# include <sys/socket.h>

class AHttpRequest;
class ListeningSocket;
class ConnectionSocket;

enum ConnectionStatus
{
	IDLE, 						//0
	RECEIVING_REQUEST,			//1
	PROCESSING_RESPONSE,		//2
	// HAS_REQUEST,
	// WAITING_FOR_RESPONSE,
	// HAS_RESPONSE,
	READY_FOR_FORMATTING_RESPONSE,	//3			 	 //used in handleInEvent
	ERROR_REQUEST_RECEIVED,			//4			 	 //used in handleInEvent
	WAITING_FOR_DATA,				//5			 	 //used in handleInEvent
	CLENT_CLOSED_READY_FOR_FORMATTING_RESPONSE, //6	 //used in handleInEvent
	CLIENT_CLOSED_ERROR_RECEIVING_DATA, 		//7	 //used in handleInEvent
	ERROR_RECEIVING_DATA_CLOSE_CONNECTION,		//8	 //used in handleInEvent
	// CLOSED,
	PREPARED_RESPONCE,				//9 			 //used in handleOutEvent
	SENT_TO_CLIENT,					//10			 //used in handleOutEvent
	ERROR_CONNECTION,				//11
	CLIENT_CLOSED_ERROR_SENDING_DATA,	//12
};

class Connection
{
private:
	/*Private members*/
	std::string					_rawMessage;
	std::string					_buffer;
	ConnectionStatus			_status;
	time_t						_timeLastUsed;
	struct pollfd				_pollFd;

	ListeningSocket*			_serverListeningSocket;
	ConnectionSocket*			_clientConnectionSocket;

	enum RequestReceivingStage	_rstatus;
	AHttpRequest*				_request;

	bool						_active;


public:
	/*Member functions*/
	void			receiveMessage();
	void			processConnectionStatus(pollfd& pollFd);
	void			processConnectionStatusResponce(pollfd& pollFd);
	bool			haveResponse();
	bool			sendToClient();
	struct pollfd	createConnectionSocket(ListeningSocket* serverListeningSocket);
	void			changeSocketMode(short mode, pollfd& pollFd);
	// bool	disconnectSocket();

	/*Getters and Setters*/
	bool			isActive();
	struct pollfd	getPollFd() const;

	/*Getters for private members*/
	std::string					getRawMessage() const;
	std::string					getBuffer() const;
	ConnectionStatus			getStatus() const;
	time_t						getTimeLastUsed() const;
	ListeningSocket*			getServerListeningSocket() const;
	ConnectionSocket*			getClientConnectionSocket() const;

	/*Constructors*/
    Connection(ListeningSocket* serverListeningSocket);

	/*Destructors*/
    ~Connection( void );

	/*Overload operators*/
	Connection &operator=(const Connection& src);
};

std::ostream& operator<<(std::ostream &output_stream, Connection& src);

#endif // CONNECTION_HPP
