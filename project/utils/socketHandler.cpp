#include "../src/core/Socket.hpp"

void acceptConnection(Socket &s)
{
    std::cout << "Using accept to handl connection" << std::endl;
}

void epollWork(Socket &s)
{
    std::cout << "Using epoll to handl connection" << std::endl;
}