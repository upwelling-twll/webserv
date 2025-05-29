#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include <iostream>
# include <ctime>

# include "../../inc/webserv.hpp"

class httpRequest;
class ListeningSocket;
class ConnectionSocket;

class Connection
{
private:
	/*Private members*/
	std::vector<std::string>	_rawMessage;
	std::string					_buffer;
	std::string					_status;
	time_t						_timeLastConnection;

	ListeningSocket*			_serverListeningSocket;
	ConnectionSocket*			_clientConnectionSocket;
	httpRequest*				_request;
	bool						_stayAlive;

public:
	/*Member functions*/
    // bool	createConnectionSocket();
	// bool	disconnectSocket();

	/*Getters and Setters*/

	/*Constructors*/
    Connection(ListeningSocket* serverListeningSocket);

	/*Destructors*/
    ~Connection( void );

	/*Overload operators*/
	Connection &operator=(const Connection& src);
};

std::ostream& operator<<(std::ostream &output_stream, Connection& src);

#endif // CONNECTION_HPP
