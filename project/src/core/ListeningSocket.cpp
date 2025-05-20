#include "ListeningSocket.hpp"

/*Member functions*/
bool	ListeningSocket::isListening() const
{
	return true; // Placeholder implementation
}

int		ListeningSocket::handle()
{
	return 0; // Placeholder implementation
}

void	ListeningSocket::listenConnectionSocket()
{
	int	i;

	std::cout << "	Listen connection" << std::endl;
	i = listen(this->_fd, 32);
	std::cout << i << std::endl;
	if (i < 0)
	{
		std::cerr << "listen() failed: " << strerror(errno) << std::endl;
		throw std::runtime_error("listen() failed"); //TODO : if error, a value of -1 is returned and the global integer variable errno is set to indicate the error
	}
	std::cout << "	Listen connection complete" << std::endl;
	return ;
}

void	ListeningSocket::configureSocketOptions()
{
	int	i;
	int	yes = 1;
	
	std::cout << "	Listen connection" << std::endl;
	i = setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	std::cout << i << std::endl;
	if (i < 0)
	{
		std::cerr << "sockopt() failed: " << strerror(errno) << std::endl;
		throw std::runtime_error("setsockopt() failed"); //TODO : if error, a value of -1 is returned and the global integer variable errno is set to indicate the error
	}
	std::cout << "	Setsockopt for listen socket complete" << std::endl;
	return ;
}

void	ListeningSocket::bindSocket()
{
	int					i;
	struct sockaddr_in	addr;

	// addr.sin_len = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_port);
	addr.sin_addr.s_addr = inet_addr(this->_ip.c_str());
	std::cout << "	Binding socket start" << std::endl;
	std::cout << *this << std::endl;
	i = bind(this->_fd, (struct sockaddr *)(&addr), sizeof(addr));
	std::cout << i << std::endl;
	if (i < 0)
	{
		std::cerr << "bind() failed: " << strerror(errno) << std::endl;
		throw std::runtime_error("bind() failed"); //TODO : if error, a value of -1 is returned and the global integer variable errno is set to indicate the error
		return ;
	}
	std::cout << "	Binding socket complete" << std::endl;
	return ;
}

/*Getters and Setters*/
void	ListeningSocket::setData(std::string data)
{
	std::cout << "	Setting data" << std::endl;
	this->_ip = data.substr(0, data.find(':'));
	this->_port = std::stoi(data.substr(data.find(':') + 1));
	std::cout << "	IP: " << this->_ip << std::endl;
	std::cout << "	PORT: " << this->_port << std::endl;
	return ;
}

/*Constructors*/
ListeningSocket::ListeningSocket(int fd) : Socket(fd)
{
   std::cout << "ListeningSocket parameterized constructor is called" << std::endl;
   _listening = true;
   _port = 0;
   _ip = "";
}

/*Destructors*/
ListeningSocket::~ListeningSocket( void )
{
    std::cout << "ListeningSocket destructor is called" << std::endl;
}

/*Overload operators*/
ListeningSocket& ListeningSocket::operator=(const ListeningSocket& src)
{
	std::cout << "ListeningSocket copy assignment is called" << std::endl;
	if (this != &src)
	{
		// Assinment variables
	}
	return (*this);
}

std::ostream& operator<<(std::ostream& output_stream, ListeningSocket& src)
{
	output_stream << "* ListeningSocket Class info:" << src.getFd() << std::endl;
	return output_stream;
}

