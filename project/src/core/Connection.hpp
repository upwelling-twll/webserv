#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include <iostream>
# include <ctime>

# include "../../inc/webserv.hpp"

class AHttpRequest;
class ListeningSocket;
class ConnectionSocket;

class Connection
{
private:
	/*Private members*/
	std::vector<std::string>	_rawMessage;
	std::string					_buffer;
	std::string					_status;
	time_t						_timeLastUsed;

	ListeningSocket*			_serverListeningSocket;
	ConnectionSocket*			_clientConnectionSocket;
	AHttpRequest*				_request;
	bool						_active;

	struct pollfd				_pollFd;

public:
	/*Member functions*/
	void			handleInEvent();
	bool			haveResponse();
	bool			sendToClients();
	struct pollfd	createConnectionSocket(ListeningSocket* serverListeningSocket);
	// bool	disconnectSocket();

	/*Getters and Setters*/
	bool			isActive();
	struct pollfd	getPollFd() const;

	/*Getters for private members*/
	std::vector<std::string>	getRawMessage() const { return _rawMessage; }
	std::string					getBuffer() const { return _buffer; }
	std::string					getStatus() const { return _status; }
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
