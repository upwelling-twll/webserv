#ifndef CONNECTIONSOCKET_HPP
# define CONNECTIONSOCKET_HPP

# include <iostream>
# include "../../inc/webserv.hpp"

enum ConnectionSocketType
{
	LISTENING_SOCKET,
	CLIENT_CONNECTION_SOCKET,
	DEMON_CONNECTION_SOCKET,
	CGI_CONNECTION_SOCKET
};

class ConnectionSocket : public Socket
{
private:
	bool					_listening;
	ConnectionSocketType	_socketType;

public:
	/*Member functions*/
    virtual bool	isListening() const;

	/*Getters and Setters*/
	ConnectionSocketType	getSocketType() const;

	/*Constructors*/
    ConnectionSocket(int fd, ConnectionSocketType type);

	/*Destructors*/
    ~ConnectionSocket( void );

	/*Overload operators*/
	ConnectionSocket &operator=(const ConnectionSocket& src);
};

std::ostream& operator<<(std::ostream &output_stream, ConnectionSocket& src);

#endif // CONNECTIONSOCKET_HPP
