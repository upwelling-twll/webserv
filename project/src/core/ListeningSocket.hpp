#ifndef LISTENINGSOCKET_HPP
# define LISTENINGSOCKET_HPP

# include <iostream>
#include <netinet/in.h>  // For sockaddr_in
#include <arpa/inet.h> 

# include "../../inc/webserv.hpp"

class ListeningSocket : public Socket
{
private:
    bool			_listening;
	int				_port;
	std::string		_ip;

public:
	/*Member functions*/
	virtual bool	isListening() const;
    virtual int		handle();
	void			configureSocketOptions();
	void			bindSocket();
	void			listenConnectionSocket();

	/*Getters and Setters*/
	void			setData(std::string ip, int port);
	/*Constructors*/
    ListeningSocket(int fd);

	/*Destructors*/
    ~ListeningSocket( void );

	/*Overload operators*/
	ListeningSocket &operator=(const ListeningSocket& src);
};

std::ostream& operator<<(std::ostream &output_stream, ListeningSocket& src);

#endif // LISTENINGSOCKET_HPP
