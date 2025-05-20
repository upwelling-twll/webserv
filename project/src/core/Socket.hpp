#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <iostream>

class Socket
{
protected:
	int					_fd;

	struct sockaddr		_addr;
	socklen_t			_addr_len;
	size_t				_addr_text_len;

public:
	/*Member functions*/
    virtual bool	isListening() const = 0;
	virtual int		handle() = 0;

	/*Getters and Setters*/
	int		getFd() const;
	void	setAddrInfo(struct sockaddr _addr, socklen_t _addr_len, size_t _addr_text_len);
	
/*Constructors*/
    Socket(int fd);
	// Socket(void);

	/*Destructors*/
    virtual ~Socket( void );

	/*Overload operators*/
	// Socket &operator=(const Socket& src);
};

std::ostream& operator<<(std::ostream &output_stream, Socket& src);

bool isListeningSocket(int fd, Socket &s);
void acceptConnection(Socket &s);
void epollWork(Socket &s);

#endif // SOCKET_HPP
