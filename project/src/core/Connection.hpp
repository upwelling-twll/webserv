#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include <iostream>
# include <ctime>

# include "../../inc/webserv.hpp"

class AHttpRequest;
class ListeningSocket;
class ConnectionSocket;

enum ConnectionStatus
{
	IDLE,
	RECEIVING_REQUEST,
	// HAS_REQUEST,
	// WAITING_FOR_RESPONSE,
	// HAS_RESPONSE,
	READY_FOR_FORMATTING_RESPONSE,				 //used in handleInEvent
	ERROR_REQUEST_RECEIVED,								 //used in handleInEvent
	WAITING_FOR_DATA,							 //used in handleInEvent
	CLENT_CLOSED_READY_FOR_FORMATTING_RESPONSE,	 //used in handleInEvent
	CLIENT_CLOSED_ERROR_RECEIVING_DATA, 		 //used in handleInEvent
	ERROR_RECEIVING_DATA_CLOSE_CONNECTION,		 //used in handleInEvent
	// CLOSED,
	ERROR_CONNECTION,
};

class Connection
{
private:
	/*Private members*/
	std::string					_rawMessage;
	std::string					_buffer;
	ConnectionStatus			_status;
	time_t						_timeLastUsed;

	ListeningSocket*			_serverListeningSocket;
	ConnectionSocket*			_clientConnectionSocket;
	AHttpRequest*				_request;
	bool						_active;

	struct pollfd				_pollFd;

public:
	/*Member functions*/
	void			handleInEvent();
	void			updateConnection();
	bool			haveResponse();
	bool			sendToClients();
	struct pollfd	createConnectionSocket(ListeningSocket* serverListeningSocket);
	void			changeSocketMode(short mode);
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
