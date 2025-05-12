#include "../inc/webserv.hpp"

void addPortsToSocketsList(std::vector<Socket> allSockets, std::vector<Port> ports)
{
    for (std::vector<Port>::iterator it = ports.begin(); it != ports.end(); ++it)
    {
        std::cout << "adding listen socket from Ports to sockets vector" << std::endl;
        allSockets.push_back(Socket(it->getListenSocket(), "listen"));
    }
    for (std::vector<Socket>::iterator it = allSockets.begin(); it != allSockets.end(); ++it)
    {
        std::cout << "setting handlers for socket obj in vector" << std::endl;
        it->setHandler(acceptConnection);
    }
}

std::vector<Socket> createSocketVec(Config config)
{
    std::vector<Socket> allSockets;

    addPortsToSocketsList(allSockets, config.getPorts());
    return (allSockets);
}
