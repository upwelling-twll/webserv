#include "../src/core/Socket.hpp"
#include "../utils/SocketIO.hpp"
#include "../src/core/Connection.hpp"
#include "../inc/webserv.hpp"

bool locateSymbol(const std::string& string, char symbol)
{
	std::string::size_type pos = string.find(symbol);
	if (pos != std::string::npos)
		return true;
	else
		return false;
}

// bool    isListeningSocket(int fd, Socket s)
// {
//     if(fd == s.getFd())
//     {
//         if (s.getType() == "listen")
//             return (true);
//         else
//             return (false);
//     }
//     std::cout << "fd != socket" << std::endl;   
//     return (false);
// }

// void acceptConnection(Socket &s)
// {
//     std::cout << "Using accept to handl connection" << std::endl;
//     std::cout << s << std::endl;
// }

// void epollWork(Socket &s)
// {
//     std::cout << "Using epoll to handl connection" << std::endl;
//     std::cout << s << std::endl;
// }