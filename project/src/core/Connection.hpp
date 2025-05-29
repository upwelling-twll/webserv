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
	struct pollfd	createConnectionSocket(ListeningSocket* serverListeningSocket);

	// bool	disconnectSocket();

	/*Getters and Setters*/
	bool			isActive();
	struct pollfd	getPollFd() const;

	/*Constructors*/
    Connection(ListeningSocket* serverListeningSocket);

	/*Destructors*/
    ~Connection( void );

	/*Overload operators*/
	Connection &operator=(const Connection& src);
};

std::ostream& operator<<(std::ostream &output_stream, Connection& src);

#endif // CONNECTION_HPP
