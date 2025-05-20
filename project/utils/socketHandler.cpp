#include "../src/core/Socket.hpp"

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