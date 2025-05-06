#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <iostream>

class Socket; 

typedef void (*SocketHandler)(Socket &);

class Socket
{
private:
	int	_fd;

public:
	/*Member functions*/
    // int				receiveRequest();
	// int				sentResponce();
	SocketHandler	handler();


	/*Getters and Setters*/
	void    setHandler(SocketHandler func);
	int		getFd();
	
/*Constructors*/
    Socket(int fd);
	// Socket(void);

	/*Destructors*/
    ~Socket( void );

	/*Overload operators*/
	// Socket &operator=(const Socket& src);
};

std::ostream& operator<<(std::ostream &output_stream, Socket& src);

void acceptConnection(Socket &s);
void epollWork(Socket &s);

#endif // SOCKET_HPP
