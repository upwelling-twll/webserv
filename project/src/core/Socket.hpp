#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <iostream>

class Socket; 

typedef void (*SocketHandler)(Socket &);

class Socket
{
private:
	int			_fd;
	std::string	_ip;
	std::string	_port;
	std::string	_type;

public:
	/*Member functions*/
    // int				receiveRequest();
	// int				sentResponce();
	SocketHandler	handler;


	/*Getters and Setters*/
	void    setHandler(SocketHandler func);
	int		getFd();
	std::string		getType();
	
/*Constructors*/
    Socket(int fd, std::string _type);
	// Socket(void);

	/*Destructors*/
    ~Socket( void );

	/*Overload operators*/
	// Socket &operator=(const Socket& src);
};

std::ostream& operator<<(std::ostream &output_stream, Socket& src);

bool isListeningSocket(int fd, Socket s);
void acceptConnection(Socket &s);
void epollWork(Socket &s);

#endif // SOCKET_HPP
