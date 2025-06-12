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
	IDLE,
	RECEIVING_REQUEST,
	// HAS_REQUEST,
	// WAITING_FOR_RESPONSE,
	// HAS_RESPONSE,
	CLIENT_CLOSED,
	// CLOSED,
	ERROR,
};

enum RequestReceivingStage
{
	START,
	NO_METHOD,
	HTTP_GET_METHOD,
	OTHER_METHOD,
	PARSE_CONTENT_LENGTH_VALUE,
	RECEIVING_BODY,
	MORE_CHUNKS,
	END,
	ERROR,
};

class Connection
{
private:
	/*Private members*/
	std::string					_rawMessage;
	std::vector<char>			_buffer;
	enum ConnectionStatus		_cstatus;
	time_t						_timeLastUsed;
	struct pollfd				_pollFd;

	ListeningSocket*			_serverListeningSocket;
	ConnectionSocket*			_clientConnectionSocket;

	enum RequestReceivingStage	_rstatus;
	AHttpRequest*				_request;

	bool						_active;


public:
	/*Member functions*/
	void			receiveRequest();
	void			handleInEvent();
	bool			haveResponse(struct pollfd fd);
	bool			sendToClients();
	struct pollfd	createConnectionSocket(ListeningSocket* serverListeningSocket);
	// bool	disconnectSocket();

	/*Getters and Setters*/
	bool			isActive();
	struct pollfd	getPollFd() const;

	/*Getters for private members*/
	std::string					getRawMessage() const { return _rawMessage; }
	std::string					getBuffer() const { return  _buffer.data(); }
	ConnectionStatus			getStatus() const { return _cstatus; }
	std::string					getStatusAsString() const;
	time_t						getTimeLastUsed() const { return _timeLastUsed; }
	ListeningSocket*			getServerListeningSocket() const { return _serverListeningSocket; }
	ConnectionSocket*			getClientConnectionSocket() const { return _clientConnectionSocket; }

	/*Constructors*/
    Connection(ListeningSocket* serverListeningSocket);

	/*Destructors*/
    ~Connection( void );

	/*Overload operators*/
	Connection &operator=(const Connection& src);
};

std::ostream& operator<<(std::ostream &output_stream, Connection& src);

#endif // CONNECTION_HPP
