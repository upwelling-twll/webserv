#include "ListeningSocket.hpp"

/*Member functions*/
bool	isListening()
{
	return true; // Placeholder implementation
}

int		handle()
{
	return 0; // Placeholder implementation
}


/*Getters and Setters*/

/*Constructors*/
ListeningSocket::ListeningSocket(int fd) : Socket(fd)
{
   std::cout << "ListeningSocket parameterized constructor is called" << std::endl;
`   _fd = fd;
   _listening = true;
   _port = 0;
   _ip = "";
}

ListeningSocket::ListeningSocket()
{
    std::cout << "ListeningSocket default constructor is called" << std::endl;
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
	output_stream << "* ListeningSocket Class info*" << std::endl;
	return output_stream;
}

