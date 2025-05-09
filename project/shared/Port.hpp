#ifndef PORT_HPP
# define PORT_HPP

# include <iostream>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <cerrno>
# include <cstring>
# include <unistd.h>

# define S_DOMAIN AF_INET

class Port
{
private:
	const std::string		_ip;
	const unsigned int		_port;
	int						_listenSocket;

public:
	/*Member functions*/
	void	optionsSocket();
	void	listenConnectionSocket();
	void	bindSocket();
    int 	createSocket();
	void	closeFd();

	/*Getters and Setters*/
	std::string const getIp();
	unsigned int getPort();
	int		getListenSocket();

	void	setListenSocket(int s);

	/*Constructors*/
    Port(const std::string ip, const int port);
	Port(void);

	/*Destructors*/
    ~Port( void );

	/*Overload operators*/
	Port &operator=(const Port& src);
};

std::ostream& operator<<(std::ostream &output_stream, Port& src);

#endif // PORT_HPP
