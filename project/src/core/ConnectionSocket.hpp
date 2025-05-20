#ifndef CONNECTIONSOCKET_HPP
# define CONNECTIONSOCKET_HPP

# include <iostream>
# include "../../inc/webserv.hpp"
class ConnectionSocket : public Socket
{
private:
	bool		_listening;

public:
	/*Member functions*/
    virtual bool	isListening() const;
	virtual int		handle();

	/*Getters and Setters*/

	/*Constructors*/
    ConnectionSocket(int fd);

	/*Destructors*/
    ~ConnectionSocket( void );

	/*Overload operators*/
	ConnectionSocket &operator=(const ConnectionSocket& src);
};

std::ostream& operator<<(std::ostream &output_stream, ConnectionSocket& src);

#endif // CONNECTIONSOCKET_HPP
